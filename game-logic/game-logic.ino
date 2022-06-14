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

void loop1() {
  turnRobot("player");
  delay(2500);
  turnRobot("dealer");
  delay(2500);
}

void loop() {
  Serial.println("Game started");
  initiateGame();

  // PLAYER'S TURN
  turnRobot("player");
  playerGameplay();

  // IF PLAYER !DEAD, DEALER'S TURN
  if (playerVal < 21) {
    turnRobot("dealer");
    dealerGameplay();
  } else { // player lost
    Serial.println("Player " + String(playerVal) + " | Dealer " + String(dealerVal));
    playerVal = 0;
  }

  if (dealerVal > 21) { // dealer lost
    Serial.println("Player " + String(playerVal) + " | Dealer " + String(dealerVal));
    dealerVal = 0;
  }

  // END GAME
  Serial.println("Game over");
  if (playerVal > dealerVal) {
    Serial.println("Player won\n");
  } else if (playerVal == dealerVal) {
    Serial.println("It's a tie\n");
    turnRobot("player");
  } else {
    Serial.println("Dealer won\n");
    turnRobot("player");
  }

  delay(1000);
}


void turnRobot (String person) {

  if(person.equals("player")) {
      digitalWrite(dirPinGM, HIGH); // Set motor direction clockwise

      // Spin motor
      for(int x = 0; x < stepsPerRevolutionGM/4; x++)
      {
        digitalWrite(stepPinGM, HIGH);
        delayMicroseconds(8000);
        digitalWrite(stepPinGM, LOW);
        delayMicroseconds(8000);
      }

    } else if(person.equals("dealer")) {
      digitalWrite(dirPinGM, LOW); // Set motor direction counterclockwise

      // Spin motor
      for(int x = 0; x < stepsPerRevolutionGM/4; x++)
      {
        digitalWrite(stepPinGM, HIGH);
        delayMicroseconds(8000);
        digitalWrite(stepPinGM, LOW);
        delayMicroseconds(8000);
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
  playerVal += readValue("player");
  dealCard();
  playerVal += readValue("player");
  dealCard();

  // DEAL 1 CARD TO DEALER
  turnRobot("dealer");
  dealerVal += readValue("dealer");
  dealCard();
}

void playerGameplay() {
  Serial.write("Player's turn\n");
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
  Serial.write("Dealer's turn\n");
  while(dealerVal < 16) {
    dealerVal += readValue("dealer");
    dealCard();
  }
}

int handleAce(String person, int val) {
  if(person.equals("player")) {
    if(playerHasAce) val = 1;
    else {
      if (playerVal + 11 < 22) {
          val = 11; playerHasAce = true;
      } else {
          val = 1; playerHasAce = true;
      }
    }
  } else{
    if(dealerHasAce) val = 1;
    else {
      if (dealerVal + 11 < 22) {
          val = 11; dealerHasAce = true;
      } else {
          val = 1; dealerHasAce = true;
      }
    }
  }
  return val;
}

int readValue(String person) {
  Serial.write("CARD"); // Ask to Computer to read a card
  while(true){
    if (Serial.available() > 0) {
      int val = Serial.readStringUntil('\n').toInt();
      if (val >= 2 && val <= 11){
        if (val == 11) {
          val = handleAce(person, val);
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
  delay(1300);

  digitalWrite(dirPinRM,LOW);
  digitalWrite(stepPinRM,HIGH);
  delay(2000);

  digitalWrite(dirPinRM,LOW);
  digitalWrite(stepPinRM,LOW);
}


boolean is_hitme() {
  Serial.write("Waiting for player...\n");
  while (true) {
    xValue = analogRead(joyX);
    yValue = analogRead(joyY);

    if (yValue > 900) {
      Serial.write("Stand\n");
      return false;
    } else if (yValue < 200) {
      Serial.write("Hit me!\n");
      return true;
    }
  }
}
