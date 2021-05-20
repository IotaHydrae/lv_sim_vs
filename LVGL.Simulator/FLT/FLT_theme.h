﻿/**
* @file FLT_theme.h
*
*/

#ifndef _FLT_THEME_H
#define _FLT_THEME_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
*      INCLUDES
*********************/
#include "FLT_Entry.h"

/*********************
*      DEFINES
*********************/

/* Colors*/
#define FLT_COLOR_PRIMARY   lv_color_make(1, 1, 1)
#define FLT_COLOR_SECONDARY lv_color_make(46, 47, 51)
#define FLT_COLOR_FONT_GRAY lv_color_make(185, 185, 185)
    
/**********************
*      TYPEDEFS
**********************/
typedef enum {
    FLT_THEME_ICON,
    FLT_THEME_BTN,
}FLT_theme_t;

/**********************
* GLOBAL PROTOTYPES
**********************/
/**
    * Initialize the default
    * @param color_primary the primary color of the theme
    * @param color_secondary the secondary color for the theme
    * @param flags ORed flags starting with `LV_THEME_DEF_FLAG_...`
    * @param font_small pointer to a small font
    * @param font_normal pointer to a normal font
    * @param font_subtitle pointer to a large font
    * @param font_title pointer to a extra large font
    * @return a pointer to reference this theme later
*/
lv_theme_t* FLT_theme_init(lv_color_t color_primary, lv_color_t color_secondary, uint32_t flags,
    const lv_font_t* font_small, const lv_font_t* font_normal, const lv_font_t* font_subtitle,
    const lv_font_t* font_title);


/**********************
*      MACROS
**********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*_FLT_THEME_H*/
