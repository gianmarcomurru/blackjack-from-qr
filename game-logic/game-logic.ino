int dealerVal; 
int playerVal;


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
  boolean decision = joystick(); 

  if (decision) {
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
  int val = random(2,11);
  Serial.println("Value is: " + val); 
  delay(1500);
  return val; 
}

void dealCard() {
  Serial.println("Dealing card..."); 
  delay(1500);
}

boolean joystick() {
  int choice = random(1,2); 
  if (choice == 1) {
    Serial.println("Hit me!");  
    delay(1500);
    return true;
  } else {
    Serial.println("Stand"); 
    delay(1500);
    return false; 
  }
}

void printStatus() {
  Serial.println("Dealer value: " + dealerVal); 
  Serial.println("Player value: " + playerVal); 
}
