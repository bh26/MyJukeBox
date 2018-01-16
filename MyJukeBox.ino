/**************************************************************************************
 * Capacitive Jukebox
 * done by Bernard Haddad
 * january 2018
 * with borrowings from many kind people that I did not keep track from 
 * the beginning.
 * The main step for music is from Mike Putnam Pitches.h, then completed by the beep() functtion 
 * coming from someone else.
 * Mission impossible rebuilt from Andre Thomas sketch
 * Frozen from Orlando S. Hoilett ( http://www.instructables.com/member/ohoilett/)
 * Fur elise from Emmanuel at http://repairmypc.net/2017/08/test-post/
 * I have 7 capacitive aluminium foils that trigger one note from the buzzer (Do, Re, Mi, Fa Sol, La, Si),
 * then one specific song.
 * For each note in the songs 3 LEDs are advancing in the WS2801 strip, and change color.
 * ***********************************************************************************
*/
#include "FastLED.h"
#include "pitches.h"

// notes in the melody:*
int buzzPin = 13;
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
//******************




//******************
#define NUM_LEDS1 32
#define DATA_PIN1 2
#define CLOCK_PIN1 3
CRGB leds1[NUM_LEDS1];

   static uint8_t hueth = 0;
int counter;
int ith = 0;
int ith_1 = 0;
int ith_2 = 0;

#include <CapacitiveSensor.h>
CapacitiveSensor LeDo = CapacitiveSensor(12,4); //10M Resistor between pins 12 and 7, you may also connect an antenna on pin 7
CapacitiveSensor LeRe = CapacitiveSensor(12,5); //10M Resistor between pins 12 and 5, you may also connect an antenna on pin 5
CapacitiveSensor LeMi = CapacitiveSensor(12,6);
CapacitiveSensor LeFa = CapacitiveSensor(12,7);
CapacitiveSensor LeSol = CapacitiveSensor(12,8);
CapacitiveSensor LeLa = CapacitiveSensor(12,9);
CapacitiveSensor LeSi = CapacitiveSensor(12,10);
unsigned long csSumDo;
unsigned long csSumRe;
unsigned long csSumMi;
unsigned long csSumFa;
unsigned long csSumSol;
unsigned long csSumLa;
unsigned long csSumSi;

void setup() {
    Serial.begin(9600);
    LEDS.addLeds<WS2801,DATA_PIN1,CLOCK_PIN1,RGB>(leds1,NUM_LEDS1);
      LEDS.setBrightness(84);

}

void loop() {
    CSread();
}

void fadeall() { for(int i = 0; i < NUM_LEDS1; i++) 
{ 
  leds1[i].nscale8(250);
  //leds2[i].nscale8(250);
  } }



void beep(int note, int duration)
{
  if (ith > (NUM_LEDS1) - 1) ith = 0;
  //Play tone on buzzerPin
  ith_1 = ith+1;
  ith_2 = ith+2;
  if (ith_1 > (NUM_LEDS1) - 1) {
    ith_1 = 0;
    ith_2 = 1;
  }
  if (ith_2 > (NUM_LEDS1) - 1) ith_2 = 0;
  tone(buzzPin, note, duration);
  if (counter % 2 == 0)
  {
     leds1[ith] = CHSV(hueth++, 255, 255);
      leds1[ith_1] = CHSV(hueth++, 255, 255);
       leds1[ith_2] = CHSV(hueth++, 255, 255);
      FastLED.show();
    delay(duration);
    
  } else
  {
     leds1[ith] = CHSV(hueth++, 128, 255);
      leds1[ith_1] = CHSV(hueth++, 128, 255);
       leds1[ith_2] = CHSV(hueth++, 128, 255);
      FastLED.show();
    delay(duration);
   
 
  }
  leds1[ith] = CRGB::Black;
    leds1[ith_1] = CRGB::Black;
    leds1[ith_2] = CRGB::Black;
    fadeall();
  noTone(buzzPin);

  //delay(50);
 Serial.print("hueth = ");
  Serial.println(hueth);
  Serial.print("ith = ");
  Serial.println(ith);
  
  ith++;
  counter++;
}
// *************************


