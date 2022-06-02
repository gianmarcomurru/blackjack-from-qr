#define joyX A0
#define joyY A1
#define joyP 8 //Pressed

void setup() {
  Serial.begin(9600);
  pinMode(joyP,INPUT_PULLUP);
}

int xValue = 0;
int yValue = 0;
int joyButton = 0; // 0 pressed, 1 not pressed

void loop() {
  // put your main code here, to run repeatedly:
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  joyButton = digitalRead(joyP);

  // //print the values with to plot or view
  // Serial.print(xValue);
  // Serial.print("\t");
  // Serial.println(yValue);


  // change behaviour
  if (joyButton == 0) {
    Serial.write("joyButton pressed\n");
    delay(750);
  }
  if (yValue > 900) {
    Serial.write("stand\n");
    delay(750);
  } else if (yValue < 200) {
    Serial.write("hitme\n");
    delay(750);
  }
}
