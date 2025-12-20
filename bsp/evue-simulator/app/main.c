//#define _DEFAULT_SOURCE /* needed for usleep() */
//#include <stdlib.h>
//#include <unistd.h>
//#define SDL_MAIN_HANDLED /*To fix SDL's "undefined reference to WinMain" \
//                            issue*/
//#include <SDL2/SDL.h>
//#include "lv_drivers/display/monitor.h"
//#include "lv_drivers/indev/keyboard.h"
//#include "lv_drivers/indev/mouse.h"
//#include "lv_drivers/indev/mousewheel.h"
//#include "lvgl/examples/lv_examples.h"
//#include "lvgl/lvgl.h"
//#include "evm_module.h"

//static void hal_init(void);
//static int tick_thread(void* data);

//void evm_module_init_ex(evm_t *e){

//}

//char* getdir(const char* filepath) {
//    int len = strlen(filepath);

//    int i = len - 1;
//    while(i >= 0) {
//        char c = filepath[i];
//        if (c == '/' || c == '\\') {
//            break;
//        }
//        i--;
//    }

//    if (i == -1 || (i == 1 && filepath[0] == '.')) {
//        char* filepath = malloc(256);
//        if(getcwd(filepath, 256) == NULL) {
//            return NULL;
//        }
//        return filepath;
//    }

//    char* dirname = malloc(i + 1);
//    memcpy(dirname, filepath, i);
//    dirname[i] = '\0';

//    return dirname;
//}

//char* getfilename(const char* filepath) {
//    int len = strlen(filepath);

//    int i = len - 1;
//    while(i >= 0) {
//        char c = filepath[i];
//        if (c == '/' || c == '\\') {
//            break;
//        }
//        i--;
//    }


//    char* filename = NULL;
//    if (i == -1) {
//        filename = malloc(len + 1);
//        memcpy(filename, filepath, len);
//        filename[len] = '\0';
//    } else {
//        int flen = len - i;
//        filename = (char *)malloc(flen + 1);
//        memcpy(filename, filepath + i + 1, flen);
//        filename[flen] = '\0';
//    }

//    return filename;
//}

//static char *filename;

//static void _evm_main(void *args) {
//    evm_main(filename);
//    while (1) {
//        lv_timer_handler();
//        lv_task_handler();
//        usleep(5 * 1000);
//    }
//}

//int main(int argc, char** argv) {
//    (void)argc; /*Unused*/
//    (void)argv; /*Unused*/

//    if( argc < 2) {
//        return 0;
//    }

//    char *dirname = getdir(argv[1]);
//    if (dirname == NULL) {
//        return 0;
//    }

//    filename = getfilename(argv[1]);
//    if (filename == NULL) {
//        return 0;
//    }

//    chdir(dirname);

//    /*Initialize LVGL*/
//    lv_init();

//    /*Initialize the HAL (display, input devices, tick) for LVGL*/
//    hal_init();

//     // lv_example_get_started_3();
//  //    lv_example_anim_3();

//      /* create a button with a label centered */
////    lv_obj_t *btn = lv_btn_create(lv_scr_act());
////    lv_obj_set_size(btn, 160, 60);
////    lv_obj_center(btn);

////    lv_obj_t *label = lv_label_create(btn);
////    lv_label_set_text(label, "Hello LVGL");
////    lv_obj_center(label);


//    _evm_main(filename);
//  //  return 0;


//      while (1) {
//          lv_timer_handler();
//          lv_task_handler();
//          usleep(5 * 1000);
//      }

//}



//int main1(int argc, char **argv) {
//    (void)argc; (void)argv;

//    /* در صورت استفاده از Wayland ممکن است نیاز به این باشد:
//       export SDL_VIDEODRIVER=x11
//    */

//    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
//        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
//        return 1;
//    }

//    char *dirname = getdir(argv[1]);
//    if (dirname == NULL) {
//        return 0;
//    }

//    filename = getfilename(argv[1]);
//    if (filename == NULL) {
//        return 0;
//    }

//    chdir(dirname);

//    /* LVGL init */
//    lv_init();

//    /* monitor driver (creates SDL window) */
//    monitor_init();

//    /* tick thread */
//    pthread_t tid;
//    if (pthread_create(&tid, NULL, tick_thread, NULL) != 0) {
//        fprintf(stderr, "Failed to create tick thread\n");
//        return 1;
//    }

//    /* display buffer (use smaller buffer to save RAM) */
//    static lv_color_t buf1[SDL_HOR_RES * 100];
//    static lv_disp_draw_buf_t draw_buf;
//    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, SDL_HOR_RES * 100);

