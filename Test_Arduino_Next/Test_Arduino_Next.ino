#include "includes.h"

NexTouch *nex_listen_list[] = 
{
  &confirm_moong, 
  &confirm_chana,
  NULL  
};  

void setup() 
{  
  
  Serial.begin(9600);  // Start serial comunication at baud=9600
  Serial2.begin(9600);
  
  scale.set_scale();
  scale.tare();
  long zero_factor = scale.read_average();
  scale.set_scale(CalibrationFactor);

  Moong_Servo.attach(Pin);  // attaches the servo on pin 3 to the servo object
  Chana_Servo.attach(Pin1);
  Moong_Servo.write(0);
  Chana_Servo.write(0);

  Serial.print("in setup");

  confirm_moong.attachPop(confirm_moongPopCallback);  // Button press
  confirm_chana.attachPop(confirm_chanaPopCallback); 
}  

void confirm_moongPopCallback(void *ptr)  // Press event for button b1
{
   display_mant.getValue(&moong_mant);
   display_dec.getValue(&moong_dec);
   moong_wt = (float)moong_dec/100;
   moong_wt = moong_wt + moong_mant;

   Moong_Servo.write(flap_angle); 
   buttonID = 1;
   
   //price of moong --> Rs 0.098 / gram
   float price_moong = 0.098;
   price_moong = 0.098 * moong_wt;
     
   Serial.println(moong_wt);
   Serial.print("Rs ");
   Serial.println(price_moong,3);

   //printing the price in display

  Serial2.print("three.display_price.txt=\"");
  Serial2.print(price_moong,3);
  Serial2.print("\"");
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
  
}  

void confirm_chanaPopCallback(void *ptr)  // Press event for button b1
{
   display_mant.getValue(&chana_mant);
   display_dec.getValue(&chana_dec);
   chana_wt = (float)chana_dec/100;
   chana_wt = chana_wt + chana_mant;
   
   Chana_Servo.write(flap_angle);   
   Serial.println(chana_wt);
   buttonID = 2;

   //price of chana dal --> Rs 0.075 / gram
   float price_chana = 0.075;
   price_chana = 0.075 * chana_wt;
     
   Serial.println(chana_wt);
   Serial.print("Rs ");
   Serial.println(price_chana,3);

   //printing the price in display

  Serial2.print("three.display_price.txt=\"");
  Serial2.print(price_chana,3);
  Serial2.print("\"");
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);
}  


void loop() 
{  

  current_wt = scale.get_units();
   //send the current weight to display page
  Serial2.print("three.cw.txt=\"");
  Serial2.print(current_wt,3);
  Serial2.print("\"");
  Serial2.write(0xff);
  Serial2.write(0xff);
  Serial2.write(0xff);

  if(buttonID ==1 && current_wt>=moong_wt)
  {
    Serial.println("Stop Moong Motor");
    rotate_moong(0);
  }
  else if(buttonID ==2 && current_wt>=chana_wt)
  {
    Serial.println("Stop Chana Motor "); 
    rotate_chana(0);
  }
  
  
  nexLoop(nex_listen_list);  // Check for any touch even

}  





//------------------------------motor-------------------------
void rotate_chana(int angle)
{
  for (int pos = 0; pos <= angle; pos += 1)
  {
    Chana_Servo.write(pos);
    delay(15);
  }
}

void rotate_moong(int angle)
{
  for (int pos = 0; pos <= angle; pos += 1)
  {
    Moong_Servo.write(pos);
    delay(15);
  }
}
