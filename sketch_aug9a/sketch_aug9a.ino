#include <LiquidCrystal.h>
#include <string.h>

//LCD pin to Arduino
const int pin_RS = 8; 
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 

LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

#define length 6
#define characters "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define correct "ZABCZY"

byte check[8] = { 0b00000, 0b00001, 0b00011, 0b10110, 0b11100, 0b01000, 0b00000, 0b00000 };
char solution[17] = {};
int position = 0;

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

void reset()
{
  lcd.begin(16, 2);
  lcd.setCursor(0,0);

  lcd.print("ENTER CODE:");
  lcd.setCursor(0,1);

  char stars[11];
  for(int i=0; i<length; i++) stars[i] = solution[i] = '*';
  for(int i=length; i<15; i++) solution[i] = ' ';
  solution[15] = check;
  stars[length] = solution[16] = '\0';
  lcd.print(stars);

  lcd.createChar(0, check); 
  lcd.setCursor(15,1);
  lcd.write(byte(0));
}

void task()
{
  lcd.setCursor(position,1);
  lcd.write(255); delay(350);
  lcd.setCursor(position,1);
  lcd.write(solution[position]); delay(350);
  //Serial.println(solution);
  //delay(1000);

  static STATE state = IDLE;
  switch(state)
  {
    case IDLE:
    {
      if(read_LCD_buttons() == 1) state = RIGHT;
      else if(read_LCD_buttons() == 2) state = UP;
      else if(read_LCD_buttons() == 3) state = DOWN;
      else if(read_LCD_buttons() == 4) state = LEFT;
      else if(read_LCD_buttons() == 5) state = SELECT;
      else state = IDLE;

      break;
    }
    case UP:
    {
      if(solution[position] == ' ') 
      {
        state = IDLE;
        break;
      }
      else if(solution[position] == '*') solution[position] = 'Z';
      else if(solution[position] == 'A') solution[position] = 'Z';
      else solution[position] --;

      state = IDLE;
      break;
    } 
    case DOWN:
    {
      if(solution[position] == ' ') 
      {
        state = IDLE;
        break;
      }
      else if(solution[position] == '*') solution[position] = 'A';
      else if(solution[position] == 'Z') solution[position] = 'A';
      else solution[position] ++;

      state = IDLE;
      break;
    }
    case LEFT:
    {
      position --;
      if(position < 0) position = 15;
      state = IDLE;
      break;
    }
    case RIGHT:
    {
      position ++;
      if(position > 15) position = 0;
      state = IDLE;
      break;
    }
    case SELECT:
    {
      char finalsolution[11];
      strncpy(finalsolution, solution, length);
      finalsolution[length] = '\0';

      if(position == 15)
      {
        if(strcmp(finalsolution, correct) == 0)
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("YOU DID IT!");
          delay(3000);

          state = SELECT;
          break;
        }
        else 
        {
          lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("WRONGGG >:(");
          delay(3000);

          reset();
        }
      }
      

      state = IDLE;
      break;
    }
  }
}

void setup() 
{
  Serial.begin(9600); //init communication over USB

  lcd.begin(16, 2);
  lcd.setCursor(0,0);

  lcd.print("ENTER CODE:");
  lcd.setCursor(0,1);

  char stars[11];
  for(int i=0; i<length; i++) stars[i] = solution[i] = '*';
  for(int i=length; i<15; i++) solution[i] = ' ';
  solution[15] = check;
  stars[length] = solution[16] = '\0';
  lcd.print(stars);

  lcd.createChar(0, check); 
  lcd.setCursor(15,1);
  lcd.write(byte(0));
}

void loop() 
{
  task();
}