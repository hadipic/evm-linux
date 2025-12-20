#ifdef EVM_USE_MODULE_LVGL

#include "evm_module.h"
#include <inttypes.h>
#include "lvgl.h"
#include "../../lvgl/src/extra/libs/png/lodepng.h"

#define FILE_PATH_SIZE  128
#define MAX_CACHE_SIZE  10

// ساختار کش تصاویر
typedef struct image_cache_entry_t {
    lv_img_dsc_t *img_dsc;
    char *filename;
    uint32_t size;
    struct image_cache_entry_t *next;
} image_cache_entry_t;

static image_cache_entry_t *image_cache = NULL;
static uint32_t cache_size = 0;
static uint32_t cache_hits = 0;
static uint32_t cache_misses = 0;

// تابع برای حذف قدیمی‌ترین entry از cache
static void remove_oldest_from_cache(void);

// تابع برای اضافه کردن به cache
static void add_to_cache(const char *filename, lv_img_dsc_t *img_dsc) {
    if (cache_size >= MAX_CACHE_SIZE) {
        remove_oldest_from_cache();
    }
    
    image_cache_entry_t *entry = lv_mem_alloc(sizeof(image_cache_entry_t));
    if (!entry) return;
    
    entry->filename = lv_mem_alloc(strlen(filename) + 1);
    if (!entry->filename) {
        lv_mem_free(entry);
        return;
    }
    
    strcpy(entry->filename, filename);
    entry->img_dsc = img_dsc;
    entry->size = img_dsc->data_size + sizeof(lv_img_dsc_t);
    entry->next = image_cache;
    image_cache = entry;
    cache_size++;
    
    printf("[IMAGE_CACHE] Added to cache: %s (%" PRIu32 " bytes)\n", filename, entry->size);
}

// تابع برای حذف از cache
static void remove_from_cache(const char *filename) {
    image_cache_entry_t **ptr = &image_cache;
    
    while (*ptr) {
        image_cache_entry_t *entry = *ptr;
        if (strcmp(entry->filename, filename) == 0) {
            *ptr = entry->next;
            
            printf("[IMAGE_CACHE] Removing from cache: %s\n", filename);
            
            if (entry->img_dsc) {
                if (entry->img_dsc->data) {
                    lv_mem_free((void *)entry->img_dsc->data);
                }
                lv_mem_free(entry->img_dsc);
            }
            
            lv_mem_free(entry->filename);
            lv_mem_free(entry);
            cache_size--;
            return;
        }
        ptr = &(*ptr)->next;
    }
}

// تابع برای حذف قدیمی‌ترین entry از cache
static void remove_oldest_from_cache(void) {
    if (!image_cache) return;
    
    image_cache_entry_t **ptr = &image_cache;
    image_cache_entry_t *oldest = image_cache;
    image_cache_entry_t *prev = NULL;
    
    // پیدا کردن آخرین entry (قدیمی‌ترین)
    while (*ptr && (*ptr)->next) {
        prev = *ptr;
        ptr = &(*ptr)->next;
    }
    
    if (prev) {
        oldest = prev->next;
        prev->next = NULL;
    } else {
        oldest = image_cache;
        image_cache = NULL;
    }
    
    printf("[IMAGE_CACHE] Removing oldest from cache: %s\n", oldest->filename);
    
    if (oldest->img_dsc) {
        if (oldest->img_dsc->data) {
            lv_mem_free((void *)oldest->img_dsc->data);
        }
        lv_mem_free(oldest->img_dsc);
    }
    
    lv_mem_free(oldest->filename);
    lv_mem_free(oldest);
    cache_size--;
}

// تابع برای پیدا کردن در cache
static lv_img_dsc_t *find_in_cache(const char *filename) {
    image_cache_entry_t *entry = image_cache;
    
    while (entry) {
        if (strcmp(entry->filename, filename) == 0) {
            cache_hits++;
            printf("[IMAGE_CACHE] Cache hit: %s\n", filename);
            return entry->img_dsc;
        }
        entry = entry->next;
    }
    
    cache_misses++;
    printf("[IMAGE_CACHE] Cache miss: %s\n", filename);
    return NULL;
}

// تابع برای پاکسازی کامل cache
static void clear_image_cache_internal(void) {
    printf("[IMAGE_CACHE] Clearing image cache (%" PRIu32 " entries)...\n", cache_size);
    
    image_cache_entry_t *entry = image_cache;
    image_cache_entry_t *next;
    int count = 0;
    
    while (entry) {
        next = entry->next;
        
        if (entry->img_dsc) {
            if (entry->img_dsc->data) {
                lv_mem_free((void *)entry->img_dsc->data);
            }
            lv_mem_free(entry->img_dsc);
        }
        
        lv_mem_free(entry->filename);
        lv_mem_free(entry);
        
        count++;
        entry = next;
    }
    
    image_cache = NULL;
    cache_size = 0;
    
    printf("[IMAGE_CACHE] Cleared %d cache entries\n", count);
    printf("[IMAGE_CACHE] Cache stats - Hits: %" PRIu32 ", Misses: %" PRIu32 "\n", cache_hits, cache_misses);
}

