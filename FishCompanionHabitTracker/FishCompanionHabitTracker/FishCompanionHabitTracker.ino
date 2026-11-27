//Invoke Library
#include <TFT_eSPI.h>       //Hardware TFT LCD Library
#include <lvgl.h>           //Software GUI builder LVGL Library
#include <ui.h>             //EEZ studio export assets
#include <screens.h>        //EEZ studio index of screens

//Invoke Rotary encoder pins
#define ENC_CLK 32          //CLK ENCODER  // S1
#define ENC_DT 33           //DT ENCODER   // S2
#define ENC_SW 25           //SW encoder   // SW

lv_indev_t *encoder_indev = NULL;   //Represents encoder for LVGL 
lv_obj_t *last_screen = NULL;       //Keeps track of last screen (called in sync_encoder_to_active_screen)

TFT_eSPI tft = TFT_eSPI();  //Loads pin configuration for LCD in TFT_eSPI library > User_Setup.h
/*Reference only
#define TFT_MOSI 23         //Connects to display SDA
#define TFT_SCLK 18         //Connects to display SCL
#define TFT_CS    5         //Connects to display CS
#define TFT_DC    4         //Connects to display DC
#define TFT_RST  22         //Connects to display RST */

//Define Display Size
#define TFT_HOR_RES 240
#define TFT_VER_RES 240

//Draw screen in lower byte size (1/10)
#define DRAW_BUF_SIZE (TFT_HOR_RES * TFT_VER_RES / 10 * (LV_COLOR_DEPTH / 8))
uint32_t draw_buf[DRAW_BUF_SIZE / 4];

//Defines rotary encoder as neutral 0 (no change)
volatile int16_t enc_diff = 0;

//Checks Rotary Encoder rotation change and direction in esp32 fast internal ram (IRAM)
void IRAM_ATTR read_encoder_isr() {
    static uint8_t prev_state = 0;
    uint8_t clk = digitalRead(ENC_CLK);
    uint8_t dt  = digitalRead(ENC_DT);
    uint8_t current_state = (clk << 1) | dt;

    if (current_state != prev_state) {
        if ((prev_state == 0b00 && current_state == 0b01) ||
            (prev_state == 0b01 && current_state == 0b11) ||
            (prev_state == 0b11 && current_state == 0b10) ||
            (prev_state == 0b10 && current_state == 0b00)) {
            enc_diff++; //adds count, rotated clockwise
        } else if ((prev_state == 0b00 && current_state == 0b10) ||
                   (prev_state == 0b10 && current_state == 0b11) ||
                   (prev_state == 0b11 && current_state == 0b01) ||
                   (prev_state == 0b01 && current_state == 0b00)) {
            enc_diff--; //minus count, rotated counter-clockwise
        }
        prev_state = current_state; //Updates state
    }
}

//Sends data from LVGL to TFT_eSPI (data to physical screen)
void my_disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map) {
    uint32_t w = lv_area_get_width(area);
    uint32_t h = lv_area_get_height(area);

    tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
    tft.pushColors((uint16_t *)px_map, w * h, true);
    tft.endWrite();

    lv_display_flush_ready(disp); //allows safe overwriting
}

//Rotary encoder handover for LVGL
void my_encoder_read(lv_indev_t *encoder_indev, lv_indev_data_t *data) {
    data->enc_diff = enc_diff;      //Rotary encoder turn, handover from read_encoder_isr to LVGL
    enc_diff = 0;                   //Prevents double count in turn

    //Checks whether rotary encoder is pressed
    if (digitalRead(ENC_SW) == LOW) {
        data->state = LV_INDEV_STATE_PRESSED;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

//Arduino's millis as main tick (time tracker)
static uint32_t my_tick(void) {
    return millis();
}

//Ensure screens are actively registered to list
void sync_encoder_to_active_screen() {
    lv_obj_t *act_scr = lv_screen_active();
    if (act_scr == last_screen) return;
    last_screen = act_scr;

    lv_group_t *target_group = NULL;

    //Loads specific btns when specific pages are on view
    if (act_scr == objects.home) {
        target_group = groups.HomeWidgets;

    } else if (act_scr == objects.hydrate) {
        target_group = groups.HydrateWidgets;
        lv_group_focus_obj(objects.hydratebtn);

    } else if (act_scr == objects.breathwork_time) {
        target_group = groups.BreathworkTimeWidgets;
        lv_group_focus_obj(objects.breathtime);
        
    } else if (act_scr == objects.breathwork_start) {
        target_group = groups.BreathworkStartWidgets;

    } else if (act_scr == objects.breathwork_finish) {
        target_group = groups.BreathworkFinishWidgets;

    } else if (act_scr == objects.run) {
        target_group = groups.RunWidget;
        lv_group_focus_obj(objects.runbtn);
    }

    //Condition to check if no screens are targetted
    if (target_group != NULL && encoder_indev != NULL) {
        lv_indev_set_group(encoder_indev, target_group);
        lv_group_set_editing(target_group, false);              //Clear any previous targetted buttons
        
        //Focus on respective assigned button when new screen shows
        lv_obj_t *focused = lv_group_get_focused(target_group);
        if (focused != NULL) {
            lv_group_focus_obj(focused);
        }
    }
}

void setup() {
    //Start Rotary Encoder GPIO pins (Internal resistors to prevent rotary encoder from being overloaded)
    pinMode(ENC_CLK, INPUT_PULLUP); //pin 32 //S1
    pinMode(ENC_DT, INPUT_PULLUP);  //pin 33 //S2
    pinMode(ENC_SW, INPUT_PULLUP);  //pin 25 //SW
    attachInterrupt(digitalPinToInterrupt(ENC_CLK), read_encoder_isr, CHANGE);
    attachInterrupt(digitalPinToInterrupt(ENC_DT), read_encoder_isr, CHANGE);

    //Start TFT_eSPI hardware
    tft.begin();
    tft.setRotation(0);         //ensure no rotation of screen

    //Start LVGL
    lv_init();
    lv_tick_set_cb(my_tick);    //uses arduino's millis

    //Create LVGL Display
    lv_display_t *disp = lv_display_create(TFT_HOR_RES, TFT_VER_RES);
    lv_display_set_flush_cb(disp, my_disp_flush);
    lv_display_set_buffers(disp, draw_buf, NULL, sizeof(draw_buf), LV_DISPLAY_RENDER_MODE_PARTIAL);

    //Create LVGL Rotary Encoder Input Device
    encoder_indev = lv_indev_create();                          //Register new input slot for LVGL
    lv_indev_set_type(encoder_indev, LV_INDEV_TYPE_ENCODER);    //Defines new input as rotary encoder
    lv_indev_set_read_cb(encoder_indev, my_encoder_read);       //Links function my_encoder_read to how it detects changes

    // Start EEZ Studio UI
    ui_init();
}

void loop() {
    lv_timer_handler();                 //Ensures LVGL runs continuously
    ui_tick();                          //Allows EEZ to run flows
    delay(5);                           //Provide 5 ms delay 
    sync_encoder_to_active_screen();    //Checks and ensures active screen is always updated

}
