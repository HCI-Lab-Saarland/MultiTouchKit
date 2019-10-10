# Multi Touch Kit Arduino Library

This is an Arduino library for Multi Touch Kit.
For more information on the project and tutorial, visit our [website](https://hci.cs.uni-saarland.de/multi-touch-kit/)!

### Installing

Download the library as a zip folder and install it as described here: 
https://www.arduino.cc/en/Guide/Libraries ("Importing a .zip Library")

### Setup

At first make the Serial Connection (https://www.arduino.cc/reference/en/language/functions/communication/serial/).

Then, add the `MultiTouchKit` object (`MultiTouchKit mtk;`),

call `mtk.setup_sensor(int rx, int tx, int* muxPins, bool raw_data, int threshold);` in setup(),

and then `mtk.read()` in `loop()`.

If you want the Arduino to send the raw values, set `raw_data` to `true`, if you want it to send true/false for every intersection to indicate if the value is above the given threshold, set `raw_data` to `false`.


### Documentation

`setupSensor(int rx, int tx, int* muxPins, bool raw_data, int threshold);`

`rx` and `tx` define the number of receiver and transmitter lines,

`int* muxPins` defines the digital pins for the multiplexer,

`bool raw_data` determins to send the raw values (raw_data==true) or touch up/down events (raw_data==false).

`int threshold` is the threshold for the touch recognition, every value above the threshold will be detected as touch if :raw_data==false

`read()` function will send the raw values or true/false (depending on the selected mode) for each intersection via Serial port.

The output of `read()` function will be lines of integer values, seperated by commas when 'raw_values = true'. The first number of each line is the number of the activated TX line and the following numbers are the values measured at the RX lines, starting at R0.
