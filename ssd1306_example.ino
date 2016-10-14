#include "Wire.h"
#include "ssd1306.h"
#include "dbg.h"

void setup()
{
      Serial.begin(115200);
      Serial.println("OLED Ready");
      postcmd(mycmd);
}

SSD1306 disp;

void loop()
{      
      cmd(0);
}

int mycmd(char *cp)
{
  switch(*cp){
 
  case 'I':disp.begin();break;
  case 'C':disp.clear();break; 
  case 'P':disp.pen(val1);break; 
  case 'V':disp.visible(val1);break; 
  case 'L':disp.lineto(val1,val2);break;
  case 'T':disp.text(cp+1);break;
  case 'M':disp.moveto(val1,val2);break;
  case 'R':disp.circle(val1);break;
  case 'Z':disp.printf("%x ",val1);break;
 
  case 'H':Serial.println(__DATE__);Serial.println(__TIME__);break;
 // case 'A':oleds.printf("Hello%u-%6u-%-6s-\n",123,5678,"9999");break;
  default:
    return 0;
  }
  return 1;
}
   
