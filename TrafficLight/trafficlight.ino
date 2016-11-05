

/*
  Traffic light by jarkojefamozny
 */


  int switchState = 0;
  bool shouldBeOn = false;
  int diff = 0;

  unsigned long time = 0;

void reset () {
  digitalWrite(13, LOW);
  digitalWrite(8, LOW);
  digitalWrite(4, LOW);
}

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(2, INPUT);
  
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  time = millis();
  switchState = digitalRead(2);
  
  if( switchState != diff ){
    if( switchState == HIGH) { 
      shouldBeOn = !shouldBeOn;
    }
  }

  diff = switchState;
  if( shouldBeOn == true ){
    reset();
    // RED light ON and OFF 
    if( (time % 14000 > 0 ) && (time % 14000 < 7000 )){
      digitalWrite(13, HIGH);         
    }
    else {
      digitalWrite(13, LOW);
    }

    // YELLOW light
    if( (time % 14000 > 5000 ) && (time % 14000 < 7000 ) ){
      digitalWrite(8, HIGH);         
    }
    else {
      digitalWrite(8, LOW);
    }   

    // GREEN light  
    if( (time % 14000 > 7001 ) && (time % 14000 < 12000 ) ){
      digitalWrite(4, HIGH);         
    }
    else {
      digitalWrite(4, LOW);
    }

     // YELLOW light
    if( (time % 14000 > 12001 ) && (time % 14000 < 13999 ) ){
      digitalWrite(8, HIGH);         
    }
    else {
      digitalWrite(8, LOW);
    }
  }
  
  // DEFAULT STATE
  else {
    reset();
    if( (time % 4000 > 2000 ) )
    {           
      digitalWrite(8, HIGH);  
    } 
    else {
       digitalWrite(8, LOW);
    }
  }
}
