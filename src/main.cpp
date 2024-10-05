extern "C"
{
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}
#include <lvgl.h>
#include <WiFi.h>
#include <ArduinoOTA.h>
#include <display_driver.h>

#include "ui/ui.h"

Arduino_DataBus *bus;
Arduino_ESP32RGBPanel *panel;
Arduino_RGB_Display *gfx;
FT6X36 ts(&Wire, TOUCH_IRQ);

static lv_disp_draw_buf_t draw_buf;
static lv_color_t *buf = (lv_color_t *)heap_caps_malloc(TFT_WIDTH * 20 * sizeof(lv_color_t), MALLOC_CAP_DMA | MALLOC_CAP_INTERNAL);

lv_obj_t *roller1;
static lv_obj_t *meter;
lv_anim_t a;
lv_anim_t b;
lv_meter_indicator_t *indic3;
lv_meter_indicator_t *indic;

static lv_style_t style_btn;
lv_theme_t *th;

#if LV_USE_LOG != 0
/* Serial debugging */
void my_print(const char *buf)
{
    Serial.printf(buf);
    Serial.flush();
}
#endif

void setup()
{
    Serial.begin(115200);
    Serial.printf("Version: %d.%d.%d\n", lv_version_major(), lv_version_minor(), lv_version_patch());

    Wire.begin(TOUCH_SDA, TOUCH_SCL, I2C_TOUCH_FREQUENCY);

    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);

    init_display_driver();
    lv_init();

    lv_theme_default_init(NULL, lv_color_hex(0xFFEB3B), lv_color_hex(0xFF7043), 1, LV_FONT_DEFAULT);

#if LV_USE_LOG != 0
    lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

    // uint16_t data[8]{1020, 44, 1020, 645, 5, 44, 3, 647};
    // lcd.setTouchCalibrate(data);

    lv_disp_draw_buf_init(&draw_buf, buf, NULL, TFT_WIDTH * 20);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = TFT_WIDTH;
    disp_drv.ver_res = TFT_HEIGHT;
    disp_drv.flush_cb = flush_pixels;
    disp_drv.draw_buf = &draw_buf;
    lv_disp_drv_register(&disp_drv);

    static lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.read_cb = touchpad_read;
    lv_indev_drv_register(&indev_drv);

    ui_init();

    
    Serial.println("Setup done");
}

unsigned long timer1;
void loop()
{
    lv_timer_handler();

    ui_tick();
}