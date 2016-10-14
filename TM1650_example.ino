#include <Wire.h>
#include "tm1650.h"
#include "dbg.h"

TM1650 d;
void setup() {
  
  Serial.begin(115200);
  delay(500);
  Serial.println(__DATE__);
  Serial.println(__FILE__);
  postcmd(mycmd);
  
}

int mycmd(char *cp,Stream *dev)
{
  switch(*cp){
  case 'S':d.begin();break;
  case 'B':d.brightness(val1);break;
  case 'I':d.display((int)val1,val2);break;
  case 'U':d.display((unsigned) val1,val2);break;
  case 'R':d.raw(val1,val2);break;
  case 'T':d.table(" 0123456789abcdefghijklmnopqrs");break;
  
  }
}
void loop()
{
 if(d.available()){
  Serial.println(d.read(),HEX);  
  d.display(d.read(),16);
 }
 cmd(0);
}
