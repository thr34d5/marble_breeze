/*
  Update 10.11.2018
  A. Rigobello - thr34d5

   -----------------------

  SD wiring:
    CS - pin 10
    MOSI - pin 11
    MISO - pin 12
    SCK - pin 13
*/

#include <SPI.h>
#include <SD.h>
#include <TimeLib.h>

File myFile;

int a = 0;
double timelapse = 30; //5s


const int A_MQ4_pin = A0; //the AOUT pin of the methane sensor goes into analog pin A0 of the arduino
const int A_MQ811_pin = A1; //the AOUT pin of the CO2 sensor goes into analog pin A1 of the arduino
const int A_MQ7_pin = A2; //the AOUT pin of the CO sensor goes into analog pin A2 of the arduino
const int Ozone = A3; //O3
const int DOUTpin = 8; //the DOUT pin of the methane sensor goes into digital pin D8 of the arduino
int limit;          //limit variable for the methane
float valueGas1;   //methane
float valueGas2;   //CO2
float valueGas3;    //CO
float valueGas4;  //O3
int gasLimit = 80;  //limit for the methane sensor

void setup() {

  Serial.begin(9600);
  pinMode(DOUTpin, INPUT);      //MQ4 sensor D0

//  while (!Serial) {                                     // wait for serial port to connect. Needed for native USB port only
//    ;
//  }

  Serial.println("initializing SD card.");

  if (!SD.begin(10)) {
    Serial.println("SD initialization failed!");
    return;
  }

  Serial.println("SD initialization done.");
  myFile = SD.open("data.txt", FILE_WRITE);
  myFile.print("new data");
  myFile.close();
}

void loop() {

  valueGas1 = analogRead(A_MQ4_pin);    //reads the analog value from the methane sensor's AOUT pin
  valueGas2 = analogRead(A_MQ811_pin);    //reads the analog value from the CO2 sensor's AOUT pin
  valueGas3 = analogRead(A_MQ7_pin);    //reads the analog value from the CO sensor's AOUT pin
  valueGas4 = analogRead(Ozone);  
  limit = digitalRead(DOUTpin);   //reads the digital value from the methane sensor's DOUT pin
//  Serial.print("Methane value: ");
//  Serial.print(valueGas1);          //prints the methane value
//  Serial.print("; CO2 value: ");
//  Serial.print(valueGas2);          //prints the CO2 value
//  Serial.print("; CO value: ");
//  Serial.println(valueGas3);          //prints the CO value

  // WRITES THE VALUES TO A TXT FILE ON THE SD CARD ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  myFile = SD.open("data.txt", FILE_WRITE);             // opens the file on SD

  if (myFile) {                                         // if the file opened okay, write to it

    myFile.print("measure#");
    myFile.print(a);  
    myFile.print(";");
    digitalClockDisplay();                              // timestamp
    myFile.print(";");
    myFile.print("Methane level:");
    myFile.print(valueGas1);
    myFile.print(";");
    myFile.print("CO2 level:");
    myFile.print(valueGas2);    
    myFile.print(";");
    myFile.print("CO level:");
    myFile.print(valueGas3);
    myFile.print(";");
    myFile.print("Ozone level");
    myFile.print(valueGas4);
    myFile.close();


  } else {
    Serial.println("error opening data.txt for writting");           // if the file didn't open, print an error to the serial monitor
  }

//Serial.print(": measure#");
   // Serial.print(a);  
    //Serial.print(";");
  // Serial.print("Methane level:");
   Serial.print(valueGas1);
   Serial.print(";");
  //  Serial.print("CO2 level:");
   Serial.print(valueGas2);    
    Serial.print(";");
 //  Serial.print("CO level:");
    Serial.print(valueGas3);
        Serial.print(";");
    Serial.println(valueGas4);
   
    a++;
/*
  myFile = SD.open("data.txt");                         // re-open the file for reading

  if (myFile) {
    Serial.println("Complete data.txt:");
    while (myFile.available()) {                        // read from the file until there's nothing else in it
      Serial.write(myFile.read());
    }
    myFile.close();
  } else {
    Serial.println("error opening data.txt for writting verification");
  }*/
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  delay(timelapse);

}

void digitalClockDisplay() {                            // digital clock display of the time
  myFile.print(hour());
  myFile.print("-");
  myFile.print(minute());
  myFile.print("-");
  myFile.print(second());
}
