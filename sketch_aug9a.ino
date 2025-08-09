#include <LiquidCrystal.h>

//LCD pin to Arduino
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 

LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

#define length 6
#define characters "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890"

byte check[8] = { 0b00000, 0b00001, 0b00011, 0b10110, 0b11100, 0b01000, 0b00000, 0b00000 };

enum STATE
{
  IDLE,
  UP,
  DOWN,
  LEFT,
  RIGHT,
  SELECT
};

int read_LCD_buttons() 
{
  int buton = analogRead(0);
  if (buton > 1000) return 0; //none
  if (buton < 50)   return 1; //right
  if (buton < 250)  return 2; //up
  if (buton < 450)  return 3; //down
  if (buton < 600)  return 4; //left
  if (buton < 920)  return 5; //select
  return 0; //none
}

void task()
{
  static STATE state = IDLE;
  switch(state)
  {
    case IDLE:
    {
      break;
    }
    case UP:
    {
      break;
    } 
    case DOWN:
    {
      break;
    }
    case LEFT:
    {
      break;
    }
    case RIGHT:
    {
      break;
    }
    case SELECT:
    {
      break;
    }
  }
}

void setup() 
{
  lcd.begin(16, 2);
  lcd.setCursor(0,0);

  lcd.print("ENTER CODE:");
  lcd.setCursor(0,1);

  char stars[11];
  for(int i=0; i<length; i++) stars[i]='*';
  stars[length]='\0';
  lcd.print(stars);

  lcd.createChar(0, check); 
  lcd.setCursor(15,1);
  lcd.write(byte(0));
}

void loop() 
{
  
}