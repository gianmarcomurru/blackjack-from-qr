#define joyX A0
#define joyY A1
#define led1 13
#define led2 7
 
void setup() {
  Serial.begin(9600);
  pinMode(led1, OUTPUT); 
  pinMode(led2, OUTPUT); 
}

int xValue = 0;
int yValue = 0; 
 
void loop() {
  // put your main code here, to run repeatedly:
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
 
  //print the values with to plot or view
  Serial.print(xValue);
  Serial.print("\t");
  Serial.println(yValue);


  // change behaviour 
  if (yValue > 900) {
    digitalWrite(led2, HIGH); 
    digitalWrite(led1, LOW); 
  } else if (yValue < 200) {
    digitalWrite(led2, LOW); 
    digitalWrite(led1, HIGH);  
  } else {
    digitalWrite(led2, LOW); 
    digitalWrite(led1, LOW);  
  }
}
