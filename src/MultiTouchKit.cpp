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


#include "MultiTouchKit.h"

MultiTouchKit::MultiTouchKit(void){
}

/**
*   @brief  Setup the sensor
*
*   @return void
*/
void MultiTouchKit::setup_sensor(int rx, int tx, int* muxPins, bool raw_data, int threshold){
    this->_numRx = rx;
    this->_numTx = tx;
    this->_muxPins = muxPins;
    this->_raw_data = raw_data;
    this->_threshold = threshold;


    // set the PWM values
    setupPWM();

    // Set mulptiplexer
    for (int k = 0; k <= this->_numTx; k++)
    {
        pinMode(this->_muxPins[k], OUTPUT);
    }

    pinMode(A0, INPUT); // this is a workaround for a bug

//     Save noise values in case of raw_data == False
    if(this->_raw_data == false){
        for (int ii=0; ii < 10; ii++){
            for (int i=0; i < this->_numTx; i++){
                selectChannelOut(i);
                // Read RX
                for (int j=0; j < this->_numRx; j++){
                     this->noise[i][j] = analogRead(j);
                }
            }
        }
    }
}

/**
*   @brief  Read multi-touch data from sensor and write it to Serial
*
*   @return void
*/
void MultiTouchKit::read(){
    if (Serial){
        if(_raw_data == true){
            for (int i=0; i < this->_numTx; i++){
                selectChannelOut(i);
                 Serial.print(i);
                // Read RX
                for (int j=0; j < this->_numRx; j++){
                     Serial.print(",");
                     Serial.print(analogRead(j));
                }

                 Serial.println();
            }
        }else{
            for (int i=0; i < this->_numTx; i++){
                selectChannelOut(i);
                 Serial.print(i);
                // Read RX
                for (int j=0; j < this->_numRx; j++){
                     Serial.print(",");
                     int tmp = analogRead(j) - noise[i][j];
                     if(tmp > this->_threshold){
                        Serial.print(true);
                     }else{
                        Serial.print(false);
                     }
                }
                 Serial.println();
            }
        }
    }
}

/**
 *   @brief  Set select_pins of the multiplexer
 *
 *   @return void
 */
void MultiTouchKit::selectChannelOut(int channel) {
    int r0 = channel & 1;
    int r1 = channel & 2;
    int r2 = channel & 4;
    int r3 = channel & 8;
    
    digitalWrite(this->_muxPins[3], (r0==0?LOW:HIGH));
    digitalWrite(this->_muxPins[2], (r1==0?LOW:HIGH));
    digitalWrite(this->_muxPins[1], (r2==0?LOW:HIGH));
    digitalWrite(this->_muxPins[0], (r3==0?LOW:HIGH));
}

/**
 *   @brief  Setup pwm parameters.
 *
 *   @return void
 */
void MultiTouchKit::setupPWM(){

    #if defined(ARDUINO_AVR_UNO)
        #define BOARD "Uno"
        ////------------- Setup for Arduino Uno ---------
        pinMode(3, OUTPUT);      // Timer02 output pin
    
        //Set frequency to 4MHz, 25% duty cycle
        TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
        TCCR2B = _BV(WGM22) | _BV(CS20);
        OCR2A = 3;
        OCR2B = 0;
    
        analogReference(INTERNAL);         //change reference to 1.1V
    
    #elif defined(ARDUINO_AVR_LILYPAD)
        #define BOARD "Lilypad"
        ////------------- Setup for Arduino Lilypad ---------
        pinMode(3, OUTPUT);      // Timer02 output pin
    
        //Set frequency to 4MHz, 25% duty cycle
        TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
        TCCR2B = _BV(WGM22) | _BV(CS20);
        OCR2A = 3;
        OCR2B = 0;
    
        analogReference(INTERNAL);         //change reference to 1.1V

    #elif defined(ARDUINO_AVR_MEGA2560)
        #define BOARD "Mega 2560"
        ////--------------- Setup for Arduino Mega --------
        pinMode(9, OUTPUT);       // Timer02 output pin

        //Set frequency to 4MHz, 25% duty cycle
        TCCR2A = _BV(COM2A0) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);
        TCCR2B = _BV(WGM22) | _BV(CS20);
        OCR2A = 3;
        OCR2B = 0;
    
        analogReference(INTERNAL1V1);         //change reference to 1.1V

    #else
        #error "Unknown board"
    #endif
}