static void convert_color_depth(uint8_t * img, uint32_t px_cnt)
{
#if LV_COLOR_DEPTH == 32
    lv_color32_t * img_argb = (lv_color32_t *)img;
    lv_color_t c;
    lv_color_t * img_c = (lv_color_t *) img;
    uint32_t i;
    for(i = 0; i < px_cnt; i++) {
        c = lv_color_make(img_argb[i].ch.red, img_argb[i].ch.green, img_argb[i].ch.blue);
        img_c[i].ch.red = c.ch.blue;
        img_c[i].ch.blue = c.ch.red;
    }
#elif LV_COLOR_DEPTH == 16
    lv_color32_t * img_argb = (lv_color32_t *)img;
    lv_color_t c;
    uint32_t i;
    for(i = 0; i < px_cnt; i++) {
        c = lv_color_make(img_argb[i].ch.blue, img_argb[i].ch.green, img_argb[i].ch.red);
        img[i * 3 + 2] = img_argb[i].ch.alpha;
        img[i * 3 + 1] = c.full >> 8;
        img[i * 3 + 0] = c.full & 0xFF;
    }
#elif LV_COLOR_DEPTH == 8
    lv_color32_t * img_argb = (lv_color32_t *)img;
    lv_color_t c;
    uint32_t i;
    for(i = 0; i < px_cnt; i++) {
        c = lv_color_make(img_argb[i].ch.red, img_argb[i].ch.green, img_argb[i].ch.blue);
        img[i * 2 + 1] = img_argb[i].ch.alpha;
        img[i * 2 + 0] = c.full;
    }
#elif LV_COLOR_DEPTH == 1
    lv_color32_t * img_argb = (lv_color32_t *)img;
    uint8_t b;
    uint32_t i;
    for(i = 0; i < px_cnt; i++) {
        b = img_argb[i].ch.red | img_argb[i].ch.green | img_argb[i].ch.blue;
        img[i * 2 + 1] = img_argb[i].ch.alpha;
        img[i * 2 + 0] = b > 128 ? 1 : 0;
    }
#endif
}

static lv_img_dsc_t *png_decode_data(const uint8_t * png_data, size_t png_data_size)
{
    if (png_data == NULL){
        return NULL;
    }
    
    unsigned error;
    unsigned char * png_decoded = NULL;
    unsigned png_width;
    unsigned png_height;

    error = lodepng_decode32(&png_decoded, &png_width, &png_height, png_data, png_data_size);

    if(error) {
        printf("[PNG_DECODE] error %u: %s\n", error, lodepng_error_text(error));
        return NULL;
    }
    
    if (png_decoded == NULL){
        return NULL;
    }
    
    convert_color_depth((uint8_t *)png_decoded, png_width * png_height);

    lv_img_dsc_t *png_dsc = lv_mem_alloc(sizeof(lv_img_dsc_t));
    if (png_dsc == NULL){
        printf("[PNG_DECODE] Failed to allocate memory for image descriptor\n");
        lv_mem_free(png_decoded);
        return NULL;
    }

    memset(png_dsc, 0, sizeof(lv_img_dsc_t));
    png_dsc->header.always_zero = 0;
    png_dsc->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;
    png_dsc->header.w = png_width;
    png_dsc->header.h = png_height;
    png_dsc->data_size = png_width * png_height * 4;
    png_dsc->data = (const uint8_t *)png_decoded;
    
    return png_dsc;
}

