# ESP32 Game Console

A retro arcade game console made using an ESP32, controlled with a PlayStation 4 controller or a mobile application, and outputs its display using VGA.
Games included: Tetris, Snake, Breakout, and Bomber.

The mobile application is made with MIT App Inventor 2:
https://appinventor.mit.edu/

VGA output uses the FabGL VGA Library by Fabrizio Di Vittorio. For more datails see:
https://github.com/fdivitto/fabgl/

PlayStation 4 input by aed3's PS4-esp32 library:
https://github.com/aed3/PS4-esp32/

This project is heavily based on Rob Cai's instructable:
https://www.instructables.com/ESP32-VGA-Arcade-Games-and-Joystick/

## Usage

1. Install the ESP32 boards on your Arduino IDE. Use this link for guidance: https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html. The project uses the `1.0.4` version.
2. Copy the contents of `libraries` folder into your `Arduino/libraries`. This project requires specific versions of FabGL and PS4-esp32, so make sure to use the versions included in the `libraries` folder.
3. Connect your ESP32 as shown in `hardware/schematic.pdf`.
4. To use a PlayStation controller, first pair the controller with this MAC address `b0:7d:64:0f:95:2c` using this tool: https://sixaxispairtool.en.lo4d.com/windows/. Then turn on the console then turn on the controller and it would connect normally. If connection issues arise, please erase the ESP32 flash memory using `esptool.py --chip esp32 erase_flash`.
5. To use your Android phone, first install `application/ControllerApp.apk` on your phone. Then turn on the console and when prompted to press the Boot button to enable application control, press it quickly. You can find the Boot button next to the ESP32's USB port. Next, open your Bluetooth settings on your phone and pair with `Game Console`. Finally, open the installed application, press `Connect to Bluetooth` and select `Game Console`.

## Images

![Image 1](images/img1.jpg)
![Image 2](images/img2.jpg)
![Image 3](images/img3.jpg)
![Image 4](images/img4.jpg)
![Image 5](images/img5.jpg)
![Image 6](images/img6.jpg)
![Image 7](images/img7.jpg)
![Image 8](images/img8.jpg)
