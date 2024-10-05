# Panlee ZX3D95CE01S EEZStudio Demo



This repo contains a ready-to-run setup and demo of using EEZ Studio's WYSIWYG LVGL UI editor, and the EEZ Flow node-based control flow system, to make a UI for the cheap and available Panlee ZX3D95CE01S-TR-V12 and similar ESP32-S3-powered home automation touchscreen panels.

It is based off this existing repo (INSERT HERE CAN'T FIND IT RN)

PlatformIO is used for dependencies and run/upload capability. The ESP32 Arduino Framework is the "OS" layer, making it easy to extend with existing Arduino libraries.

Required Arduino libraries are:

- moononournation/GFX Library for Arduino: *Sets up and controls writes to the LCD*
  
  lvgl/lvgl @ ^8.3.9: *Obviously required for the LVGL GUI*
  
  strange-v/FT6X36: *Touchscreen driver*

Currently it does not implement any communications whatsoever, so is only useful as a jumping-off point.



## Getting started

1. Install EEZ Studio from the website: https://www.envox.eu/studio/studio-introduction

2. Install PlatformIO.

3. Clone this repo.

4. On Nix, run `nix-shell` to get a set-up dependency shell with PlatformIO.

5. Open the project in EEZ Studio.
   
   1. Make your changes.
   
   2. Compile the project in EEZ Studio to output the LVGL files to the `src/ui` folder.

6. Connect your unit using USB Serial converter (make sure you're using TX0 and RX0, not TX1/RX1!)

7. In a terminal, run `platformio run -t upload`

8. Follow as the project is compiled and uploaded.



## Notes

If you use extra fonts, or other optional LVGL features, make sure you enable them in `include/lv_conf.h`, the main LVGL config file!



To implement native C++ code integration with EEZ Flow and the LVGL UI, you'll definitely want to read this article:  
[native-interface-lvgl-with-flow/README.md at master · eez-open/native-interface-lvgl-with-flow · GitHub](https://github.com/eez-open/native-interface-lvgl-with-flow/blob/master/README.md)



As always, no warranty provided.


