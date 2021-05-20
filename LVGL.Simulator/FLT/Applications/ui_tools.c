#include "ui_tools.h"


lv_obj_t *FLT_show_statusbar(lv_color_t color, uint8_t opa)
{
	uint8_t hour=14,min=9;
	LV_IMG_DECLARE(status_bar_wifi);
	/*Left consist of
	time 
	show apps icon when apps notice come
	*/

	/*Right consist of
	DEFAULT: WIFI BlueTooth Battery
	Others:
	*/
	lv_obj_t *statusBar = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_clean_style_list(statusBar, LV_OBJ_PART_MAIN);
	lv_obj_set_style_local_bg_opa(statusBar, LV_OBJ_PART_MAIN,
                                LV_STATE_DEFAULT, opa);

	lv_obj_set_style_local_bg_color(statusBar, LV_OBJ_PART_MAIN,
	LV_STATE_DEFAULT, color);

	lv_obj_set_size(statusBar, LV_HOR_RES, LV_VER_RES/10);

	lv_obj_t *time = lv_label_create(statusBar, NULL);
	lv_obj_set_style_local_text_font(time, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
	lv_obj_set_style_local_text_color(time, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
	lv_label_set_text_fmt(time, "%02d:%02d",hour, min);
	lv_obj_align(time,statusBar, LV_ALIGN_IN_LEFT_MID, 20, 0);

	lv_obj_t *wifi_icon = lv_img_create(statusBar, NULL);
	lv_img_set_src(wifi_icon, &status_bar_wifi);
	lv_img_set_zoom(wifi_icon, 256);
	lv_obj_align(wifi_icon,statusBar, LV_ALIGN_IN_RIGHT_MID, -20, 0);

	return statusBar;
}

void FLT_show_background(lv_color_t color)
{
	lv_obj_t *bg = lv_obj_create(lv_scr_act(), NULL);
	lv_obj_clean_style_list(bg, LV_OBJ_PART_MAIN);
	lv_obj_set_style_local_bg_opa(bg, LV_OBJ_PART_MAIN,
		LV_STATE_DEFAULT, LV_OPA_COVER);

	lv_obj_set_style_local_bg_color(bg, LV_OBJ_PART_MAIN,
		LV_STATE_DEFAULT, color);
	lv_obj_set_size(bg, LV_HOR_RES, LV_VER_RES);
}

static void set_icon_style(lv_obj_t* obj, lv_color_t color)
{
    static lv_style_t  style;
    lv_style_init(&style);
    lv_style_set_text_color(&style, LV_STATE_DEFAULT, FLT_COLOR_FONT_GRAY);

    /*border*/
	lv_style_set_radius(&style, LV_STATE_DEFAULT, 10);
	

    /*shadow*/
    /*lv_style_set_shadow_opa(&style, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_shadow_color(&style, LV_STATE_DEFAULT, color);
    lv_style_set_shadow_width(&style, LV_STATE_DEFAULT, 10);
    lv_style_set_shadow_spread(&style, LV_STATE_DEFAULT, 5);*/

    /*properties for background*/
	lv_style_set_bg_color(&style, LV_STATE_DEFAULT, color);
    lv_style_set_bg_opa(&style, LV_STATE_DEFAULT, LV_OPA_COVER);


    /*make the button smaller when pressed*/
    lv_style_set_transform_height(&style, LV_STATE_PRESSED, -2);
    lv_style_set_transform_width(&style, LV_STATE_PRESSED, -2);
    static lv_anim_path_t path;
    lv_anim_path_init(&path);
    lv_anim_path_set_cb(&path, lv_anim_path_overshoot);
    lv_style_set_transition_prop_1(&style, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_HEIGHT);
    lv_style_set_transition_prop_2(&style, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_WIDTH);
    lv_style_set_transition_time(&style, LV_STATE_DEFAULT, 50);

    lv_style_set_transition_path(&style, LV_STATE_DEFAULT, &path);
    lv_obj_clean_style_list(obj, LV_OBJ_PART_MAIN);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &style);
}

lv_obj_t *FLT_add_icon_lite(lv_obj_t* parent, lv_color_t bg_color, const char* txt)
{
	lv_obj_t *bg = lv_obj_create(parent, NULL);
	lv_obj_set_click(bg, true);
    lv_obj_set_size(bg, ICON_WIDTH_HEIGHT, ICON_WIDTH_HEIGHT);
    set_icon_style(bg, bg_color);

	if(txt){
		/*label in bg*/
		lv_obj_t* label = lv_label_create(bg, NULL);
		lv_label_set_text(label, txt);
		//lv_obj_set_style_local_text_color(label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
		lv_obj_set_style_local_text_font(label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_normal());
		lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -5);
	}
	return bg;
}

lv_obj_t* FLT_add_icon(lv_obj_t* parent, const void* src_img, const char* txt)
{
    lv_obj_t* bg = lv_img_create(parent, NULL);
    lv_obj_set_click(bg, true);
    lv_theme_apply(bg, (lv_theme_style_t)FLT_THEME_ICON);
    lv_img_set_src(bg, src_img);
    lv_img_set_antialias(bg, false);

	if(txt){
		/*label in bg*/
		lv_obj_t* label = lv_label_create(bg, NULL);
		lv_label_set_text(label, txt);
		//lv_obj_set_style_local_text_color(label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
		lv_obj_set_style_local_text_font(label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_normal());
		lv_obj_align(label, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -5);
	}

    return bg;
}

lv_obj_t *FLT_add_adver(lv_obj_t* parent)
{
	return 0;
}

/*lv_obj_t *FLT_add_folder(lv_obj_t* parent, lv_color_t bg_color)
{
	return 0;
}*/