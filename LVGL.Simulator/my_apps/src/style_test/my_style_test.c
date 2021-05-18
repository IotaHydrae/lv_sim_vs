#include "../../my_apps.h"


void my_style_test(void)
{
    static lv_style_t style;
    static lv_style_t style2;
    lv_style_init(&style);
    lv_style_init(&style2);
    //lv_style_set_size(&style, LV_STATE_DEFAULT, 100);
    lv_style_set_radius(&style, LV_STATE_DEFAULT, LV_RADIUS_CIRCLE);

    /*
    Properties of background
    bg_color        specifies the color of the background
    bg_opa          specifies opacity of the background
    bg_grad_color   specifies the color of the background's gradient
                    The color on the right or bottom is bg_grad_dir != LV_GRAD_DIR_NONE

    bg_main_stop    specifies where should the gradient start 0~255
    bg_grad_stop    specifies where should the gradient stop
    bg_grad_dir     specifies the direction of the gradient
                    Can be LV_GRAD_DIR_NONE/HOR/VER

    bg_blend_mode   set the blend mode of the background
    */
    lv_style_set_bg_opa(&style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_color(&style, LV_STATE_DEFAULT, LV_COLOR_BLUE);
    lv_style_set_bg_grad_color(&style, LV_STATE_DEFAULT, LV_COLOR_RED);
    lv_style_set_bg_grad_dir(&style, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);
    lv_style_set_bg_blend_mode(&style, LV_STATE_DEFAULT, LV_BLEND_MODE_SUBTRACTIVE);

    lv_style_set_bg_main_stop(&style, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_grad_stop(&style, LV_STATE_DEFAULT, 255);
    lv_style_set_bg_color(&style, LV_STATE_PRESSED, LV_COLOR_BLACK);

    /*
    Properties of border
    border_color        specifies the color of the border
    border_opa          specifies the opacity of the border
    border_width        set the width of the border
    border_side         specifies which sides of the border to draw.
                        Can be LV_BORDER_SIDE_NONE/LEFT/RIGHT/TOP/BOTTOM/FULL
                        ORed values are also possible

    border_post         the botder will be drawn after all children have been drawn.
    border_blend_mode   set the blend mode of the border
    */
    lv_style_set_border_color(&style, LV_STATE_DEFAULT, LV_COLOR_BLUE);
    lv_style_set_border_width(&style, LV_STATE_DEFAULT, 10);
    lv_style_set_border_opa(&style, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_border_side(&style, LV_STATE_DEFAULT, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT);

    lv_style_copy(&style2, &style);
    lv_style_set_bg_color(&style2, LV_STATE_DEFAULT, LV_COLOR_AQUA);

    /*Create an object with the new style*/
    lv_obj_t* obj = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(obj, 720, 180);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &style);
    //lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &style2);

    //lv_obj_set_style_local_bg_color(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_RED);
    lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);
}

/**
 * @brief a test for lvgl style outline
 * @param  
*/
void my_style_test2(void)
{
    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_radius(&style, LV_STATE_DEFAULT, 5);
    lv_style_set_bg_opa(&style, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_bg_color(&style, LV_STATE_DEFAULT, LV_COLOR_GRAY);

    /*
    Properties of outline
    outline_color       specifies the color of the outline
    outline_opa         specifies opacity of the outline
    outline_width       set the width of the outline
    outline_pad         set ehe space between the object and the outline
    outline_blend_mode  set the blend mode of the outline
    */
    /* Add outline */
    lv_style_set_outline_width(&style, LV_STATE_DEFAULT, 2);
    lv_style_set_outline_color(&style, LV_STATE_DEFAULT, LV_COLOR_BLUE);
    lv_style_set_outline_pad(&style, LV_STATE_DEFAULT, 8);

    lv_obj_t* obj = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &style);
    lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);
}

/**
 * @brief a test for lvgl style shadow
 * @param  
*/
void my_style_test3(void)
{
    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_radius(&style, LV_STATE_DEFAULT, 5);
    lv_style_set_bg_opa(&style, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_bg_color(&style, LV_STATE_DEFAULT, LV_COLOR_GRAY);

    /*
    Properties of shadow
    shadow_color    specifies the color of the shadow
    shadow_opa      specifies the opacity of the shadow
    shadow_width    set the width(blur size) of the outline
    shadow_ofs_x    set the an X offset for the shadow
    shadow_ofs_y    set the an Y offset for the shadow
    shadow_spread   make the shadow larger than the background
                    in every direction by this value.

    shadow_blend_mode   set the blend mode of the shadow
    */
    /* Add a shadow */
    lv_style_set_shadow_width(&style, LV_STATE_DEFAULT, 8);
    lv_style_set_shadow_color(&style, LV_STATE_DEFAULT, LV_COLOR_BLUE);
    lv_style_set_shadow_opa(&style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_shadow_ofs_x(&style, LV_STATE_DEFAULT, 10);
    lv_style_set_shadow_ofs_y(&style, LV_STATE_DEFAULT, 20);
 
    lv_obj_t* obj = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &style);
    lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);
}

