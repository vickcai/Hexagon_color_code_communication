/*
  Software serial multple serial test
 
 Receives from the two software serial ports, 
 sends to the hardware serial port. 
 
 In order to listen on a software port, you call port.listen(). 
 When using two software serial ports, you have to switch ports
 by listen()ing on each one in turn. Pick a logical time to switch
 ports, like the end of an expected transmission, or when the 
 buffer is empty. This example switches ports when there is nothing
 more to read from a port
 
 The circuit: 
 Two devices which communicate serially are needed.
 * First serial device's TX attached to digital pin 7, RX to pin 8
 * Second serial device's TX attached to digital pin 2, RX to pin 3
 
 created 18 Apr. 2011
 modified 9 Apr 2012
 by Tom Igoe
 based on Mikal Hart's twoPortRXExample
 
 This example code is in the public domain.
 //This code is edited to communicate two arduino together
 
 //for hexagon color block concept. The two communication fo red hexagon block
 and blue hexagon block to form purple hexagon block when put together.
 
 
 */

#include <SoftwareSerial.h>


// software serial #1: TX = digital pin 7, RX = digital pin 8
SoftwareSerial portOne(7, 8);


int redPin = 4;	// R petal on RGB LED module connected to digital pin 11
int greenPin = 5;	// G petal on RGB LED module connected to digital pin 9
int bluePin = 6;	// B petal on RGB LED module connected to digital pin 10
int R = 255;
int G = 255;
int B = 255;
int currentColor= (R, G, B);
String inString = "";    // string to hold input

int red, green, blue = 0;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only

  }


  // Start each software serial port
  portOne.begin(9600);



  pinMode(redPin, OUTPUT);	// sets the redPin to be an output
  pinMode(greenPin, OUTPUT);	// sets the greenPin to be an output
  pinMode(bluePin, OUTPUT);	// sets the bluePin to be an output
}

void color (unsigned char red, unsigned char green, unsigned char blue)     // the color generating function
{	 
  analogWrite(redPin, 255-red);	 
  analogWrite(bluePin, 255-blue);
  analogWrite(greenPin, 255-green);
}	 

void loop()
{
  // By default, the last intialized port is listening.
  // when you want to listen on a port, explicitly select it:
  portOne.listen();
 
 int inChar;

  // Read serial input:
  if (Serial.available() > 0) {
    inChar = portOne.read();
  }

  if (isDigit(inChar)) {
    // convert the incoming byte to a char 
    // and add it to the string:
 inString += (char)inChar; 
  }
  

  // if you get a comma, convert to a number,
  // set the appropriate color, and increment
  // the color counter:
  if (inChar == ',') {
    // do something different for each value of currentColor:
    switch (currentColor) {
    case 0:    // 0 = red
      R = inString.toInt();
      // clear the string for new input:
      inString = ""; 
      break;
    case 1:    // 1 = green:
      green = inString.toInt();
      // clear the string for new input:
      inString = ""; 
      break;
    }
    currentColor++;
  }
  // if you get a newline, you know you've got
  // the last color, i.e. blue:
  if (inChar == '\n') {
    blue = inString.toInt();

    // set the levels of the LED.
    // subtract value from 255 because a higher
    // analogWrite level means a dimmer LED, since
    // you're raising the level on the anode:
    analogWrite(4,  255 - red);
    analogWrite(5, 255 - green);
    analogWrite(6, 255 - blue);

    // print the colors:
    Serial.print("Red: ");
    Serial.print(red);
    Serial.print(", Green: ");
    Serial.print(green);
    Serial.print(", Blue: ");
    Serial.println(blue);

    // clear the string for new input:
    inString = ""; 
    // reset the color counter:
    currentColor = 0;
  }


 

  // blank line to separate data from the two ports:
  Serial.println();


  portOne.print(R);
   portOne.print(',');
  portOne.print(G);
  portOne.print(',');
 portOne.print(B);
  portOne.print('\n');
 
 // "255, 0, 255\n"  
   
    //RGB LED 



  // Basic colors:
  color( R, G , B);	// turn the RGB LED red

}







