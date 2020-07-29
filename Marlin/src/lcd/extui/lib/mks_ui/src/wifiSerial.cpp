#include "../../../../../MarlinCore.h"

#if ENABLED(TFT_LITTLE_VGL_UI)

#include "../inc/wifiSerial.h"

#if USE_WIFI_FUNCTION

#include <libmaple/libmaple.h>
#include <libmaple/gpio.h>
#include <libmaple/timer.h>
#include <libmaple/usart.h>
#include <libmaple/ring_buffer.h>


DEFINE_WFSERIAL(WifiSerial1, 1);

WifiSerial::WifiSerial(usart_dev *usart_device,
                               uint8 tx_pin,
                               uint8 rx_pin) {
    this->usart_device = usart_device;
    this->tx_pin = tx_pin;
    this->rx_pin = rx_pin;
}

/*
 * Set up/tear down
 */

#if STM32_MCU_SERIES == STM32_SERIES_F1
/* F1 MCUs have no GPIO_AFR[HL], so turn off PWM if there's a conflict
 * on this GPIO bit. */
static void disable_timer_if_necessary(timer_dev *dev, uint8 ch) {
    if (dev != NULL) {
        timer_set_mode(dev, ch, TIMER_DISABLED);
    }
}
#elif (STM32_MCU_SERIES == STM32_SERIES_F2) ||    \
      (STM32_MCU_SERIES == STM32_SERIES_F4)
#define disable_timer_if_necessary(dev, ch) ((void)0)
#else
#warning "Unsupported STM32 series; timer conflicts are possible"
#endif

void WifiSerial::begin(uint32 baud) 
{
	begin(baud,SERIAL_8N1);
}
/*
 * Roger Clark.
 * Note. The config parameter is not currently used. This is a work in progress.  
 * Code needs to be written to set the config of the hardware serial control register in question.
 *
*/

void WifiSerial::begin(uint32 baud, uint8_t config) 
{
 //   ASSERT(baud <= this->usart_device->max_baud);// Roger Clark. Assert doesn't do anything useful, we may as well save the space in flash and ram etc

    if (baud > this->usart_device->max_baud) {
        return;
    }

    const stm32_pin_info *txi = &PIN_MAP[this->tx_pin];
    const stm32_pin_info *rxi = &PIN_MAP[this->rx_pin];

    disable_timer_if_necessary(txi->timer_device, txi->timer_channel);

    usart_init(this->usart_device);
    /*
    Reinitialize the receive buffer, mks_esp8266 fixed data frame length is 1k bytes
    */
    rb_init(this->usart_device->rb, WIFI_RX_BUF_SIZE, wifiRxBuf);
	
    usart_config_gpios_async(this->usart_device,
                             rxi->gpio_device, rxi->gpio_bit,
                             txi->gpio_device, txi->gpio_bit,
                             config);
    usart_set_baud_rate(this->usart_device, USART_USE_PCLK, baud);
    usart_enable(this->usart_device);
}

void WifiSerial::end(void) {
    usart_disable(this->usart_device);
}

int WifiSerial::available(void) {
    return usart_data_available(this->usart_device);
}

/*
 * I/O
 */

int WifiSerial::read(void) {
	if(usart_data_available(usart_device) > 0) {
		return usart_getc(usart_device);
	} else {
		return -1;
	}
}

size_t WifiSerial::write(unsigned char ch) {

    usart_putc(this->usart_device, ch);
    return 1;
}

int WifiSerial::wifi_rb_is_full(void)
{
	return rb_is_full(this->usart_device->rb);
}

#endif

#endif
