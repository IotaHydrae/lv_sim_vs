/**
* @file vending_machine.c
*/


/*********************
*      INCLUDES
*********************/
#include "vending_machine_theme.h"

/*********************
*      DEFINES
*********************/
#define VENDING_MACHINE_ANIM_DELAY (40)
#define VENDING_MACHINE_ANIM_TIME   (150)
#define VENDING_MACHINE_ANIM_Y  (20)

#define VENDING_MACHINE_TITLE_PAD (20)

#define VENDING_MACHINE_BG_NORMAL (2 * (LV_VER_RES / 3))
#define VENDING_MACHINE_BG_SMALL  (2.5 * (LV_VER_RES / 3))

#define STUFF_LIST_LEN 256
/**********************
*      TYPEDEFS
**********************/


/**********************
* STATIC PROTOTYPES
**********************/
static void home_open(uint32_t delay);
static void store_open(uint32_t delay);
static void code_open(uint32_t delay);
static void help_open(uint32_t delay);

LV_EVENT_CB_DECLARE(store_open_event_cb);
LV_EVENT_CB_DECLARE(code_open_event_cb);
LV_EVENT_CB_DECLARE(help_open_event_cb);
LV_EVENT_CB_DECLARE(goods_handler);
LV_EVENT_CB_DECLARE(goods_pay);
LV_EVENT_CB_DECLARE(lbl_pay_info_handler);

static void show_background(void);
static lv_obj_t* add_icon(lv_obj_t* parent, const void* src_bg, const void* src_icon, const char* txt);
static lv_obj_t* add_title(const char* text);
static void vending_machine_anim_in(lv_obj_t* obj, uint32_t delay);
static void vending_machine_anim_out_all(lv_obj_t* obj, uint32_t delay);
static void set_icon_style(lv_obj_t* obj, lv_color_t color_start, lv_color_t color_end, uint8_t dir);
static lv_obj_t*
add_icon2(lv_obj_t* parent,
    lv_color_t color_start, lv_color_t color_end,
    const void* src_icon, const char* text);
static void store_anim_ready(lv_anim_t* a);
static lv_obj_t* add_loader(void (*end_cb)(lv_anim_t*));
static void loader_anim_cb(void* arc, lv_anim_value_t v);
static void Init_stuffs(void);
/**********************
* STATIC VARIABLES
**********************/
LV_IMG_DECLARE(lv_vending_machine_img_cola);
LV_IMG_DECLARE(lv_vending_machine_img_cola_150);
LV_IMG_DECLARE(lv_vending_machine_img_costa);
LV_IMG_DECLARE(lv_vending_machine_img_fenta);
LV_IMG_DECLARE(lv_vending_machine_img_jianlibao);
LV_IMG_DECLARE(lv_vending_machine_img_xuebi);
LV_IMG_DECLARE(lv_vending_machine_img_yiquan);
LV_IMG_DECLARE(lv_vending_machine_img_yiquan2);


#if 1
void* goods_img[] = {
&lv_vending_machine_img_cola,
&lv_vending_machine_img_costa,
&lv_vending_machine_img_fenta,
&lv_vending_machine_img_jianlibao,
&lv_vending_machine_img_xuebi,
&lv_vending_machine_img_yiquan
};

char* goods_name[] = {
    "可口可乐",
    "咖世家COSTA",
    "芬达橘子味汽水",
    "健力宝碳酸饮料",
    "雪碧碳酸饮料",
    "怡泉苏打水"
};

char* goods_info[] = {
    "450ml",
    "450ml",
    "330ml",
    "330ml",
    "330ml",
    "450ml",
};

float goods_price[] = {
    3,2.5,4,6,2,8
};
#endif

static lv_obj_t* pay_screen;

static lv_obj_t *bg_top;
static lv_obj_t *bg_bottom;

static lv_color_t bg_color_pre;
static lv_color_t bg_color_act;


static lv_obj_t* goods_big_img;
static lv_obj_t* goods_info_label;
static lv_obj_t* lbl_goods_number;

static uint32_t goods_count;
static uint32_t current_goods_price;

/**********************
*      MACROS
**********************/

/**********************
* GLOBAL FUNCTIONS
**********************/
void vending_machine(void)
{
    /*LV_IMG_DECLARE(lv_vending_machine_wallpaper1);
    
    lv_obj_t* wp = lv_img_create(NULL, NULL);
    lv_obj_set_size(wp, LV_HOR_RES, LV_VER_RES);
    lv_img_set_src(wp, &lv_vending_machine_wallpaper1);
    lv_scr_load(wp);*/
    
    bg_color_pre = VENDING_MACHINE_BLUE;
    bg_color_act = VENDING_MACHINE_BLUE;

    lv_theme_t* th = vending_machine_theme_init(LV_COLOR_BLACK, LV_COLOR_BLACK, 0,
        &lv_font_simhei_14, &lv_font_simhei_22,
        &lv_font_simhei_28, &lv_font_simhei_32);
    lv_theme_set_act(th);

    lv_obj_t* scr = lv_obj_create(NULL, NULL);
    lv_scr_load(scr);
    
    show_background();

    home_open(0);
}

