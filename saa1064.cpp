/*
        (c) Martti@Lumme.org 2016
        Free to copy, use and modify when this header remains in the code
*/
#include "saa1064.h"
static int digits[17]=
{0xbd, 0x09, 0x75, 0x6d, 0xc9, 0xec, 0xfc,0x0d,
 0xfd, 0xed, 0xdd, 0xf8, 0xb4, 0x79, 0xf4, 0xd4, 0x40};
/*
 * 0 abcdef- 
 * 1 -bc---- 00001001
 * 2 ab-de-g 01110101  1=b
 * 3 abcd--g
 * 4 -bc--fg 11001001
 * 5 a-cd-fg
 * 6 a-cdefg
 * 7 abc----
 * 8 abcdefg
 * 9 abc--fg
 * 01=b
 * 02=dp
 * 04=a
 * 08=c
 * 10=e
 * 20=d
 * 40=g
 * 80=f
 * 
 * 
 * 7    6    5     4    3    2    1    0
 *     12mA  6mA  3mA test 24on  13on 1234  
 * C0 = 0 C0 = 1 C1 = 0/1 C2 = 0/1 C3 = 1 C4 = 1 C5 = 1 C6 = 1

 */

 
SAA1064::SAA1064()
{
  Wire.begin(); 
}
size_t SAA1064:: write(uint8_t dat)
{
  static byte ps;
          Wire.beginTransmission(SAA1064_ADDR);
          Wire.write((((ps++)&3)+1));
          Wire.write(digits[dat]);; 
          Wire.endTransmission(); 
}
void SAA1064::display(int val,uint8_t rad)
{
  if(val>=0) display((unsigned)val,rad);
  else{
    display((unsigned)-val,rad);
    raw(4,0x40); 
  }
}
void SAA1064::display(unsigned int val,uint8_t rad)
{
  rad &=0x1f;
  rad = rad?rad:10;
  for(int i=1;i<5;i++){
    Wire.beginTransmission(SAA1064_ADDR);
    Wire.write(i);
    if(val==0&&rad==10&&i>1) Wire.write(0);
    else Wire.write(digits[val%rad]);val /=rad;
    Serial.println(val);
    Wire.endTransmission();  
  }  
}
void SAA1064::begin()
{
  brightness(7);
  raw(1,digits[16]);
}
void SAA1064::brightness(uint8_t br)
{
 Wire.beginTransmission(SAA1064_ADDR);
 Wire.write(0); 
 Wire.write((br<<4) | 7);  
 Wire.endTransmission();
}
void SAA1064::raw(uint8_t pos,uint8_t chr)
{
 Wire.beginTransmission(SAA1064_ADDR);
 Wire.write(pos); 
 Wire.write(chr);  
 Wire.endTransmission();
}
