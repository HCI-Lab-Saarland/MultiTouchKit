# Multi Touch Kit Arduino

This is a library for the Multi-Touch Kit
Designed and tested to work with Arduino Uno, MEGA2560, LilyPad(ATmega 328P)

For details on using this library see the tutorial at:
----> https://hci.cs.uni-saarland.de/multi-touch-kit/

Here you find the Arduino Code for Multi Touch Kit.
For more information on the project, visit our [website](https://hci.cs.uni-saarland.de/multi-touch-kit/)!

### Installing

Just download the zip folder and install it like described here: https://www.arduino.cc/en/Guide/Libraries ("Importing a .zip Library")

### Setup

You need to create a Serial Connection (https://www.arduino.cc/reference/en/language/functions/communication/serial/).
Create a `MultiTouchKit` object (`MultiTouchKit mtk;`), call `mtk.setup_sensor(int rx, int tx, int* muxPins, bool raw_data, int threshold);` in setup(), and then `mtk.read()` in `loop()`.

If you want the Arduino to send the raw values, set `raw_data` to `true`, if you want it to send true/false for every intersection to indicate if the value is above the given threshold, set `raw_data` to `false`.

Best is you check out the example and change the values as needed.


### Documentation

`setupSensor(int rx, int tx, int* muxPins, bool raw_data, int threshold);`
`rx` and `tx` are the number of receiver and transmission lines, `int* muxPins` are the digital pins for the multiplexer, 
`bool raw_data` determins if the arduino should send the raw values (raw_data==true) or for each point if it is touched or not (raw_data==false).
`int threshold` is the threshold for the touchrecognition, every value above the threshold will be detected as touch if raw_data==false

`read()` will send the raw values or true/false (depending on the chosen mode) for each transmittor/receiver intersection via Serial
you should call this method in `loop()`.