static void show_background(void)
{
    bg_top = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_clean_style_list(bg_top, LV_OBJ_PART_MAIN);
    lv_obj_set_style_local_bg_opa(bg_top, LV_OBJ_PART_MAIN,
        LV_STATE_DEFAULT, LV_OPA_COVER);

    lv_obj_set_style_local_bg_color(bg_top, LV_OBJ_PART_MAIN,
        LV_STATE_DEFAULT, VENDING_MACHINE_GROUP2_COLOR3);
    lv_obj_set_size(bg_top, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_y(bg_top, -LV_VER_RES / 2);

    bg_bottom = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_clean_style_list(bg_bottom, LV_OBJ_PART_MAIN);

    lv_obj_set_style_local_bg_opa(bg_bottom, LV_OBJ_PART_MAIN,
        LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_obj_set_style_local_bg_color(bg_bottom, LV_OBJ_PART_MAIN,
        LV_STATE_DEFAULT, VENDING_MACHINE_GROUP2_COLOR3);

    lv_obj_set_size(bg_bottom, LV_HOR_RES, LV_VER_RES);
    lv_obj_set_y(bg_bottom, LV_VER_RES / 2);
}

/**********************
* STATIC FUNCTIONS
**********************/
static void home_open(uint32_t delay)
{
    LV_IMG_DECLARE(lv_vending_machine_wallpaper1)

    lv_obj_t* title = add_title("12:11 4月26日 周一");
    lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_RIGHT, -30, VENDING_MACHINE_TITLE_PAD);

    delay += VENDING_MACHINE_ANIM_DELAY;
    vending_machine_anim_in(title, delay);

    /*a box to add app interface*/
    lv_coord_t box_w = 720;
    lv_obj_t* box = lv_obj_create(lv_scr_act(), NULL);
    
    //lv_img_set_src(box, &lv_vending_machine_wallpaper1);
    lv_obj_set_size(box, box_w, 360);

    lv_obj_set_style_local_border_color(box, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_GRAY);
    lv_obj_set_style_local_border_width(box, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 4);
    lv_obj_set_style_local_border_opa(box, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, LV_OPA_10);
    lv_obj_set_style_local_bg_color(box, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, VENDING_MACHINE_GROUP2_COLOR2);
    lv_obj_set_style_local_bg_grad_color(box, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, VENDING_MACHINE_GROUP2_COLOR3);
    lv_obj_set_style_local_bg_main_stop(box, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 127);
    lv_obj_set_style_local_bg_grad_stop(box, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);
    lv_obj_set_style_local_bg_grad_dir(box, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, LV_GRAD_DIR_VER);
    
    lv_obj_align(box, NULL, LV_ALIGN_IN_TOP_MID, 0, 80);
    delay += VENDING_MACHINE_ANIM_DELAY;
    vending_machine_anim_in(box, delay);

    LV_IMG_DECLARE(lv_demo_printer_img_btn_bg_1);
    LV_IMG_DECLARE(lv_demo_printer_img_btn_bg_2);
    LV_IMG_DECLARE(lv_demo_printer_img_btn_bg_3);
    LV_IMG_DECLARE(lv_demo_printer_img_btn_bg_4);


    LV_IMG_DECLARE(lv_vending_machine_img_shop);
    LV_IMG_DECLARE(lv_vending_machine_img_package);
    LV_IMG_DECLARE(lv_vending_machine_img_help);
    lv_obj_t* icon;

    icon = add_icon2(box, LV_COLOR_WHITE, VENDING_MACHINE_GROUP1_COLOR5, &lv_vending_machine_img_shop, "首页");
    lv_obj_set_event_cb(icon, store_open_event_cb);
    lv_obj_align_origo(icon, NULL, LV_ALIGN_IN_LEFT_MID, 2 * (box_w - 20) / 8 + 10, 0);
    lv_obj_fade_in(icon, VENDING_MACHINE_ANIM_TIME * 2, delay + VENDING_MACHINE_ANIM_TIME + 50);

    icon = add_icon2(box, LV_COLOR_WHITE, VENDING_MACHINE_GROUP1_COLOR5, &lv_vending_machine_img_package, "取货码");
    lv_obj_align_origo(icon, NULL, LV_ALIGN_IN_LEFT_MID, 4 * (box_w - 20) / 8 + 10, 0);
    lv_obj_fade_in(icon, VENDING_MACHINE_ANIM_TIME * 2, delay + VENDING_MACHINE_ANIM_TIME + 50);

 /*   icon = add_icon(box, &lv_demo_printer_img_btn_bg_3, &lv_vending_machine_img_help, "帮助");
    lv_obj_align_origo(icon, NULL, LV_ALIGN_IN_LEFT_MID, 6 * (box_w - 20) / 8 + 10, 0);
    lv_obj_fade_in(icon, VENDING_MACHINE_ANIM_TIME * 2, delay + VENDING_MACHINE_ANIM_TIME + 50);
    */
    icon = add_icon2(box, LV_COLOR_WHITE, VENDING_MACHINE_GROUP1_COLOR5, &lv_vending_machine_img_help, "帮助");
    lv_obj_align_origo(icon, NULL, LV_ALIGN_IN_LEFT_MID, 6 * (box_w - 20) / 8 + 10, 0);
    lv_obj_fade_in(icon, VENDING_MACHINE_ANIM_TIME * 2, delay + VENDING_MACHINE_ANIM_TIME + 50);

    delay += VENDING_MACHINE_ANIM_DELAY;
    vending_machine_anim_in(box, delay);

    box = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(box, 500, 60);
    lv_obj_align(box, NULL, LV_ALIGN_IN_BOTTOM_LEFT, LV_HOR_RES / 5.5,
        -LV_HOR_RES / 40);
    lv_obj_set_style_local_value_font(box, LV_CONT_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simhei_32);
    lv_obj_set_style_local_value_str(box, LV_CONT_PART_MAIN, LV_STATE_DEFAULT,
        "取货口");

    delay += VENDING_MACHINE_ANIM_DELAY;
    vending_machine_anim_in(box, delay);
}

/*LV_EVENT_CB_DECLARE(store_open_event_cb);*/
LV_EVENT_CB_DECLARE(store_open_event_cb)
{
    if (e == LV_EVENT_CLICKED) {
        vending_machine_anim_out_all(lv_scr_act(), 0);
        uint32_t delay = 200;
        lv_obj_t* arc = add_loader(store_anim_ready);
        lv_obj_align(arc, NULL, LV_ALIGN_CENTER, 0, -40);

        lv_obj_t* txt = lv_label_create(lv_scr_act(), NULL);
        lv_label_set_text(txt, "加载中,请稍等片刻...");
        lv_theme_apply(txt, (lv_theme_style_t)VENDING_MACHINE_THEME_LABEL_WHITE);
        lv_obj_align(txt, arc, LV_ALIGN_OUT_BOTTOM_MID, 0, 60);

        vending_machine_anim_in(arc, delay);
        delay += VENDING_MACHINE_ANIM_DELAY;
        vending_machine_anim_in(txt, delay);
    }
    
}

static int atoi(char s[])
{
    int i, n;
    n = 0;

    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
    {
        n = 10 * n + s[i] - '0';
    }
    return n;
}

static void inline goods_count_handler(lv_obj_t* obj, lv_event_t event)
{
    goods_count = atoi(lv_label_get_text(lbl_goods_number));
    if (event == LV_EVENT_CLICKED || event == LV_EVENT_LONG_PRESSED_REPEAT) {
        lv_obj_t* label = lv_obj_get_child(obj, NULL);
        if (strcmp(lv_label_get_text(label), "-") == 0) {
            
            if (goods_count >= 1) {
                --goods_count;
            }
            // printf("%s %d\n", lv_label_get_text(label), goods_count);
        }
        else {
            if (goods_count < 100) {
                ++goods_count;
            }
            printf("%s %d\n", lv_label_get_text(label), goods_count);
        }
        lv_label_set_text_fmt(lbl_goods_number, "%d", goods_count);
    }
}

LV_EVENT_CB_DECLARE(lbl_pay_info_handler)
{
    if (e == LV_EVENT_CLICKED) {
        lv_coord_t start_x = lv_obj_get_x(obj);
        /*click anim for label pay info*/
        lv_anim_t anim_lbl_pay_info;
        lv_anim_init(&anim_lbl_pay_info);
        lv_anim_set_var(&anim_lbl_pay_info, obj);
        lv_anim_set_time(&anim_lbl_pay_info, 100);
        lv_anim_set_delay(&anim_lbl_pay_info, 200);
        lv_anim_set_exec_cb(&anim_lbl_pay_info, (lv_anim_exec_xcb_t)lv_obj_set_x);
        lv_anim_set_values(&anim_lbl_pay_info, start_x+10, start_x-10);
        lv_anim_start(&anim_lbl_pay_info);

        lv_anim_t anim_lbl_pay_info2;
        lv_anim_init(&anim_lbl_pay_info2);
        lv_anim_set_var(&anim_lbl_pay_info2, obj);
        lv_anim_set_time(&anim_lbl_pay_info2, 100);
        lv_anim_set_delay(&anim_lbl_pay_info2, 200);
        lv_anim_set_exec_cb(&anim_lbl_pay_info2, (lv_anim_exec_xcb_t)lv_obj_set_x);
        lv_anim_set_values(&anim_lbl_pay_info2, start_x - 10, start_x);
        lv_anim_start(&anim_lbl_pay_info2);
    }
}

LV_EVENT_CB_DECLARE(btn_pay_ok_handler)
{
    vending_machine_anim_out_all(pay_screen, 0);
    show_background();
    store_open(0);
}

LV_EVENT_CB_DECLARE(goods_pay)
{
    LV_IMG_DECLARE(lv_vending_machine_qr_code);
    char* str_pay_ok = "支付完成";
    char* str_pay_help = "支付遇到问题";
    

    if (e == LV_EVENT_CLICKED) {
        //vending_machine_anim_out_all(lv_scr_act(), 0);
        pay_screen = lv_obj_create(NULL, NULL);
        lv_obj_set_style_local_bg_color(pay_screen, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
        lv_scr_load(pay_screen);

        lv_obj_t* btn_pay_info = lv_btn_create(pay_screen, NULL);
        lv_obj_set_size(btn_pay_info, 32 * 20, 20 * 2);


        /*label info*/
        lv_obj_t* lbl_pay_info = lv_label_create(btn_pay_info, NULL);
        lv_label_set_long_mode(lbl_pay_info, LV_LABEL_LONG_SROLL_CIRC);
        lv_obj_set_size(lbl_pay_info, 32 * 20, 20 * 2);
        lv_label_set_align(lbl_pay_info, LV_LABEL_ALIGN_CENTER);
        /*local style for label pay info*/
        lv_obj_set_style_local_radius(lbl_pay_info, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 5);
        lv_obj_set_style_local_border_width(lbl_pay_info, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 3);
        lv_obj_set_style_local_border_color(lbl_pay_info, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_SILVER);
        lv_obj_set_style_local_text_color(lbl_pay_info, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, VENDING_MACHINE_LIGHT);
        lv_obj_set_style_local_text_font(lbl_pay_info, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());

        /*text for label pay info*/
        printf("%d,%d,total:%d\n", goods_count,current_goods_price,goods_count*current_goods_price);
        lv_label_set_text_fmt(lbl_pay_info, "请扫描二维码支付%d元", goods_count*current_goods_price);

        /*alignment for label pay info*/
        lv_obj_align(btn_pay_info, pay_screen, LV_ALIGN_CENTER, 0, -lv_obj_get_height(pay_screen)/2.5);

        lv_obj_set_event_cb(btn_pay_info, lbl_pay_info_handler);


        /*img qr code*/
        lv_obj_t* pay_qr_code = lv_img_create(pay_screen, NULL);
        lv_img_set_src(pay_qr_code, &lv_vending_machine_qr_code);
        lv_img_set_zoom(pay_qr_code, 128);
        lv_img_set_auto_size(pay_qr_code, true);
        lv_obj_align(pay_qr_code, pay_screen, LV_ALIGN_CENTER, 0, -50);

        /*bottom  view*/
        /*pay ok btn*/
        lv_obj_t* btn_pay_ok = lv_btn_create(pay_screen, NULL);
        lv_obj_align(btn_pay_ok, pay_screen, LV_ALIGN_CENTER, -150, 70);
        lv_obj_set_size(btn_pay_ok, 24 * sizeof(str_pay_ok), 50);
        lv_obj_set_event_cb(btn_pay_ok, btn_pay_ok_handler);
        lv_obj_t* lbl_btn_pay_ok = lv_label_create(btn_pay_ok, NULL);
        lv_label_set_text(lbl_btn_pay_ok, str_pay_ok);
        lv_label_set_long_mode(lbl_btn_pay_ok, LV_LABEL_LONG_DOT);
        lv_label_set_align(lbl_btn_pay_ok, LV_LABEL_ALIGN_CENTER);
        lv_obj_set_style_local_text_font(lbl_btn_pay_ok, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_normal());
        lv_obj_set_size(lbl_btn_pay_ok, 24 * sizeof(str_pay_ok), 50);
        lv_obj_set_style_local_text_line_space(lbl_btn_pay_ok, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 40);

        /*pay help btn*/
        lv_obj_t* btn_pay_help = lv_btn_create(pay_screen, btn_pay_ok);
        lv_obj_set_size(btn_pay_help, 24 * sizeof(str_pay_help), 50);
        lv_obj_align(btn_pay_help, btn_pay_ok, LV_ALIGN_OUT_RIGHT_MID, 50, 0);
        lv_obj_t* lbl_btn_pay_help = lv_label_create(btn_pay_help, lbl_btn_pay_ok);
        lv_obj_set_size(lbl_btn_pay_help, 24 * sizeof(str_pay_help), 50);
        lv_label_set_text(lbl_btn_pay_help, str_pay_help);
    }
}

static void goods_refresh_helper(lv_obj_t *obj)
{
    /*get obj info*/
    int i;
    char* btn_txt = lv_list_get_btn_text(obj);
    for (i = 0; i < sizeof(goods_name) / sizeof(goods_name[0]); i++)
    {
        if (strcmp(btn_txt, goods_name[i]) == 0) {
            lv_img_set_src(goods_big_img, goods_img[i]);
            break;
        }
    }
    if (lv_img_get_src(goods_big_img) == NULL) {
        lv_img_set_src(goods_big_img, &lv_vending_machine_img_cola_150);
    }
    
    //lv_img_set_auto_size(goods_big_img, true);
    lv_img_set_zoom(goods_big_img, 512);
    current_goods_price = (int)goods_price[i];
    lv_label_set_text_fmt(goods_info_label, "商品名称:\n%s\n\n更多信息:\n%s\n\n价格(元):\n%d\n",
                                            goods_name[i],
                                            goods_info[i],
                                            current_goods_price);
    
}

/**
 * @brief designed to make list radio
 * @param obj 
 * @param event 
*/
LV_EVENT_CB_DECLARE(goods_handler);
/*A event handler to make list like radio box*/
static void goods_handler(lv_obj_t* obj, lv_event_t event)
{
    /*get current btn's parent*/
    lv_obj_t* list = lv_obj_get_parent(obj);
    
    if (event == LV_EVENT_CLICKED) {

        /*get the first btn in list*/
        lv_obj_t* tmp_btn = lv_obj_get_child_back(list, NULL);

        /*for each the list*/
        for (; tmp_btn != NULL;) {
            /*pass current btn*/
            if (lv_list_get_btn_text(obj) == lv_list_get_btn_text(tmp_btn)) {
                tmp_btn = lv_obj_get_child_back(list, tmp_btn);
                continue;
            }
            /*set other btn state released*/
            lv_btn_set_state(tmp_btn, LV_BTN_STATE_RELEASED);
            tmp_btn = lv_obj_get_child_back(list, tmp_btn);
        }

        /*finally call goods refresh func*/
        goods_refresh_helper(obj);

        /*finally call refresh func for right view*/
        //goods_info_refresh_func()

    }
}

/**
 * @brief Called by store_anim_ready, show stroe page.
 * @param delay 
*/
static void store_open(uint32_t delay)
{
    LV_IMG_DECLARE(lv_vending_machine_img_wifi);
    /*create top bar*/
    lv_obj_t* box = lv_obj_create(lv_scr_act(), NULL);
    lv_theme_apply(box, VENDING_MACHINE_THEME_TOP_VIEW);
    lv_obj_set_size(box, LV_HOR_RES, LV_VER_RES / 15);
    /*create function states: wifi battery,,*/
    lv_obj_t* wifi_status = lv_img_create(box, NULL);
    lv_theme_apply(wifi_status, VENDING_MACHINE_THEME_TOP_IMAGE);
    lv_img_set_src(wifi_status, &lv_vending_machine_img_wifi);
    lv_obj_align(wifi_status, NULL, LV_ALIGN_IN_TOP_RIGHT, -10, 5);
   
    vending_machine_anim_in(box, 0);
    /* create shop block */
    box = lv_obj_create(lv_scr_act(), NULL);
    //lv_obj_clean_style_list(box, LV_OBJ_PART_MAIN);
    lv_coord_t box_w = 720;
    lv_obj_set_size(box, box_w, 360);
    lv_obj_align(box, NULL, LV_ALIGN_IN_TOP_MID, 0, 60);
    delay += VENDING_MACHINE_ANIM_DELAY;
    vending_machine_anim_in(box, delay);
    /*create shop list*/
    lv_obj_t* shop_list = lv_list_create(box, NULL);
    //lv_list_set_scroll_propagation(shop_list, true);

    lv_obj_set_size(shop_list, 340, 360);
    lv_obj_align(shop_list, box, LV_ALIGN_IN_BOTTOM_LEFT, 10, 10);


    lv_obj_t* list_btn;

    uint32_t i;
    for (i = 0; i < sizeof(goods_name) / sizeof(goods_name[0]); i++) {
        
        list_btn = lv_list_add_btn(shop_list, goods_img[i], goods_name[i]);
        lv_btn_set_checkable(list_btn, true);
        if (i == 0)lv_btn_set_state(list_btn, LV_BTN_STATE_PRESSED);
        //lv_obj_set_style_local_text_font(list_btn, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simhei_28);
        lv_obj_set_style_local_bg_color(list_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, VENDING_MACHINE_LIGHT);
        lv_obj_set_event_cb(list_btn, goods_handler);
    }

#if 0
    pstuff ptmp = head;
    while (ptmp) {
        list_btn = lv_list_add_btn(shop_list, ptmp->img_src, ptmp->name);
        lv_btn_set_checkable(list_btn, true);
        
        //lv_obj_set_style_local_text_font(list_btn, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simhei_28);
        lv_obj_set_style_local_bg_color(list_btn, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, VENDING_MACHINE_LIGHT);
        lv_obj_set_event_cb(list_btn, goods_handler);
        ptmp = ptmp->nstuff;
    }
#endif

    /* create right view */
    lv_obj_t* rview = lv_obj_create(box, NULL);
    lv_coord_t rview_wh = 340;
    //lv_obj_clean_style_list(rview, LV_OBJ_PART_MAIN);
    lv_obj_set_size(rview, rview_wh, rview_wh);

    lv_obj_align(rview, box, LV_ALIGN_IN_BOTTOM_RIGHT, -10, -10);
    lv_obj_set_style_local_bg_color(rview, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, VENDING_MACHINE_LIGHT);

    /*bigger size image of good*/
    
    goods_big_img = lv_img_create(rview, NULL);
    lv_img_set_src(goods_big_img, &lv_vending_machine_img_cola);
    lv_img_set_zoom(goods_big_img, 512);
    lv_obj_align(goods_big_img, rview, LV_ALIGN_IN_TOP_MID, -80, rview_wh/15);

    /*more infomation about current good*/
    goods_info_label = lv_label_create(rview, NULL);
    lv_label_set_long_mode(goods_info_label, LV_LABEL_LONG_CROP);
    lv_obj_set_size(goods_info_label, 150, 170);
    current_goods_price = (int)goods_price[0];
    lv_label_set_text_fmt(goods_info_label, "商品名称:\n%s\n\n更多信息:\n%s\n\n价格(元):\n%d\n",
        goods_name[0],
        goods_info[0],
        (int)goods_price[0]);
    lv_obj_align(goods_info_label, rview, LV_ALIGN_IN_TOP_MID, rview_wh/4, rview_wh /20);
    lv_obj_set_style_local_radius(goods_info_label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 10);
    lv_obj_set_style_local_border_width(goods_info_label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 3);
    lv_obj_set_style_local_border_color(goods_info_label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_set_style_local_pad_all(goods_info_label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, 10);
    lv_obj_set_style_local_text_font(goods_info_label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_small());


    /*btn -*/
    lv_obj_t* btn_down = lv_btn_create(rview, NULL);
    lv_obj_set_size(btn_down, 75, 50);
    lv_obj_align(btn_down, rview, LV_ALIGN_IN_BOTTOM_LEFT, 20, -rview_wh/4);
    lv_obj_set_event_cb(btn_down, goods_count_handler);
    lv_obj_t* lbl_btn_down = lv_label_create(btn_down, NULL);
    lv_label_set_text(lbl_btn_down, "-");
    lv_obj_set_style_local_text_font(lbl_btn_down, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());


    /*label count*/
    lbl_goods_number = lv_label_create(rview, NULL);
    lv_label_set_long_mode(lbl_goods_number, LV_LABEL_LONG_BREAK);
    lv_obj_set_size(lbl_goods_number, 100, 20);
    lv_label_set_align(lbl_goods_number, LV_LABEL_ALIGN_CENTER);
    lv_obj_align(lbl_goods_number, rview, LV_ALIGN_IN_BOTTOM_LEFT, 40+75+5, -rview_wh / 4 - 30);
    lv_obj_set_style_local_radius(lbl_goods_number, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 10);
    lv_obj_set_style_local_border_width(lbl_goods_number, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 3);
    lv_obj_set_style_local_pad_all(lbl_goods_number, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 10);
    lv_obj_set_style_local_pad_left(lbl_goods_number, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 25);
    lv_obj_set_style_local_pad_right(lbl_goods_number, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, 25);
    lv_obj_set_style_local_text_font(lbl_goods_number, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());
    lv_label_set_text(lbl_goods_number, "0");
    

    /*btn +*/
    lv_obj_t* btn_up = lv_btn_create(rview, btn_down);
    lv_obj_set_size(btn_up, 75, 50);
    lv_obj_align(btn_up, rview, LV_ALIGN_IN_BOTTOM_RIGHT, -20, -rview_wh / 4);
    lv_obj_set_event_cb(btn_up, goods_count_handler);
    lv_obj_t* lbl_btn_up = lv_label_create(btn_up, NULL);
    lv_label_set_text(lbl_btn_up, "+");
    lv_obj_set_style_local_text_font(lbl_btn_up, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_title());

    /*pay button*/
    lv_obj_t* btn_pay = lv_btn_create(rview, NULL);
    lv_obj_set_style_local_bg_color(btn_pay, LV_BTN_PART_MAIN,LV_STATE_DEFAULT ,VENDING_MACHINE_GREEN);
    lv_obj_set_style_local_bg_color(btn_pay, LV_BTN_PART_MAIN, LV_STATE_PRESSED, VENDING_MACHINE_GREEN);
    lv_obj_set_size(btn_pay, 120, 50);
    lv_obj_align(btn_pay, rview, LV_ALIGN_IN_BOTTOM_RIGHT, -rview_wh/15, -rview_wh/20);
    lv_obj_set_event_cb(btn_pay, goods_pay);

    lv_obj_t* lbl_btn_pay = lv_label_create(btn_pay, lbl_btn_down);
    lv_obj_set_style_local_text_font(lbl_btn_pay, LV_LABEL_PART_MAIN, LV_STATE_DEFAULT, lv_theme_get_font_subtitle());
    lv_label_set_text(lbl_btn_pay, "立即下单");

}

static void store_anim_ready(lv_anim_t* a)
{
    vending_machine_anim_out_all(lv_scr_act(), 0);
    store_open(0);
}

static lv_obj_t* add_loader(void (*end_cb)(lv_anim_t*))
{
    lv_obj_t* arc = lv_arc_create(lv_scr_act(), NULL);
    lv_arc_set_bg_angles(arc, 0, 0);
    lv_arc_set_start_angle(arc, 270);
    lv_obj_set_size(arc, 150, 150);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, loader_anim_cb);
    lv_anim_set_ready_cb(&a, end_cb);
    lv_anim_set_values(&a, 0, 110);
    lv_anim_set_time(&a, 200);
    lv_anim_set_var(&a, arc);
    lv_anim_start(&a);

    return arc;
}

static void loader_anim_cb(void* arc, lv_anim_value_t v)
{
    if (v > 100) v = 100;
    lv_arc_set_end_angle(arc, v * 360 / 100 + 270);

    static char buf[32];
    lv_snprintf(buf, sizeof(buf), "%d %%", v);
    lv_obj_set_style_local_value_str(arc, LV_ARC_PART_BG, LV_STATE_DEFAULT, buf);
}

static void vending_machine_anim_in(lv_obj_t* obj, uint32_t delay)
{
    if (obj != bg_top && obj != bg_bottom && obj != lv_scr_act()) {
        lv_anim_t a;
        lv_anim_init(&a);

        lv_anim_set_var(&a, obj);
        lv_anim_set_time(&a, VENDING_MACHINE_ANIM_TIME);
        lv_anim_set_delay(&a, delay);
        lv_anim_set_values(&a, lv_obj_get_y(obj) - VENDING_MACHINE_ANIM_Y,
            lv_obj_get_y(obj));
        lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);

        lv_anim_start(&a);
    }
}
static void vending_machine_anim_out_all(lv_obj_t* obj, uint32_t delay)
{
    lv_obj_t* child = lv_obj_get_child_back(obj, NULL);
    while (child) {
        if (child != bg_top && child != bg_bottom && child != lv_scr_act()) {
            lv_anim_t a;
            lv_anim_init(&a);
            lv_anim_set_var(&a, child);
            lv_anim_set_time(&a, VENDING_MACHINE_ANIM_TIME);
            lv_anim_set_delay(&a, delay);
            lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t)lv_obj_set_y);
            if (lv_obj_get_y(child) < 80) {
                lv_anim_set_values(&a, lv_obj_get_y(child),
                    lv_obj_get_y(child) - VENDING_MACHINE_ANIM_Y);
            }
            else {
                lv_anim_set_values(&a, lv_obj_get_y(child),
                    lv_obj_get_y(child) + VENDING_MACHINE_ANIM_Y);

                delay += VENDING_MACHINE_ANIM_DELAY;
            }
            lv_anim_set_ready_cb(&a, lv_obj_del_anim_ready_cb);
            lv_anim_start(&a);
        }
        child = lv_obj_get_child_back(obj, child);
    }
}