/**
 * @brief a test for lvgl style pattern
 * @param
*/
void my_style_test4(void)
{
    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_radius(&style, LV_STATE_DEFAULT, 5);
    lv_style_set_bg_opa(&style, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_bg_color(&style, LV_STATE_DEFAULT, LV_COLOR_GRAY);

    /*
    Properties of pattern
    pattern_image       pointer to an lv_img_dsc_t variable, a path to an image file or a symbol
    pattern_opa         specifies opacity of the pattern.
    pattern_recolor     Mix this color to the pattern image.
                        In case of symbols(text)it will be the text color.

    pattern_recolor_opa     intensity of recoloring Default value LV_OPR_TRANSP
    pattern_repeat      true-the pattern will be repeated as a mosaic
                        false-place the pattern in the middle of the background

    pattern_blend_mode  set the blend mode of the pattern
    */

    /* Add a repeat pattern */
    lv_style_set_pattern_image(&style, LV_STATE_DEFAULT, LV_SYMBOL_WIFI);
    //lv_style_set_pattern_recolor(&style, LV_STATE_DEFAULT, LV_COLOR_RED); /* recolor */
    lv_style_set_pattern_opa(&style, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_pattern_repeat(&style, LV_STATE_DEFAULT, true); /* repeat */
    lv_style_set_pattern_repeat(&style, LV_STATE_DEFAULT, false); /* no-repeat */

    lv_obj_t* obj = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &style);
    lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);
}

/**
 * @brief a test for lvgl style value properties
 * @param
*/
void my_style_test5(void)
{
    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_radius(&style, LV_STATE_DEFAULT, 5);
    lv_style_set_bg_opa(&style, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_bg_color(&style, LV_STATE_DEFAULT, LV_COLOR_GRAY);

    /*
    value is an arbitrary text drawn to the
    background. it can be a lightweighted
    replacement of creating label objects.
    */
    /*
    Properties of value
    value_str       pointer to text to display. Only the pointer is saved
                    (Don't use local variable with lv_style_set_value_str,
                    instead use static, global or dynamically allocated data.)

    value_color     color of text
    value_opa       opacity of the text
    value_font      pointer to font of te text
    value_letter_space      letter space of the text
    value_line_space        line space of the text
    value_align     Alignment of the text
    value_ofs_x     X offset from the original position of the alignment
    value_ofs_y     Y offset from the original position of the alignment
    value_blend_mode        set the blend mode of the text
    */
    /* Test value properties here */
    lv_style_set_value_color(&style, LV_STATE_DEFAULT, LV_COLOR_BLUE);
    lv_style_set_value_opa(&style, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_value_letter_space(&style, LV_STATE_DEFAULT, 5);
    lv_style_set_value_line_space(&style, LV_STATE_DEFAULT, 0);
    lv_style_set_value_align(&style, LV_STATE_DEFAULT, LV_ALIGN_CENTER);
    lv_style_set_value_ofs_x(&style, LV_STATE_DEFAULT, 0);
    lv_style_set_value_ofs_y(&style, LV_STATE_DEFAULT, 0);

    lv_obj_t* obj = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &style);
    lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);

    /*Add a value text to the local style. This way every object can have different text*/
    lv_obj_set_style_local_value_str(obj, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, "TEXT");
}

