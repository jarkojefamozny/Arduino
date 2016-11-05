/*
  Laser entry denial device

 Parts required:
 photoresistor
 resistors
 piezo
 laser 

 inspired by project 6 - Light Theremin
 Created by jarkojefamozny
*/

// variable to hold sensor value
int sensorValue;
// variable to calibrate high value
int sensorHigh = 0;

void setup() {
  Serial.begin(9600);
  // 10 sec calibration
  while (millis() < 10000) {
    // record the maximum sensor value
    sensorValue = analogRead(A0);
    if (sensorValue > sensorHigh) {
      sensorHigh = sensorValue;
    }
    Serial.print("THe highest value yet = ");
    Serial.print(sensorHigh);
    Serial.print("\n");
  }
}

void loop() {
    
  //read the input from A0 and store it in a variable
  sensorValue = analogRead(A0);
  
    Serial.print("Sensor value = ");
    Serial.print(sensorValue);
    Serial.print("\n");
    if( (sensorValue + 20) < sensorHigh || (sensorValue - 20) > sensorHigh )
    {
      Serial.print("Busted\n");
      int pitch = map(sensorValue,  400, sensorHigh, 50, 4000);
      //instead of blowing things up we trigger the beeper
      tone(8, pitch, 5000);
      delay(1000);
    }
}

