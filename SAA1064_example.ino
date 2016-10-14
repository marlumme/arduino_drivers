#include "Wire.h"
#include <avr/pgmspace.h>
#include "saa1064.h"
#include "dbg.h"

SAA1064 d;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
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
  }
}


void loop() {
  cmd(0);

}