/**
 * @brief a test for lvgl style value properties
 * @param
*/
void my_style_test6(void)
{
    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_radius(&style, LV_STATE_DEFAULT, 5);
    lv_style_set_bg_opa(&style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_color(&style, LV_STATE_DEFAULT, LV_COLOR_SILVER);
    lv_style_set_border_width(&style, LV_STATE_DEFAULT, 2);
    lv_style_set_border_color(&style, LV_STATE_DEFAULT, LV_COLOR_BLUE);

    lv_style_set_pad_top(&style, LV_STATE_DEFAULT, 10);
    lv_style_set_pad_bottom(&style, LV_STATE_DEFAULT, 10);
    lv_style_set_pad_left(&style, LV_STATE_DEFAULT, 10);
    lv_style_set_pad_right(&style, LV_STATE_DEFAULT, 10);

    /*
    Text properties
    Properties for textual object.
    text_color      color of the text
    text_opa        opacity of the text
    text_font       pointer to font of the text
    text_letter_space   letter space of the text
    text_line_space     line space of the text
    text_decor      add text decoration. Can be LV_TEXT_DECOR_NOR/UNDERLINE/STRIKETHROUGH
    text_sel_color  set color of the text selection
    text_sel_bg_color   set background color of the text selection.
    text_blend_mode     set the blend mode of the text
    */
    /* Test text properties here */
    lv_style_set_text_color(&style, LV_STATE_DEFAULT, LV_COLOR_BLUE);
    lv_style_set_text_letter_space(&style, LV_STATE_DEFAULT, 5);
    lv_style_set_text_line_space(&style, LV_STATE_DEFAULT, 20);
    lv_style_set_text_decor(&style, LV_STATE_DEFAULT, LV_TEXT_DECOR_UNDERLINE);

    lv_obj_t* obj = lv_label_create(lv_scr_act(), NULL);
    lv_obj_add_style(obj, LV_LABEL_PART_MAIN, &style);
    lv_label_set_text(obj, "Text of\n"
                            "a label.");
    lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);
    
}

/**
 * @brief a test for line properties
 * @param  
*/
void my_style_test7(void)
{
    static lv_style_t style;
    lv_style_init(&style);

    /*Properties of lines*/
    /*
    line_color      color of the line
    line_opa        opacity of the line
    line_width      width of the line
    line_dash_width width of dash. Dashing is drawn only for horizontal or vertical lines.
    line_dash_gap   gap between two dash line. Dashing is drawn only for horizontal or vertical lines.
    line_rounded    draw rounded line endings.
    line_blend_mode set the blend mode of the line.
    */
    lv_style_set_line_color(&style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_line_width(&style, LV_STATE_DEFAULT, 6);
    lv_style_set_line_rounded(&style, LV_STATE_DEFAULT, true);
#if LV_USE_LINE
    lv_obj_t* obj = lv_line_create(lv_scr_act(), NULL);
    lv_obj_add_style(obj, LV_LINE_PART_MAIN, &style);

    /*draw a check*/
    static lv_point_t p[] = { {10, 30}, {30, 50}, {100, 0} };
    lv_line_set_points(obj, p, 3);

    /*draw a rectangle*/
    static lv_point_t p2[] = { {0, 0}, {0, 50}, {50, 50}, {50, 0}, {0, 0} };
    lv_line_set_points(obj, p2, 5);

    lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);
#endif
}

