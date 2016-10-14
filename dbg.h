/*
        (c) Martti@Lumme.org 2016
        Free to copy, use and modify when this header remains in the code
*/
#ifndef DBG_H
#define DBG_H
#include "arduino.h"
#include "Wire.h"
#include <EEPROM.h>

extern long arg[10];
extern int args;

#define val arg[0]
#define val2 arg[1]
#define val3 arg[2]
#define val4 arg[2]


unsigned long timeset(unsigned long dst);  // eases to make timing
int timeout(long dst); // timeout is true when result from timeset has passed
void motor(int m,int speed);  // simple motor driving
int i2cScan(); // i2c scanner
int line(); // captures line from rs232
int exec(char *cp); // executes command pointed
int cmd(); //reads command and executes it
int extcmd(int (char*)); // user commands linking

/* Currently Implemented single letter commands
 *  s set(bin)
 *  c clr(pin)
 *  g get(pin)
 *  d delay(pin,updown,delay) 
 *  l lenght(pin,period)
 *  p analog_out(pin,value)
 *  a analog_in(pin)
 *  t time()
 *  e eprom_list() / eprom_read(at) / eprom_write(at,data,...)
 *  o onewite // unimplemented
 *  i i2c scan() / read(adr) / write(at,data,...)
 *  f frequency(val,period)
 *  m motor(device, speed)
 *  = evaluate
 *  ! show(args, ...)
 *  ? 
 *  & version()
 
  case '!':for(i=0;i<args;i++) Serial.println(arg[i]); Serial.println(args);Serial.println(ep);break;
  case '?':
      out = val;yes=1;break;
  case '&':/// version
     Serial.println("CMD");
 
        Serial.println(__DATE__);Serial.println(__TIME__); break;

 */






#endif
