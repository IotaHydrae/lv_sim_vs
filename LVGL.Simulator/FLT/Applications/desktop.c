#include "utils.h"
#include "ui_tools.h"


typedef struct {
        lv_obj_t *screen;
		lv_theme_t *theme;

        lv_obj_t *icon1;
        lv_obj_t *icon2;
        lv_obj_t *icon3;
        lv_obj_t *icon4;
        lv_obj_t *icon5;

		lv_obj_t *folder;
}lv_ui;

typedef struct {
	void *img_data;
	char *text;
	uint8_t text_size;
	uint32_t  text_color;
	uint8_t text_position;

	uint8_t category;
}adver;

typedef enum {
	DESKTOP_CATEGORY_MUSIC,
	DESKTOP_CATEGORY_MOIVE,
	DESKTOP_CATEGORY_ARTICLE,
}CATEGORY;

/*Defines for adver pos 0*/
#define ADVER_POS0_SIZE 2
#define ADVER_POS0_REFRESH_TIME 4000

#define ADVER_POS1_SIZE 5
#define ADVER_POS1_REFRESH_TIME 6000
/**********************
** STATIC VAR
***********************/
static lv_ui ui;
static lv_obj_t *tileview;

static int adver_pos0_index=0;
static adver adver_pos0[ADVER_POS0_SIZE];
static lv_obj_t * btn_ad_pos0;
static lv_obj_t *img_ad_pos0;
static lv_obj_t * label_ad1_pos0;

static int adver_pos1_index=0;
static adver adver_pos1[ADVER_POS1_SIZE];
static lv_obj_t * btn_ad_pos1;
static lv_obj_t *img_ad_pos1;
static lv_obj_t * label_ad1_pos1;

/*Prototype*/
static void adver_pos0_update(lv_task_t *task);
static void adver_pos0_init(void);
static void adver_pos1_update(lv_task_t *task);
static void adver_pos1_init(void);

LV_IMG_DECLARE(desktop_music_category);
LV_IMG_DECLARE(desktop_movie_category);
LV_IMG_DECLARE(desktop_book_category);
LV_EVENT_CB_DECLARE(btn_ad_pos0_event_handler);
LV_EVENT_CB_DECLARE(btn_ad_pos1_event_handler);

static void __self_init()
{
	ui.theme = FLT_theme_init(FLT_COLOR_PRIMARY, FLT_COLOR_SECONDARY, 0,
		&lv_font_simhei_14, &lv_font_simhei_22,
		&lv_font_simhei_28, &lv_font_simhei_32);

	ui.screen = lv_obj_create(NULL, NULL);
	
	
}

