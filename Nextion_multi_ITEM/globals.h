#include <Nextion.h>

int variable1 = 0;
int counter = 0;
int CurrentPage = 0; //variable creation to store which page is on

//constants
bool motor_rotated = false;//the rotation of motor is false
bool weight_given = false; //there is no current weight
bool motor_rotated_zero = true; // rotation angle of motor is zero currently
const int out = 20 ;
const int clck = 21;
float current_wt,item1_wt,item2_wt;
int flap_angle = 100;
int servoPin1 = 3;
int servoPin2 = 4;
int divisor = 1;
String data_from_display="";
int decimalPlaces = 0;
int pos = 0;    // variable to store the servo position

float CalibrationFactor = -110215;


//declarations

NexButton b0 = NexButton(0,2,"b0"); //button added
NexSlider h0 = NexSlider(0,9,"h0"); //slider for item1
NexSlider h1 = NexSlider(0,10,"h1"); //slider for item2
NexPage page0 = NexPage(0,0,"page0"); //page added as a touch event

NexTouch *nex_listen_list[]=
{
  &b0, //button added
  &h0, //slider added for item1
  &h1, //slider added for item2
  &page0, //Page added as a touch event
  NULL //string terminated
};