void CSread() {
    long csDo = LeDo.capacitiveSensor(80); //a: Sensor resolution is set to 80
    long csRe = LeRe.capacitiveSensor(80); //a: Sensor resolution is set to 80
    long csMi = LeMi.capacitiveSensor(80); //a: Sensor resolution is set to 80
    long csFa = LeFa.capacitiveSensor(80); //a: Sensor resolution is set to 80
    long csSol = LeSol.capacitiveSensor(80); //a: Sensor resolution is set to 80
    long csLa = LeLa.capacitiveSensor(80); //a: Sensor resolution is set to 80
    long csSi = LeSi.capacitiveSensor(80); //a: Sensor resolution is set to 80


if (csDo > 200) { //b: Arbitrary number
    csSumDo += csDo;
if (csSumDo >= 10000) {
   Serial.print("Trigger csDo: ");
   Serial.println(csDo);
   joue(1);
    ith = 0;
   Fur_Elise();

   if (csSumDo > 0) { csSumDo = 0; } //Reset
      LeDo.reset_CS_AutoCal(); //Stops readings
}
} else {
    csSumDo = 0; //Timeout caused by bad readings
}
    
if (csRe > 200) { //b: Arbitrary number
    csSumRe += csRe;
if (csSumRe >= 6000) {
   Serial.print("Trigger csRe: ");
   Serial.println(csRe);
   joue(2);
    ith = 0;
   StarWars();

   if (csSumRe > 0) { csSumRe = 0; } //Reset
      LeRe.reset_CS_AutoCal(); //Stops readings
}
} else {
    csSumRe = 0; //Timeout caused by bad readings
}


if (csMi > 200) { //b: Arbitrary number
    csSumMi += csMi;
if (csSumMi >= 6000) {
   Serial.print("Trigger csMi: ");
   Serial.println(csMi);
   joue(3);
   
   ith = 0;
   HappyBirthday();
   
   if (csSumMi > 0) { csSumDo = 0; } //Reset
      LeMi.reset_CS_AutoCal(); //Stops readings
}
} else {
    csSumMi = 0; //Timeout caused by bad readings
}
    


if (csFa > 200) { //b: Arbitrary number
    csSumFa += csFa;
if (csSumFa >= 6000) {
   Serial.print("Trigger csFa: ");
   Serial.println(csFa);
   joue(4);
 
    ith = 0;
   Cucaracha();

   if (csSumFa > 0) { csSumFa = 0; } //Reset
      LeFa.reset_CS_AutoCal(); //Stops readings
}
} else {
    csSumFa = 0; //Timeout caused by bad readings
}

if (csSol > 200) { //b: Arbitrary number
    csSumSol += csSol;
if (csSumSol >= 6000) {
   Serial.print("Trigger csSol: ");
   Serial.println(csSol);
   joue(5);

  Frozen();

   if (csSumSol > 0) { csSumSol = 0; } //Reset
      LeSol.reset_CS_AutoCal(); //Stops readings
}
} else {
    csSumSol = 0; //Timeout caused by bad readings
}

if (csLa > 200) { //b: Arbitrary number
    csSumLa += csLa;
if (csSumLa >= 6000) {
   Serial.print("Trigger csLa: ");
   Serial.println(csLa);
   joue(6);
  
   Mission_Impossible();

   if (csSumLa > 0) { csSumLa = 0; } //Reset
      LeLa.reset_CS_AutoCal(); //Stops readings
}
} else {
    csSumLa = 0; //Timeout caused by bad readings
}

if (csSi > 200) { //b: Arbitrary number
    csSumSi += csSi;
if (csSumSi >= 6000) {
   Serial.print("Trigger csSi: ");
   Serial.println(csSi);
   joue(4);

    ith = 0;
      TheRainsofCastamere();

   if (csSumSi > 0) { csSumSi = 0; } //Reset
      LeSi.reset_CS_AutoCal(); //Stops readings
}
} else {
    csSumSi = 0; //Timeout caused by bad readings
}

}

