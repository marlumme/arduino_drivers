/*
        (c) Martti@Lumme.org 2016
        Free to copy, use and modify when this header remains in the code
*/
#ifndef SSD1306_h
#define SSD1306_h
#include <Arduino.h>


#include <Wire.h>

/*
class Sink : public Stream
{
 private:
  char buf[200];
  byte ci;
 public:
  Sink(){}
  ~Sink(){}
  void (*cback)(char*);
  char *spool();
//  void spool(void (fnk)(char*)){cback=fnk}
  virtual size_t write(uint8_t byte);
   int read(){}
  int available(){}
  void flush(){}
  int peek(){}
  using Print::write;
};
*/
class SSD1306 : public Stream{
  public:
    SSD1306(byte address=0x3c, byte offset=0,byte sda=0, byte scl=0 );
    ~SSD1306(){};
    void begin(void);
    void clear(void);
    void visible(uint8_t onoff);
    void setPixel(int  x,int  y,int c);
    void moveto(int x,int y);
    void lineto(int x,int y);
    void circle(int r);
    void pen(int c);
    void text(unsigned char *txt);
    virtual size_t write(uint8_t byte);
    using Print::write;
    int read(){return 0;}
    int available(){return 0;}
    void flush(){}
    int peek(){return 0;}
  private:
 
    uint8_t _sda, _scl, _address, _offset;
    int _x,_y,_c;
    void sendcommand(uint8_t com);
    void setRY(uint8_t row,uint8_t col);
    void wrByte(uint8_t data);
    byte rdByte();
    void wrChar(uint8_t data);

    void init(void);
};

#endif

