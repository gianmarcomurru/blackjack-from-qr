int i;            // iterator
// LED on Pin 13 for digital on/off demo
int ledPin = LED_BUILTIN;
String led;

void setup()
{
  // LED on Pin 13 for digital on/off demo
  pinMode(ledPin, OUTPUT);
  
  // Open the serial connection, 9600 baud
  Serial.begin(9600);

}


void loop(){
  if (Serial.available() > 0) {
    led = Serial.readStringUntil('\n');
    for (i = 0; i < led.toInt(); i++) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(100);
      digitalWrite(LED_BUILTIN, LOW);
      delay(100);
    }
  }
}