void joue(int note)
{
   int noteDuration = 1000 / 4;
   int pauseBetweenNotes = noteDuration * 1.30;
   switch (note){
    case 1:
    tone(buzzPin, NOTE_C3, noteDuration);
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzPin);
    break;
    case 2:
    tone(buzzPin, NOTE_D3, noteDuration);
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzPin);
    break;
    case 3:
    tone(buzzPin, NOTE_E3, noteDuration);
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzPin);
    break;
    case 4:
    tone(buzzPin, NOTE_F3, noteDuration);
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzPin);
    break;
    case 5:
    tone(buzzPin, NOTE_G3, noteDuration);
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzPin);
    break;
    case 6:
    tone(buzzPin, NOTE_A3, noteDuration);
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzPin);
    break;
    case 7:
    tone(buzzPin, NOTE_B3, noteDuration);
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(buzzPin);
    break;
   
   }
    
}



void HappyBirthday() { //*********************************************
  beep(Do, 250);
  beep(Do, 250);
  beep(Re, 500);
  beep(Do, 500);
  beep(Fa, 500);
  beep(Mi, 1000);
  beep(Do, 250);
  beep(Do, 250);
  beep(Re, 500);
  beep(Do, 500);
  beep(Sol, 500);
  beep(Fa, 1000);
  beep(Do, 250);
  beep(Do, 250);
  beep(Doo, 500);
  beep(La, 500);
  beep(Fa, 500);
  beep(Mi, 500);
  beep(Re, 1000);
  beep(LaS, 250);
  beep(LaS, 250);
  beep(La, 500);
  beep(Fa, 500);
  beep(Sol, 500);
  beep(Fa, 1000);

}


