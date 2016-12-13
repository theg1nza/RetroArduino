#define  c     3830     // 261 Hz 
#define  d     3400     // 294 Hz 
#define  e     3038     // 329 Hz 
#define  f     2864     // 349 Hz 
#define  h     2703     // 370 Hz
#define  g     2550     // 392 Hz 
#define  a     2272     // 440 Hz 
#define  b     2028     // 493 Hz 
#define  C     1912     // 523 Hz 
#define  D     1703     // 587 Hz
#define  E     1517     // 659 Hz
#define  F     1433     // 698 Hz
#define  G     1275      // 784 Hz
#define  A     1136      // 880 Hz
#define  R     0

// SETUP ============================================
// Set up speaker on a PWM pin (digital 9, 10 or 11)
const int speakerOut = 9;
const int bo1 = 2;
const int bo2 = 3;
const int bo3 = 4;
const int bo4 = 5;
// Do we want debugging on serial out? 1 for yes, 0 for no
int DEBUG = 1;
int etatbo1;
int etatbo2;
int etatbo3;
int etatbo4;

void setup() { 
  pinMode(bo1, INPUT);
  pinMode(bo2, INPUT);
  pinMode(bo3, INPUT);
  pinMode(bo4, INPUT);
  
  pinMode(speakerOut, OUTPUT);
  if (DEBUG) { 
    Serial.begin(9600); // Set serial out if we want debugging
  } 
}

// MELODY and TIMING  =======================================
//  melody[] is an array of notes, accompanied by beats[], 
//  which sets each note's relative length (higher #, longer note)
int melody4[] = {R,  d,  g,  g, a, g, h, e,  c,  e,  a,  a, b, a, g, h,  d,  d,  b,  b, C, b, a, g,  e,  d, d, e,  a,  h,  g,  d,  g,  g,  g,  h,  h,  g,  h,  e,  d,  a,  b,  a,  g,  D,  d,  d, d, e,  a,  h,  g,  d,  g,  g, a, g, h, e,  c,  e,  a,  a, b, a, g, h,  d,  d,  b,  b, C, b, a, g,  e,  d, d, e,  a,  h,  g,  R};
int melody3[] = {R,  R,  d,  g,  g, g,  a,  b,  b, b,  b, a, b, C,  h,  a,  g,  R, D, D,  b, E,  D, D,  C, C,  C, C,  a, D,  C, C,  b, b,  d,  g,  g, g,  a,  b,  b, b,  b, a, b, C,  h,  a,  g,  R};
int melody2[] = {g,  C,  C,  C,  D,  C,  C, D, E,  E,  E,  F,  E,  D,  C,  C, C, C, b, a, g,  g, g, C,  C, C, b, C, D,  g,  C,  C,  C,  D,  C,  C, D, E,  E,  E,  F,  E,  D,  C,  C, C, C, b, a, g,  g, g, C, C, C,  D,  D, C};
int melody1[] = {g,  E,  D,  C,   g,  g,  g, g,  E,  D,  C,  a,  R,  a,  F,  E,  D,  b,  R,  G,  G,  F,  D, E,  R,   g,  E,  D,  C,  g,  R,  g,  E,  D,  C,  a,  a,  a,  F,  E,  D,  G,  G,  G,  G,  A,  G,  F,  D,  C,  G,  E,  E,  E,  E,  E,  E,  E,  G,  C,  D, E,  R,  F,  F,  F,  F, F,  E,  E,  E, E, E,  D,  D,  E,  D,  G,  E,  E,  E,  E,  E,  E,  E,  G,  C,  D, E,  R,  F,  F,  F,  F, F,  E,  E,  E, E, G,  G,  F,  D,  C};

int beats4[]  = {32, 16, 16, 8, 8, 8, 8, 16, 16, 16, 16, 8, 8, 8, 8, 16, 16, 16, 16, 8, 8, 8, 8, 16, 16, 8, 8, 16, 16, 16, 32, 16, 16, 16, 16, 32, 16, 16, 16, 16, 32, 16, 16, 16, 16, 16, 16, 8, 8, 16, 16, 16, 32, 16, 16, 8, 8, 8, 8, 16, 16, 16, 16, 8, 8, 8, 8, 16, 16, 16, 16, 8, 8, 8, 8, 16, 16, 8, 8, 16, 16, 16, 32, 16};
int beats3[]  = {16, 16, 16, 12, 4, 16, 16, 12, 4, 24, 8, 8, 8, 16, 16, 16, 16, 8, 8, 12, 4, 24, 8, 12, 4, 24, 8, 12, 4, 24, 8, 12, 4, 16, 16, 12, 4, 16, 16, 12, 4, 24, 8, 8, 8, 16, 16, 16, 16, 16};
int beats2[]  = {16, 16, 16, 16, 16, 48, 8, 8, 16, 16, 16, 16, 48, 16, 24, 8, 8, 8, 8, 8, 48, 8, 8, 32, 8, 8, 8, 8, 48, 16, 16, 16, 16, 16, 48, 8, 8, 16, 16, 16, 16, 48, 16, 24, 8, 8, 8, 8, 8, 48, 8, 8, 32, 8, 8, 8, 8, 64}; 
int beats1[]  = {16, 16, 16, 16,  48, 8,  8, 16, 16, 16, 16, 48, 16, 16, 16, 16, 16, 48, 16, 16, 16, 16, 16, 48, 16, 16, 16, 16, 16, 48, 16, 16, 16, 16, 16, 48, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 32, 32, 16, 16, 32, 16, 16, 32, 16, 16, 24, 8, 48, 16, 16, 16, 24, 8, 16, 16, 16, 8, 8, 16, 16, 16, 16, 32, 32, 16, 16, 32, 16, 16, 32, 16, 16, 24, 8, 48, 16, 16, 16, 24, 8, 16, 16, 16, 8, 8, 16, 16, 16, 16, 64};

