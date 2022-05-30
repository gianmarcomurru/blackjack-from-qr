
// Define pin connections & motor's steps per revolution
const int dirPin = 6;
const int stepPin = 5;
const int stepsPerRevolution = 200;


void setup() {
  // pins for card dealing dc motor
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT); 

  // pins for base stepper motor
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);

}

void loop() {
  //dealCard();
  //delay(3000); // Wait a second

}  

void turnRobot(String person) {
  
  if(person.equals("player")) {
      digitalWrite(dirPin, HIGH); // Set motor direction clockwise

      // Spin motor
      for(int x = 0; x < stepsPerRevolution/3; x++)
      {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(3000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(3000);
      }
      
    } else if(person.equals("dealer")) {
      digitalWrite(dirPin, LOW); // Set motor direction counterclockwise
    
      // Spin motor
      for(int x = 0; x < stepsPerRevolution/3; x++)
      {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(3000);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(3000);
      }
    }  
}

void dealCard() {
  digitalWrite(2,HIGH);
  digitalWrite(3,LOW);
  delay(1200);
  
  digitalWrite(2,LOW);
  digitalWrite(3,HIGH);
  delay(1000);

  digitalWrite(2,LOW);
  digitalWrite(3,LOW);
}