void Cucaracha() {  //*********************************************************
  beep(d, 200);
  beep(d, 200);
  beep(d, 200);
  beep(f, 200);
  delay(200);
  beep(l, 200);
  delay(200);
  beep(d, 200);
  beep(d, 200);
  beep(d, 200);
  delay(200);
  beep(f, 400);
  beep(l, 1000);
  delay(400);
  beep(f, 200);
  beep(f, 200);
  beep(m, 200);
  beep(m, 200);
  beep(r, 200);
  beep(r, 200);
  beep(d, 1000);
  delay(200);
  beep(d, 200);
  beep(d, 200);
  beep(d, 200);
  beep(m, 400);
  delay(200);
  beep(s, 200);
  delay(200);
  delay(200);
  beep(d, 200);
  beep(d, 200);
  beep(d, 200);
  beep(m, 400);
  delay(200);
  beep(s, 1000);
  delay(400);
  beep(Do, 200);
  beep(Re, 200);
  beep(Do, 200);
  beep(lS, 200);
  beep(l, 200);
  beep(s, 200);
  beep(f, 400);
  delay(1600);
  beep(d, 200);
  beep(d, 200);
  beep(f, 200);
  beep(f, 200);
  beep(l, 200);
  beep(l, 200);
  beep(Do, 400);
  delay(200);
  beep(l, 1000);
  delay(200);
  beep(Do, 400);
  beep(Re, 200);
  beep(Do, 200);
  beep(lS, 200);
  beep(l, 200);
  beep(Do, 200);
  beep(lS, 400);
  delay(200);
  beep(s, 1000);
  delay(400);
  beep(d, 200);
  beep(d, 200);
  beep(m, 200);
  beep(m, 200);
  beep(s, 200);
  beep(s, 200);
  beep(lS, 400);
  delay(200);
  beep(s, 1000);
  delay(200);
  beep(Do, 400);
  beep(Re, 200);
  beep(Do, 200);
  beep(lS, 200);
  beep(l, 200);
  beep(s, 200);
  beep(f, 1000);
  delay(1600);
}
void TheRainsofCastamere() {  //****************************************************
  
  beep(la, 500);
  beep(f, 750);
  beep(la, 250);
  beep(m, 750);
  beep(la, 250);
  beep(f, 500);
  beep(s, 500);
  beep(m, 750);
  beep(la, 250);
  beep(s, 500);
  beep(f, 500);
  beep(m, 500);
  beep(r, 500);
  beep(m, 2000); 
  beep(l, 250);
  beep(l, 500);
  beep(lS, 250);
  beep(s, 500);
  beep(d, 250);
  beep(d, 250);
  beep(l, 500);
  beep(lS, 500);
  beep(s, 750);
  beep(l, 250);
  beep(lS, 500);
  beep(l, 500);
  beep(s, 500);
  beep(f, 500);
  beep(m, 1500);
  beep(la, 250);
  beep(la, 250); 
  beep(f, 750);
  beep(la, 125);
  beep(m, 750);
  beep(la, 250);
  beep(f, 500);
  beep(s, 500);
  beep(m, 750);
  beep(la, 250);
  beep(s, 500);
  beep(f, 500);
  beep(m, 500);
  beep(r, 500);
  beep(m, 1500);
  beep(d, 500);
  beep(l, 750);
  beep(lS, 250);
  beep(s, 750);
  beep(d, 250); 
  beep(l, 500);
  beep(lS, 500);
  beep(s, 750);
  beep(l, 250);
  beep(lS, 500);
  beep(l, 500);
  beep(s, 500);
  beep(f, 500);
  beep(m, 1500);
  beep(d, 500);
  beep(l, 750);
  beep(lS, 250);
  beep(s, 750);
  beep(d, 250);
  beep(l, 500);
  beep(lS, 500);
  beep(s, 750);
  beep(l, 250);
  beep(lS, 500);
  beep(l, 500);
  beep(s, 500);
  beep(f, 500);
  beep(r, 2000);

  delay(1500);

  beep(la, 500);
  beep(m, 250);
  beep(f, 250);
  beep(r, 1000);
  beep(f, 500);
  beep(f, 250);
  beep(m, 250);
  beep(la, 1000);
  delay(250);
  beep(la, 250);
  beep(f, 250);
  beep(f, 250);
  beep(r, 1000);
  beep(f, 500);
  beep(f, 250);
  beep(m, 1250);
  beep(la, 500);
  beep(m, 250);
  beep(f, 250);
  beep(r, 1000);
  beep(l, 500);
  beep(l, 500);
  beep(s, 500);
  beep(r, 750);
  beep(f, 250);
  beep(f, 750);
  beep(r, 250);
  beep(m, 750);
  beep(f, 250);
  beep(r, 1500);
  beep(la, 500);
  beep(m, 250);
  beep(f, 250);
  beep(l, 500);
  beep(l, 500);
  beep(s, 500);
  beep(r, 750);
  beep(f, 250);
  beep(f, 750);
  beep(r, 250);
  beep(l, 250);
  beep(s, 250);
  beep(m, 250);
  beep(f, 250);
  beep(r, 2000);
}

// **************************


void StarWars() {  //*************************************************
    beep(La,600); 
    beep(La,600);     
    beep(La,600); 
    beep(Fa, 420); 
    beep(Doo,180);
    beep(La,600);
    beep(Fa, 420);
    beep(Doo, 180);
    beep(La,1200);
    beep( eH, 600);
    beep( eH, 600);
    beep( eH, 600);    
    beep( fH, 420); 
    beep(Doo, 180);
    beep(gS, 600);
    beep(Fa, 420);
    beep(Doo, 180);
    beep(La,1200);
    beep( aH, 600);
    beep(La, 420); 
    beep(La,180);
    beep( aH, 600);
    beep( gSH, 300); 
    beep( gH, 300);
    
    beep( fSH, 180);
    beep( fH, 180);    
    beep( fSH, 300);
    delay(300);
    beep( aS, 300);    
    beep( dSH, 600);  
    beep( dH, 300);  
    beep( cSH, 300);  
    beep(Doo, 180);  
    beep( LaS, 180);  
    beep(Doo, 300);      
    delay(300);
    beep(Fa,180);  
    beep( gS, 600);  
    beep(Fa,450);  
    beep(La,180); 
    beep(Doo, 600); 
    beep(La,450);  
    beep(Doo, 180); 
    beep(eH, 1200); 
    beep( aH, 600);
    beep(La, 420); 
    beep(La,180);
    beep( aH, 600);
    beep( gSH, 300); 
    beep(gH, 300);
    beep(fSH, 180);
    beep( fH, 180);    
    beep( fSH, 300);
    delay(300);
    beep(aS, 300);    
    beep( dSH, 600);  
    beep( dH, 300);  
    beep( cSH, 300);  
    beep(Doo, 180);  
    beep( LaS, 180);  
    beep(Doo, 300);      
    delay(300);
    beep(Fa,300);  
    beep( gS, 600);  
    beep(Fa,450);  
    beep(Doo, 180); 
    beep(La, 600);            
    beep(Fa, 450);            
    beep( Do, 180);            
    beep(La,1200);      
}


