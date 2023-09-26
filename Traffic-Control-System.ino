// Ultrasonic Sensor Pins (Analog)
const int mainRoadSensorTrigger = A4;
const int mainRoadSensorEcho = A5;
const int entryGateSensorTrigger = A0;
const int entryGateSensorEcho = A1;
const int exitGateSensorTrigger = A2;
const int exitGateSensorEcho = A3;

// Traffic Light Control Pins
const int mainRoadRed = 9;
const int mainRoadGreen = 10;
const int pedestrianRed = 4;
const int pedestrianGreen = 5;
const int parkingRed = 11;
const int parkingGreen = 6;
const int buzzer =2;

//motor Pins
const int boomGateEntryMotorPin1 = 7;
const int boomGateEntryMotorPin2 = 3;
const int boomGateExitMotorPin1 = 12;
const int boomGateExitMotorPin2 = 13;

// Push Button for Pedestrian Signal
const int pedestrianButton = 8;

long duration, distance, mainRoadSensor,entryGateSensor,exitGateSensor;

void setup() {
  Serial.begin (9600);
  
  //Ultrasoic Sensors
  pinMode(mainRoadSensorTrigger, OUTPUT);
  pinMode(mainRoadSensorEcho, INPUT);
  pinMode(entryGateSensorTrigger, OUTPUT);
  pinMode(entryGateSensorEcho, INPUT);
  pinMode(exitGateSensorTrigger, OUTPUT);
  pinMode(exitGateSensorEcho, INPUT);
  
  pinMode(mainRoadRed, OUTPUT);
  pinMode(mainRoadGreen, OUTPUT);
  pinMode(pedestrianRed, OUTPUT);
  pinMode(pedestrianGreen, OUTPUT);
  pinMode(parkingRed, OUTPUT);
  pinMode(parkingGreen, OUTPUT);
  pinMode(buzzer, OUTPUT);

  //motorPins
  pinMode(boomGateEntryMotorPin1, OUTPUT);
  pinMode(boomGateEntryMotorPin2, OUTPUT);
  pinMode(boomGateExitMotorPin1, OUTPUT);
  pinMode(boomGateExitMotorPin2, OUTPUT);

  pinMode(pedestrianButton, INPUT_PULLUP);

  InitialState();
}

void loop() {
  UltrasonicSensor(mainRoadSensorTrigger, mainRoadSensorEcho);
  mainRoadSensor = distance;
  delay(10);

  UltrasonicSensor(entryGateSensorTrigger, entryGateSensorEcho);
  entryGateSensor = distance;
  delay(10);

  UltrasonicSensor(exitGateSensorTrigger, exitGateSensorEcho);
  exitGateSensor = distance;
  delay(10);

  byte pedestrianButtonState = digitalRead(pedestrianButton);

  //Print Values Using Serial Monitor
  Serial.print("mainRoadSensor : ");
  Serial.println(mainRoadSensor);
  Serial.print("entryGateSensor : ");
  Serial.println(entryGateSensor);
  Serial.print("exitGateSensor : ");
  Serial.println(exitGateSensor);
  
  if ((pedestrianButtonState == HIGH) &&  mainRoadSensor<20) {
    digitalWrite(mainRoadGreen, HIGH);
    digitalWrite(pedestrianRed, HIGH);

    digitalWrite(mainRoadRed, HIGH);
    delay(2000);

    digitalWrite(mainRoadGreen, LOW);
    delay(1000);

    digitalWrite(pedestrianRed, LOW); 
    digitalWrite(pedestrianGreen, HIGH);
    delay(3000);

    digitalWrite(pedestrianGreen, LOW);
    digitalWrite(pedestrianRed, HIGH); 
    delay(1000);

    digitalWrite(mainRoadGreen, HIGH);
    delay(1000);

    digitalWrite(mainRoadGreen, LOW);
    digitalWrite(pedestrianGreen, LOW);
    delay(1000);

    digitalWrite(buzzer, HIGH);
    digitalWrite(parkingRed, HIGH);
    digitalWrite(parkingGreen, LOW);
    boomGateMotorState('I');

    InitialState();
  }

  else if (mainRoadSensor>20 && (entryGateSensor<20 || exitGateSensor<20)) {
    for (int i = 2; i == 0; i--) {
      digitalWrite(pedestrianRed, LOW);
      delay(500);
      digitalWrite(pedestrianRed, HIGH);
      delay(500);
    }
    digitalWrite(pedestrianRed, HIGH);
    digitalWrite(pedestrianGreen, LOW);

    digitalWrite(mainRoadRed, HIGH);
    digitalWrite(mainRoadGreen, LOW);
    
    digitalWrite(parkingRed, LOW);
    digitalWrite(parkingGreen, HIGH);

    if (entryGateSensor<20 && exitGateSensor<20){
      boomGateMotors();
    }else if (exitGateSensor<20){
      boomGateMotorState('X');
    }else if (entryGateSensor<20) {
      boomGateMotorState('E'); 
    }
    
    digitalWrite(buzzer, LOW);

    InitialState();
  }
  else if (mainRoadSensor<20) {
    digitalWrite(mainRoadRed, LOW);
    digitalWrite(mainRoadGreen, HIGH);
    digitalWrite(pedestrianRed, HIGH);
    digitalWrite(pedestrianGreen, LOW);
    digitalWrite(parkingRed, HIGH);
    digitalWrite(parkingGreen, LOW);
    digitalWrite(buzzer, LOW);
    boomGateMotorState('I');
  }
  else{
    InitialState();
  }
}