//    /* register display driver */
//    static lv_disp_drv_t disp_drv;
//    lv_disp_drv_init(&disp_drv);
//    disp_drv.draw_buf = &draw_buf;
//    disp_drv.flush_cb = monitor_flush;
//    disp_drv.hor_res = SDL_HOR_RES;
//    disp_drv.ver_res = SDL_VER_RES;
//    lv_disp_drv_register(&disp_drv);

//    /* input devices: mouse, keyboard, mousewheel */
//    mouse_init();
//    static lv_indev_drv_t indev_drv;
//    lv_indev_drv_init(&indev_drv);
//    indev_drv.type = LV_INDEV_TYPE_POINTER;
//    indev_drv.read_cb = mouse_read;
//    lv_indev_drv_register(&indev_drv);

//    keyboard_init();
//    static lv_indev_drv_t kb_drv;
//    lv_indev_drv_init(&kb_drv);
//    kb_drv.type = LV_INDEV_TYPE_KEYPAD;
//    kb_drv.read_cb = keyboard_read;
//    lv_indev_drv_register(&kb_drv);

//    mousewheel_init();
//    static lv_indev_drv_t mw_drv;
//    lv_indev_drv_init(&mw_drv);
//    mw_drv.type = LV_INDEV_TYPE_ENCODER;
//    mw_drv.read_cb = mousewheel_read;
//    lv_indev_drv_register(&mw_drv);

//    /* create a button with a label centered */
//    lv_obj_t *btn = lv_btn_create(lv_scr_act());
//    lv_obj_set_size(btn, 160, 60);
//    lv_obj_center(btn);

//    lv_obj_t *label = lv_label_create(btn);
//    lv_label_set_text(label, "Hello LVGL");
//    lv_obj_center(label);

//    pthread_t evm_tid;
//    pthread_create(&evm_tid, NULL, (void*(*)(void*))_evm_main, NULL);


//    /* main loop */
//    while (1) {
//        SDL_Event e;
//        while (SDL_PollEvent(&e)) {
//            if (e.type == SDL_QUIT) {
//                SDL_Quit();
//                return 0;
//            }
//        }
//        lv_timer_handler();
//        SDL_Delay(5);
//    }

//    SDL_Quit();
//    return 0;
//}


///**********************
// *   STATIC FUNCTIONS
// **********************/
///**
// * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
// * library
// */
//static void hal_init(void) {
//    /* Use the 'monitor' driver which creates window on PC's monitor to simulate
//     * a display*/
//    monitor_init();
//    /* Tick init.
//     * You have to call 'lv_tick_inc()' in periodically to inform LittelvGL
//     * about how much time were elapsed Create an SDL thread to do this*/
//    SDL_CreateThread(tick_thread, "tick", NULL);

//    /*Create a display buffer*/
//    static lv_disp_draw_buf_t disp_buf1;
//    static lv_color_t buf1_1[SDL_HOR_RES * SDL_VER_RES];
//    static lv_color_t buf1_2[SDL_HOR_RES * SDL_VER_RES];
//    lv_disp_draw_buf_init(&disp_buf1, buf1_1, buf1_2, SDL_HOR_RES * SDL_VER_RES);

//    /*Create a display*/
//    static lv_disp_drv_t disp_drv;
//    lv_disp_drv_init(&disp_drv); /*Basic initialization*/
//    disp_drv.draw_buf = &disp_buf1;
//    disp_drv.flush_cb = monitor_flush;
//    disp_drv.hor_res = SDL_HOR_RES;
//    disp_drv.ver_res = SDL_VER_RES;
//    disp_drv.antialiasing = 1;

//    lv_disp_t* disp = lv_disp_drv_register(&disp_drv);

//    lv_group_t* g = lv_group_create();
//    lv_group_set_default(g);

//    /* Add the mouse as input device
//     * Use the 'mouse' driver which reads the PC's mouse*/
//    mouse_init();
//    static lv_indev_drv_t indev_drv_1;
//    lv_indev_drv_init(&indev_drv_1); /*Basic initialization*/
//    indev_drv_1.type = LV_INDEV_TYPE_POINTER;

//    /*This function will be called periodically (by the library) to get the
//     * mouse position and state*/
//    indev_drv_1.read_cb = mouse_read;
//    lv_indev_t* mouse_indev = lv_indev_drv_register(&indev_drv_1);