void Mission_Impossible() { //***************************************
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_D5,50);
beep(NOTE_DS5,50);
beep(NOTE_F5,50);
beep(NOTE_FS5,50);
beep(NOTE_G5,50); 
beep(NOTE_G2,200);
delay(350);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_AS2,200);
delay(180);
beep(NOTE_C3,200);
delay(180);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_F2,200);
delay(180);
beep(NOTE_FS2,200);
delay(180);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_AS2,200);
delay(180);
beep(NOTE_C3,200);
delay(180);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_F2,200);
delay(180);
beep(NOTE_FS2,200);
delay(180);
  beep(NOTE_G3,200);
  delay(350);
  beep(NOTE_G3,200);
  delay(350);
  beep(NOTE_AS3,200);
  delay(180);
  beep(NOTE_C4,200);
  delay(180);
  beep(NOTE_G3,200);
  delay(400);
  beep(NOTE_G3,200);
  delay(350);
  beep(NOTE_F3,200);
  delay(180);
  beep(NOTE_FS3,200);
  delay(180);
  beep(NOTE_G3,200);
  delay(350);
  beep(NOTE_G3,200);
  delay(350);;
  beep(NOTE_AS3,200);
  delay(200);
  beep(NOTE_C4,200);
  delay(180);
  beep(NOTE_G3,200);
  delay(350);
  beep(NOTE_G3,200);
  delay(350);
  beep(NOTE_F3,200);
  delay(180);
  beep(NOTE_FS3,200);
  delay(180);
