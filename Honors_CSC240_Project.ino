/*
 * Title:  Honors Synthesizer
 * Desc:   This program emulates the functions of a synthesizer
 * Author: Jacob Porter
 * Date:   5 / 8 / 2023
 */



#define VRX_PIN  A0 // Arduino pin connected to VRX pin in joystick
#define VRY_PIN  A1 // Arduino pin connected to VRY pin in joystick

int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis

const int trigPin = 9; // Trigger Pin for ultrasonic Sensor
const int echoPin = 10; // Echo Pin for ultrasonic Sensor
float duration, distance; // Floats used to calculate total distance

int buttonOne = 1;  // Pin 1 for Button one used for ultrasonic Sensor
int buttonTwo = 2;  // Pin 2 for Button two used for arrpegio
int buttonThree = 3; // Pin 3 for button three used for joystick
int buttonFour = 4; // Pin 4 for button four used for starwars theme
int buttonFive = 5; // Pin 5 for button five used for octaves

int soundOut = 13; // Pin out for our 1/4 inch line

void setup() {

  // put your setup code here, to run once:
  pinMode(buttonOne, INPUT_PULLUP); // Read button 1 as input
  pinMode(buttonTwo, INPUT_PULLUP); // Read button 2 as input
  pinMode(buttonThree, INPUT_PULLUP); // Read button 3 as input
  pinMode(buttonFour, INPUT_PULLUP); // Read button 4 as input
  pinMode(buttonFive, INPUT_PULLUP); // Read button 4 as input
  
  pinMode(soundOut, OUTPUT); // Pin 13 with sound out will be output for tone() function
  pinMode(trigPin, OUTPUT); // Trigger pin for ultrasonic will be output 
  pinMode(echoPin, INPUT_PULLUP); // Echo pin for ultrasonic will be an input pin
  Serial.begin(9600); // Start reading serial values at 9600
}

void loop() {
  
  xValue = analogRead(VRX_PIN); // Set int values for the data coming in through joystick in x direction
  yValue = analogRead(VRY_PIN); // Set int values for the data coming in through joystick in y direction

  // put your main code here, to run repeatedly:

  // Setup for pulsing the ultrasonic
  digitalWrite(trigPin, LOW); // Write the pin to Low
  delay(2); // Wait 2ms
  digitalWrite(trigPin, HIGH); // update pin to High
  delay(20); // Wait 20ms
  digitalWrite(trigPin, LOW); // Write the pin to low again
  
  // Calculate the math behind each pulse
  duration = pulseIn(echoPin, HIGH);  // Value when the echo pulse is HIGH
  distance = (duration*.0343)/2; // Turn that value into distance of [cm]

    // Motion Sensor (Button ONE)
    if(digitalRead(buttonOne) == LOW) {
       motionSensor();
    }

    // Arpegio (Button TWO)
    if(digitalRead(buttonTwo) == LOW) {
       arpegio();   
    }
    

    // Joy stick functionality (Button THREE)
    if(digitalRead(buttonThree) == LOW) {
      int noteJoy = 440;
      int delayValue = 10;
      for(int i = 0; i < 12; i++) {
        tone(soundOut, noteJoy, delayValue);
        delayValue = yValue + 20;
        noteJoy = xValue + 200;
        }
     }

     // Star Wars (Button FOUR)
     if(digitalRead(buttonFour) == LOW) {
        starWars();
        }

      // Octave Player (Button FIVE)
      if(digitalRead(buttonFive) == LOW) {
        octaves();
        }
}

// motionSensor() uses ultrasonic sensor to play the C major Scale
void motionSensor() {

   double noteC = 256; // Our base note C 
   double newNote = 1.0; // new note to be modified for each interval
   // Each conditional uses 10 centimeter increments
    if((distance > 0) && (distance < 10)) { // Plays C 
      tone(soundOut, noteC, 100);
      }
      
    if((distance > 10) && (distance < 20)) { // Plays D
      newNote = noteC * (9.0/8.0);
      tone(soundOut, newNote, 100);
    }
    
    if((distance > 20) && (distance < 30)) { // Plays E
      newNote = noteC * (81.0 / 64.0);
      tone(soundOut, newNote, 100);
    }
            
    if((distance > 30) && (distance < 40)) { // Plays F
      newNote = noteC * (4.0 / 3.0);
      tone(soundOut, newNote, 100);
    }
    
    if((distance > 40) && (distance < 50)) { // Plays G
      newNote = noteC * (3.0 / 2.0);
      tone(soundOut, newNote, 100);
    }
      
    if((distance > 50) && (distance < 60)) { // Plays A
      newNote = noteC * (27.0 / 16.0);
      tone(soundOut, newNote, 100);
    }
    
    if((distance > 60) && (distance < 70)) { // Plays B
      newNote = noteC * (243.0 / 128.0);
      tone(soundOut, newNote, 100);
    }

    if((distance > 70) && (distance < 80)) { // Plays C    
        newNote = noteC * 2;
        tone(soundOut, newNote, 100);
    }
     
 
      
 }


