#ifndef __UI_TOOLS_H__
#define __UI_TOOLS_H__

/*********************
 * Include
 * ********************/
#include "Applications.h"

/*********************
 * Defines
 * ********************/


#define ICON_WIDTH_HEIGHT 100
#define PAD_ICON (LV_VER_RES_MAX / 20)
#define PAD_STATUS_BAR (LV_VER_RES_MAX / 12)
#define LV_SET_LOCAL_STYLE(sn, obj, val) lv_obj_set_style_local_##sn(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, val)

/*********************
 * Prototype
 * ********************/
lv_obj_t *FLT_show_statusbar(lv_color_t color, uint8_t opa);
void FLT_show_background(lv_color_t color);
lv_obj_t* FLT_add_icon(lv_obj_t* parent, const void* src_img, const char* txt);
lv_obj_t *FLT_add_icon_lite(lv_obj_t* parent, lv_color_t bg_color, const char* txt);
#endif