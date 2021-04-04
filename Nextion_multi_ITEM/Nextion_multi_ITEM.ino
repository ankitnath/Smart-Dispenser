#include "globals.h"
#include "includes.h"


HX711 scale(out, clck);

void rotate_motor_item1(int angle);
void rotate_motor_item2(int angle);

void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600); //to nextion
  myservo1.attach(3);  // attaches the servo on pin 3 to the servo object
  myservo2.attach(9); 
  scale.set_scale();
  scale.tare();
  long zero_factor = scale.read_average();
  scale.set_scale(CalibrationFactor);
  myservo1.write(0);
  myservo2.write(0);
  b0.attachPop(b0PopCallback); //Button release
}

void b0PopCallback(void *ptr) //Release event for button 0
{
//  myservo1.write(0);
//  myservo2.write(0);
}

//Page change event:

void page0PushCallback(void *ptr) //page 0 
{
   CurrentPage = 0; //Set variable as 0 so arduino knows page 0 is loaded on the display 
}// End of press event

char buffer[100] = {0}; //This is needed only if you are going to receive a text from the display. 


void loop()
{  
     if(Serial2.available() && weight_given == false)
   {
     delay(30);

     weight_given = true;
     motor_rotated = false;
//     rotate_motor_item1(flap_angle);
//     rotate_motor_item2(flap_angle);
     
     while(Serial2.available())
     {
      data_from_display +=char(Serial2.read());
     }
     Serial.println(data_from_display);

     //reading data of item1
     if(data_from_display.substring(0,5)=="float")
     {
      rotate_motor_item1(flap_angle);
      decimalPlaces = (data_from_display.substring(5,6).toInt());
      for(int x=0;x<decimalPlaces;x++)
      {
       divisor*=10;
      }
      //Serial.print("Divisor - "+String(divisor));
       item1_wt = float(data_from_display.substring(6).toInt())/divisor;
       data_from_display="";
       divisor=1;     
      
     }

     //reading data of item2
     if(data_from_display.substring(0,5)=="floaf")
     {
      
      rotate_motor_item2(flap_angle);
      decimalPlaces = (data_from_display.substring(5,6).toInt());
      for(int x=0;x<decimalPlaces;x++)
      {
       divisor*=10;
      }
      //Serial.print("Divisor - "+String(divisor));
       item2_wt = float(data_from_display.substring(6).toInt())/divisor;
       data_from_display="";
       divisor=1;     
      
     }
     
   }
      current_wt = scale.get_units();
      Serial.print("Current weight :");
      Serial.println(current_wt);
      Serial2.print("cw.txt=\"");
      Serial2.print(current_wt,3);
      Serial2.print("\"");
      Serial2.write(0xff);
      Serial2.write(0xff);
      Serial2.write(0xff);
      nexLoop(nex_listen_list); //check for any touch event

      if(current_wt >= item1_wt && motor_rotated == false && weight_given == true)
      {
        rotate_motor_item1(0);
        Serial.print("Weight is : ");
        Serial.println(current_wt);
        motor_rotated = true;
        weight_given = false;
        data_from_display="";
        divisor=1;
      }
      else if(current_wt >= item2_wt && motor_rotated == false && weight_given == true)
      {
        rotate_motor_item2(0);
        Serial.print("Weight is : ");
        Serial.println(current_wt);
        motor_rotated = true;
        weight_given = false;
        data_from_display="";
        divisor=1;
      }
}

       
void rotate_motor_item1(int angle)
{
  for (int pos = 0; pos <= angle; pos += 1)
  {
    myservo1.write(pos);
    delay(15);
  }
}

void rotate_motor_item2(int angle)
{
  for (int pos = 0; pos <= angle; pos += 1)
  {
    myservo2.write(pos);
    delay(15);
  }
}