beep(NOTE_AS5,150);
delay(50);
beep(NOTE_G5,150);
delay(50);
beep(NOTE_D5,800);
delay(700); 
beep(NOTE_AS5,150);
delay(50);
beep(NOTE_G5,150);
delay(50);
beep(NOTE_CS5,800);
delay(700); 
beep(NOTE_AS5,150);
delay(50);
beep(NOTE_G5,150);
delay(50);
beep(NOTE_C5,800);
delay(700); 
beep(NOTE_AS4,150);
delay(50);
beep(NOTE_C5,400);
delay(1200);
beep(NOTE_AS4,200);
beep(NOTE_G4,200);
beep(NOTE_FS5,600);
delay(800);
beep(NOTE_AS4,200);
beep(NOTE_G4,200);
beep(NOTE_F5,600);
delay(800);
beep(NOTE_AS4,200);
beep(NOTE_G4,200);
beep(NOTE_E5,600);
delay(800);
beep(NOTE_DS5,200);
beep(NOTE_D5,400);
delay(1200);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
delay(380);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
delay(380);
beep(NOTE_CS5,25);
beep(NOTE_F5,25);
beep(NOTE_AS5,25);
beep(NOTE_CS5,25);
beep(NOTE_F5,25);
beep(NOTE_AS5,25);
beep(NOTE_CS5,25);
beep(NOTE_F5,25);
delay(180);
beep(NOTE_DS5,25);
beep(NOTE_G5,25);
beep(NOTE_C6,25);
beep(NOTE_DS5,25);
beep(NOTE_G5,25);
beep(NOTE_C6,25);
beep(NOTE_DS5,25);
beep(NOTE_G5,25);
delay(180);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
delay(380);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
delay(380);
beep(NOTE_GS4,25);
beep(NOTE_C5,25);
beep(NOTE_F5,25);
beep(NOTE_GS4,25);
beep(NOTE_C5,25);
beep(NOTE_F5,25);
beep(NOTE_GS4,25);
beep(NOTE_C5,25);
delay(180);
beep(NOTE_A4,25);
beep(NOTE_CS5,25);
beep(NOTE_FS5,25);
beep(NOTE_A4,25);
beep(NOTE_CS5,25);
beep(NOTE_FS5,25);
beep(NOTE_A4,25);
beep(NOTE_CS5,25);
delay(180);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
delay(380);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
delay(380);
beep(NOTE_CS5,25);
beep(NOTE_F5,25);
beep(NOTE_AS5,25);
beep(NOTE_CS5,25);
beep(NOTE_F5,25);
beep(NOTE_AS5,25);
beep(NOTE_CS5,25);
beep(NOTE_F5,25);
delay(180);
beep(NOTE_DS5,25);
beep(NOTE_G5,25);
beep(NOTE_C6,25);
beep(NOTE_DS5,25);
beep(NOTE_G5,25);
beep(NOTE_C6,25);
beep(NOTE_DS5,25);
beep(NOTE_G5,25);
delay(180);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
delay(380);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
delay(380);
beep(NOTE_GS4,25);
beep(NOTE_C5,25);
beep(NOTE_F5,25);
beep(NOTE_GS4,25);
beep(NOTE_C5,25);
beep(NOTE_F5,25);
beep(NOTE_GS4,25);
beep(NOTE_C5,25);
delay(180);
beep(NOTE_A4,25);
beep(NOTE_CS5,25);
beep(NOTE_FS5,25);
beep(NOTE_A4,25);
beep(NOTE_CS5,25);
beep(NOTE_FS5,25);
beep(NOTE_A4,25);
beep(NOTE_CS5,25);
delay(180);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_AS2,200);
delay(180);
beep(NOTE_C3,200);
delay(180);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_F2,200);
delay(180);
beep(NOTE_FS2,200);
delay(180);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_AS2,200);
delay(180);
beep(NOTE_C3,200);
delay(180);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_F2,200);
delay(180);
beep(NOTE_FS2,200);
delay(180);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_AS2,200);
delay(180);
beep(NOTE_C3,200);
delay(180);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_G2,200);
delay(350);
beep(NOTE_F2,200);
delay(180);
beep(NOTE_FS2,200);
delay(180);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
beep(NOTE_G5,25);
beep(NOTE_AS4,25);
beep(NOTE_D5,25);
delay(300);
    beep(NOTE_GS3,400);//GSHARP
}



void Frozen(){  //************************************************************
beep(NOTE_F6,250);
beep(NOTE_G6,250);
beep(NOTE_GS6,1000);
beep(NOTE_DS6,250);
beep(NOTE_DS6,250);
beep(NOTE_AS6,1000);
beep(NOTE_GS6,500);
beep(NOTE_F6,250);
beep(NOTE_F6,250);
beep(NOTE_F6,500);
beep(NOTE_F6,250);
beep(NOTE_G6,500);
beep(NOTE_GS6,1000);
beep(NOTE_F6,250);
beep(NOTE_G6,250);
beep(NOTE_GS6,1000);
beep(NOTE_DS6,250);
beep(NOTE_DS6,250);
beep(NOTE_C7,500);
beep(NOTE_AS6,1000);
beep(NOTE_GS6,250);
beep(NOTE_AS6,250);
beep(NOTE_C7,500);
beep(NOTE_C7,250);
beep(NOTE_CS7,500);
beep(NOTE_C7,500);
beep(NOTE_AS6,500);
beep(NOTE_GS6,1000);
beep(NOTE_DS7,660);
beep(NOTE_C7,660);
beep(NOTE_AS6,1000);
beep(NOTE_GS6,500);
beep(NOTE_GS6,500);
beep(NOTE_DS7,625);
beep(NOTE_C7,750);
beep(NOTE_GS6,500);
beep(NOTE_GS6,500);
beep(NOTE_GS6,500);
beep(NOTE_G6,660);
beep(NOTE_DS6,660);
beep(NOTE_DS6,1000);
beep(NOTE_C6,250);
beep(NOTE_CS6,500);
beep(NOTE_CS6,250);
beep(NOTE_C6,250);
beep(NOTE_CS6,250);
beep(NOTE_C6,250);
beep(NOTE_CS6,250);
beep(NOTE_CS6,250);
beep(NOTE_C6,250);
beep(NOTE_GS5,1000);
}

