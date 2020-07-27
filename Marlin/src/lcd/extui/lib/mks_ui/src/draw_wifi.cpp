#include "../../../../../MarlinCore.h"
#if ENABLED(TFT_LITTLE_VGL_UI)
#include "lv_conf.h"
//#include "../../lvgl/src/lv_objx/lv_imgbtn.h"
//#include "../../lvgl/src/lv_objx/lv_img.h"
//#include "../../lvgl/src/lv_core/lv_disp.h"
//#include "../../lvgl/src/lv_core/lv_refr.h"
//#include "../../MarlinCore.h"
#include "../../../../../../Configuration.h"
#include "../inc/draw_ui.h"
#include "../../../../../module/temperature.h"

static lv_obj_t * scr;
static lv_obj_t * wifi_name_text,*wifi_key_text,*wifi_state_text,*wifi_ip_text;

#define ID_W_RETURN			1
#define ID_W_CLOUD			2
#define ID_W_RECONNECT		3

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch(obj->mks_obj_id)
	{
		case ID_W_RETURN:
	    if(event == LV_EVENT_CLICKED) {
			
	    }
	    else if(event == LV_EVENT_RELEASED) {
			clear_cur_ui();
	        lv_draw_set();
	    }
		break;
		case ID_W_CLOUD:
	    if(event == LV_EVENT_CLICKED) {
			
	    }
	    else if(event == LV_EVENT_RELEASED) {
			//clear_cur_ui();
	        //draw_return_ui();
	    }
		break;
		case ID_W_RECONNECT:
	    if(event == LV_EVENT_CLICKED) {
			
	    }
	    else if(event == LV_EVENT_RELEASED) {
			clear_cur_ui();
	        	lv_draw_wifi_list();
	    }
		break;
	}
}


void lv_draw_wifi(void)
{
	lv_obj_t *buttonBack=NULL,*label_Back=NULL;
	lv_obj_t *buttonCloud=NULL,*label_Cloud=NULL;
	lv_obj_t *buttonReconnect=NULL,*label_Reconnect=NULL;
	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != WIFI_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = WIFI_UI;
	}
	disp_state = WIFI_UI;

	scr = lv_obj_create(NULL, NULL);
	
	lv_obj_set_style(scr, &tft_style_scr);
  lv_scr_load(scr);
  lv_obj_clean(scr);

  lv_obj_t * title = lv_label_create(scr, NULL);
	lv_obj_set_style(title, &tft_style_lable_rel);
	lv_obj_set_pos(title,TITLE_XPOS,TITLE_YPOS);
	lv_label_set_text(title, creat_title_text());
  
  lv_refr_now(lv_refr_get_disp_refreshing());
	
	LV_IMG_DECLARE(bmp_pic);
	
    /*Create an Image button*/
	buttonBack = lv_imgbtn_create(scr, NULL);
	if(gCfgItems.wifi_mode_sel == STA_MODEL)
	{
		//buttonCloud = lv_imgbtn_create(scr, NULL);
		buttonReconnect = lv_imgbtn_create(scr, NULL);
	}

	lv_obj_set_event_cb_mks(buttonBack, event_handler,ID_W_RETURN,"bmp_return.bin",0);	
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_PR, &tft_style_lable_pre);
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_REL, &tft_style_lable_rel);

	lv_obj_set_pos(buttonBack,BTN_X_PIXEL*3+INTERVAL_V*4,  BTN_Y_PIXEL+INTERVAL_H+titleHeight);
	lv_btn_set_layout(buttonBack, LV_LAYOUT_OFF);

	if(gCfgItems.wifi_mode_sel == STA_MODEL)
	{
		//lv_obj_set_event_cb_mks(buttonCloud, event_handler,ID_W_CLOUD,"bmp_cloud.bin",0);	
	    //lv_imgbtn_set_src(buttonCloud, LV_BTN_STATE_REL, &bmp_pic);
	    //lv_imgbtn_set_src(buttonCloud, LV_BTN_STATE_PR, &bmp_pic);	
		//lv_imgbtn_set_style(buttonCloud, LV_BTN_STATE_PR, &tft_style_lable_pre);
		//lv_imgbtn_set_style(buttonCloud, LV_BTN_STATE_REL, &tft_style_lable_rel);

		//lv_obj_set_pos(buttonCloud,BTN_X_PIXEL+INTERVAL_V*2,  BTN_Y_PIXEL+INTERVAL_H+titleHeight);
		//lv_btn_set_layout(buttonCloud, LV_LAYOUT_OFF);

		lv_obj_set_event_cb_mks(buttonReconnect, event_handler,ID_W_RECONNECT,"bmp_wifi.bin",0);	
	    lv_imgbtn_set_src(buttonReconnect, LV_BTN_STATE_REL, &bmp_pic);
	    lv_imgbtn_set_src(buttonReconnect, LV_BTN_STATE_PR, &bmp_pic);	
		lv_imgbtn_set_style(buttonReconnect, LV_BTN_STATE_PR, &tft_style_lable_pre);
		lv_imgbtn_set_style(buttonReconnect, LV_BTN_STATE_REL, &tft_style_lable_rel);

		lv_obj_set_pos(buttonReconnect,BTN_X_PIXEL*2+INTERVAL_V*3,  BTN_Y_PIXEL+INTERVAL_H+titleHeight);
		lv_btn_set_layout(buttonReconnect, LV_LAYOUT_OFF);
	}

	label_Back = lv_label_create(buttonBack, NULL);
	
	if(gCfgItems.wifi_mode_sel == STA_MODEL)
	{
		//label_Cloud = lv_label_create(buttonCloud, NULL);
		label_Reconnect = lv_label_create(buttonReconnect, NULL);
	}
	
	if(gCfgItems.multiple_language !=0)
	{
		lv_label_set_text(label_Back, common_menu.text_back);
		lv_obj_align(label_Back, buttonBack, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);

		if(gCfgItems.wifi_mode_sel == STA_MODEL)
		{
			//lv_label_set_text(label_Cloud, common_menu.text_back);
			//lv_obj_align(label_Cloud, buttonCloud, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);

			lv_label_set_text(label_Reconnect, wifi_menu.reconnect);
			lv_obj_align(label_Reconnect, buttonReconnect, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);
		}
	}

	wifi_ip_text = lv_label_create(scr, NULL);
	lv_obj_set_style(wifi_ip_text, &tft_style_lable_rel);

	wifi_name_text = lv_label_create(scr, NULL);
	lv_obj_set_style(wifi_name_text, &tft_style_lable_rel);

	wifi_key_text = lv_label_create(scr, NULL);
	lv_obj_set_style(wifi_key_text, &tft_style_lable_rel);
	
	wifi_state_text = lv_label_create(scr, NULL);
	lv_obj_set_style(wifi_state_text, &tft_style_lable_rel);

	disp_wifi_state();
}

