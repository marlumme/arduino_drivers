/*
	(c) Martti@Lumme.org 2016
	Free to copy, use and modify when this header remains in the code
*/
#include "dbg.h"

long arg[10];
int args;

int (*cmdext)(char*);

void motor(int m, int speed)
{
  Serial.print(m);Serial.print(" Motor ");Serial.println(speed);
  byte dir,pwm;
  if(m==1) {
    pwm=5;dir=4;
  }else{
    pwm=6;dir=7;
  }
  pinMode(pwm,OUTPUT);pinMode(dir,OUTPUT);
  if(speed<0){
    speed=-speed;
    digitalWrite(dir,0);
  } else{
    digitalWrite(dir,1);
  }
  analogWrite(pwm,speed);
}

int i2cScan()
{
  byte nDevices,address,error;
      Serial.println(F("Scanning..."));
     
      nDevices = 0;
      for(address = 1; address < 127; address++ )
      {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
     
        if (error == 0)
        {
          Serial.print(nDevices);Serial.print(F(" I2C at  0x"));
          Serial.println(address,HEX);
          
     
          nDevices++;
        }
        else if (error==4)
        {
          Serial.print(F("Unknow error at address 0x"));
          if (address<16)
            Serial.print("0");
          Serial.println(address,HEX);
        }    
      }

     
      return nDevices;
 }

unsigned long timeset(unsigned long dst)
{
  return millis()+dst;
}
int timeout(long dst)
{
  dst -= (long) millis();
  return dst<0;
}

int line()
{
  static char bf[80];
  static char *cp=bf;
  static char ch=0;
 
  while(Serial.available()){
    ch = Serial.read();
    if(ch==10) continue;
    if(cp-bf>78) ch=13;
    if(ch==13) {
      cp = bf;
      return bf;
    }
    *cp++ = ch;
    *cp = 0;
    
  }
  return 0;  
}
int exec(char *cp)
{
  static long def=0;
  int i;
  long out;byte yes;


  char ch,*ep,*fp;
  yes = 0;
  while(isspace(*cp)) cp++;
  fp = cp;
  if(*cp=='@'){
    cp++;
    if(*cp++ != EEPROM.read(0)) return 0;
  }
  ch = *cp++;
  if(*cp==':') cp++;
  args=0;
  for(args=0;args<10;args++){
     arg[args] = strtol(ep=cp,&cp,0);
     if(ep==cp) break;
  }
  if(*cp > ' ') ch=0x1b;
  switch(ch){
    
  case 's':  ///set
        pinMode(val,OUTPUT);digitalWrite(val,1);break;
  case 'c':  ///clr
        pinMode(val,OUTPUT);digitalWrite(val,0);break;
  case 'g':/// get io
        pinMode(val,INPUT_PULLUP);out=digitalRead(val);yes=1;break;
  case 'd': ///delay
        pinMode(val,OUTPUT);digitalWrite(val,val3);delay(val2);digitalWrite(val,!val3);break;
  case 'l':{
        long asec;
        args=0;
        pinMode(val,INPUT_PULLUP);
        asec = timeset(val2);
        val3 = val4 = -1;
        i= digitalRead(val);
        for(;!timeout(asec);){
          if(i!= digitalRead(val)){
            def = millis();
            i = !i;
            if(i) val3 = def-val2;
            else val4 = def-val2;
            args++;
            val2 = def;
          }
        }
        Serial.println(args);
        Serial.println(val3);
        Serial.println(val4);
        }     
  case 'p':///analog out pwm
        analogWrite(val,val2);break;  
  case 'a':/// analog in
        if(arg>1){
          for(i=0;i<val2;i++){
            Serial.println(analogRead(val));
            delay(val3);
          }
        } else {
        out=analogRead(val);yes=1;
        }
        break; 
  case 't':///uptime ms
        out=millis();yes=1;break;  
  case 'e':///eeprom
           if(args==0) for(i=0;i<16;i++) {
            Serial.print(EEPROM.read(def++),HEX);Serial.print(' ');
           } else if(args==1) {out=EEPROM.read(val);yes=1;}
           else {
            for(i=0;i<args;i++) EEPROM.write(i+val,arg[i+1]);
           }
           break;
  case 'o':/// onewire
  case 'i': //I2C
        if(args==0){
          i2cScan();
          break;
        } 
        if(args==1){
          Wire.requestFrom((int)val,(int)1,(int)true);  // 
            out=Wire.read();yes=1;
            break;;
        }
        Wire.beginTransmission((int)val);
        for(i=1;i<args;i++) Wire.write(arg[i]);
        Wire.endTransmission();
        break;
  case 'f':/// frequence
        tone(val,val2);break;
  case 'm': /// motor as in romeo v2
        motor(val,val2);break;
  case '=':
        out = val;yes=1;
        for(;*cp;){
          ch = *cp++;
          def = strtol(cp,&cp,0);
          switch(*cp++){
          case '+':out += def;break;
          case '-':out -= def;break;
          case '*':out *= def;break;
          case '/':out /= def;break;
          case '%':out %= def;break;
          default:cp="";
          }
        }
        break;
 
  case '!':for(i=0;i<args;i++) Serial.println(arg[i]); Serial.println(args);Serial.println(ep);break;
  case '?':
      out = val;yes=1;break;
  case '&':/// version
     Serial.println("CMD");
 
        Serial.println(__DATE__);Serial.println(__TIME__); break;
  default:
    if(cmdext&&cmdext(fp)) return 1;
    Serial.print(fp);Serial.println("??");
    return 0;
  }
  if(yes){

    Serial.println(out);
    Serial.print("HEX ");Serial.println(out,HEX);
    Serial.print("BIN ");Serial.println(out,BIN);


  }
  return 1;
}

int cmd()
{
  char *cp;
  cp = line();
  if(!cp) return 0;
  Serial.println(cp);
  return exec(cp);
}

int extcmd(int (*cext) (char*))
{
  cmdext = cext;

}

