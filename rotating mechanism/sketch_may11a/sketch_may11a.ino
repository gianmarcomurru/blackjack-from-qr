// Define pin connections & motor's steps per revolution
const int dirPinRM = 2;
const int stepPinRM = 3;
const int stepsPerRevolutionRM = 200;

void setup()
{
  // Declare pins as Outputs
  pinMode(stepPinRM, OUTPUT);
  pinMode(dirPinRM, OUTPUT);
}
void loop()
{
  // Set motor direction clockwise
  digitalWrite(dirPinRM, HIGH);

  // Spin motor slowly
  for(int x = 0; x < stepsPerRevolutionRM; x++)
  {
    digitalWrite(stepPinRM, HIGH);
    delayMicroseconds(2000);
    digitalWrite(stepPinRM, LOW);
    delayMicroseconds(2000);
  }
  delay(1000); // Wait a second

  // Set motor direction counterclockwise
  digitalWrite(dirPinRM, LOW);

  // Spin motor quickly
  for(int x = 0; x < stepsPerRevolutionRM; x++)
  {
    digitalWrite(stepPinRM, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPinRM, LOW);
    delayMicroseconds(1000);
  }
  delay(1000); // Wait a second
}
