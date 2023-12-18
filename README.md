## BL Bento Box Controller

The BL Bento Box Controller is an ESP8266 based device that connects to your Bambulab X1,X1C,P1P Or P1S and controls the Bento Box strip on the state of the printer.

### Features

- Connects to Bambulab X1, X1C, P1P, or P1S
- Controls relay for use with Bento Box filter based on printer state
  
### Components

- Uses this type of ESP01S relay board commonly found on Aliexpress
  - ![](https://arduinodiy.files.wordpress.com/2018/06/wifirelay.png)
- ESP01 non S is not recommended as per this article
    - https://arduinodiy.wordpress.com/2018/07/05/simple-wifi-relay-board-3/

### Setup Instructions

- Install Platformio in VsCode with platform Espressif8266 ESP01-1M
- Head to Platformio tab
- Head to D1 project task
- Enter ESP01S into Bootloader mode before plugging in following:
  - https://makeradvisor.com/esp8266-esp-01-usb-serial-programmer/
- Build Filesystem Image and Upload Filesystem Image
- Build and Upload under General
- Head to https://dutchdevelop.com/blled-configuration-setup/ to finish setup

### License

The BLBentoController is released under Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International (CC BY-NC-SA 4.0) license. See the [LICENSE](https://github.com/Ray160/BLBentoController/blob/main/LICENSE) file for more details.

### Credits
>Ray160: Lead Programmer  
DutchDeveloper: Inspiration for foundation of the code  
xps3riments: Inspiration for foundation of the code  

### Author

This project was created by Ray160 with original code by [DutchDeveloper](https://dutchdevelop.com/).