static lv_obj_t* add_icon(lv_obj_t* parent, const void* src_bg, const void* src_icon, const char* txt)
{
    lv_obj_t* bg = lv_img_create(parent, NULL);
    lv_obj_set_click(bg, true);
    lv_theme_apply(bg, (lv_theme_style_t)VENDING_MACHINE_THEME_ICON);
    lv_img_set_src(bg, src_bg);
    lv_img_set_antialias(bg, false);

    /*icon in bg*/
    lv_obj_t* icon = lv_img_create(bg, NULL);
    lv_img_set_src(icon, src_icon);
    lv_obj_set_style_local_image_recolor_opa(icon, LV_IMG_PART_MAIN,
        LV_STATE_DEFAULT, LV_OPA_0);
    lv_obj_align(icon, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -40);


    /*lv_obj_t* icon2 = lv_obj_create(bg, NULL);
    lv_img_set_src(icon2, src_icon);
    lv_obj_set_style_local_image_recolor_opa(icon2, LV_IMG_PART_MAIN,
        LV_STATE_DEFAULT, LV_OPA_0);
    lv_obj_align(icon2, NULL, LV_ALIGN_IN_TOP_RIGHT, -30, 30);*/

    /*label in bg*/
    lv_obj_t* label = lv_label_create(bg, NULL);
    lv_label_set_text(label, txt);
    //lv_obj_set_style_local_text_color(label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_style_local_text_font(label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simhei_32);
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    return bg;
}

