# Fish Companion Habit Tracker

### Table of Contents
- Write-up
- Features
- Project Components & Libraries
- Setup Guide
- Acknowledgements

---
### Write-up
> 1. *What is the creative motivation / intended use of your project.
(Why did you make it? Who do you envision using it? What do you want the audience to experience?)*

The project was intended to be a tamagotchi style habit tracker taking the form of a fun portable keychain.

It stems from a strong mix of desires:

- One is to keep track and motivate basic needs such as ensuring enough water is consumed even while busy.
- Another is to have an excuse to have something analog, something physical to play with and deviate away from everything all screens, having an input for fun in my daily carry.
- Another is the flexibility in building my own system that fits best for me. Having the freedom and control in tracking what I want can help increase how I interact with the habit tracker as I have already tried to use the habit tracker apps myself and sometimes my expectations and own systems clashes with the systems that habit tracker apps put
- Lastly, to have an offline tracker that doesn't pass off data to third-parties unconsented. This is especially true with current habit tracker apps that have constant ads and subscriptions which dissappoints the experience and motivation.

I envisioned age groups like me to be using it, especially with how keychains are used to customise our bags and personalities, but this time it even provides utility / purpose! Maybe evoke a sense of nostalgia but mostly fun.

> 2. *Describe how you implemented the project.
(What generative techniques have you used, and why? What other software tools or libraries did you use?)* 

The project uses a microcontroller, the ESP32-Wroom-32e to execute code that computes and tracks habits while also displaying relevant visuals in order. This was used to help allow the project be small and portable.

Both EEZ studio and LVGL were used for having a strong system in building embedded UIs that are lightweight, considering there isn't much storage on the ESP32.
- LVGL for its existing wide variety of systems and assets in UI such as buttons with text and margins, forms and more.
- EEZ studio itself was used to create the UI with a visual drag, drop and adjust system, giving more flexibility. It also allowed dragging code blocks and linking directly to buttons. EEZ studio also reduced most of the programming needed by creating builds that require just dragging the files, especially those that are necessary foundation code but can be offloaded, focusing more on the design

The fish visuals were hand made by myself in illustrator with simple shapes as well. It includes 3 states that aim to urge more action from an emotional animal. First sad crying fish when no habits are done, second, neutral fish when at least 1 habit is done, lastly, happy eyed fish when all habits are done, giving a sense of accomplishment.

Both the rotary encoder and round LCD screen were chosen for its unique round form factor and way of interaction. The rotary encoder was chosen not only for its unique / traditional way the input was used to select objects, but also to align with the movement of the circle when used alongside the circular screen. For example, the way the buttons sits and follow along the curve of the bottom circle connects better with the mind-muscle interaction when twisting the knob. The rotary encoder was also chosen because it has 360 free rotation, allowin it to feel less restrictive. It lastly also has a built in button so it reduces the amount of components needed and reduces the footprint since its meant to be portable and small.

As the screen was only 3cm large, minimal text must be used to ensure maximum readability while also creating less friction from reading words. Simple icons were used to represent what the buttons do such as the relevant habit icons for each button.

All images had to be compressed in EEZ studio with the RGB565A8 format and reduced in scale to reduce the amount of storage used


>3. *How successful was your project in meeting your creative aims.
(What works well? What challenges did you face? What might you change if you had more time?)*

It was successful in creating a habit tracker that reacts to the number of habits done, accepting rotating and button press input while also displaying on a circular display. It is able to utilise an existing UI system, incoporate custom flows and habits and put it together on a circular display. It was even able to store values that kept the status of what habits are done.

I would have changed alot. Find a fitting power source as from what I remember, it consumes alot of battery. Mostly due to time, I wasn't able to create a case for it, have it be more open to creating a system where the user can add their own habits, and even add a companion local web app that syncs the progress and showcases the trends


---

