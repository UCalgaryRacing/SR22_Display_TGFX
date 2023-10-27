This repository contains the code for the dashboard display on the SR22. For hardware we went with a STM32F7508-DK for the MCU and Display. There is an additional breakout board that attaches to the Arduino header that contains the CAN tranceiver and the step down converter. For software we used FreeRTOS as the OS and the GUI was generated using TouchGFX. The display has 3 modes: 
- Driver: this is the display that will show when the car is driving. It only shows the most relevant datafields.
- Powertrain: this screen shows all of the powertrain datafields that it recieves from the ECU.
- Suspension: This displays the suspension sensors along with GPS status.

Additionally the display also interfaces with a OEM7600 GPS reciever via UART. It uses the GPS data to calculate lap time, and it also sends the data to the data logger over CAN. 

A row of 16 Neopixel WS2812b LEDs are used as the RPM lights.



# STM32F7508-DK TBS

The default IDE is set to STM32CubeIDE, to change IDE open the STM32F7508-DK.ioc with CubeMX and select from the supported IDEs (EWARM, MDK-ARM, and STM32CubeIDE). Supports flashing of the STM32F7508-DK board directly from TouchGFX Designer using GCC and STM32CubeProgrammer. Flashing the board requires STM32CubeProgrammer which can be downloaded from the ST webpage.

This TBS is configured for 272 x 480 pixels 16bpp screen resolution.

Performance testing can be done using the GPIO pins designated with the following signals: VSYNC_FREQ  - Pin PB4(D3), RENDER_TIME - Pin PC6(D1), FRAME_RATE  - Pin PC7(D0), MCU_ACTIVE  - Pin PG6(D2). 

 
