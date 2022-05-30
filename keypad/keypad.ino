// set pin numbers:
const int buttonPin[] = {9,10,11,12};

// variables will change:
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int buttonState4 = 0;

void setup() {
    // initialize the Serial Monitor @ 9600
    Serial.begin(9600);  
    // initialize the keypad pin(s) as an input:
    for(int x=0; x<4; x++)
    {
        pinMode(buttonPin[x], INPUT_PULLUP); 
    }  
}

void loop(){
    buttonState1 = digitalRead(buttonPin[0]);
    buttonState2 = digitalRead(buttonPin[1]);
    buttonState3 = digitalRead(buttonPin[2]);
    buttonState4 = digitalRead(buttonPin[3]);

    if (buttonState1 == LOW) {    
        Serial.print(" 1 ");
    }

    if (buttonState2 == LOW) {
        Serial.print(" 2 ");
    }

    if (buttonState3 == LOW) {
        Serial.print(" 3 ");
    }

    if (buttonState4 == LOW) {
        Serial.print(" 4 ");
    }
}