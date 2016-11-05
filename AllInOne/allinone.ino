/*
All in one device - time, temperature, date + little bonus
by jarkojetomas
*/


// pins
#include <LiquidCrystal.h>

LiquidCrystal lcd(12,11,5,4,3,2);
int termoPin = A0;

// values
int termoValue = 0;
float temperature = 0;

const int MAX_VALUES = 200;

float temperatureValues[MAX_VALUES] = {};
int currentIndex = 0;

long int lastTime = 0;

void setup() {
  lcd.begin(16, 2);
  
  pinMode(termoPin, INPUT);
  lcd.setCursor(0,0);
  lcd.print("Vitaj :)");
  Serial.begin(9600);
}


void updateThermoValue()
{
  termoValue = analogRead( termoPin );
  float voltage = (termoValue / 1024.0 ) * 5.0;
  temperature = ( voltage - 0.5) * 100 + 2;
  temperatureValues[ currentIndex++ ] = temperature;

  if ( currentIndex >= MAX_VALUES )
  {
    currentIndex = 0;
  }
}


float getAvgTemperature()
{
  float sum = 0;

  for ( int i = 0; i < MAX_VALUES; i++ )
  {
    sum += temperatureValues[ i ];  
  }

  return sum / MAX_VALUES;
}


void debug()
{
  /* Tempeature values  
   
  Serial.print("Last values: [ ");
  for( int i = 0; i < MAX_VALUES; i++)
  {
    Serial.print( tempeatureValues[i] );
    Serial.print( ", " );
  }
  Serial.println("]");
  
  */

  
  Serial.println( getAvgTemperature() );
}


void loop() { 
  long int time = millis();

  if ( time % 200 < 10 )
  {
    updateThermoValue();
  }
  //debug();

  if( time % 117 < 10 )
  {
    Serial.println("server:getTime");
    Serial.println("server:getDate");
  }
  
  String initDate;
  String initTime;
  
  if(Serial.available() > 0)
  {
    if(Serial.peek() == 'D') 
    {
      initDate = Serial.readStringUntil('\n');
    }
    if(Serial.peek() == 'T') 
    {
      initTime = Serial.readStringUntil('\n');
    }
  }
  
  // DATE
  
  if( (time % 25000 > 0 ) && (time % 25000 < 5000 ))
  {
    if( (time % 25000 > 0 ) && (time % 25000 < 50 )){
      lcd.clear();
    }
    lcd.setCursor(0, 0);
    lcd.print("Date");
    lcd.setCursor(0, 1);
    lcd.print(initDate.substring(2));
  }

  // TIME
    
  if( (time % 25000 > 5001 ) && (time % 25000 < 10000 ))
  {
    if( (time % 25000 > 5001 ) && (time % 25000 < 5050 )){
      lcd.clear();
    }
    lcd.setCursor(0, 0);
    lcd.print("Time");
    lcd.setCursor(0, 1);
    lcd.print(initTime.substring(2));
  }

  // TEMPERATURE
  
  if( (time % 25000 > 10001 ) && (time % 25000 < 15000 ))
  {
    if( (time % 25000 > 10001 ) && (time % 25000 < 10050 )){
      lcd.clear();
    }
    lcd.setCursor(0, 0);
    lcd.print("Temperature");
    lcd.setCursor(0, 1);
    lcd.print(getAvgTemperature());
    lcd.setCursor(6, 1);
    lcd.print((char)223);
    lcd.setCursor(7, 1);
    lcd.print("C");
  }
  
  if( (time % 25000 > 15001 ) && (time % 25000 < 18500 ))
  {
    if( (time % 25000 > 15001 ) && (time % 25000 < 15050 )){
      lcd.clear();
    }
    lcd.setCursor(0, 0);
    lcd.print("Who is the most");
    //lcd.print("It's time to");
    lcd.setCursor(0, 1);
    lcd.print("AWESOME person?");
    //lcd.print("    play");
  }

  if( (time % 25000 > 18501 ) && (time % 25000 < 20000 ))
  {
    if( (time % 25000 > 18501 ) && (time % 25000 < 18550 )){
      lcd.clear();
    }
    lcd.setCursor(5, 0);
    lcd.print("YOU");
    //lcd.print("Rainbow Six:");
    //lcd.setCursor(0, 1);
    //lcd.print("Siege");
  }

  if( (time % 25000 > 20001 ) && (time % 25000 < 23000 ))
  {
    if( (time % 25000 > 20001 ) && (time % 25000 < 20050 )){
      lcd.clear();
    }
    lcd.setCursor(0, 0);
    lcd.print("This product is");
    lcd.setCursor(0, 1);
    lcd.print("brought to you");
  }
  if( (time % 25000 > 23001 ) && (time % 25000 < 25000 ))
  {
    if( (time % 25000 > 23001 ) && (time % 25000 < 23050 )){
      lcd.clear();
    }
    lcd.setCursor(0, 0);
    lcd.print("by :");
    lcd.setCursor(0, 1);
    lcd.print("JARKOJETOMAS");
  }
}

