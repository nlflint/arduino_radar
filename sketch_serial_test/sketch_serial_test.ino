/*
 * ATtinySerialOutExample.cpp
 * Example for using ATtinySerialOut library
 *
 *  Copyright (C) 2015-2019  Armin Joachimsmeyer
 *  Email: armin.joachimsmeyer@gmail.com
 *
 *  This file is part of TinySerialOut https://github.com/ArminJo/ATtinySerialOut.
 *
 *  TinySerialOut is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/gpl.html>.
 *
 */

#include <Arduino.h> // needed for main()

#include "ATtinySerialOut.h"

#include <avr/pgmspace.h> // needed for PSTR()

#define TINY_SERIAL_DO_NOT_USE_115200BAUD

void setup(void) {
//    OSCCAL = 0x;
    initTXPin();

    //Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_ATTINY_SERIAL_OUT));

//    writeString("OSCCAL=");
//    writeUnsignedByteHexWithPrefix(OSCCAL);
    
//    pinMode(0, OUTPUT);
//    digitalWrite(0, LOW); // turn the LED off by making the voltage LOW
}

void loop(void) {
//  OSCCAL += 1;
  for (uint8_t tIndex = 0; tIndex < 5; tIndex++)
  {
    
    /*
     * Example of 3 Byte output. View in combined ASSCI / HEX View in HTerm (http://www.der-hammer.info/terminal/)
     * Otherwise use writeUnsignedByteHexWithoutPrefix or writeUnsignedByteHex
     */
//    write1Start8Data1StopNoParityWithCliSei('I');
//    writeBinary(tIndex);                    // 1 Byte binary output
//    writeUnsignedByte(tIndex);              // 1-3 Byte ASCII output
//    writeUnsignedByteHexWithPrefix(tIndex); // 4 Byte output
//    writeUnsignedByteHex(tIndex);           // 2 Byte output
//    write1Start8Data1StopNoParityWithCliSei('\n');
    /*
     * Serial.print usage example
     */
    Serial.print("\n\rHello, this is OSCALa:");
    Serial.print(OSCCAL, HEX);
    Serial.print("\n\rHello, this is OSCALb:");
    Serial.print(OSCCAL, HEX);
    Serial.print("\n\rHello, this is OSCALc:");
    Serial.print(OSCCAL, HEX);
    Serial.print("\n\rHello, this is OSCALd:");
    Serial.print(OSCCAL, HEX);
//    Serial.print((char) tIndex);
//    Serial.print(" | ");
//    Serial.print(tIndex);
//    Serial.print(" | ");
//    Serial.print(tIndex, HEX);
//    Serial.print(" | ");
//    Serial.printHex(tIndex);
//    Serial.print(" | ");
//    Serial.println(tIndex);
    
    //digitalWrite(0, LOW); // turn the LED off by making the voltage LOW
//    delay(100);
    //digitalWrite(0, HIGH); // turn the LED on (HIGH is the voltage level)
  }
}