void disp_wifi_state()
{
	memset(public_buf_m, 0, sizeof(public_buf_m));
	strcpy(public_buf_m,wifi_menu.ip);
	strcat(public_buf_m,ipPara.ip_addr);
	lv_label_set_text(wifi_ip_text, public_buf_m);
	lv_obj_align(wifi_ip_text, NULL, LV_ALIGN_CENTER,0, -100);

	memset(public_buf_m, 0, sizeof(public_buf_m));
	strcpy(public_buf_m,wifi_menu.wifi);
	strcat(public_buf_m,wifiPara.ap_name);
	lv_label_set_text(wifi_name_text, public_buf_m);
	lv_obj_align(wifi_name_text, NULL, LV_ALIGN_CENTER,0, -70);

	if(wifiPara.mode == AP_MODEL)
	{
		memset(public_buf_m, 0, sizeof(public_buf_m));
		strcpy(public_buf_m,wifi_menu.key);
		strcat(public_buf_m,wifiPara.keyCode);
		lv_label_set_text(wifi_key_text, public_buf_m);
		lv_obj_align(wifi_key_text, NULL, LV_ALIGN_CENTER,0, -40);

		memset(public_buf_m, 0, sizeof(public_buf_m));
		strcpy(public_buf_m,wifi_menu.state_ap);
		if(wifi_link_state == WIFI_CONNECTED)
			strcat(public_buf_m,wifi_menu.connected);
		else if(wifi_link_state == WIFI_NOT_CONFIG)
			strcat(public_buf_m,wifi_menu.disconnected);
		else
			strcat(public_buf_m,wifi_menu.exception);
		lv_label_set_text(wifi_state_text, public_buf_m);
		lv_obj_align(wifi_state_text, NULL, LV_ALIGN_CENTER,0, -10);
		
	}
	else
	{
		memset(public_buf_m, 0, sizeof(public_buf_m));
		strcpy(public_buf_m,wifi_menu.state_sta);
		if(wifi_link_state == WIFI_CONNECTED)
			strcat(public_buf_m,wifi_menu.connected);
		else if(wifi_link_state == WIFI_NOT_CONFIG)
			strcat(public_buf_m,wifi_menu.disconnected);
		else
			strcat(public_buf_m,wifi_menu.exception);
		lv_label_set_text(wifi_state_text, public_buf_m);
		lv_obj_align(wifi_state_text, NULL, LV_ALIGN_CENTER,0, -40);

		lv_label_set_text(wifi_key_text, "");
		lv_obj_align(wifi_key_text, NULL, LV_ALIGN_CENTER,0, -10);
	}
}

void lv_clear_wifi()
{
	lv_obj_del(scr);
}
#endif