void Fur_Elise () {  //*************************************************************
   beep(NOTE_E6, 250);
  beep(NOTE_DS6, 250);
  
  //Measure 2
  beep(NOTE_E6, 250);
  beep(NOTE_DS6, 250);
  beep(NOTE_E6, 250);
  beep(NOTE_B5, 250);
  beep(NOTE_D6, 250);
  beep(NOTE_C6, 250);
  
  //Measure 3
  beep(NOTE_A3, 250);
  beep(NOTE_E4, 250);
  beep(NOTE_A4, 250);
  beep(NOTE_C5, 250);
  beep(NOTE_E5, 250);
  beep(NOTE_A5, 250);
  
  //Measure 4
  beep(NOTE_E3, 250);
  beep(NOTE_E4, 250);
  beep(NOTE_GS4, 250);
  beep(NOTE_E5, 250);
  beep(NOTE_GS5, 250);
  beep(NOTE_B5, 250);
  
  //Measure 5
  beep(NOTE_A3, 250);
  beep(NOTE_E4, 250);
  beep(NOTE_A4, 250);
  beep(NOTE_E5, 250);
  beep(NOTE_E6, 250);
  beep(NOTE_DS6, 250);
  
  //Measure 6
  beep(NOTE_E6, 250);
  beep(NOTE_DS6, 250);
  beep(NOTE_E6, 250);
  beep(NOTE_B5, 250);
  beep(NOTE_D6, 250);
  beep(NOTE_C6, 250);
  
  //Measure 7
  beep(NOTE_A3, 250);
  beep(NOTE_E4, 250);
  beep(NOTE_A4, 250);
  beep(NOTE_C5, 250);
  beep(NOTE_E5, 250);
  beep(NOTE_A5, 250);
  
  //Measure 8
  beep(NOTE_E3, 250);
  beep(NOTE_E4, 250);
  beep(NOTE_GS4, 250);
  beep(NOTE_E5, 250);
  beep(NOTE_GS5, 250);
  beep(NOTE_B5, 250);
  
  //Measure 9
  beep(NOTE_A3, 250);
  beep(NOTE_E4, 250);
  beep(NOTE_A4, 250);
  beep(NOTE_E5, 250);
  beep(NOTE_C6, 250);
  beep(NOTE_D6, 250);
  
  //Measure 10
  beep(NOTE_C4, 250);
  beep(NOTE_G4, 250);
  beep(NOTE_C5, 250);
  beep(NOTE_G5, 250);
  beep(NOTE_F6, 250);
  beep(NOTE_E6, 250);
  
  //Measure 11
  beep(NOTE_G3, 250);
  beep(NOTE_G4, 250);
  beep(NOTE_B4, 250);
  beep(NOTE_F5, 250);
  beep(NOTE_E6, 250);
  beep(NOTE_D6, 250);
  
  //Measure 12
  beep(NOTE_A3, 250);
  beep(NOTE_E4, 250);
  beep(NOTE_A4, 250);
  beep(NOTE_E5, 250);
  beep(NOTE_D6, 250);
  beep(NOTE_C6, 250);
  
  //Measure 13
  beep(NOTE_E3, 250);
  beep(NOTE_E4, 250);
  beep(NOTE_A5, 250);
    beep(NOTE_E6, 250);
  beep(NOTE_DS6, 250);
  
  //Measure 14
  beep(NOTE_E6, 250);
  beep(NOTE_DS6, 250);
  beep(NOTE_E6, 250);
  beep(NOTE_B5, 250);
  beep(NOTE_D6, 250);
  beep(NOTE_C6, 250);
    beep(NOTE_A3, 250);
delay(250); 
}
 