/**
 * @brief a test of image properties
 * @param  
*/
void my_style_test8(void)
{
    LV_IMG_DECLARE(img_cogwheel_argb_2);
    static lv_style_t style;
    lv_style_init(&style);

    /*Initialize background and border*/
    lv_style_set_radius(&style, LV_STATE_DEFAULT, 5);
    lv_style_set_bg_color(&style, LV_STATE_DEFAULT, LV_COLOR_SILVER);
    lv_style_set_bg_opa(&style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_grad_color(&style, LV_STATE_DEFAULT, LV_COLOR_BLUE);
    lv_style_set_bg_grad_dir(&style, LV_STATE_DEFAULT, LV_GRAD_DIR_HOR);

    lv_style_set_border_width(&style, LV_STATE_DEFAULT, 2);
    lv_style_set_border_color(&style, LV_STATE_DEFAULT, LV_COLOR_ORANGE);

    lv_style_set_bg_main_stop(&style, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_grad_stop(&style, LV_STATE_DEFAULT, 255);

    /*make children objects stay away from me*/
    //lv_style_set_pad_all(&style, LV_STATE_DEFAULT, 10);

    lv_style_set_pad_top(&style, LV_STATE_DEFAULT, 10);
    lv_style_set_pad_bottom(&style, LV_STATE_DEFAULT, 10);
    lv_style_set_pad_left(&style, LV_STATE_DEFAULT, 10);
    lv_style_set_pad_right(&style, LV_STATE_DEFAULT, 10);


    /*
    Properties of image
    image_recolor       Mix the color to the pattern image
    image_recolor_opa   Intensity of recoloring
    image_opa           opacity of the image
    image_blend_mode    set the blend mode of the image
    */

    lv_style_set_image_recolor(&style, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_style_set_image_recolor_opa(&style, LV_STATE_DEFAULT, LV_OPA_50);

#if LV_USE_IMG
    lv_obj_t* obj = lv_img_create(lv_scr_act(), NULL);
    lv_obj_t* text = lv_label_create(obj, NULL);
    lv_label_set_text(text, "cogwheel_argb");
    lv_obj_align_origo(text, obj, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_obj_add_style(obj, LV_IMG_PART_MAIN, &style);
    lv_img_set_src(obj, &img_cogwheel_argb_2);

    lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);
#endif
}


/**
 * @brief a test for transition 
 * @param  
*/
void my_style_test9(void)
{
    static lv_style_t style;
    lv_style_init(&style);

    /* Initialize the baackground and border */
    lv_style_set_radius(&style, LV_STATE_DEFAULT, 5);
    lv_style_set_bg_color(&style, LV_STATE_DEFAULT, LV_COLOR_SILVER);
    lv_style_set_bg_opa(&style, LV_STATE_DEFAULT, LV_OPA_COVER);

    lv_style_set_bg_color(&style, LV_STATE_PRESSED, LV_COLOR_RED);

    lv_style_set_border_width(&style, LV_STATE_DEFAULT, 4);
    lv_style_set_border_color(&style, LV_STATE_DEFAULT, LV_COLOR_ORANGE);
    lv_style_set_border_color(&style, LV_STATE_PRESSED, LV_COLOR_YELLOW);

    /*
    Properties of transition
    transition_time         time of the transition
    transition_delay        delay before the transition
    transition_prop_1       a property on which transition should be applied.
                            Use the property name with upper case with LV_STYLE_
                            prefix, e.g. LV_STYLE_BG_COLOR

    transition_prop_2
    transition_prop_3
    transition_prop_4
    transition_prop_5
    transition_prop_6
    transition_path         an animation path for the tansition
                            (Needs to be static or global variable because only
                            its pointer is saved).
    */

    lv_style_set_transition_time(&style, LV_STATE_DEFAULT, 100);
    lv_style_set_transition_time(&style, LV_STATE_PRESSED, 100);

    lv_style_set_transition_delay(&style, LV_STATE_DEFAULT, 100);

    lv_style_set_transition_prop_1(&style, LV_STATE_DEFAULT, LV_STYLE_BG_COLOR);
    lv_style_set_transition_prop_2(&style, LV_STATE_DEFAULT, LV_STYLE_BORDER_COLOR);

    /* create a object */
    lv_obj_t* obj = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &style);
    lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);
}

/**
 * @brief a test for scale
 * @param  
*/
void my_style_test10(void)
{
    static lv_style_t style;
    lv_style_init(&style);

    lv_style_set_radius(&style, LV_STATE_DEFAULT, 5);
    lv_style_set_bg_opa(&style, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_bg_color(&style, LV_STATE_DEFAULT, LV_COLOR_SILVER);

    lv_style_set_pad_top(&style, LV_STATE_DEFAULT, 20);
    lv_style_set_pad_inner(&style, LV_STATE_DEFAULT, 20);
    lv_style_set_pad_left(&style, LV_STATE_DEFAULT, 5);
    lv_style_set_pad_right(&style, LV_STATE_DEFAULT, 5);

    /*
    Properties of scale
    scale_grad_color            in normal region make gradient to this color on te scale lines
    scale_end_color             color of the scale lines in te end region
    scale_width                 width of the scale
    scale_border_width          width of a border drawn on the outer side of the scale in the normal region
    scale_end_border_width      width of a border drawn on the outer side of the scale in the end region

    scale_end_line_width        width of a scale lines in the end region
    */
    lv_style_set_scale_end_color(&style, LV_STATE_DEFAULT, LV_COLOR_RED);
    lv_style_set_line_color(&style, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_style_set_scale_grad_color(&style, LV_STATE_DEFAULT, LV_COLOR_BLUE);
    lv_style_set_line_width(&style, LV_STATE_DEFAULT, 2);
    lv_style_set_scale_end_line_width(&style, LV_STATE_DEFAULT, 4);
    lv_style_set_scale_end_border_width(&style, LV_STATE_DEFAULT, 4);
    

    lv_obj_t* obj = lv_gauge_create(lv_scr_act(), NULL);
    lv_obj_add_style(obj, LV_GAUGE_PART_MAIN, &style);
    lv_obj_align(obj, NULL, LV_ALIGN_CENTER, 0, 0);
}
