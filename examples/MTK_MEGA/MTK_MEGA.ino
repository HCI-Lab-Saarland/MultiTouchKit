/***************************************************
 This is a library for the Multi-Touch Kit
 Designed and tested to work with Arduino Uno, MEGA2560, LilyPad(ATmega 328P)
 Note: Please remind to disconnect AREF pin from AVCC on Lilypad
 
 For details on using this library see the tutorial at:
 ----> https://hci.cs.uni-saarland.de/multi-touch-kit/
 
 Written by Narjes Pourjafarian, Jan Dickmann, Juergen Steimle (Saarland University), 
            Anusha Withana (University of Sydney), Joe Paradiso (MIT)
 MIT license, all text above must be included in any redistribution
 ****************************************************/

 // This example shows how to use the Multi-Touch Kit library with an Arduino Mega and a 16x16 sensor
 // Connect pin 3 on the Uno and pin 9 on the Mega to the Signal pin of the multiplexer
 // Note: Please remind to disconnect AREF pin from AVCC for Lilypad

#include <MultiTouchKit.h>

//----- Multiplexer input pins (for MEGA) -----
int s0 = 48;
int s1 = 49;
int s2 = 50;
int s3 = 51;

int muxPins[4] = {s3, s2, s1, s0};

//----- Number of receiver (RX) and transmitter (TX) lines -----
int RX_num = 16;
int TX_num = 16;

//----- Receive raw capacitance data or touch up/down states -----
boolean raw_data = true;  // true: receive raw capacitance data, false: receive touch up/down states
int threshold = 30;  // Threshold for detecting touch down state (only required if raw_data = false). 
                    // Change this variable based on your sensor. (for more info. check the tutorial)

MultiTouchKit mtk;

void setup() {
  //Serial connection, make sure to use the same baud rate in the processing sketch
  Serial.begin(115200);

  //setup the Sensor
  mtk.setup_sensor(TX_num,RX_num,muxPins,raw_data,threshold);
}

void loop() {
  //Continuously writes multi-touch data to Serial.
  //Each row represents all RX values read from one TX line seperated by "," (the first value is TX ID)
  mtk.read();
}
