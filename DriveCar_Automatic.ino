#include <Wire.h>
#include <ArduinoNunchuk.h>

ArduinoNunchuk nunchuk = ArduinoNunchuk();
int needSetUpA = 0;
int needSetUpB = 0;
int needSetUpC = 0;
int needSetUpD = 0;
const int pingPin = 7;

void setup()
{
    //Setup Channel A
  pinMode(12, OUTPUT); //Initiates Motor Channel A pin
  pinMode(9, OUTPUT); //Initiates Brake Channel A pin

  //Setup Channel B
  pinMode(13, OUTPUT); //Initiates Motor Channel A pin
  pinMode(8, OUTPUT);  //Initiates Brake Channel A pin
  
  nunchuk.init();
  Serial.begin(9600);
}

void loop()
{
  nunchuk.update();
  if( nunchuk.zButton == 1){
    autonomous();  
  }

  while(nunchuk.analogY > 135){
    if(needSetUpA == 0){
        digitalWrite(12, HIGH); //Establishes forward direction of Channel A
        digitalWrite(9, LOW);   //Disengage the Brake for Channel A
        digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
        digitalWrite(8, LOW);   //Disengage the Brake for Channel B
        needSetUpA = 1;
        needSetUpB = 0;
        needSetUpC = 0;
        needSetUpD = 0;
        nunchuk.update();
        if( nunchuk.zButton == 1){
          autonomous();  
        }
    } else {
        int maxSpeed = (nunchuk.analogY - 130) * 3;
        if (maxSpeed > 255){
          maxSpeed = 255;
        }
        analogWrite(3, maxSpeed); 
        analogWrite(11, maxSpeed);    
        nunchuk.update();
        if( nunchuk.zButton == 1){
          autonomous();  
        }
    }
  }
  
  while( nunchuk.analogY < 120){
    if(needSetUpB == 0){
        digitalWrite(12, LOW); //Establishes backward direction of Channel A
        digitalWrite(9, LOW);   //Disengage the Brake for Channel A      
        digitalWrite(13, LOW);  //Establishes backward direction of Channel B
        digitalWrite(8, LOW);   //Disengage the Brake for Channel B
        needSetUpB = 1;
        needSetUpA = 0;
        needSetUpC = 0;
        needSetUpD = 0;
        nunchuk.update();
        if( nunchuk.zButton == 1){
          autonomous();  
        }
    } else {
      int maxSpeed = (120 - nunchuk.analogY) * 3;
      if (maxSpeed > 255){
        maxSpeed = 255;  
      }
      analogWrite(3, maxSpeed);  
      analogWrite(11, maxSpeed);    
      nunchuk.update();
      if( nunchuk.zButton == 1){
        autonomous();  
      }
    }
  }
  
  while (nunchuk.analogX > 130){
      if(needSetUpC == 0){
        digitalWrite(12, HIGH); //Establishes forward direction of Channel A
        digitalWrite(9, LOW);   //Disengage the Brake for Channel A      
        digitalWrite(13, LOW);  //Establishes backward direction of Channel B
        digitalWrite(8, LOW);   //Disengage the Brake for Channel B
        needSetUpB = 0;
        needSetUpA = 0;
        needSetUpC = 1;
        needSetUpD = 0;
        nunchuk.update();
        if( nunchuk.zButton == 1){
          autonomous();  
        }
      } else {
        int maxSpeed = (nunchuk.analogX - 130) * 3;
        if (maxSpeed > 255){
          maxSpeed = 255;
        }
        analogWrite(3, maxSpeed); 
        analogWrite(11, maxSpeed);   
        nunchuk.update();
        if( nunchuk.zButton == 1){
          autonomous();  
        }
    }
  }
  
  while( nunchuk.analogX < 120){
    if(needSetUpD == 0){
        digitalWrite(12, LOW); //Establishes backward direction of Channel A
        digitalWrite(9, LOW);   //Disengage the Brake for Channel A      
        digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
        digitalWrite(8, LOW);   //Disengage the Brake for Channel B
        needSetUpB = 0;
        needSetUpA = 0;
        needSetUpC = 0;
        needSetUpD = 1;
        nunchuk.update();
        if( nunchuk.zButton == 1){
          autonomous();  
        }
    } else {
      int maxSpeed = (120 - nunchuk.analogX) * 3;
      if (maxSpeed > 255){
        maxSpeed = 255;  
      }
      analogWrite(3, maxSpeed); 
      analogWrite(11, maxSpeed);  
      nunchuk.update();
        if( nunchuk.zButton == 1){
          autonomous();  
        }
    }
  }
  
  digitalWrite(9, HIGH);  //Engage the Brake for Channel A
  digitalWrite(8, HIGH);  //Engage the Brake for Channel B
  needSetUpA = 0;
  needSetUpB = 0;
  needSetUpC = 0;
  needSetUpD = 0;
}

void autonomous()
{
  int x = 1;
  while(x){
    // establish variables for duration of the ping, 
    // and the distance result in inches and centimeters:
    long duration, inches, cm;
    digitalWrite(12, HIGH); //Establishes forward direction of Channel A
    digitalWrite(9, LOW);   //Disengage the Brake for Channel A
    digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
    digitalWrite(8, LOW);   //Disengage the Brake for Channel B
    
    analogWrite(3, 255); 
    analogWrite(11, 255); 
  
    // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    pinMode(pingPin, OUTPUT);
    digitalWrite(pingPin, LOW);
    delayMicroseconds(2);
    digitalWrite(pingPin, HIGH);
    delayMicroseconds(5);
    digitalWrite(pingPin, LOW);
  
    // The same pin is used to read the signal from the PING))): a HIGH
    // pulse whose duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(pingPin, INPUT);
    duration = pulseIn(pingPin, HIGH);
  
    // convert the time into a distance
    inches = microsecondsToInches(duration);
    cm = microsecondsToCentimeters(duration);
    
    if( inches <= 1 ){
        digitalWrite(12, HIGH); //Establishes forward direction of Channel A
        digitalWrite(9, LOW);   //Disengage the Brake for Channel A      
        digitalWrite(13, LOW);  //Establishes backward direction of Channel B
        digitalWrite(8, LOW);   //Disengage the Brake for Channel B
        analogWrite(3, 255);  
        analogWrite(11, 255);  
        delay(500);
        digitalWrite(12, HIGH); //Establishes forward direction of Channel A
        digitalWrite(9, LOW);   //Disengage the Brake for Channel A
        digitalWrite(13, HIGH);  //Establishes forward direction of Channel B
        digitalWrite(8, LOW);   //Disengage the Brake for Channel B
        //check to see if want to exit
        nunchuk.update();
        if(nunchuk.zButton == 1){
          x = 0; 
        }
        
    }
    
    //Serial.print(inches);
    //Serial.print("in, ");
    //Serial.print(cm);
    //Serial.print("cm");
    //Serial.println();
    
    delay(100);
    nunchuk.update();
    if(nunchuk.zButton == 1){
      x = 0; 
    }
  }
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
