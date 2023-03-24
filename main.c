#include "gd32vf103.h"
#include "drivers.h"
#include "lcd.h"
#include "pwm.h"

int main(void){
		
	int lookUpTbl[16]={1,4,7,14,2,5,8,0,3,6,9,15,10,11,12,13};
	int key;
  int numbervariable = 0;

	t5omsi();                               // Initialize timer5 1kHz
	colinit();                              // Initialize column toolbox
	l88init();                              // Initialize 8*8 led toolbox
	keyinit();                              // Initialize keyboard toolbox
	Lcd_SetType(LCD_INVERTED);                // or use LCD_INVERTED!
	Lcd_Init();
	LCD_Clear(BLACK);
	LCD_ShowStr(20, 10, "ENGINE POWER", WHITE, TRANSPARENT);
  T1powerUpInitPWM(0x1);                  // Timer #1, Ch #2 & 3 PWM
  T1setPWMmotorB(0);                       //nollställer motorn



	while (1){
		LCD_WR_Queue();
		l88row(colset());

		// if (t5expq()) {
      key=keyscan();
    

      switch(lookUpTbl[key]){
        case 2: numbervariable+=10; break;
        case 1: numbervariable-=10; break;
        case 0: numbervariable = 50;
      }
      if (numbervariable>100) numbervariable = 100;
      if (numbervariable<0) numbervariable = 0;

      // if (key >= 0)
      // LCD_ShowNum(50,40,lookUpTbl[key],2,GREEN); // kan användas för att kolla vad lookUpTbl[key] innehåller
      
      LCD_ShowChar(80,40,'%',1,GREEN);
      LCD_ShowNum(50,40,numbervariable,3,GREEN);
      T1setPWMmotorB(numbervariable * -1);
      
		// }
	}
}