//    keyboard_init();
//    static lv_indev_drv_t indev_drv_2;
//    lv_indev_drv_init(&indev_drv_2); /*Basic initialization*/
//    indev_drv_2.type = LV_INDEV_TYPE_KEYPAD;
//    indev_drv_2.read_cb = keyboard_read;
//    lv_indev_t* kb_indev = lv_indev_drv_register(&indev_drv_2);
//    lv_indev_set_group(kb_indev, g);
//    mousewheel_init();
//    static lv_indev_drv_t indev_drv_3;
//    lv_indev_drv_init(&indev_drv_3); /*Basic initialization*/
//    indev_drv_3.type = LV_INDEV_TYPE_ENCODER;
//    indev_drv_3.read_cb = mousewheel_read;

//    lv_indev_t* enc_indev = lv_indev_drv_register(&indev_drv_3);
//    lv_indev_set_group(enc_indev, g);



//}

///**
// * A task to measure the elapsed time for LVGL
// * @param data unused
// * @return never return
// */
//static int tick_thread(void* data) {
//    (void)data;

//    while (1) {
//        SDL_Delay(5);
//        lv_tick_inc(5); /*Tell LittelvGL that 5 milliseconds were elapsed*/
//    }

//    return 0;
//}


#define _DEFAULT_SOURCE
#include <stdlib.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <unistd.h>

// استفاده از درایورهای SDL مدرن به جای درایورهای قدیمی
#include "lv_drivers/sdl/sdl.h"
#include "lvgl/lvgl.h"
#include "evm_module.h"
#include "lv_drivers/indev/mousewheel.h"
#include "lvgl/examples/lv_examples.h"
#include "lv_drivers/indev/mouse.h"
// تعریف تابع evm_module_init_ex برای رفع خطای لینک
void evm_module_init_ex(evm_t *e) {
    printf("🔧 Extended EVM modules loaded\n");
    (void)e;
}

// تعاریف مدیریت برنامه‌ها
typedef struct {
    char name[32];
    char path[256];
    char full_path[512];  // مسیر کامل برای اجرا
    char type[8];
    int size;
    bool is_running;
} evm_app_t;

static evm_app_t *apps = NULL;
static int app_count = 0;
static int selected_app = 0;
static bool app_running = false;
static evm_t *current_evm = NULL;
static bool evm_initialized = false;

// متغیرهای LVGL
static lv_obj_t *current_screen = NULL;
static lv_obj_t *launcher_screen = NULL;
static lv_obj_t *app_list = NULL;
static lv_obj_t *status_label = NULL;
static lv_obj_t *selected_label = NULL;

// تنظیمات نمایشگر
#define LCD_WIDTH   480
#define LCD_HEIGHT  320
#define LVGL_BUFFER_SIZE (LCD_WIDTH * 40)

// تابع برای فراخوانی lv_tick_inc
static int tick_thread(void* data) {
    (void)data;
    while (1) {
        SDL_Delay(5);
        lv_tick_inc(5);
    }
    return 0;
}

// ========================= توابع کمکی =========================

// تابع برای به‌روزرسانی وضعیت
static void update_status(void) {
    if (!status_label) return;

    char status[64];
    if (app_count > 0) {
        snprintf(status, sizeof(status), "App %d/%d", selected_app + 1, app_count);
    } else {
        snprintf(status, sizeof(status), "No applications");
    }
    lv_label_set_text(status_label, status);
}

// ========================= رابط کاربری لانچر =========================

