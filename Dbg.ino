#include "ssd1306.h"
#include "dbg.h"

void setup()
{
      Wire.begin();
      Serial.begin(9600);
      extcmd(mycmd);
}

SSD1306 disp;

void loop()
{      
      cmd();
}

int mycmd(char *cp)
{
 
  switch(*cp){
  case 'I':disp.begin();break;
  case 'C':disp.clear();break; 
  case 'P':disp.pen(val);break; 
  case 'V':disp.visible(val);break; 
  case 'L':disp.lineto(val,val2);break;
  case 'T':disp.text(cp+1);break;
  case 'M':disp.moveto(val,val2);break;
  case 'R':disp.circle(val);break;
  default:
    return 0;
  }
  return 1;
}
   
