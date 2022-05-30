// JOYSTICK PINs
#define joyX A0
#define joyY A1

int dealerVal; 
int playerVal;
int nPlayer;
char aces[];

// JOYSTICK
int xValue = 0;
int yValue = 0; 

// KEYPAD
const int buttonPin[] = {9,10,11,12};
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;

void setup() {
  Serial.begin(9600); 
}

void loop() {
  Serial.println("Game started");
  initiateGame(); 

  // PLAYER'S TURN
  turnRobot("PLAYER"); 
  playerGameplay();

  // IF PLAYER !DEAD, DEALER'S TURN
  if (playerVal < 21) {
    turnRobot("DEALER"); 
    dealerGameplay(); 
  } else {
    playerVal = 0;
  }

  if (dealerVal > 21) {
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

void initiateGame() {
  dealerVal = 0; 
  playerVal = 0; 

  // WAIT FOR PLAYER NUMBER
  nPlayer = keypad();

  // DEAL 2 CARDS TO PLAYER 
  turnRobot("player"); 
  playerVal += readValue(); 
  dealCard(); 
  playerVal += readValue(); 
  dealCard();

  // DEAL 1 CARD TO DEALER
  turnRobot("dealer"); 
  dealerVal += readValue(); 
}

void playerGameplay() {

  if (is_hitme()) {
    playerVal += readValue(); 
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
    dealerVal += readValue();    
  }
}

void turnRobot(String person) {
  Serial.println("Turning to " + person + " position");
  delay(1500);
}

int readValue() {
  Serial.write("CARD"); // Ask to Rasperry Pi to read a card
  delay(200);
  if (Serial.available() > 0) {
    // int val = random(2,11);
    int val = Serial.readStringUntil('\n');
    if (val == "a") {
      
    } else {
      val = toInt(val);
    }
    // Serial.println("Value is: " + val); 
    // delay(500);
    return val; 
  }
}

void dealCard() {
  Serial.println("Dealing card...");
  delay(500);
}

boolean is_hitme() {
  while (true) {
    xValue = analogRead(joyX);
    yValue = analogRead(joyY);

    if (yValue > 900) {
      // Serial.println("Hit me!");  
      // delay(500);
      return true;
    } else if (yValue < 200) {
      // Serial.println("Stand"); 
      // delay(500);
      return false; 
    }
  } 
}

int keypad(){
    while (true) {
      buttonState1 = digitalRead(buttonPin[0]);
      buttonState2 = digitalRead(buttonPin[1]);
      buttonState3 = digitalRead(buttonPin[2]);
      buttonState4 = digitalRead(buttonPin[3]);

      if (buttonState1 == LOW) {    
        return 1;
      }

      if (buttonState2 == LOW) {
        return 2;
      }

      if (buttonState3 == LOW) {
        return 3;
      }

      if (buttonState4 == LOW) {
        return 4;
      }
    }
}

void printStatus() {
  Serial.println("Dealer value: " + dealerVal); 
  Serial.println("Player value: " + playerVal); 
}