EVM_FUNCTION(png_decode)
{
    EVM_EPCV;
    
    if (argc < 1) {
        printf("[PNG_DECODE] png_decode requires 1 argument\n");
        return EVM_UNDEFINED;
    }
    
    char *src = evm_2_string(e, v[0]);
    if (!src) {
        printf("[PNG_DECODE] Invalid filename\n");
        return EVM_UNDEFINED;
    }
    
    char fn[FILE_PATH_SIZE];
    sprintf(fn, "S:%s", src);
    
    printf("[PNG_DECODE] Loading PNG: %s\n", fn);
    
    lv_img_dsc_t *cached_img = find_in_cache(fn);
    if (cached_img) {
        evm_string_free(e, src);
        evm_val_t result = evm_mk_invoke(e, cached_img);
        printf("[PNG_DECODE] Returning from cache\n");
        return result;
    }
    
    lv_fs_file_t file;
    lv_fs_res_t fs_res = lv_fs_open(&file, fn, LV_FS_MODE_RD);
    
    if (fs_res != LV_FS_RES_OK) {
        printf("[PNG_DECODE] Cannot open file: %s (error: %d)\n", fn, fs_res);
        evm_string_free(e, src);
        return EVM_UNDEFINED;
    }
    
    uint32_t file_size;
    lv_fs_seek(&file, 0, LV_FS_SEEK_END);
    lv_fs_tell(&file, &file_size);
    lv_fs_seek(&file, 0, LV_FS_SEEK_SET);
    
    if (file_size == 0 || file_size > 1024 * 1024) {
        printf("[PNG_DECODE] Invalid file size: %lu bytes\n", (unsigned long)file_size);
        lv_fs_close(&file);
        evm_string_free(e, src);
        return EVM_UNDEFINED;
    }
    
    printf("[PNG_DECODE] File size: %lu bytes\n", (unsigned long)file_size);
    
    unsigned char *png_data = (unsigned char*)lv_mem_alloc(file_size);
    if (!png_data) {
        printf("[PNG_DECODE] Memory allocation failed for %lu bytes\n", (unsigned long)file_size);
        lv_fs_close(&file);
        evm_string_free(e, src);
        return EVM_UNDEFINED;
    }
    
    uint32_t bytes_read;
    fs_res = lv_fs_read(&file, png_data, file_size, &bytes_read);
    lv_fs_close(&file);
    
    if (fs_res != LV_FS_RES_OK || bytes_read != file_size) {
        printf("[PNG_DECODE] Read failed: %lu of %lu bytes\n", 
               (unsigned long)bytes_read, (unsigned long)file_size);
        lv_mem_free(png_data);
        evm_string_free(e, src);
        return EVM_UNDEFINED;
    }
    
    printf("[PNG_DECODE] File read successfully, decoding PNG...\n");
    
    lv_img_dsc_t *png_dsc = png_decode_data((const uint8_t *)png_data, file_size);
    lv_mem_free(png_data);
    
    if (!png_dsc) {
        printf("[PNG_DECODE] PNG decoding failed\n");
        evm_string_free(e, src);
        return EVM_UNDEFINED;
    }
    
    printf("[PNG_DECODE] PNG decoded successfully: %dx%d pixels\n", 
           png_dsc->header.w, png_dsc->header.h);
    
    add_to_cache(fn, png_dsc);
    
    evm_val_t result = evm_mk_invoke(e, png_dsc);
    evm_string_free(e, src);
    return result;
}

EVM_FUNCTION(file_exists)
{
    EVM_EPCV;
    
    if (argc < 1) {
        return evm_mk_boolean(e, 0);
    }
    
    char *src = evm_2_string(e, v[0]);
    if (!src) {
        return evm_mk_boolean(e, 0);
    }
    
    char fn[FILE_PATH_SIZE];
    sprintf(fn, "S:%s", src);
    evm_string_free(e, src);
    
    lv_fs_file_t file;
    lv_fs_res_t res = lv_fs_open(&file, fn, LV_FS_MODE_RD);
    
    if (res == LV_FS_RES_OK) {
        lv_fs_close(&file);
        return evm_mk_boolean(e, 1);
    }
    
    return evm_mk_boolean(e, 0);
}

EVM_FUNCTION(png_destroy) {
    EVM_EPCV;
    
    if (argc < 1) {
        printf("[PNG_DESTROY] png_destroy requires 1 argument\n");
        return evm_mk_boolean(e, 0);
    }
    
    lv_img_dsc_t *png_dsc = evm_object_get_user_data(e, v[0]);
    if( !png_dsc ) {
        printf("[PNG_DESTROY] png_destroy: No image data found\n");
        return evm_mk_boolean(e, 0);
    }
    
    image_cache_entry_t *entry = image_cache;
    while (entry) {
        if (entry->img_dsc == png_dsc) {
            remove_from_cache(entry->filename);
            break;
        }
        entry = entry->next;
    }
    
    if (png_dsc->data) {
        lv_mem_free((void *)png_dsc->data);
    }
    lv_mem_free(png_dsc);
    
    evm_object_set_user_data(e, v[0], NULL);
    
    printf("[PNG_DESTROY] Image destroyed successfully\n");
    return evm_mk_boolean(e, 1);
}

// تابع EVM برای پاکسازی کش
EVM_FUNCTION(clear_image_cache) {
    EVM_EPCV;
    clear_image_cache_internal();
    return evm_mk_boolean(e, 1);
}

EVM_FUNCTION(get_cache_info) {
    EVM_EPCV;
    evm_val_t info = evm_object_create(e);
    
    evm_prop_set(e, info, "size", evm_mk_number(e, cache_size));
    evm_prop_set(e, info, "hits", evm_mk_number(e, cache_hits));
    evm_prop_set(e, info, "misses", evm_mk_number(e, cache_misses));
    evm_prop_set(e, info, "max_size", evm_mk_number(e, MAX_CACHE_SIZE));
    
    return info;
}

void evm_module_lvgl_image(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    
    evm_prop_set(e, obj, "png_decode", evm_mk_native(e, png_decode, "png_decode", 1));
    evm_prop_set(e, obj, "png_destroy", evm_mk_native(e, png_destroy, "png_destroy", 1));
    evm_prop_set(e, obj, "file_exists", evm_mk_native(e, file_exists, "file_exists", 1));
    
    evm_prop_set(e, obj, "clear_image_cache", evm_mk_native(e, clear_image_cache, "clear_image_cache", 0));
    evm_prop_set(e, obj, "get_cache_info", evm_mk_native(e, get_cache_info, "get_cache_info", 0));
    
    evm_module_add(e, "@native.image", obj);
    evm_val_free(e, obj);
}
#endif