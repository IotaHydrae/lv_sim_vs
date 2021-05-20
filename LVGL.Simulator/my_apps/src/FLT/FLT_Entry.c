#include "Applications/Applications.h"
#include "FLT_theme.h"

static lv_theme_t *current_theme;

/*Prototype*/

void FLT_showBackground(lv_color_t color);

/**
 * @brief Entrance of FLT Project, should:
 * setrnv
 * call desktop app
 * @param  
*/
void FLT_Entry(void)
{
    current_theme = FLT_theme_init(FLT_COLOR_PRIMARY, FLT_COLOR_SECONDARY, 0,
        &lv_font_simhei_14, &lv_font_simhei_22,
        &lv_font_simhei_28, &lv_font_simhei_32);
    lv_theme_set_act(current_theme);
    lv_obj_t* scr = lv_obj_create(NULL, NULL);
    lv_scr_load(scr);


    FLT_showBackground(lv_theme_get_color_primary());
}
void FLT_showBackground(lv_color_t color)
{
    lv_obj_t *bg = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_clean_style_list(bg, LV_OBJ_PART_MAIN);
    lv_obj_set_style_local_bg_opa(bg, LV_OBJ_PART_MAIN,
        LV_STATE_DEFAULT, LV_OPA_COVER);

    lv_obj_set_style_local_bg_color(bg, LV_OBJ_PART_MAIN,
        LV_STATE_DEFAULT, color);
    lv_obj_set_size(bg, LV_HOR_RES, LV_VER_RES);
}
