
/*********************
*      INCLUDES
*********************/
#include "FLT_Entry.h"
#include "FLT_theme.h"
/*********************
*      DEFINES
*********************/

/**********************
*      TYPEDEFS
**********************/

/**********************
*  STATIC PROTOTYPES
**********************/
static void theme_apply(lv_obj_t* obj, lv_theme_style_t name);

/**********************
*  STATIC VARIABLES
**********************/
static lv_theme_t theme;

static lv_style_t style_pad;
static lv_style_t style_circle;

static lv_style_t style_bg;
static lv_style_t style_box;
static lv_style_t style_box_border;
static lv_style_t style_btn;
static lv_style_t style_btn_border;
static lv_style_t style_title;
static lv_style_t style_label_white;
static lv_style_t style_back;
static lv_style_t style_icon;
static lv_style_t style_bar_indic;
static lv_style_t style_slider_knob;
static lv_style_t style_scrollbar;
static lv_style_t style_list_btn;
static lv_style_t style_ddlist_list;
static lv_style_t style_ddlist_selected;
static lv_style_t style_sw_bg;
static lv_style_t style_sw_indic;
static lv_style_t style_sw_knob;
static lv_style_t style_arc_bg;
static lv_style_t style_arc_indic;

static lv_style_t style_top_view;
static lv_style_t style_top_img;
/**********************
*      MACROS
**********************/

/**********************
*   STATIC FUNCTIONS
**********************/

/**
 * @brief initialize all style
 * @param
*/
static void basic_init(void)
{

}

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
    const lv_font_t* font_title)
{
    theme.color_primary = color_primary;
    theme.color_secondary = color_secondary;
    theme.font_small = font_small;
    theme.font_normal = font_normal;
    theme.font_subtitle = font_subtitle;
    theme.font_title = font_title;

    theme.flags = flags;

    basic_init();
    theme.apply_xcb = theme_apply;

    return &theme;
}

static void theme_apply(lv_obj_t* obj, lv_theme_style_t name)
{

}
