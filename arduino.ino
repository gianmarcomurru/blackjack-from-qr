#define joyX A0
#define joyY A1
#define led1 13
#define led2 7

// iterator
int i;

// LED on Pin 13 for digital on/off demo
int ledPin = LED_BUILTIN;
String led;

// Joystick
int xValue = 0;
int yValue = 0; 

void setup()
{
  // LED on Pin 13 for digital on/off demo
  pinMode(ledPin, OUTPUT);
  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT); 
  
  // Open the serial connection, 9600 baud
  Serial.begin(9600);

}



void loop(){
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);

  if (Serial.available() > 0) {
    led = Serial.readStringUntil('\n');
    for (i = 0; i < led.toInt(); i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(150);
      digitalWrite(LED_BUILTIN, LOW);
      delay(150);
    }
  }

  if (yValue > 900) {
    digitalWrite(led2, HIGH);
    digitalWrite(led1, LOW); 
    Serial.write("stand"); 
    delay(100);
  } else if (yValue < 200) {
    digitalWrite(led2, LOW); 
    digitalWrite(led1, HIGH);  
    Serial.write("hitme");
    delay(100);
  } else {
    digitalWrite(led2, LOW); 
    digitalWrite(led1, LOW);  
  }
}
