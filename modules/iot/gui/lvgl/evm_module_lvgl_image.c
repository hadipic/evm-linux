#ifdef CONFIG_EVM_MODULE_LVGL

#include "evm_module.h"
#include "lodepng.h"
#include "lvgl.h"

#define FILE_PATH_SIZE  128

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
    uint32_t error;                 /*For the return values of png decoder functions*/
    /*Decode the PNG image*/
    unsigned char * png_decoded;    /*Will be pointer to the decoded image*/
    uint32_t png_width;             /*Will be the width of the decoded image*/
    uint32_t png_height;            /*Will be the width of the decoded image*/

    /*Decode the loaded image in ARGB8888 */
    error = lodepng_decode32((unsigned char**)&png_decoded,&png_width, &png_height, png_data, png_data_size);

    if(error) {
        printf("error %u: %s\n", error, lodepng_error_text(error));
        return NULL;
    }
    if (png_decoded == NULL){
        return NULL;
    }
    convert_color_depth((uint8_t *)png_decoded, png_width * png_height);

    lv_img_dsc_t *png_dsc = lv_mem_alloc(sizeof(lv_img_dsc_t));

    if (png_dsc == NULL){
        lv_mem_free(png_decoded);
        return NULL;
    }

    memset(png_dsc, 0, sizeof(lv_img_dsc_t));
    png_dsc->header.always_zero = 0;                          /*It must be zero*/
    png_dsc->header.cf = LV_IMG_CF_TRUE_COLOR_ALPHA;//;      /*LV_IMG_CF_RAW_ALPHA;//Set the color format*/
    png_dsc->header.w = png_width;
    png_dsc->header.h = png_height;
    png_dsc->data_size =png_width * png_height * 4;
    png_dsc->data = (const uint8_t *)png_decoded;
    return png_dsc;
}

static evm_val_t png_decode(evm_t *e, evm_val_t p, int argc, evm_val_t *v)
{
    uint32_t error;                 /*For the return values of png decoder functions*/
    const char *src = evm_2_string(e, v[0]);
#if LV_PNG_USE_LV_FILESYSTEM
    char fn[FILE_PATH_SIZE];
    sprintf(fn, "C:%s", src);
#else
    char fn[FILE_PATH_SIZE];
    sprintf(fn, "%s", src);
#endif
    /*Load the PNG file into buffer. It's still compressed (not decoded)*/
    unsigned char * png_data;      /*Pointer to the loaded data. Same as the original file just loaded into the RAM*/
    size_t png_data_size;          /*Size of `png_data` in bytes "C:/audio_calibration_record_file"*/

    error = lodepng_load_file(&png_data, &png_data_size, fn);//"C:/png_decoder_test.png");   /*Load the file*/
    if(error) {
        printf("error %u: %s\n", error, lodepng_error_text(error));
        return EVM_UNDEFINED;
    }

    lv_img_dsc_t *png_dsc = png_decode_data((const uint8_t *)png_data, png_data_size);
    if (png_data){
        lv_mem_free(png_data);
    }

    evm_val_t res = evm_object_create_user_data(e, png_dsc);
    return res;
}

static evm_val_t png_destroy(evm_t *e, evm_val_t p, int argc, evm_val_t *v) {
    lv_img_dsc_t *png_dsc = evm_object_get_user_data(e, v[0]);
    if( !png_dsc )
        return evm_mk_boolean(e, 0);
    evm_free((void *)png_dsc->data);
    evm_free(png_dsc);
    evm_object_set_user_data(e, v[0], NULL);
    return evm_mk_boolean(e, 1);
}

void evm_module_lvgl_image(evm_t *e) {
    evm_val_t obj = evm_object_create(e);
    evm_prop_set(e, obj, "png_decode", evm_mk_native(e, png_decode, "png_decode", 1));
    evm_prop_set(e, obj, "png_destroy", evm_mk_native(e, png_destroy, "png_destroy", 1));
    evm_module_add(e, "image", obj);
}
#endif
