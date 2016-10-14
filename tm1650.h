/*
        (c) Martti@Lumme.org 2016
        Free to copy, use and modify when this header remains in the code
*/
#ifndef _TM1650_H
#define _TM1650_H
#include <Arduino.h>
#include <Wire.h>
#define TM1650_DISPLAY_BASE 0x34
#define TM1650_CONTROL_BASE 0x24
class TM1650 :public Stream{
  public:
    TM1650();
    void begin();
    void display(int val, uint16_t rad=10); // signed default is decimal
    void display(unsigned int val, uint16_t rad=10); // unsigned
    void raw(uint8_t pos, uint8_t chr); // raw code to position
    void brightness(uint8_t vol); // brightness
    virtual size_t write(uint8_t dat); //stream write
    using Print::write;
    int read(); // current key press
    int available(); // if key changed return true
    void flush(){}
    int peek(){return 0;}
    void table(char *tbl){_tbl=tbl;}  // user translation, default is 0--31
  private:
    char *_tbl=0;
 
    
};
#endif