static lv_obj_t*
add_icon2(lv_obj_t* parent,
    lv_color_t color_start, lv_color_t color_end,
    const void* src_icon, const char* text)
{
    lv_obj_t* bg = lv_obj_create(parent, NULL);
    lv_obj_set_click(bg, true);
    lv_obj_set_size(bg, 150, 150);
    set_icon_style(bg, color_start, color_end, LV_GRAD_DIR_VER);
    lv_obj_set_style_local_bg_color(bg, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color_start);
    lv_obj_set_style_local_bg_grad_color(bg, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, color_end);

    /*lv_obj_set_style_local_bg_color(bg, LV_OBJ_PART_MAIN, LV_STATE_PRESSED, color_end);
    lv_obj_set_style_local_bg_grad_color(bg, LV_OBJ_PART_MAIN, LV_STATE_PRESSED, color_start);*/

    lv_obj_t* icon = lv_img_create(bg, NULL);
    lv_img_set_src(icon, src_icon);
    lv_obj_set_style_local_image_recolor_opa(icon, LV_IMG_PART_MAIN,
        LV_STATE_DEFAULT, LV_OPA_0);
    lv_obj_align(icon, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, -20);

    lv_obj_t* label = lv_label_create(bg, NULL);
    lv_label_set_text(label, text);
    //lv_obj_set_style_local_text_color(label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    lv_obj_set_style_local_text_font(label, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, &lv_font_simhei_32);
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, 0);

    return bg;
}