void desktop(void)
{
	LV_IMG_DECLARE(desktop_home_manager);
	LV_IMG_DECLARE(desktop_music);
	LV_IMG_DECLARE(desktop_book);
	LV_IMG_DECLARE(desktop_movie);
	LV_IMG_DECLARE(desktop_clock);

	LV_IMG_DECLARE(desktop_phone);
	LV_IMG_DECLARE(desktop_setting);
	LV_IMG_DECLARE(desktop_message);
	LV_IMG_DECLARE(desktop_more);

	__self_init();
	lv_theme_set_act(ui.theme);
	lv_scr_load(ui.screen);
	FLT_show_background(lv_theme_get_color_primary());
	lv_obj_t *statusBar = FLT_show_statusbar(lv_theme_get_color_secondary(), LV_OPA_50);


	static lv_point_t valid_pos[] = {{0,0}, {1, 0},{2, 0}};

	
    tileview = lv_tileview_create(lv_scr_act(), NULL);
    lv_tileview_set_valid_positions(tileview, valid_pos, 3);
    lv_tileview_set_edge_flash(tileview, false);
	lv_tileview_set_anim_time(tileview,0);
	/*
	* Tile 1: Icon folder and adver span
	*/
    lv_obj_t * tile1 = lv_obj_create(tileview, NULL);
    lv_obj_set_size(tile1, LV_HOR_RES, LV_VER_RES);
    lv_tileview_add_element(tileview, tile1);
	


	lv_obj_t *icon_img;
	ui.icon1 = FLT_add_icon_lite(tile1, lv_theme_get_color_secondary(), "智能管家");
	icon_img = lv_img_create(ui.icon1, NULL);
	lv_img_set_src(icon_img, &desktop_home_manager);
	lv_obj_align(icon_img, ui.icon1,LV_ALIGN_CENTER, 0, -LV_VER_RES/30);
	lv_obj_align(ui.icon1, statusBar,LV_ALIGN_OUT_BOTTOM_LEFT, PAD_ICON, PAD_STATUS_BAR);

	ui.icon2 = FLT_add_icon_lite(tile1, lv_theme_get_color_secondary(), "音乐");
	icon_img = lv_img_create(ui.icon2, NULL);
	lv_img_set_src(icon_img, &desktop_music);
	lv_obj_align(icon_img, ui.icon2,LV_ALIGN_CENTER, 0, -LV_VER_RES/30);
	lv_obj_align(ui.icon2, ui.icon1, LV_ALIGN_OUT_RIGHT_MID, PAD_ICON, 0);

	ui.icon3 = FLT_add_icon_lite(tile1, lv_theme_get_color_secondary(), "阅读");
	icon_img = lv_img_create(ui.icon3, NULL);
	lv_img_set_src(icon_img, &desktop_book);
	lv_obj_align(icon_img, ui.icon3,LV_ALIGN_CENTER, 0, -LV_VER_RES/30);
	lv_obj_align(ui.icon3, ui.icon1, LV_ALIGN_OUT_BOTTOM_MID, 0, PAD_ICON);

	ui.icon4 = FLT_add_icon_lite(tile1, lv_theme_get_color_secondary(), "播放器");
	icon_img = lv_img_create(ui.icon4, NULL);
	lv_img_set_src(icon_img, &desktop_movie);
	lv_obj_align(icon_img, ui.icon4,LV_ALIGN_CENTER, 0, -LV_VER_RES/30);	
	lv_obj_align(ui.icon4, ui.icon2, LV_ALIGN_OUT_BOTTOM_MID, 0, PAD_ICON);

	ui.icon5 = FLT_add_icon_lite(tile1, lv_theme_get_color_secondary(), "时钟");
	icon_img = lv_img_create(ui.icon5, NULL);
	lv_img_set_src(icon_img, &desktop_clock);
	lv_obj_align(icon_img, ui.icon5,LV_ALIGN_CENTER, 0, -LV_VER_RES/30);	
	lv_obj_align(ui.icon5, ui.icon3, LV_ALIGN_OUT_BOTTOM_MID, 0, PAD_ICON);

	/*folder here*/
	ui.folder= FLT_add_icon_lite(tile1, lv_theme_get_color_secondary(), NULL);

		icon_img = lv_img_create(ui.folder, NULL);
	lv_img_set_src(icon_img, &desktop_phone);
	lv_img_set_zoom(icon_img,224);
	lv_obj_align(icon_img, ui.folder,LV_ALIGN_IN_TOP_LEFT, 2, 2);

		icon_img = lv_img_create(ui.folder, NULL);
	lv_img_set_src(icon_img, &desktop_setting);
	lv_img_set_zoom(icon_img,224);
	lv_obj_align(icon_img, ui.folder,LV_ALIGN_IN_TOP_RIGHT, 0, 2);

		icon_img = lv_img_create(ui.folder, NULL);
	lv_img_set_src(icon_img, &desktop_message);
	lv_img_set_zoom(icon_img,224);
	lv_obj_align(icon_img, ui.folder,LV_ALIGN_IN_BOTTOM_LEFT, 2, -2);

		icon_img = lv_img_create(ui.folder, NULL);
	lv_img_set_src(icon_img, &desktop_more);
	lv_img_set_zoom(icon_img,190);
	lv_obj_align(icon_img, ui.folder,LV_ALIGN_IN_BOTTOM_RIGHT, 0, -2);

	lv_obj_align(ui.folder, ui.icon4, LV_ALIGN_OUT_BOTTOM_MID, 0, PAD_ICON);

	/* right area of tile is a ad span */
	adver_pos0_init();
	btn_ad_pos0 = lv_btn_create(tile1, NULL);
	lv_obj_set_event_cb(btn_ad_pos0, btn_ad_pos1_event_handler);
	lv_theme_apply(btn_ad_pos0, (lv_theme_style_t)FLT_THEME_BTN);
	lv_btn_set_fit(btn_ad_pos0, LV_FIT_NONE);
	LV_SET_LOCAL_STYLE(radius, btn_ad_pos0, 40);
	lv_obj_set_size(btn_ad_pos0, LV_HOR_RES*0.6, LV_VER_RES*0.8);	/* 480x384 in res800x480 */
    lv_obj_align(btn_ad_pos0, NULL, LV_ALIGN_CENTER, LV_HOR_RES/7, LV_VER_RES/20);
	/*The button needs to be explicitly added to the 
	Tileview to enable the user to scroll the Tileview with the button too.
	If you don't do this, mouse click on the buttom and move will not scroll the tileview*/
	lv_tileview_add_element(tileview, btn_ad_pos0);

	img_ad_pos0 = lv_img_create(btn_ad_pos0, NULL);
	lv_img_set_src(img_ad_pos0, adver_pos0[adver_pos0_index].img_data);

    label_ad1_pos0 = lv_label_create(tile1, NULL);
	lv_label_set_text(label_ad1_pos0, adver_pos0[adver_pos0_index].text);
	adver_pos0_update(NULL);
	lv_task_create(adver_pos0_update, ADVER_POS0_REFRESH_TIME, LV_TASK_PRIO_MID, NULL);

    /*
	*	Tile2: A image button with label info
	*/
	LV_IMG_DECLARE(desktop_ad0_radius40);
	adver_pos1_init();
	lv_obj_t *tile2;
    tile2 = lv_obj_create(tileview, tile1);
    lv_obj_set_pos(tile2, LV_HOR_RES, 0);
    lv_tileview_add_element(tileview, tile2);

    btn_ad_pos1 = lv_btn_create(tile2, NULL);
	lv_tileview_add_element(tileview, btn_ad_pos1);
	lv_obj_set_event_cb(btn_ad_pos1, btn_ad_pos1_event_handler);
	lv_theme_apply(btn_ad_pos1, (lv_theme_style_t)FLT_THEME_BTN);
	lv_btn_set_fit(btn_ad_pos1, LV_FIT_NONE);
	LV_SET_LOCAL_STYLE(radius, btn_ad_pos1, 40);
	lv_obj_set_size(btn_ad_pos1, LV_HOR_RES*0.9, LV_VER_RES*0.8);	/* 720x384 in res800x480 */
    lv_obj_align(btn_ad_pos1, NULL, LV_ALIGN_CENTER, 0, LV_VER_RES/20);

	img_ad_pos1 = lv_img_create(btn_ad_pos1, NULL);
	lv_img_set_src(img_ad_pos1, adver_pos1[adver_pos1_index].img_data);

    label_ad1_pos1 = lv_label_create(tile2, NULL);
	adver_pos1_update(NULL);
	lv_task_create(adver_pos1_update, ADVER_POS1_REFRESH_TIME, LV_TASK_PRIO_MID, NULL);

    /*Tile3: Two image button with label info*/
    lv_obj_t * tile3 = lv_obj_create(tileview, tile1);
    lv_obj_set_pos(tile3, LV_HOR_RES*2, 0);
    lv_tileview_add_element(tileview, tile3);

    lv_obj_t * btn = lv_btn_create(tile3, NULL);
    lv_obj_align(btn, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_tileview_add_element(tileview, btn);
    lv_obj_t * label = lv_label_create(btn, NULL);
    lv_label_set_text(label, "Tile3: a button");
}

/* display update functions */
static void adver_pos0_update(lv_task_t *task){
	printf("%d,%d\n", adver_pos0_index,lv_tick_get());
	//lv_obj_t *btn = lv_obj_get_child_back(tile2, NULL);
	lv_img_set_src(img_ad_pos0, adver_pos0[adver_pos0_index].img_data);
	lv_label_set_text(label_ad1_pos0, adver_pos0[adver_pos0_index].text);
	LV_SET_LOCAL_STYLE(text_color, label_ad1_pos0, lv_color_hex(adver_pos0[adver_pos0_index].text_color));
	switch(adver_pos0[adver_pos0_index].text_size){
	case 14:
		LV_SET_LOCAL_STYLE(text_font, label_ad1_pos0, &lv_font_simhei_14);
		break;
	case 22:
		LV_SET_LOCAL_STYLE(text_font, label_ad1_pos0, &lv_font_simhei_22);
		break;
	case 28:
		LV_SET_LOCAL_STYLE(text_font, label_ad1_pos0, &lv_font_simhei_28);
		break;
	case 32:
		LV_SET_LOCAL_STYLE(text_font, label_ad1_pos0, &lv_font_simhei_32);
		break;
	default:
		LV_SET_LOCAL_STYLE(text_font, label_ad1_pos0, &lv_font_simhei_28);
		break;
	}

	const uint8_t hor_diff = 20,vert_diff =10;
	switch(adver_pos0[adver_pos0_index].text_position){
	case LV_ALIGN_IN_TOP_LEFT:
		lv_obj_align(label_ad1_pos0, btn_ad_pos0, LV_ALIGN_IN_TOP_LEFT, 
						LV_HOR_RES/hor_diff, LV_VER_RES/vert_diff);
		break;
	case LV_ALIGN_IN_TOP_RIGHT:
		lv_obj_align(label_ad1_pos0, btn_ad_pos0, LV_ALIGN_IN_TOP_RIGHT, 
						-LV_HOR_RES/hor_diff, LV_VER_RES/vert_diff);
		break;
	case LV_ALIGN_IN_BOTTOM_LEFT:
		lv_obj_align(label_ad1_pos0, btn_ad_pos0, LV_ALIGN_IN_BOTTOM_LEFT, 
						LV_HOR_RES/hor_diff, -LV_VER_RES/vert_diff);
		break;
	case LV_ALIGN_IN_BOTTOM_RIGHT:
		lv_obj_align(label_ad1_pos0, btn_ad_pos0, LV_ALIGN_IN_BOTTOM_RIGHT, 
						-LV_HOR_RES/hor_diff, -LV_VER_RES/vert_diff);
		break;
	default:
		lv_obj_align(label_ad1_pos0, btn_ad_pos0, LV_ALIGN_IN_BOTTOM_LEFT, 
						LV_HOR_RES/hor_diff, -LV_VER_RES/vert_diff);
		break;
	}
	lv_refr_now(NULL);
	printf("%s\n", adver_pos0[adver_pos0_index].text);

	/*finally*/
	adver_pos0_index++;
	if(adver_pos0_index >(ADVER_POS0_SIZE-1))adver_pos0_index=0;
}

static void adver_pos1_update(lv_task_t *task){
	
	printf("%d,%d\n", adver_pos1_index,lv_tick_get());
	//lv_obj_t *btn = lv_obj_get_child_back(tile2, NULL);
	lv_img_set_src(img_ad_pos1, adver_pos1[adver_pos1_index].img_data);
	lv_label_set_text(label_ad1_pos1, adver_pos1[adver_pos1_index].text);
	LV_SET_LOCAL_STYLE(text_color, label_ad1_pos1, lv_color_hex(adver_pos1[adver_pos1_index].text_color));
	switch(adver_pos1[adver_pos1_index].text_size){
	case 14:
		LV_SET_LOCAL_STYLE(text_font, label_ad1_pos1, &lv_font_simhei_14);
		break;
	case 22:
		LV_SET_LOCAL_STYLE(text_font, label_ad1_pos1, &lv_font_simhei_22);
		break;
	case 28:
		LV_SET_LOCAL_STYLE(text_font, label_ad1_pos1, &lv_font_simhei_28);
		break;
	case 32:
		LV_SET_LOCAL_STYLE(text_font, label_ad1_pos1, &lv_font_simhei_32);
		break;
	default:
		LV_SET_LOCAL_STYLE(text_font, label_ad1_pos1, &lv_font_simhei_28);
		break;
	}

	const uint8_t hor_diff = 20,vert_diff =10;
	switch(adver_pos1[adver_pos1_index].text_position){
	case LV_ALIGN_IN_TOP_LEFT:
		lv_obj_align(label_ad1_pos1, btn_ad_pos1, LV_ALIGN_IN_TOP_LEFT, 
						LV_HOR_RES/hor_diff, LV_VER_RES/vert_diff);
		break;
	case LV_ALIGN_IN_TOP_RIGHT:
		lv_obj_align(label_ad1_pos1, btn_ad_pos1, LV_ALIGN_IN_TOP_RIGHT, 
						-LV_HOR_RES/hor_diff, LV_VER_RES/vert_diff);
		break;
	case LV_ALIGN_IN_BOTTOM_LEFT:
		lv_obj_align(label_ad1_pos1, btn_ad_pos1, LV_ALIGN_IN_BOTTOM_LEFT, 
						LV_HOR_RES/hor_diff, -LV_VER_RES/vert_diff);
		break;
	case LV_ALIGN_IN_BOTTOM_RIGHT:
		lv_obj_align(label_ad1_pos1, btn_ad_pos1, LV_ALIGN_IN_BOTTOM_RIGHT, 
						-LV_HOR_RES/hor_diff, -LV_VER_RES/vert_diff);
		break;
	default:
		lv_obj_align(label_ad1_pos1, btn_ad_pos1, LV_ALIGN_IN_BOTTOM_LEFT, 
						LV_HOR_RES/hor_diff, -LV_VER_RES/vert_diff);
		break;
	}
	lv_refr_now(NULL);
	printf("%s\n", adver_pos1[adver_pos1_index].text);

	/*finally*/
	adver_pos1_index++;
	if(adver_pos1_index >(ADVER_POS1_SIZE-1))adver_pos1_index=0;
}

/* other init functions */

static void adver_pos0_init(void)
{
	/*
	typedef struct {
	void *img_data;
	char *text;
	uint8_t text_color;
	uint8_t text_position;

	uint8_t category;
	}adver;
	*/
	
	/*img declarations*/
	LV_IMG_DECLARE(desktop_coffe_night_radius40);
	LV_IMG_DECLARE(desktop_star_night_radius40);

	const void *adver_pos0_data_array1[] = {
		&desktop_coffe_night_radius40,
		&desktop_star_night_radius40,
	};
	const void *adver_pos0_data_array2[] = {
		"《夜晚露天咖啡座》",
		"《有星星的夜空》"
	};
	const long adver_pos0_data_array3[] = {
		32,0xb9b9b9,LV_ALIGN_IN_BOTTOM_LEFT,DESKTOP_CATEGORY_ARTICLE,
		32,0xb9b9b9,LV_ALIGN_IN_BOTTOM_LEFT,DESKTOP_CATEGORY_ARTICLE,
	};

	int i,j;
	for(i=0,j=0; i<ADVER_POS0_SIZE;i++,j+=4){
		adver_pos0[i].img_data = (lv_img_dsc_t *)adver_pos0_data_array1[i];
		adver_pos0[i].text = (char *)adver_pos0_data_array2[i];

		adver_pos0[i].text_size = adver_pos0_data_array3[j];
		adver_pos0[i].text_color = adver_pos0_data_array3[j+1];
		adver_pos0[i].text_position = adver_pos0_data_array3[j+2];
		adver_pos0[i].category = adver_pos0_data_array3[j+3];
	}
}

static void adver_pos1_init(void)
{
	/*
	typedef struct {
	void *img_data;
	char *text;
	uint8_t text_color;
	uint8_t text_position;

	uint8_t category;
	}adver;
	*/

	LV_IMG_DECLARE(desktop_ad0_radius40);
	LV_IMG_DECLARE(desktop_ad1_radius40);
	LV_IMG_DECLARE(desktop_ad2_radius40);
	LV_IMG_DECLARE(desktop_ad3_radius40);
	LV_IMG_DECLARE(desktop_ad4_radius40);

	const void *adver_pos1_data_array1[] = {
		&desktop_ad0_radius40,
		&desktop_ad1_radius40,
		&desktop_ad2_radius40,
		&desktop_ad3_radius40,
		&desktop_ad4_radius40,
	};

	const void *adver_pos1_data_array2[] = {
		"狂鸟招主播企鹅群！所有主播90%提成",
		"一个面向单色显示屏的开源GUI接口库。",
		"推送到了 韦东山/qemu_image_for_imx6ull 的 master 分支",
		"在某宝上淘换了两个白牌的单总线舵机",
		"自己总结的这十年来做Qt开发以来的经验",
	};

	const long adver_pos1_data_array3[] = {
		32,0xb9b9b9,LV_ALIGN_IN_BOTTOM_RIGHT,DESKTOP_CATEGORY_ARTICLE,
		32,0xb9b9b9,LV_ALIGN_IN_BOTTOM_LEFT,DESKTOP_CATEGORY_ARTICLE,
		22,0x191919,LV_ALIGN_IN_BOTTOM_LEFT,DESKTOP_CATEGORY_ARTICLE,
		28,0x191919,LV_ALIGN_IN_BOTTOM_LEFT,DESKTOP_CATEGORY_ARTICLE,
		32,0xb9b9b9,LV_ALIGN_IN_BOTTOM_LEFT,DESKTOP_CATEGORY_ARTICLE,

	};
	int i,j;
	for(i=0,j=0; i<ADVER_POS1_SIZE;i++,j+=4)
	{
		adver_pos1[i].img_data = (lv_img_dsc_t *)adver_pos1_data_array1[i];
		adver_pos1[i].text = (char *)adver_pos1_data_array2[i];
		
		adver_pos1[i].text_size = adver_pos1_data_array3[j];
		adver_pos1[i].text_color = adver_pos1_data_array3[j+1];
		adver_pos1[i].text_position = adver_pos1_data_array3[j+2];
		adver_pos1[i].category = adver_pos1_data_array3[j+3];
	}
}

#if 0
void tile_test(void)
{
static lv_point_t valid_pos[] = {{0,0}, {1, 0},{2, 0}};
    lv_obj_t *tileview;
    tileview = lv_tileview_create(lv_scr_act(), NULL);
    lv_tileview_set_valid_positions(tileview, valid_pos, 3);
    lv_tileview_set_edge_flash(tileview, false);

    lv_obj_t * tile1 = lv_obj_create(tileview, NULL);
    lv_obj_set_size(tile1, LV_HOR_RES, LV_VER_RES);
    lv_tileview_add_element(tileview, tile1);

    /*Tile1: just a label*/
    lv_obj_t * label = lv_label_create(tile1, NULL);
    lv_label_set_text(label, "Scroll down");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    /*Tile2: a list*/
    lv_obj_t * list = lv_list_create(tileview, NULL);
    lv_obj_set_size(list, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_pos(list, LV_HOR_RES, 0);
    lv_list_set_scroll_propagation(list, true);
    lv_list_set_scrollbar_mode(list, LV_SCROLLBAR_MODE_OFF);

    lv_list_add_btn(list, NULL, "One");
    lv_list_add_btn(list, NULL, "Two");
    lv_list_add_btn(list, NULL, "Three");
    lv_list_add_btn(list, NULL, "Four");
    lv_list_add_btn(list, NULL, "Five");
    lv_list_add_btn(list, NULL, "Six");
    lv_list_add_btn(list, NULL, "Seven");
    lv_list_add_btn(list, NULL, "Eight");
	
    /*Tile3: a button*/
    lv_obj_t * tile3 = lv_obj_create(tileview, tile1);
    lv_obj_set_pos(tile3, LV_HOR_RES*2, 0);
    lv_tileview_add_element(tileview, tile3);

    lv_obj_t * btn = lv_btn_create(tile3, NULL);
    lv_obj_align(btn, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_tileview_add_element(tileview, btn);
    label = lv_label_create(btn, NULL);
    lv_label_set_text(label, "No scroll up");
}
#endif
LV_EVENT_CB_DECLARE(btn_ad_pos0_event_handler)
{
	if (e == LV_EVENT_CLICKED){
		printf("%d\n", lv_tick_get());
	}
}

LV_EVENT_CB_DECLARE(btn_ad_pos1_event_handler)
{
	switch (e){
		case LV_EVENT_CLICKED:
		printf("%d\n", lv_tick_get());
		break;
	}
}