static void create_launcher_ui(void) {
    printf("🎨 Creating launcher UI...\n");

    launcher_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(launcher_screen, lv_color_hex(0x1a1a2e), 0);
    lv_obj_clear_flag(launcher_screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_size(launcher_screen, LCD_WIDTH, LCD_HEIGHT);

    // هدر
    lv_obj_t *header = lv_obj_create(launcher_screen);
    lv_obj_set_size(header, LCD_WIDTH, 50);
    lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(header, lv_color_hex(0x16213e), 0);
    lv_obj_set_style_border_width(header, 0, 0);

    // عنوان لانچر
    lv_obj_t *title = lv_label_create(header);
    lv_label_set_text(title, "EVM LAUNCHER - Desktop");
    lv_obj_set_style_text_color(title, lv_color_hex(0x00ff88), 0);
    lv_obj_set_style_text_font(title, &lv_font_montserrat_16, 0);
    lv_obj_align(title, LV_ALIGN_CENTER, 0, 0);

    // کانتینر اصلی برای لیست برنامه‌ها
    lv_obj_t *main_container = lv_obj_create(launcher_screen);
    lv_obj_set_size(main_container, LCD_WIDTH - 40, 200);
    lv_obj_align(main_container, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(main_container, lv_color_hex(0x0f3460), 0);
    lv_obj_set_style_border_color(main_container, lv_color_hex(0x00ff88), 0);
    lv_obj_set_style_border_width(main_container, 2, 0);
    lv_obj_set_style_radius(main_container, 10, 0);

    // عنوان لیست
    lv_obj_t *list_title = lv_label_create(main_container);
    lv_label_set_text(list_title, "APPLICATIONS:");
    lv_obj_set_style_text_color(list_title, lv_color_hex(0x88ccff), 0);
    lv_obj_set_style_text_font(list_title, &lv_font_montserrat_14, 0);
    lv_obj_align(list_title, LV_ALIGN_TOP_LEFT, 10, 10);

    // لیست برنامه‌ها
    app_list = lv_label_create(main_container);
    lv_obj_set_width(app_list, LCD_WIDTH - 80);
    lv_obj_align(app_list, LV_ALIGN_TOP_LEFT, 15, 35);
    lv_obj_set_style_text_color(app_list, lv_color_white(), 0);
    lv_obj_set_style_text_font(app_list, &lv_font_montserrat_14, 0);

    // وضعیت انتخاب
    lv_obj_t *status_container = lv_obj_create(launcher_screen);
    lv_obj_set_size(status_container, LCD_WIDTH - 40, 30);
    lv_obj_align(status_container, LV_ALIGN_BOTTOM_MID, 0, -40);
    lv_obj_set_style_bg_color(status_container, lv_color_hex(0x16213e), 0);
    lv_obj_set_style_border_width(status_container, 0, 0);

    status_label = lv_label_create(status_container);
    lv_obj_set_style_text_color(status_label, lv_color_hex(0x50ff7f), 0);
    lv_obj_set_style_text_font(status_label, &lv_font_montserrat_12, 0);
    lv_obj_align(status_label, LV_ALIGN_CENTER, 0, 0);

    // اطلاعات برنامه انتخاب شده
    selected_label = lv_label_create(launcher_screen);
    lv_obj_set_style_text_color(selected_label, lv_color_hex(0xffd700), 0);
    lv_obj_set_style_text_font(selected_label, &lv_font_montserrat_12, 0);
    lv_obj_align(selected_label, LV_ALIGN_BOTTOM_MID, 0, -10);

    printf("✅ Launcher UI created\n");
}

// ========================= به‌روزرسانی UI =========================

static void update_launcher_ui(void) {
    if (!app_list || !status_label || !selected_label) {
        return;
    }

    // به‌روزرسانی وضعیت
    update_status();

    if (app_count > 0) {
        // به‌روزرسانی لیست برنامه‌ها
        char list_text[1024] = "";
        int pos = 0;

        // نمایش 5 برنامه در لیست
        int start = (selected_app >= 2) ? selected_app - 2 : 0;
        int end = (start + 5 < app_count) ? start + 5 : app_count;

        for (int i = start; i < end; i++) {
            if (i == selected_app) {
                snprintf(list_text + pos, sizeof(list_text) - pos, "> %s [%s] %d bytes\n",
                        apps[i].name, apps[i].type, apps[i].size);
            } else {
                snprintf(list_text + pos, sizeof(list_text) - pos, "  %s [%s] %d bytes\n",
                        apps[i].name, apps[i].type, apps[i].size);
            }
            pos = strlen(list_text);
        }

        lv_label_set_text(app_list, list_text);

        // اطلاعات برنامه انتخاب شده - با محدودیت طول
        char selected[128];
        char short_path[80];
        const char *path = apps[selected_app].path;

        // کوتاه کردن مسیر اگر طولانی است
        if (strlen(path) > 70) {
            snprintf(short_path, sizeof(short_path), "...%s", path + strlen(path) - 67);
        } else {
            strncpy(short_path, path, sizeof(short_path) - 1);
            short_path[sizeof(short_path) - 1] = '\0';
        }

        snprintf(selected, sizeof(selected), "%s - ENTER: Launch, ESC: Exit", short_path);
        lv_label_set_text(selected_label, selected);
    } else {
        lv_label_set_text(app_list, "No apps found\n\nAdd .js files to 'apps' directory");
        lv_label_set_text(selected_label, "Create 'apps' folder and add JavaScript files");
    }
}

// ========================= نمایش صفحات =========================

static void show_launcher(void) {
    if (!launcher_screen) {
        create_launcher_ui();
    }

    lv_scr_load(launcher_screen);
    current_screen = launcher_screen;
    update_launcher_ui();
    app_running = false;

    printf("🏠 Launcher shown\n");
}

static void show_app_screen(void) {
    lv_obj_t *app_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(app_screen, lv_color_hex(0x1a1a2e), 0);
    lv_obj_set_size(app_screen, LCD_WIDTH, LCD_HEIGHT);

    // هدر برنامه
    lv_obj_t *header = lv_obj_create(app_screen);
    lv_obj_set_size(header, LCD_WIDTH, 40);
    lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_bg_color(header, lv_color_hex(0x16213e), 0);
    lv_obj_set_style_border_width(header, 0, 0);

    // عنوان برنامه
    lv_obj_t *app_title = lv_label_create(header);
    if (selected_app >= 0 && selected_app < app_count) {
        char title[64];
        snprintf(title, sizeof(title), "▶ %s", apps[selected_app].name);
        lv_label_set_text(app_title, title);
    } else {
        lv_label_set_text(app_title, "▶ EVM APP");
    }
    lv_obj_set_style_text_color(app_title, lv_color_hex(0x00ff88), 0);
    lv_obj_set_style_text_font(app_title, &lv_font_montserrat_16, 0);
    lv_obj_align(app_title, LV_ALIGN_CENTER, 0, 0);

    // محتوای اصلی
    lv_obj_t *content = lv_obj_create(app_screen);
    lv_obj_set_size(content, LCD_WIDTH - 20, 200);
    lv_obj_align(content, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_bg_color(content, lv_color_hex(0x0f3460), 0);
    lv_obj_set_style_border_width(content, 1, 0);
    lv_obj_set_style_radius(content, 5, 0);

    // وضعیت اجرا
    lv_obj_t *status_icon = lv_label_create(content);
    lv_label_set_text(status_icon, LV_SYMBOL_REFRESH);
    lv_obj_set_style_text_color(status_icon, lv_color_hex(0x50ff7f), 0);
    lv_obj_set_style_text_font(status_icon, &lv_font_montserrat_20, 0);
    lv_obj_align(status_icon, LV_ALIGN_TOP_MID, 0, 20);

    lv_obj_t *status_text = lv_label_create(content);
    lv_label_set_text(status_text, "EVM Running...");
    lv_obj_set_style_text_color(status_text, lv_color_white(), 0);
    lv_obj_set_style_text_font(status_text, &lv_font_montserrat_14, 0);
    lv_obj_align(status_text, LV_ALIGN_CENTER, 0, 0);

    // کنسول خروجی
    lv_obj_t *console = lv_label_create(content);
    lv_obj_set_width(console, LCD_WIDTH - 60);
    lv_obj_align(console, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_text_color(console, lv_color_hex(0x88ccff), 0);
    lv_obj_set_style_text_font(console, &lv_font_montserrat_10, 0);
    lv_label_set_text(console, "Check console for application output...");

    // راهنما
    lv_obj_t *footer = lv_label_create(app_screen);
    lv_label_set_text(footer, "Press ESC to return to launcher");
    lv_obj_set_style_text_color(footer, lv_color_hex(0x888888), 0);
    lv_obj_set_style_text_font(footer, &lv_font_montserrat_12, 0);
    lv_obj_align(footer, LV_ALIGN_BOTTOM_MID, 0, -20);

    lv_scr_load(app_screen);
    current_screen = app_screen;

    printf("📱 App screen shown\n");
}

// ========================= اسکن برنامه‌ها =========================

static int scan_evm_apps(const char *base_path) {
    printf("🔍 Scanning for EVM applications in: %s\n", base_path);

    // آزادسازی قبلی
    if (apps) {
        free(apps);
        apps = NULL;
    }
    app_count = 0;

    // بررسی وجود دایرکتوری
    struct stat st;
    if (stat(base_path, &st) != 0) {
        printf("📁 Creating directory: %s\n", base_path);
        if (mkdir(base_path, 0755) != 0) {
            printf("❌ Failed to create directory: %s\n", base_path);
            return 0;
        }
        printf("✅ Created directory: %s\n", base_path);
        return 0;
    }

    DIR *dir = opendir(base_path);
    if (!dir) {
        printf("❌ Cannot open directory: %s\n", base_path);
        return 0;
    }

    struct dirent *entry;
    int total_files = 0;

    // شمارش فایل‌های معتبر
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            const char *ext = strrchr(entry->d_name, '.');
            if (ext && (strcasecmp(ext, ".js") == 0 ||
                       strcasecmp(ext, ".qml") == 0 ||
                       strcasecmp(ext, ".evm") == 0)) {
                total_files++;
            }
        }
    }

    if (total_files == 0) {
        closedir(dir);
        printf("📭 No EVM files found in %s\n", base_path);
        return 0;
    }

    // تخصیص حافظه
    apps = (evm_app_t *)malloc(total_files * sizeof(evm_app_t));
    if (!apps) {
        printf("❌ Failed to allocate memory for apps\n");
        closedir(dir);
        return 0;
    }

    memset(apps, 0, total_files * sizeof(evm_app_t));

    // پر کردن اطلاعات
    rewinddir(dir);
    int count = 0;

    while ((entry = readdir(dir)) != NULL && count < total_files) {
        if (entry->d_type == DT_REG) {
            const char *ext = strrchr(entry->d_name, '.');
            if (ext && (strcasecmp(ext, ".js") == 0 ||
                       strcasecmp(ext, ".qml") == 0 ||
                       strcasecmp(ext, ".evm") == 0)) {

                // مسیر نسبی برای نمایش
                snprintf(apps[count].path, sizeof(apps[count].path),
                        "%s/%s", base_path, entry->d_name);

                // مسیر کامل مطلق برای اجرا
                char cwd[512];
                if (getcwd(cwd, sizeof(cwd)) != NULL) {
                    snprintf(apps[count].full_path, sizeof(apps[count].full_path),
                            "%s/%s/%s", cwd, base_path, entry->d_name);
                } else {
                    strncpy(apps[count].full_path, apps[count].path, sizeof(apps[count].full_path) - 1);
                }

                // نام نمایشی
                char display_name[32];
                strncpy(display_name, entry->d_name, sizeof(display_name) - 1);
                char *dot = strrchr(display_name, '.');
                if (dot) *dot = '\0';

                // تبدیل به حروف بزرگ
                for (char *p = display_name; *p; p++) {
                    *p = toupper((unsigned char)*p);
                }

                strncpy(apps[count].name, display_name, sizeof(apps[count].name) - 1);

                // نوع فایل
                if (strcasecmp(ext, ".js") == 0) {
                    strcpy(apps[count].type, "JS");
                } else if (strcasecmp(ext, ".qml") == 0) {
                    strcpy(apps[count].type, "QML");
                } else {
                    strcpy(apps[count].type, "EVM");
                }

                // اندازه فایل
                struct stat file_st;
                if (stat(apps[count].full_path, &file_st) == 0) {
                    apps[count].size = file_st.st_size;
                }

                apps[count].is_running = false;

                printf("📦 Found %s app: %s (%d bytes)\n",
                       apps[count].type, apps[count].name, apps[count].size);
                printf("   Path: %s\n", apps[count].full_path);

                count++;
            }
        }
    }

    closedir(dir);
    app_count = count;

    printf("✅ Scan complete: %d applications found\n", app_count);
    return app_count;
}

// ========================= مدیریت EVM =========================

static int init_evm(void) {
    if (evm_initialized) {
        printf("✅ EVM already initialized\n");
        return 0;
    }

    printf("🚀 Initializing EVM and modules...\n");

    // ایجاد EVM
    current_evm = evm_init();
    if (!current_evm) {
        printf("❌ Failed to initialize EVM\n");
        return -1;
    }

    // مقداردهی اولیه ماژول‌ها
    evm_module_init(current_evm);

    evm_initialized = true;
    printf("✅ EVM and modules initialized successfully\n");
    return 0;
}

static void cleanup_evm(void) {
    if (current_evm) {
        printf("🧹 Cleaning up EVM...\n");

        // اجرای GC قبل از deinit
        printf("🧹 Running final garbage collection...\n");
        evm_heap_gc(current_evm);
        SDL_Delay(10);
        evm_heap_gc(current_evm);

        evm_deinit(current_evm);
        current_evm = NULL;
    }
    evm_initialized = false;
    app_running = false;
}

// ========================= مدیریت برنامه‌ها =========================

static void launch_selected_app(void) {
    if (selected_app < 0 || selected_app >= app_count) {
        printf("❌ Invalid app selection\n");
        return;
    }

    printf("🚀 Launching: %s\n", apps[selected_app].name);
    printf("📄 File: %s\n", apps[selected_app].full_path);

    // تغییر به دایرکتوری برنامه برای دسترسی به فایل‌های وابسته
    char app_dir[512];
    strncpy(app_dir, apps[selected_app].full_path, sizeof(app_dir) - 1);
    char *last_slash = strrchr(app_dir, '/');
    if (last_slash) {
        *last_slash = '\0';
        printf("📁 Changing to app directory: %s\n", app_dir);
        if (chdir(app_dir) != 0) {
            printf("⚠️ Warning: Could not change to app directory\n");
        }
    }

    // مقداردهی اولیه EVM
    if (init_evm() != 0) {
        return;
    }

    // نمایش صفحه برنامه
    show_app_screen();

    // اجرای فایل با استفاده از مسیر کامل
    printf("📝 Executing EVM script...\n");

    // فقط نام فایل را برای اجرا بفرست (چون دایرکتوری تغییر کرد)
    char *filename_only = strrchr(apps[selected_app].full_path, '/');
    if (filename_only) {
        filename_only++; // رد شدن از /
    } else {
        filename_only = apps[selected_app].full_path;
    }

    printf("🎯 Executing: %s\n", filename_only);

    int result = evm_run_file(current_evm, EVM_UNDEFINED, filename_only);

    if (result == 1) {
        app_running = true;
        apps[selected_app].is_running = true;
        printf("✅ App executed successfully\n");
        printf("⏰ Application is running in background\n");
    } else {
        printf("❌ Failed to execute app\n");
        // بازگشت به لانچر پس از 2 ثانیه
        SDL_Delay(2000);
        show_launcher();
    }
}

static void stop_current_app(void) {
    printf("💾 Stopping current app...\n");

    if (app_running) {
        printf("🛑 Stopping app execution...\n");

        app_running = false;

        // توقف تمام برنامه‌ها
        for (int i = 0; i < app_count; i++) {
            apps[i].is_running = false;
        }

        // بازگشت به دایرکتوری اصلی
        printf("📁 Returning to original directory\n");
        // اینجا می‌توانید دایرکتوری اصلی را ذخیره و بازگردانید اگر نیاز است

        show_launcher();

        printf("✅ App stopped\n");
    } else {
        printf("⚠️ No app is currently running\n");
    }
}

// ========================= مدیریت رویدادها =========================

static void handle_keyboard(SDL_Event *e) {
    if (e->type == SDL_KEYDOWN) {
        switch (e->key.keysym.sym) {
            case SDLK_UP:
                if (!app_running && app_count > 0) {
                    selected_app = (selected_app - 1 + app_count) % app_count;
                    update_launcher_ui();
                    printf("⬆️ Selected app: %d - %s\n", selected_app, apps[selected_app].name);
                }
                break;

            case SDLK_DOWN:
                if (!app_running && app_count > 0) {
                    selected_app = (selected_app + 1) % app_count;
                    update_launcher_ui();
                    printf("⬇️ Selected app: %d - %s\n", selected_app, apps[selected_app].name);
                }
                break;

            case SDLK_RETURN:
                if (!app_running && app_count > 0) {
                    launch_selected_app();
                }
                break;

            case SDLK_ESCAPE:
                if (app_running) {
                    stop_current_app();
                } else {
                    printf("👋 Exiting...\n");
                    exit(0);
                }
                break;
        }
    }
}

// ========================= تابع اصلی =========================
static void sdl_input_read(lv_indev_drv_t *indev_drv, lv_indev_data_t *data)
{
    int mx, my;
    uint32_t btn = SDL_GetMouseState(&mx, &my);

    data->point.x = mx;
    data->point.y = my;
    data->state = (btn & SDL_BUTTON_LMASK) ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;

    static int scroll = 0;
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_MOUSEWHEEL) {
            scroll += e.wheel.y * 30;
        }
    }
    data->enc_diff = scroll;
    scroll = 0;
}