static void set_icon_style(lv_obj_t* obj, lv_color_t color_start, lv_color_t color_end, uint8_t dir)
{
    static lv_style_t  style;
    lv_style_init(&style);
    lv_style_set_text_color(&style, LV_STATE_DEFAULT, VENDING_MACHINE_BLACK);

    /*border*/
    lv_style_set_radius(&style, LV_STATE_DEFAULT, 20);
    lv_style_set_border_width(&style, LV_STATE_DEFAULT, 4);
    lv_style_set_border_color(&style, LV_STATE_DEFAULT, VENDING_MACHINE_GROUP1_COLOR5);

    /*shadow*/
    lv_style_set_shadow_opa(&style, LV_STATE_DEFAULT, LV_OPA_50);
    lv_style_set_shadow_color(&style, LV_STATE_DEFAULT, VENDING_MACHINE_GROUP1_COLOR5);
    lv_style_set_shadow_width(&style, LV_STATE_DEFAULT, 10);
    lv_style_set_shadow_spread(&style, LV_STATE_DEFAULT, 5);

    /*properties for background*/
    lv_style_set_bg_opa(&style, LV_STATE_DEFAULT, LV_OPA_COVER);
    lv_style_set_bg_main_stop(&style, LV_STATE_DEFAULT, 0);
    lv_style_set_bg_grad_stop(&style, LV_STATE_DEFAULT, 255);
    lv_style_set_bg_grad_dir(&style, LV_STATE_DEFAULT, dir);

    /*make the button smaller when pressed*/
    lv_style_set_transform_height(&style, LV_STATE_PRESSED, -5);
    lv_style_set_transform_width(&style, LV_STATE_PRESSED, -5);
    static lv_anim_path_t path;
    lv_anim_path_init(&path);
    lv_anim_path_set_cb(&path, lv_anim_path_overshoot);
    lv_style_set_transition_prop_1(&style, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_HEIGHT);
    lv_style_set_transition_prop_2(&style, LV_STATE_DEFAULT, LV_STYLE_TRANSFORM_WIDTH);
    lv_style_set_transition_time(&style, LV_STATE_DEFAULT, 300);

    lv_style_set_transition_path(&style, LV_STATE_DEFAULT, &path);
    lv_obj_clean_style_list(obj, LV_OBJ_PART_MAIN);
    lv_obj_add_style(obj, LV_OBJ_PART_MAIN, &style);
}
static lv_obj_t *add_title(const char* text)
{
    lv_obj_t* title = lv_label_create(lv_scr_act(), NULL);
    lv_theme_apply(title, (lv_theme_style_t)VENDING_MACHINE_THEME_TITLE);
    lv_label_set_text(title, text);
    lv_obj_set_style_local_text_color(title, LV_OBJ_PART_MAIN, LV_STATE_DEFAULT, LV_COLOR_WHITE);
    lv_obj_align(title, NULL, LV_ALIGN_IN_TOP_RIGHT,
        0, VENDING_MACHINE_TITLE_PAD);
    return title;
}

#if 0
void Init_stuffs(void)
{
    head = (pstuff)malloc(sizeof(pstuff));
    end = head;

    void* goods_img[] = {
        &lv_vending_machine_img_cola,
        &lv_vending_machine_img_costa,
        &lv_vending_machine_img_fenta,
        &lv_vending_machine_img_jianlibao,
        &lv_vending_machine_img_xuebi,
        &lv_vending_machine_img_yiquan
    };

    char* goods_name[] = {
        "可口可乐 450ml",
        "咖世家COSTA 450ml",
        "芬达橘子味汽水 330ml",
        "健力宝碳酸饮料 330ml",
        "雪碧碳酸饮料 330ml",
        "怡泉苏打水 450ml"
    };

    const float goods_price[] = {
        3.0
        ,6.0
        ,2.5,
        3,
        2.5,
        4
    };

    
    for (int i = 0; i < sizeof(goods_name) / sizeof(goods_name[0]); i++) {
        printf("%d\n", i);
        node = (pstuff)malloc(sizeof(pstuff));
        node->id = i;
        node->img_src = goods_img[i];
        node->name = goods_name[i];
        node->price = goods_price[i];

        end->nstuff = node;
        end = node;
    }

}
#endif