### Project Components & Libraries
- Physical Components:
    - ESP32-Wroom-32e
    - GC9A01 TFT LCD TFT 8-Pin 1.28" Round, 240px x 240px (https://kuriosity.sg/products/lcd-tft-1-28-round-gc9a01)
    - Rotary Encoder 20pulse rev, 5V, No built-in resistance (https://kuriosity.sg/products/rotary-encoder-20pulse-rev)

- Software:
    - EEZ Studio (GUI Builder) (https://www.envox.eu/studio/studio-introduction/)
        - LVGL with EEZ Flow configuration v9.5.0
        - Display: 240x240
        - Circular Display
        - Loaded default typeface: Montserrat

- Arduino IDE additional files
    Boards Manager:
        - esp32 by Espressif v3.3.12 (https://github.com/espressif/arduino-esp32)
    Libraries:
        - TFT_eSPI (LCD library) (https://github.com/Bodmer/TFT_eSPI)
        - lvgl by kisvegabor v9.5.0 (GUI library) (https://lvgl.io)
---

### Setup Guide
##### Arduino IDE configurations
1. Tools > Partition Scheme > Huge APP (3MB No OTA/1MB SPIFFS)
2. Board select: "ESP32-WROOM_DA Module" 
---

> If libraries are not installed, the following configurations are needed to ensure the project works as intended

##### LVGL Library configuration
**lv_conf_template.h**   
Refer to "lv_conf_template.h" instructions
Copy lv_conf_template.h to the level beside lvgl and rename as lv_conf.h

Ensure under section /* clang-format off */
set value to 1 for
"#if 1 /* Set this to "1" to enable content */"

##### TFT_eSPI Library configuration
**User_Setup.h**   
Under Section 1, ensure these lines of code are uncommented, and comment out the rest of their respective sections
1. "#define GC9A01_DRIVER"
2. "#define TFT_SDA_READ      // This option is for ESP32 ONLY, tested with ST7789 and GC9A01 display only"
3. #define TFT_WIDTH 240
4. #define TFT_HEIGHT 240

Under Section 2 with the title "For ESP32 Dev board (only tested with GC9A01 display)"
Ensure the following pins are assigned and comment out other lines:
#define TFT_MOSI 23  // Connects to display SDA
#define TFT_SCLK 18  // Connects to display SCL
#define TFT_CS    5  // Connects to display CS
#define TFT_DC    4  // Connects to display DC
#define TFT_RST  22  // Connects to display RST

**User_Setup_Select.h**   
Only "#include <User_Setup.h>" should be uncommented

---

# Acknowledgements
Guidance by Ashley Hi

UI assets by EEZ Studio Software
Typeface Montserrat default loaded by EEZ Studio Software

Icons used:  
1. <a href="https://www.flaticon.com/free-icons/breathing" title="breathing icons">Breathing icons created by HAJICON - Flaticon</a>
2. <a href="https://www.flaticon.com/free-icons/runner" title="runner icons">Runner icons created by Magnific - Flaticon</a>
3. <a href="https://www.flaticon.com/free-icons/hydration" title="hydration icons">Hydration icons created by meaicon - Flaticon</a>


- Physical Components:
    - ESP32-Wroom-32e 
    - GC9A01 TFT LCD TFT 8-Pin 1.28" Round, 240px x 240px (https://kuriosity.sg/products/lcd-tft-1-28-round-gc9a01)
    - Rotary Encoder 20pulse rev, 5V, No built-in resistance (https://kuriosity.sg/products/rotary-encoder-20pulse-rev)

- Software:
    - EEZ Studio (GUI Builder) (https://www.envox.eu/studio/studio-introduction/)
        - LVGL with EEZ Flow configuration v9.5.0
        - Display: 240x240
        - Circular Display
        - Loaded default typeface: Montserrat
        - Default UI assets by EEZ studio

- Arduino IDE additional files
    Boards Manager:
        - esp32 by Espressif v3.3.12 (https://github.com/espressif/arduino-esp32)
    Libraries:
        - TFT_eSPI (LCD library) (https://github.com/Bodmer/TFT_eSPI)
        - lvgl by kisvegabor v9.5.0 (GUI library) (https://lvgl.io)

AI assistance was used in this project.