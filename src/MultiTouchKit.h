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

#ifndef MULTITOUCHKIT_H
#define MULTITOUCHKIT_H

#include <Arduino.h>

// Constants
#define MTK_DEFAULT_RX         6            // Default RX channels
#define MTK_DEFAULT_TX         6            // Default TX channels
#define MTK_MAX_TX             16           // Max TX channels
#define MTK_DEFAULT_MUX_CNTRL  4            // Default Mux control channels
#define MTK_MAX_MUX_CNTRL      4            // Max Mux control channels



class MultiTouchKit
{
  private:
    // Dimensions
    int _numRx = MTK_DEFAULT_RX;
    int _numTx = MTK_DEFAULT_TX;
    int _numMuxPins= MTK_DEFAULT_MUX_CNTRL;
    char*_adcPins;
    int*_muxPins;
    bool _raw_data;
    int _threshold;

    //---------- Converting Decimal to Binary -----------

    int noise [16][16];
                    
    void setupPWM();
    void selectChannelOut(int channel);

  public:
    // Prototypes
    MultiTouchKit();

    // Setup
    void setup_sensor(int rx, int tx, int* muxPins, bool raw_data, int threshold);

    // Run measurements and send them via Serial
    void read();
};

#endif //MULTITOUCHKIT_H
