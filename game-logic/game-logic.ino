// JOYSTICK PINs
#define joyX A0
#define joyY A1
#define joyP 8 //Pressed
//#define led1 10

int dealerVal;
int playerVal;
bool dealerHasAce = false;
bool playerHasAce = false;

// JOYSTICK
int xValue = 0;
int yValue = 0;
int joyButton = 0; // 0 pressed, 1 not pressed

// ROTATING MECHANISM
const int dirPinRM = 2;
const int stepPinRM = 3;
const int stepsPerRevolutionRM = 200;

// GENERAL MOTOR
const int dirPinGM = 6;
const int stepPinGM = 5;
const int stepsPerRevolutionGM = 200;


void setup() {
  Serial.begin(9600);
  pinMode(joyP,INPUT_PULLUP);
  // pins for card dealing dc motor
  pinMode(dirPinRM,OUTPUT);
  pinMode(stepPinRM,OUTPUT);

  // pins for base stepper motor
  pinMode(stepPinGM, OUTPUT);
  pinMode(dirPinGM, OUTPUT);
}

void loop() {
  Serial.println("Game started");
  //digitalWrite(led1, HIGH);
  initiateGame();

  // PLAYER'S TURN
  turnRobot("player");
  playerGameplay();

  // IF PLAYER !DEAD, DEALER'S TURN
  if (playerVal < 21) {
    turnRobot("dealer");
    dealerGameplay();
  } else { // player lost
    playerVal = 0;
  }

  if (dealerVal > 21) { // dealer lost
    dealerVal = 0;
  }

  // END GAME
  Serial.println("Game over");
  if (playerVal > dealerVal) {
    Serial.println("Player won");
  } else if (playerVal == dealerVal) {
    Serial.println("It's a tie");
  } else {
    Serial.println("Dealer won");
  }

  delay(10000);
}


void turnRobot (String person) {

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

void initiateGame() {
  dealerVal = 0;
  playerVal = 0;
  joyButton = digitalRead(joyP);

  // WAIT FOR PLAYER TO PRESS JOYSTICK BUTTON
  while (joyButton == 1){
    delay(100);
    joyButton = digitalRead(joyP);
  }

  // DEAL 2 CARDS TO PLAYER
  turnRobot("player");
  playerVal += readValue("player");
  dealCard();
  playerVal += readValue("player");
  dealCard();

  // DEAL 1 CARD TO DEALER
  turnRobot("dealer");
  dealerVal += readValue("dealer");
}

void playerGameplay() {
  if (is_hitme()) {
    playerVal += readValue("player");
    dealCard();
    if (playerVal < 21) {
      playerGameplay();
    } else {
      return;
    }
  } else {
    return;
  }
}

void dealerGameplay() {

  while(dealerVal < 16) {
    dealerVal += readValue("dealer");
  }
}

int readValue(String person) {
  Serial.write("CARD"); // Ask to Rasperry Pi to read a card
  while(true){
    if (Serial.available() > 0) {
      int val = Serial.readStringUntil('\n').toInt();
      if (val >= 2 && val <= 11){
        if (val == 11) {
          if(person.equals("player")) {
            if(playerHasAce) val = 1;
            else { val = 11; playerHasAce = true; }
          } else{
            if(dealerHasAce) val = 1;
            else { val = 11; dealerHasAce = true; }
          }
        }
        return val;
      }
    }
    delay(200);
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


boolean is_hitme() {
  while (true) {
    xValue = analogRead(joyX);
    yValue = analogRead(joyY);

    return (yValue > 900);
  }
}

/*
void printStatus() {
  Serial.println("Dealer value: " + dealerVal);
  Serial.println("Player value: " + playerVal);
}
*/
