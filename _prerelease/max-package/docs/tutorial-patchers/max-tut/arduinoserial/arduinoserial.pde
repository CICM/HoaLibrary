// Arduino Serial Tester
// rld, cycling'74, 3.2008

long randomvalue = 0; // random value
long countervalue = 0; // counter value
int serialvalue; // value for serial input
int started = 0; // flag for whether we've received serial yet

void setup() 
{ 
  Serial.begin(9600); // open the arduino serial port
} 
 

void loop() 
{ 
  if(Serial.available()) // check to see if there's serial data in the buffer
  {
    serialvalue = Serial.read(); // read a byte of serial data
    started = 1; // set the started flag to on
  }
  if(started) { // loop once serial data has been received
    randomvalue = random(1000); // pick a new random number
    Serial.print(countervalue); // print the counter
    Serial.print(" "); // print a space
    Serial.print(randomvalue); // print the random value
    Serial.print(" "); // print a space
    Serial.print(serialvalue); // echo the received serial value
    Serial.println(); // print a line-feed
    countervalue = (countervalue+1)%1000; // increment the counter
    delay(100); // pause
  }
} 