int MAX_COUNT4 = sizeof(melody4) / 2;
int MAX_COUNT3 = sizeof(melody3) / 2;
int MAX_COUNT2 = sizeof(melody2) / 2; // Melody length, for looping.
int MAX_COUNT1 = sizeof(melody1) / 2; // Melody length, for looping.

// Set overall tempo
long tempo4 = 20000;
long tempo3 = 55000;
long tempo2 = 40000;
long tempo1 = 20000;
// Set length of pause between notes
int pause = 1000;
// Loop variable to increase Rest length
int rest_count4 = 30;
int rest_count3 = 30;
int rest_count2 = 60; //<-BLETCHEROUS HACK; See NOTES
int rest_count1 = 30;


int tone_ = 0;
int beat = 0;
long duration  = 0;

// PLAY TONE  ==============================================
// Pulse the speaker to play a tone for a particular duration
void playTone1() {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    } 
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count1; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                 
}

void jgb() {
  for (int i=0; i<MAX_COUNT1; i++) {
    tone_ = melody1[i];
    beat = beats1[i];

    duration = beat * tempo1; // Set up timing

    playTone1(); 
    // A pause between notes...
    delayMicroseconds(pause);

    if (DEBUG) { // If debugging, report loop, tone, beat, and duration
      Serial.print(i);
      Serial.print(":");
      Serial.print(beat);
      Serial.print(" ");    
      Serial.print(tone_);
      Serial.print(" ");
      Serial.println(duration);
    }
  }
}

void playTone2() {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    } 
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count2; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                 
}

void ppn() {
  for (int i=0; i<MAX_COUNT2; i++) {
    tone_ = melody2[i];
    beat = beats2[i];

    duration = beat * tempo2; // Set up timing

    playTone2(); 
    // A pause between notes...
    delayMicroseconds(pause);

    if (DEBUG) { // If debugging, report loop, tone, beat, and duration
      Serial.print(i);
      Serial.print(":");
      Serial.print(beat);
      Serial.print(" ");    
      Serial.print(tone_);
      Serial.print(" ");
      Serial.println(duration);
    }
  }
}


void playTone3() {
    long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    } 
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count3; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                 
}

void oct() {
  for (int i=0; i<MAX_COUNT3; i++) {
    tone_ = melody3[i];
    beat = beats3[i];

    duration = beat * tempo3; // Set up timing

    playTone3(); 
    // A pause between notes...
    delayMicroseconds(pause);

    if (DEBUG) { // If debugging, report loop, tone, beat, and duration
      Serial.print(i);
      Serial.print(":");
      Serial.print(beat);
      Serial.print(" ");    
      Serial.print(tone_);
      Serial.print(" ");
      Serial.println(duration);
    }
  }
}

void playTone4() {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    } 
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count4; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                 
}

void wmc() {
  for (int i=0; i<MAX_COUNT4; i++) {
    tone_ = melody4[i];
    beat = beats4[i];

    duration = beat * tempo4; // Set up timing

    playTone1(); 
    // A pause between notes...
    delayMicroseconds(pause);

    if (DEBUG) { // If debugging, report loop, tone, beat, and duration
      Serial.print(i);
      Serial.print(":");
      Serial.print(beat);
      Serial.print(" ");    
      Serial.print(tone_);
      Serial.print(" ");
      Serial.println(duration);
    }
  }
}

// LET THE WILD RUMPUS BEGIN =============================
void loop() {
  etatbo1 = digitalRead(bo1);
  etatbo2 = digitalRead(bo2);
  etatbo3 = digitalRead(bo3);
  etatbo4 = digitalRead(bo4);
  
  playmelody();
}
void playmelody() {
  
  if (etatbo1 == LOW && etatbo2 == HIGH && etatbo3 == HIGH && etatbo4 == HIGH) {
    jgb();
  }

  else if (etatbo1 == HIGH && etatbo2 == LOW && etatbo3 == HIGH && etatbo4 == HIGH) {
    ppn();
  }

  else if (etatbo1 == HIGH && etatbo2 == HIGH && etatbo3 == LOW && etatbo4 == HIGH) {
    oct();
  }

  else if (etatbo1 == HIGH && etatbo2 == HIGH && etatbo3 == HIGH && etatbo4 == LOW) {
    wmc();
  }

  else {
    loop();
  }
}

// Set up a counter to pull from melody[] and beats[]
  