static void register_input_devices(void)
{
    // موس + اسکرول
    static lv_indev_drv_t mouse_drv;
    lv_indev_drv_init(&mouse_drv);
    mouse_drv.type = LV_INDEV_TYPE_POINTER;
    mouse_drv.read_cb = sdl_input_read;
    lv_indev_drv_register(&mouse_drv);

    // کیبورد
    static lv_indev_drv_t kb_drv;
    lv_indev_drv_init(&kb_drv);
    kb_drv.type = LV_INDEV_TYPE_KEYPAD;
    kb_drv.read_cb = sdl_keyboard_read;
    lv_indev_t *kb = lv_indev_drv_register(&kb_drv);

    // گروه برای کیبورد
    static lv_group_t *g = NULL;
    if (!g) g = lv_group_create();
    lv_indev_set_group(kb, g);
    // آبجکت‌هایی که می‌خوای با کیبورد کنترل بشن رو اضافه کن
   // if (launcher_list) lv_group_add_obj(g, launcher_list);
}

//
int main(int argc, char** argv) {
    printf("=================================\n");
    printf("       EVM Launcher - Desktop\n");
    printf("=================================\n");

    // ذخیره دایرکتوری اصلی
    char original_cwd[512];
    if (getcwd(original_cwd, sizeof(original_cwd)) == NULL) {
        printf("⚠️ Warning: Could not get current working directory\n");
        original_cwd[0] = '\0';
    } else {
        printf("📁 Original directory: %s\n", original_cwd);
    }

    // تعیین مسیر برنامه‌ها
    const char *apps_path = "apps";
    if (argc > 1) {
        apps_path = argv[1];
    }

    printf("📁 Apps directory: %s\n", apps_path);

    // اسکن برنامه‌ها
    int found_apps = scan_evm_apps(apps_path);

    // مقداردهی اولیه SDL و LVGL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    // LVGL init
    lv_init();

    // استفاده از درایور SDL مدرن
    sdl_init();

    // ایجاد thread برای tick
    SDL_Thread *tick_thread_id = SDL_CreateThread(tick_thread, "tick", NULL);
    if (!tick_thread_id) {
        printf("❌ Failed to create tick thread\n");
        return 1;
    }

    // display buffer با استفاده از درایور SDL
    static lv_color_t buf1[SDL_HOR_RES * 100];
    static lv_disp_draw_buf_t draw_buf;
    lv_disp_draw_buf_init(&draw_buf, buf1, NULL, SDL_HOR_RES * 100);

    // register display driver با درایور SDL
    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &draw_buf;
    disp_drv.flush_cb = sdl_display_flush;
    disp_drv.hor_res = SDL_HOR_RES;
    disp_drv.ver_res = SDL_VER_RES;
    lv_disp_drv_register(&disp_drv);

//    // input devices با درایور SDL
//    static lv_indev_drv_t indev_drv;
//    lv_indev_drv_init(&indev_drv);
//    indev_drv.type = LV_INDEV_TYPE_POINTER;
//    indev_drv.read_cb = sdl_mouse_read;
//    lv_indev_drv_register(&indev_drv);

    // موس + اسکرول
    static lv_indev_drv_t mouse_drv;
    lv_indev_drv_init(&mouse_drv);
    mouse_drv.type = LV_INDEV_TYPE_POINTER;
    mouse_drv.read_cb = sdl_input_read;
    lv_indev_drv_register(&mouse_drv);

//        mouse_init();
//        static lv_indev_drv_t indev_drv1;
//        lv_indev_drv_init(&indev_drv1);
//        indev_drv1.type = LV_INDEV_TYPE_POINTER;
//        indev_drv1.read_cb = mouse_read;
//        lv_indev_drv_register(&indev_drv1);


//        mousewheel_init();
//        static lv_indev_drv_t mw_drv;
//        lv_indev_drv_init(&mw_drv);
//        mw_drv.type = LV_INDEV_TYPE_ENCODER;
//        mw_drv.read_cb = mousewheel_read;
//        lv_indev_drv_register(&mw_drv);

        static lv_indev_drv_t kb_drv;
        lv_indev_drv_init(&kb_drv);
        kb_drv.type = LV_INDEV_TYPE_KEYPAD;
        kb_drv.read_cb = sdl_keyboard_read;
        lv_indev_drv_register(&kb_drv);


    // نمایش لانچر
    show_launcher();

    printf("✅ EVM Launcher ready!\n");
    printf("🎮 Controls: UP/DOWN to navigate, ENTER to launch, ESC to stop/exit\n");
    printf("📱 Found %d applications\n", found_apps);

    // حلقه اصلی
    while (1) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                printf("👋 Exit requested\n");
                goto cleanup;
            }
            handle_keyboard(&e);
        }

        lv_timer_handler();
        SDL_Delay(5);
    }

cleanup:
    // پاک‌سازی
    if (apps) {
        free(apps);
        apps = NULL;
    }

    // بازگشت به دایرکتوری اصلی
    if (original_cwd[0] != '\0') {
        chdir(original_cwd);
    }

    cleanup_evm();

    SDL_Quit();
    printf("✅ Cleanup completed\n");
    return 0;
}
