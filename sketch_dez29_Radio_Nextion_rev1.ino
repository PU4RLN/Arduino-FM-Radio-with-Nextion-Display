//References used to learn about Nextion Display and TEA 5767
//https://www.youtube.com/watch?v=2zDb9GMNKpM&list=FLKZo3DRsU-xVdMtiIv7x7zQ&index=13&t=25s
//https://www.youtube.com/watch?v=uUxnkGxpYJQ&list=FLKZo3DRsU-xVdMtiIv7x7zQ&index=9&t=3s
//https://www.youtube.com/watch?v=2zDb9GMNKpM&list=FLKZo3DRsU-xVdMtiIv7x7zQ&index=8
//https://www.youtube.com/watch?v=WF9RXlG8LlY&list=FLKZo3DRsU-xVdMtiIv7x7zQ&index=58
//https://www.youtube.com/watch?v=xAd5q9y9kKs&list=FLKZo3DRsU-xVdMtiIv7x7zQ&index=19

//Arduino NANO
//choose Atmega 328p old bootloader
//pin TX - Nextion Yellow
//pin RX - Nextion Blue
//Pin A4 - SDA
//Pin A5 - SLK
//improved version

#include "Nextion.h"

#include <Wire.h>
#include <TEA5767Radio.h>

TEA5767Radio radio = TEA5767Radio();


// Declare a text object [page id:0,component id:2, component name: "texNumber"].
NexText texNumber = NexText(1, 2, "texNumber");

// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexButton buttonPlus = NexButton(1, 5, "buttonPlus");
NexButton buttonPlus1 = NexButton(1, 7, "buttonPlus1");

// Declare a button object [page id:0,component id:4, component name: "buttonMinus"].
NexButton buttonMinus = NexButton(1, 4, "buttonMinus");
NexButton buttonMinus1 = NexButton(1, 6, "buttonMinus1");

NexProgressBar j0 = NexProgressBar(1, 1, "j0");

NexPage page0 = NexPage(0, 0, "page0"); //initial message
NexPage page1 = NexPage(1, 0, "page1"); //radio
NexPage page2 = NexPage(2, 0, "page2"); //optional

//float number = 93.3;
float number = 933;
float freq = 93.3;
float bar_value = 0;
char buffer[10] = {0};


// Register object texNumber, buttonPlus, buttonMinus, to the touch event list.

NexTouch *nex_listen_list[] =
{
  &texNumber,
  &buttonPlus,
  &buttonMinus,
  &buttonPlus1,
  &buttonMinus1,
  NULL
};



/*
   buttonPlus component pop callback function.
   In this example,the value of the "number" component will plus 1 any time when buttonPlus is pressed.
*/
void buttonPlusPushCallback(void *ptr)
{
  dbSerialPrintln("buttonPlusPushCallback");

  number = number + 1;
  if( number > 1081) number =880 ;
  radioscreen ();
        
 
}
void buttonPlus1PushCallback(void *ptr)
{
  dbSerialPrintln("buttonPlus1PushCallback");

  number = number + 10;
  if( number > 1081) number =880 ;
  radioscreen ();
      
}

void buttonMinusPushCallback(void *ptr)
{
  dbSerialPrintln("buttonMinusPushCallback");

        number = number -1 ;
        if( number < 880) number = 1080 ;
        radioscreen ();
}
void buttonMinus1PushCallback(void *ptr)
{
  dbSerialPrintln("buttonMinus1PushCallback");

        number = number -10 ;
        if( number < 880) number = 1080 ;
        radioscreen ();
}


void setup(void)
{
  
  nexInit();
  
  Serial.begin(9600);
  Wire.begin();

page0.show();
delay(5000);
page1.show();
  
  radio.setFrequency(93.3);
  number = 933;
  bar_value = map(number, 880, 1080, 1, 100);
  j0.setValue(bar_value);

  buttonPlus.attachPush(buttonPlusPushCallback);
  buttonPlus1.attachPush(buttonPlus1PushCallback);

  buttonMinus.attachPush(buttonMinusPushCallback);
  buttonMinus1.attachPush(buttonMinus1PushCallback);

 
}

void loop(void)
{
  nexLoop(nex_listen_list);
  String command = "texNumber.txt=\""+String(number/10,1)+"\"";
        Serial.print(command);
        Serial.write(0xff);
        Serial.write(0xff);
        Serial.write(0xff);

}

 void radioscreen ()
{
        radio.setFrequency(number/10);
        bar_value = map(number, 880, 1080, 1, 100);
        j0.setValue(bar_value);
        
} 
