//================== Servo & Pump ==================
#define PUMP_PIN 4
//================== L298N Motor Driver ==================
#define ENA 9
#define IN1 8
#define IN2 7
#define IN3 6
#define IN4 5
#define ENB 10
//================== Flame Sensors ==================
#define LEFT_FLAME A0
#define FRONT_FLAME A1
#define RIGHT_FLAME A2
int motorSpeed = 170;
// Adjust after checking Serial Monitor
int flameThreshold = 500;
int stopThreshold = 250;

void setup()
{
  Serial.begin(9600);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, LOW);
  
  analogWrite(ENA, motorSpeed);
  analogWrite(ENB, motorSpeed);
  
  stopRobot();
  
  Serial.println("Fire Fighting Robot Ready");
}

void loop()
{
  int left = analogRead(LEFT_FLAME);
  int front = analogRead(FRONT_FLAME);
  int right = analogRead(RIGHT_FLAME);

  Serial.print("Left: ");
  Serial.print(left);
  Serial.print(" Front: ");
  Serial.print(front);
  Serial.print(" Right: ");
  Serial.println(right);
  
  //================== Fire Reached ==================
  if(front < stopThreshold)
  {
    stopRobot();
    Serial.println("Fire Reached");
    digitalWrite(PUMP_PIN, HIGH);
    extinguishFire();
    digitalWrite(PUMP_PIN, LOW);
    delay(1000);
  }
  //================== Fire in Front ==================
  else if(front < flameThreshold)
  {
    forward();
  }
  //================== Fire on Left ==================
  else if(left < flameThreshold)
  {
    turnLeft();
  }
  //================== Fire on Right ==================
  else if(right < flameThreshold)
  {
    turnRight();
  }
  //================== Search ==================
  else
  {
    searchFire();
  }
  delay(50);
}

//================== Motor Functions ==================
void forward()
{
  analogWrite(ENA, 170);
  analogWrite(ENB, 170);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnLeft()
{
  analogWrite(ENA, 220);
  analogWrite(ENB, 100);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight()
{
  analogWrite(ENA, 100);
  analogWrite(ENB, 220);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopRobot()
{
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void searchFire()
{
  // Rotate to search for fire
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void extinguishFire()
{
  Serial.println("Extinguishing Fire...");
  Serial.println("Fire Extinguished");
}
