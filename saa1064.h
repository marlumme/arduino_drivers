/*
        (c) Martti@Lumme.org 2016
        Free to copy, use and modify when this header remains in the code
*/
#ifndef _SAA1064_H
#define _SAA1064_H
#include <Arduino.h>
#include <Wire.h>
#define SAA1064_ADDR  (0x70 >> 1)

class SAA1064 :public Stream{
  public:
    SAA1064();
    void begin();
    void display(int val, uint8_t rad=-10);
    void display(unsigned int val, uint8_t rad=-10);
    void raw(uint8_t pos,uint8_t chr);
    void brightness(uint8_t vol);
    virtual size_t write(uint8_t dat);
    using Print::write;
    int read(){return 0;}
    int available(){return 0;}
    void flush(){}
    int peek(){return 0;}
  private:
 
    
};
#endif
