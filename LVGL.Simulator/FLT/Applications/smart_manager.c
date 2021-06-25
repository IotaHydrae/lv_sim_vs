#include "utils.h"
#include "ui_tools.h"

//-----------------------------------------------------------------------------
//      Copyright © 2021 jensenhua. All rights reserved
//
//      @FileName   :  smart_manager.c
//      @Author     :  jensenhua   
//      @Version    :  v1.0.0
//      @Date       :  21/05/23
//      @Description:  
//      @Others     :  
//      @License    :  GNU General Public License, version 3 (GPL-3.0)
//
//
//
// FLT  Copyright (C) 2020  jessenhua (h1657802074@gmail.com) 
//                                                                       
// This file is part of FLT                                   
//   ____ ____  _      __     _______  ___                               
//  / ___|  _ \| |     \ \   / /___ / / _ \                              
// | |  _| |_) | |      \ \ / /  |_ \| | | |                             
// | |_| |  __/| |___    \ V /  ___) | |_| |                             
//  \____|_|   |_____|    \_/  |____(_)___/                              
//                                                                       
// FLT is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by  
// the Free Software Foundation, either version 3 of the License, or     
// (at your option) any later version.                                   
//                                                                       
// This program is distributed in the hope that it will be useful, but   
// WITHOUT ANY WARRANTY; without even the implied warranty of            
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU     
// General Public License for more details.                              
//                                                                       
// You should have received a copy of the GNU General Public License     
// along with this program.  If not, see <http://www.gnu.org/licenses/>. 
//-----------------------------------------------------------------------------

/*  UI 
page1 overview
page2 air conditioner
page3 Electric heating
page4 Refrigerator
page5 Washing machine
page6 chandelier
page7
*/

/* struct of widgets in this app */
typedef struct {
        lv_obj_t *screen;
		lv_theme_t *theme;
}lv_ui;

/*static variable*/
static lv_ui ui;
static lv_obj_t *tileview;

//-----------------------------------------------------------------------------
//      @Function   :  __self_init
//      @Description:  init screen and theme
//      @Input      :  
//      @Output     :  
//      @Returns    :  
//      @Others     :  Others info for this function
//-----------------------------------------------------------------------------
static void __self_init()
{
	ui.theme = FLT_theme_init(FLT_COLOR_PRIMARY, FLT_COLOR_SECONDARY, 0,
		&lv_font_simhei_14, &lv_font_simhei_22,
		&lv_font_simhei_28, &lv_font_simhei_32);

	ui.screen = lv_obj_create(lv_scr_act(), NULL);
	// lv_obj_reset_style_list(ui.screen, LV_OBJ_PART_MAIN);
	lv_obj_set_pos(ui.screen, 0, 0);
	lv_obj_set_size(ui.screen, LV_HOR_RES, LV_VER_RES);
	
}

//-----------------------------------------------------------------------------
//      @Function   :  Name of function
//      @Description:  Just description for function
//      @Input      :  Param inputs
//      @Output     :  Function output
//      @Returns    :  Result
//      @Others     :  Others info for this function
//-----------------------------------------------------------------------------
void smart_manager(void)
{
	__self_init();
	lv_theme_set_act(ui.theme);
	lv_scr_load(ui.screen);
	FLT_show_background(lv_theme_get_color_primary());
	
	lv_obj_t *statusBar = FLT_show_statusbar(lv_theme_get_color_secondary(), LV_OPA_50);
	lv_task_create(FLT_update_statusBar, 1000,LV_TASK_PRIO_MID, NULL);

	/* create tileview */
	static lv_point_t valid_pos[] = {{0,0}, {1, 0}, {2, 0}};
    tileview = lv_tileview_create(lv_scr_act(), NULL);
    lv_tileview_set_valid_positions(tileview, valid_pos, 3);
    lv_tileview_set_edge_flash(tileview, false);
	lv_tileview_set_anim_time(tileview,0);

	/*
	* Tile 1: main box to save other stuff
	*/
    lv_obj_t * tile1 = lv_obj_create(tileview, NULL);
    lv_obj_set_size(tile1, LV_HOR_RES, LV_VER_RES);
    lv_tileview_add_element(tileview, tile1);

	lv_obj_t *main_box = lv_obj_create(tile1, NULL);
	lv_theme_apply(main_box, (lv_theme_style_t)FLT_THEME_BOX);
	lv_obj_set_size(main_box, LV_HOR_RES/1.1, LV_VER_RES/1.2);
	lv_obj_align(main_box, statusBar, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);

	/* title */
	lv_obj_t *label_main_box = lv_label_create(main_box, NULL);
	lv_label_set_text(label_main_box, "设备");
	lv_theme_apply(label_main_box, (lv_theme_style_t)FLT_THEME_LABEL_TITLE);
	lv_obj_align(label_main_box, main_box, LV_ALIGN_IN_TOP_MID, 0, 10);
	LV_SET_LOCAL_STYLE(text_font, label_main_box, lv_theme_get_font_title());

	/* air conditioner control bar */
	// lv_obj_t *air_control_bar = lv_obj_create(main_box, NULL);
	// lv_theme_apply(air_control_bar, (lv_theme_style_t)FLT_THEME_BOX);
	// LV_SET_LOCAL_STYLE(bg_color, air_control_bar, LV_COLOR_WHITE);
	// lv_obj_set_size(air_control_bar, lv_obj_get_width(main_box)/3,lv_obj_get_height(main_box)/5);
	// lv_obj_align(air_control_bar, main_box, LV_ALIGN_IN_TOP_LEFT, 30, 50);
	lv_obj_t *air_control_bar = FLT_add_control_bar(main_box, lv_obj_get_width(main_box)/3,lv_obj_get_height(main_box)/5);
	lv_obj_align(air_control_bar, main_box, LV_ALIGN_IN_TOP_LEFT, 30, 50);
}