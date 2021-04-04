#include <Nextion.h>  
#include <HX711.h>
#include <Servo.h>

//constants
const int out = 20 ;
const int clck = 21;
HX711 scale(out, clck);
float CalibrationFactor = -110215;
float current_wt;
float moong_wt,chana_wt;
int buttonID;

//servo parameters
int flap_angle = 100;
int Pin = 3;
int Pin1 = 9;
Servo Moong_Servo;  // create servo object to control a servo
Servo Chana_Servo;
int pos = 0;    // variable to store the servo position

uint32_t moong_mant,moong_dec;
uint32_t chana_mant,chana_dec;

NexButton confirm_moong = NexButton(2,4, "confirm_moong");  // Button added
NexButton confirm_chana = NexButton(3,4, "confirm_chana");

//Display
NexNumber display_mant = NexNumber(4,3,"display_mant");
NexNumber display_dec = NexNumber(4,5,"display_dec");
