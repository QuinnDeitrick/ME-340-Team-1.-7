
// Clockwise and counter-clockwise definitions.
// Depending on how you wired your motors, you may need to swap.
#define FORWARD  0
#define REVERSE 1

// Motor definitions to make life easier:
#define MOTOR_R 0
#define MOTOR_L 1

// Pin Assignments //
//Default pins:
#define DIRA 2 // Direction control for motor A
#define PWMA 3  // PWM control (speed) for motor A
#define DIRB 4 // Direction control for motor B
#define PWMB 11 // PWM control (speed) for motor B

int DEFAULTV = 200;

int phototransR = 9; //the digital input pin
int phototransL = 10; //the digital input pin
//int phototransA = A0;//the analog input pin
//decrlaring variables to store the input values
int valR=0;
int valL=0;
//int aval=0;

// the setup routine runs once when you press reset:
void setup() {
  //set input pins
  pinMode(phototransR, INPUT);
    pinMode(phototransL, INPUT);
//  pinMode(phototransA, INPUT);
  setupArdumoto(); // Set all pins as outputs
  
  }

// the loop routine runs over and over again forever:
void loop() {
  //read the input values from the digital and analog pins
  valR=digitalRead(phototransR);
   valL=digitalRead(phototransL);
  //aval = analogRead(phototransA);

  // both sensors straddle line, reads white means head stright forward
   
  // Drive motor A and B at medium speed in the direction indicated by the 
  //phototransistor
  
  if(valR==LOW && valL==LOW){ //BOTH ON WHITE
    
  driveArdumoto(MOTOR_R, FORWARD, DEFAULTV); // Set motor A to run at half
  driveArdumoto(MOTOR_L, FORWARD, DEFAULTV);  // Set motor B to FORWARD at half
  }
  else if (valR==HIGH && valL==LOW){  //right on black left on white
    // turn rught
  driveArdumoto(MOTOR_R, FORWARD, 0.5*DEFAULTV); // Set motor A to run at half
  driveArdumoto(MOTOR_L, FORWARD, DEFAULTV);  // Set motor B to FORWARD at half
   
  }
  
  else if (valR==LOW && valL==HIGH){ //rihgt on white, left on black
    // turn left
  driveArdumoto(MOTOR_R, FORWARD, DEFAULTV); // Set motor A to run at half
  driveArdumoto(MOTOR_L, FORWARD, 0.5*DEFAULTV);  // Set motor B to FORWARD at half
  }
  
  else{ //both on black
    // stop, spin in place, go backwards, random input
  stopArdumoto(MOTOR_R);  // STOP motor A 
  stopArdumoto(MOTOR_L);  // STOP motor B 
  }
 }


void setupArdumoto()
{
  // All pins should be setup as outputs:
  pinMode(PWMA, OUTPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  // Initialize all pins as low:
  digitalWrite(PWMA, LOW);
  digitalWrite(PWMB, LOW);
  digitalWrite(DIRA, LOW);
  digitalWrite(DIRB, LOW);
}

// stopArdumoto makes a motor stop
void stopArdumoto(byte motor)
{
  driveArdumoto(motor, 0, 0);
}
// driveArdumoto drives 'motor' in 'dir' direction at 'spd' speed
void driveArdumoto(byte motor, byte dir, byte spd)
{
  if (motor == MOTOR_A)
  {
    digitalWrite(DIRA, dir);
    analogWrite(PWMA, spd);
  }
  else if (motor == MOTOR_B)
  {
    digitalWrite(DIRB, dir);
    analogWrite(PWMB, spd);
  }  
}
