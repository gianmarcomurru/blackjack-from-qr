
// Define pin connections & motor's steps per revolution
const int dirPinGM = 6;
const int stepPinGM = 5;
const int dirPinRM = 2;
const int stepPinRM = 3;
const int stepsPerRevolutionGM = 200;


void setup() {
  // pins for card dealing dc motor
  pinMode(dirPinRM,OUTPUT);
  pinMode(stepPinRM,OUTPUT);

  // pins for base stepper motor
  pinMode(stepPinGM, OUTPUT);
  pinMode(dirPinGM, OUTPUT);

}

void loop() {
  turnRobot("dealer");
  delay(3000);
  dealCard();
  delay(3000);

  turnRobot("player");
  delay(3000);
  dealCard();
  delay(3000);

}

void turnRobot(String person) {

  if(person.equals("player")) {
      digitalWrite(dirPinGM, HIGH); // Set motor direction clockwise

      // Spin motor
      for(int x = 0; x < stepsPerRevolutionGM/3; x++)
      {
        digitalWrite(stepPinGM, HIGH);
        delayMicroseconds(3000);
        digitalWrite(stepPinGM, LOW);
        delayMicroseconds(3000);
      }

    } else if(person.equals("dealer")) {
      digitalWrite(dirPinGM, LOW); // Set motor direction counterclockwise

      // Spin motor
      for(int x = 0; x < stepsPerRevolutionGM/3; x++)
      {
        digitalWrite(stepPinGM, HIGH);
        delayMicroseconds(3000);
        digitalWrite(stepPinGM, LOW);
        delayMicroseconds(3000);
      }
    }
}

void dealCard() {
  digitalWrite(dirPinRM,HIGH);
  digitalWrite(stepPinRM,LOW);
  delay(1400);

  digitalWrite(dirPinRM,LOW);
  digitalWrite(stepPinRM,HIGH);
  delay(2000);

  digitalWrite(dirPinRM,LOW);
  digitalWrite(stepPinRM,LOW);
}