// arpegio() plays the notes C, D, G, B, C, B, G, D, C
 void arpegio() {
    double baseNote = 128.0; // Base Note is a C
    double newNote = 1.0;

    for(int i = 0; i < 2; i++){
    // Start the sequence
    tone(soundOut, baseNote, 200); // Plays a C
    delay(200);

    newNote = baseNote * (9.0 / 8.0);
    tone(soundOut, newNote, 200); // Plays a D
    delay(200);


    newNote = baseNote * (3.0 / 2.0);
    tone(soundOut, newNote, 200); // Plays a G
    delay(200);

    newNote = baseNote * (243.0 / 128.0);
    tone(soundOut, newNote, 200); // Plays a B
    delay(200);

    newNote = baseNote * (2.0 / 1.0);
    tone(soundOut, newNote, 200); // Plays a C (octave up)
    delay(200);
    
    newNote = baseNote * (243.0 / 128.0);
    tone(soundOut, newNote, 200); // Plays a B
    delay(200);

    newNote = baseNote * (3.0 / 2.0);
    tone(soundOut, newNote, 200); // Plays a G
    delay(200);    
   

    newNote = baseNote * (9.0 / 8.0);
    tone(soundOut, newNote, 200); // Plays a D
    delay(200);

    newNote = baseNote * (1.0 / 1.0);
    tone(soundOut, newNote, 200); // Plays a C
    delay(200);

    baseNote = baseNote * (4.0 / 3.0);
    tone(soundOut, baseNote, 200); // Plays a C
    delay(200);

    newNote = baseNote * (9.0 / 8.0);
    tone(soundOut, newNote, 200); // Plays a D
    delay(200);


    newNote = baseNote * (3.0 / 2.0);
    tone(soundOut, newNote, 200); // Plays a G
    delay(200);

    newNote = baseNote * (243.0 / 128.0);
    tone(soundOut, newNote, 200); // Plays a B
    delay(200);

    newNote = baseNote * (2.0 / 1.0);
    tone(soundOut, newNote, 200); // Plays a C (octave up)
    delay(200);
    
    newNote = baseNote * (243.0 / 128.0);
    tone(soundOut, newNote, 200); // Plays a B
    delay(200);

    newNote = baseNote * (3.0 / 2.0);
    tone(soundOut, newNote, 200); // Plays a G
    delay(200);    
   

    newNote = baseNote * (9.0 / 8.0);
    tone(soundOut, newNote, 200); // Plays a D
    delay(200);

    newNote = baseNote * (1.0 / 1.0);
    tone(soundOut, newNote, 200); // Plays a C
    delay(200);
    }
  }

// starWars() plays the main theme from Star Wars using intervals
  void starWars() {
    double baseNote = 256.0; // Base note is a 'C'
    double newNote = 1.0; // NewNote for when we modify the base note to play intervals

    // This plays star wars theme
    for(int i = 0; i < 2; i++){
    tone(soundOut, baseNote, 1000);
    delay(1000);
    
    newNote = baseNote * (3.0 / 2.0);
    tone(soundOut, newNote, 1000);
    delay(1000);

    newNote = baseNote * (4.0 / 3.0);
    tone(soundOut, newNote, 500);
    delay(200);

    newNote = baseNote * (81.0 / 64.0);
    tone(soundOut, newNote, 500);
    delay(200);

    newNote = baseNote * (9.0 / 8.0);
    tone(soundOut, newNote, 500);
    delay(200);

    newNote = baseNote * (2.0 / 1.0);
    tone(soundOut, newNote, 1000);
    delay(1000);

    newNote = baseNote * (3.0 / 2.0);
    tone(soundOut, newNote, 1000);
    delay(1000);

    newNote = baseNote * (4.0 / 3.0);
    tone(soundOut, newNote, 500);
    delay(200);

    newNote = baseNote * (81.0 / 64.0);
    tone(soundOut, newNote, 500);
    delay(200);

    newNote = baseNote * (9.0 / 8.0);
    tone(soundOut, newNote, 500);
    delay(200);

    newNote = baseNote * (2.0 / 1.0);
    tone(soundOut, newNote, 1000);
    delay(1000);

    newNote = baseNote * (3.0 / 2.0);
    tone(soundOut, newNote, 1000);
    delay(1000);

    newNote = baseNote * (4.0 / 3.0);
    tone(soundOut, newNote, 300);
    delay(300);
    
    newNote = baseNote * (81.0 / 64.0);
    tone(soundOut, newNote, 300);
    delay(300);    

    newNote = baseNote * (4.0 / 3.0);
    tone(soundOut, newNote, 500);
    delay(500);    

    newNote = baseNote * (9.0 / 8.0);
    tone(soundOut, newNote, 1000);
    delay(1000); // End of the main theme
    }
 }
     // Octaves function plays the octave of a note 4 times
    void octaves() {
      double baseNoteA = 440.0; // Starting tone is 'A'
      double newNote = 1.0;
      for(int i = 0; i < 5; i++) {
        tone(soundOut, baseNoteA, 100);
        newNote = baseNoteA * 2.0;
        delay(100);
        tone(soundOut, newNote, 100);
        }
      }
  
