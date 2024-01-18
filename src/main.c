/*
 * Final_Project.c
 *
 * Created: 4/24/2023 2:53:32 PM
 * Author : eplsn, gthangavel
 */ 

#define F_CPU 16000000L

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#include <lcd.h>
#include <klavestnica.h>
#include <TM1637.h>

#define keypadChars "1234567890*#ABCD"

uint8_t ledNumbers[] = (uint8_t[]) {
           TM1637_SPAT_0,
           TM1637_SPAT_1,
           TM1637_SPAT_2,
           TM1637_SPAT_3,
           TM1637_SPAT_4,
           TM1637_SPAT_5,
           TM1637_SPAT_6,
           TM1637_SPAT_7,
           TM1637_SPAT_8,
           TM1637_SPAT_9
           };

int startingTimeMinDigit1;
int startingTimeMinDigit2;
int startingTimeSecDigit1;
int startingTimeSecDigit2;


int main(void)
{
  lcd_init(LCD_DISP_ON);
  lcd_clrscr();
  TM1637_setBrightness(0);
  
  mainMenu();
  
}

void mainMenu(void) {
  lcd_puts("A:3 min B:2 min\n");
  lcd_puts("C:1 min D:custom");
  for(;;)
  {
    uint8_t tmp = nacitajklavesy();
    char charPressed = zistiklaves(tmp);
    
    if (isalnum(charPressed)) {
      
      if (charPressed == 'A' || charPressed == 'B' || charPressed == 'C' || charPressed == 'D') {
        lcd_clrscr();
        if (charPressed == 'A'){
          lcd_puts("3 minutes");
          startingTimeSecDigit1 = 0;
          startingTimeSecDigit2 = 0;
          startingTimeMinDigit1 = 0;
          startingTimeMinDigit2 = 3;

        }
        else if (charPressed == 'B'){
          lcd_puts("2 minutes");
          startingTimeSecDigit1 = 0;
          startingTimeSecDigit2 = 0;
          startingTimeMinDigit1 = 0;
          startingTimeMinDigit2 = 2;
        }
        else if (charPressed == 'C'){
          lcd_puts("1 minutes");
          startingTimeSecDigit1 = 0;
          startingTimeSecDigit2 = 0;
          startingTimeMinDigit1 = 0;
          startingTimeMinDigit2 = 1;
        }
        else {
          customTime();
          startGame();
        }
      }
    }
  }
}


void customTime() {
  lcd_puts("enter minutes\n");
  lcd_puts("(00-99) #enter");
  
  char customTime[8];
  int customMinute[2];
  int customSecond[2];
  int k = 0;
  
  for(;;) {
    lcd_command(0x0f);
    uint8_t tmp = drzanieklavesy();
    char charPressed = zistiklaves(tmp);
    
    if (isdigit(charPressed)) {
      lcd_clrscr();
      customTime[k] = charPressed;
      customTime[++k] = 0;
      lcd_puts(customTime);
      
      customMinute[k%2] = atoi(&charPressed);
    }
    else if (charPressed == '#') {
      lcd_clrscr();
      break;	
    }
    
  }
  
  k=0;
  lcd_clrscr();
  lcd_puts("enter seconds\n");
  lcd_puts("(00-59) #enter");

  for(;;) {
    lcd_command(0x0f);
    uint8_t tmp = drzanieklavesy();
    char charPressed = zistiklaves(tmp);
    
    if (isdigit(charPressed)) {
      lcd_clrscr();
      customTime[k] = charPressed;
      customTime[++k] = 0;
      lcd_puts(customTime);
      
      customSecond[k%2] = atoi(&charPressed);
    }
    else if (charPressed == '#') {
      lcd_clrscr();
      break;
    }
    
    startingTimeMinDigit1 = customMinute[0];
    startingTimeMinDigit2 = customMinute[1];
    startingTimeSecDigit1 = customSecond[0];
    startingTimeSecDigit2 = customSecond[1];
  }
  
}

void startGame() {
  TM1637_init();
  TM1637_setSegments((uint8_t[]) { ledNumbers[startingTimeMinDigit2], ledNumbers[startingTimeMinDigit1], ledNumbers[startingTimeSecDigit2], ledNumbers[startingTimeSecDigit1] }, 4, 0);
  TM1637_turnOnAndSetBrightness(TM1637_MAX_BRIGHTNESS);
  lcd_clrscr();
  lcd_puts(("set time to %d%d:%d%d\n", startingTimeMinDigit1, startingTimeMinDigit2, startingTimeSecDigit1, startingTimeSecDigit1, startingTimeSecDigit2));
  _delay_ms(1000);
  lcd_clrscr();
  lcd_puts("game starts in\n");
  lcd_puts("3");
  _delay_ms(1000);
  lcd_clrscr();
  lcd_puts("game starts in\n");
  lcd_puts("2");
  _delay_ms(1000);
  lcd_clrscr();
  lcd_puts("game starts in\n");
  lcd_puts("1");
  _delay_ms(1000);
  lcd_clrscr();
  lcd_puts("game started!!!\n");
  lcd_puts("player1's turn\n");
  player1turn();
  return;
}

void player1turn() {
  while(startingTimeMinDigit1 != 0 || startingTimeMinDigit2 != 0 || startingTimeSecDigit1 != 0 || startingTimeSecDigit2 != 0) {
    TM1637_setSegments((uint8_t[]) { ledNumbers[startingTimeMinDigit2], ledNumbers[startingTimeMinDigit1], ledNumbers[startingTimeSecDigit2], ledNumbers[startingTimeSecDigit1] }, 4, 0);
      
    startingTimeSecDigit1--;
    if (startingTimeSecDigit1 == -1){
      startingTimeSecDigit1 = 9;
      startingTimeSecDigit2--;
      if (startingTimeSecDigit2 == -1){
        startingTimeSecDigit2 = 5;
        startingTimeMinDigit1--;
        if (startingTimeMinDigit1 == -1){
          startingTimeMinDigit1 = 9;
          startingTimeMinDigit2--;
          if (startingTimeSecDigit2 == -1){
            startingTimeMinDigit2 = 0;
          }
        }
      }
    }

    _delay_ms(1000);
  }
  TM1637_setSegments((uint8_t[]) { ledNumbers[startingTimeMinDigit2], ledNumbers[startingTimeMinDigit1], ledNumbers[startingTimeSecDigit2], ledNumbers[startingTimeSecDigit1] }, 4, 0);
  PORTB |= (1 << PORTB4);
  _delay_ms(1000);
  PORTB &= ~(1 << PORTB4);
}



