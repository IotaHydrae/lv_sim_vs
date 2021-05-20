/**
* @file vending_machine_theme.h
*
*/

#ifndef _VENDING_MACHINE_THEME_H
#define _VENDING_MACHINE_THEME_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
*      INCLUDES
*********************/
#include "vending_machine.h"

/*********************
*      DEFINES
*********************/

/*Colors*/
#define VENDING_MACHINE_WHITE           lv_color_hex(0xffffff)
#define VENDING_MACHINE_LIGHT           lv_color_hex(0xf3f8fe)
#define VENDING_MACHINE_GRAY            lv_color_hex(0x8a8a8a)
#define VENDING_MACHINE_LIGHT_GRAY      lv_color_hex(0xc4c4c4)
#define VENDING_MACHINE_BLUE            lv_color_hex(0x2f3243) //006fb6
#define VENDING_MACHINE_GREEN           lv_color_hex(0x4cb242)
#define VENDING_MACHINE_RED             lv_color_hex(0xd51732)
#define VENDING_MACHINE_BLACK           lv_color_hex(0x2f3243)

        
#define VENDING_MACHINE_PALEGREEN       lv_color_hex(0x98FB98)
#define VENDING_MACHINE_LIME            lv_color_hex(0x00ff00)
#define VENDING_MACHINE_GRAY2           lv_color_hex(0xb7b9b8)

/*color group 1*/
#define VENDING_MACHINE_GROUP1_COLOR1   lv_color_make(254, 67, 101)
#define VENDING_MACHINE_GROUP1_COLOR2   lv_color_make(252, 157, 154)
#define VENDING_MACHINE_GROUP1_COLOR3   lv_color_make(249, 205, 173)
#define VENDING_MACHINE_GROUP1_COLOR4   lv_color_make(200, 200, 169)
#define VENDING_MACHINE_GROUP1_COLOR5   lv_color_make(131, 175, 155)

/*color group 2 Forest*/
#define VENDING_MACHINE_GROUP2_COLOR1   lv_color_make(254, 254, 254)
#define VENDING_MACHINE_GROUP2_COLOR2   lv_color_make(160, 191, 124)
#define VENDING_MACHINE_GROUP2_COLOR3   lv_color_make(101, 147, 74)
#define VENDING_MACHINE_GROUP2_COLOR4   lv_color_make(64, 116, 52)
#define VENDING_MACHINE_GROUP2_COLOR5   lv_color_make(3, 35, 14)

/**********************
*      TYPEDEFS
**********************/
typedef enum {
    VENDING_MACHINE_THEME_TITLE = _LV_THEME_BUILTIN_LAST,
    VENDING_MACHINE_THEME_LABEL_WHITE,
    VENDING_MACHINE_THEME_ICON,
    VENDING_MACHINE_THEME_BTN_BORDER,
    VENDING_MACHINE_THEME_BTN_CIRCLE,
    VENDING_MACHINE_THEME_BOX_BORDER,
    VENDING_MACHINE_THEME_BTN_BACK,
    VENDING_MACHINE_THEME_TOP_VIEW,
    VENDING_MACHINE_THEME_TOP_IMAGE,

}vending_machine_theme_t;

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
lv_theme_t* vending_machine_theme_init(lv_color_t color_primary, lv_color_t color_secondary, uint32_t flags,
                                    const lv_font_t* font_small, const lv_font_t* font_normal, const lv_font_t* font_subtitle,
                                    const lv_font_t* font_title);

/**********************
*      MACROS
**********************/

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*FIRST_APP_EXAMPLES_H*/