//Sensor Distance Calc..
bool UltrasonicSensor(int trigPin,int echoPin){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
}

void InitialState() {
  digitalWrite(mainRoadRed, HIGH);
  digitalWrite(mainRoadGreen, LOW);
  digitalWrite(pedestrianRed, LOW);
  digitalWrite(pedestrianGreen, HIGH);
  digitalWrite(parkingRed, HIGH);
  digitalWrite(parkingGreen, LOW);
  digitalWrite(buzzer, HIGH);
  boomGateMotorState('I');
}

void boomGateMotorState (char state) {          //How to call => boomGateMotorState('state'); //EntryMotor    ExitMotor   InitialState
  if (state == 'E') {
    digitalWrite(boomGateEntryMotorPin1, HIGH);
    digitalWrite(boomGateEntryMotorPin2, LOW);
    digitalWrite(boomGateExitMotorPin1, LOW);
    digitalWrite(boomGateExitMotorPin2, LOW);
    delay(1000);
    digitalWrite(boomGateEntryMotorPin1, LOW);
    digitalWrite(boomGateEntryMotorPin2, HIGH);
    digitalWrite(boomGateExitMotorPin1, LOW);
    digitalWrite(boomGateExitMotorPin2, LOW);
    delay(1000);
    digitalWrite(boomGateEntryMotorPin1, LOW);
    digitalWrite(boomGateEntryMotorPin2, LOW);
    digitalWrite(boomGateExitMotorPin1, LOW);
    digitalWrite(boomGateExitMotorPin2, LOW);
    delay(1000);
  }
  else if (state == 'X') {
    digitalWrite(boomGateEntryMotorPin1, LOW);
    digitalWrite(boomGateEntryMotorPin2, LOW);
    digitalWrite(boomGateExitMotorPin1, LOW);
    digitalWrite(boomGateExitMotorPin2, HIGH);
    delay(1000);
    digitalWrite(boomGateEntryMotorPin1, LOW);
    digitalWrite(boomGateEntryMotorPin2, LOW);
    digitalWrite(boomGateExitMotorPin1, HIGH);
    digitalWrite(boomGateExitMotorPin2, LOW);
    delay(1000);
    digitalWrite(boomGateEntryMotorPin1, LOW);
    digitalWrite(boomGateEntryMotorPin2, LOW);
    digitalWrite(boomGateExitMotorPin1, LOW);
    digitalWrite(boomGateExitMotorPin2, LOW);
    delay(1000);
  }
  else if (state == 'I') {
    digitalWrite(boomGateEntryMotorPin1, LOW);
    digitalWrite(boomGateEntryMotorPin2, LOW);
    digitalWrite(boomGateExitMotorPin1, LOW);
    digitalWrite(boomGateExitMotorPin2, LOW);
  }
}

void boomGateMotors(){
    digitalWrite(boomGateEntryMotorPin1, HIGH);
    digitalWrite(boomGateEntryMotorPin2, LOW);
    digitalWrite(boomGateExitMotorPin1, LOW);
    digitalWrite(boomGateExitMotorPin2, HIGH);
    delay(1000);
    digitalWrite(boomGateEntryMotorPin1, LOW);
    digitalWrite(boomGateEntryMotorPin2, HIGH);
    digitalWrite(boomGateExitMotorPin1, HIGH);
    digitalWrite(boomGateExitMotorPin2, LOW);
    delay(1000);
    digitalWrite(boomGateEntryMotorPin1, LOW);
    digitalWrite(boomGateEntryMotorPin2, LOW);
    digitalWrite(boomGateExitMotorPin1, LOW);
    digitalWrite(boomGateExitMotorPin2, LOW);
    delay(1000);
}
