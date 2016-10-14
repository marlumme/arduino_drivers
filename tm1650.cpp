/*
        (c) Martti@Lumme.org 2016
        Free to copy, use and modify when this header remains in the code
*/

#include "tm1650.h"

static byte digits[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7f,
0x6f, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71,0x40};


void TM1650::display(unsigned int val,uint16_t rad)
{
  uint8_t dot;
  dot = rad>>8;
  rad &=0x1f;
  rad = rad?rad:10;
  for(int i=3;i>=0;i--){

    if(val==0&&rad==10&&i!=3) Wire.wr(TM1650_DISPLAY_BASE+i,0,0);
    else Wire.wr(TM1650_DISPLAY_BASE+i,digits[val%rad]|((dot&1)?0x80:0),0,0);val /=rad;
    dot >>=1; 
  }  
}
void TM1650::display(int val,uint16_t rad)
{
  if(val>=0) display((unsigned)val,rad);
  else{
    display((unsigned)-val,rad);
    raw(4,digits[16]); 
  }
}

size_t TM1650::write(uint8_t chr)
{
  static byte ps;
 Wire.wr(TM1650_DISPLAY_BASE+((ps++)&3),chr,0,0);
}

void TM1650::raw(uint8_t pos,uint8_t chr)
{
 Wire.wr(TM1650_DISPLAY_BASE+4-pos,chr,0,0);
}
void TM1650::brightness (uint8_t br)
{
  Wire.wr(TM1650_CONTROL_BASE,(br<<4) | 1,0,0);
}

void TM1650::begin()
{
  brightness(7);
  raw(1,digits[16]);
}
int TM1650::available()
{
  uint8_t x;
  static uint8_t lx;
  x = read();
  if(lx==x) return 0;
  lx = x;
  return x;
}
int TM1650::read()
{
  // 76543210
  // 01xxz1yy y=4..7 x=40..70
  // 01xxz1xx y=c..f
   uint8_t x; 
  Wire.requestFrom(TM1650_CONTROL_BASE,1,true);
  x = Wire.read();
  if(x & 0x44 != 0x44) return 0x20;
  x = (x & 3) | ((x & 0x38)>>1);
  if(_tbl) x = _tbl[x];
  return x;
  
}

TM1650::TM1650()
{
  Wire.begin();
}

