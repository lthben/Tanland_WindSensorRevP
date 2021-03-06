/*Author: Benjamin Low (benjamin.low@digimagic.com.sg)
* Date: 17 Aug 2015
* Description: Based on the public domain code by Paul Bagder (dated 2014)
* for the Modern Device Rev P Wind Sensor
* Requires a Wind Sensor Rev P from Modern Device
* http://moderndevice.com/product/wind-sensor-rev-p/
*
* The Rev P requires at least at least an 8 volt supply. The easiest way to power it
* if you are using an Arduino is to use a 9 volt or higher supply on the external power jack
* and power the sensor from Vin.
*
* Hardware hookup
* Sensor     Arduino Pin
* Ground     Ground
* +10-12V      Vin
* Out          A0
* TMP          A2
*
* Adapted for project Tanland in Ayutthaya, Thailand, for the heat wave
* installation. Serial writes a byte value 0f 0-255 for the wind sensor.
* A higher reading means stronger airflow.
*/

const int OutPin  = A0;   // wind sensor analog pin  hooked up to Wind P sensor "OUT" pin
const int TempPin = A2;   // temp sesnsor analog pin hooked up to Wind P sensor "TMP" pin


void setup() {
  Serial.begin(9600);
  
}

void loop() {

  // read wind
  int windADunits = analogRead(OutPin);
//  Serial.print("RW ");   // print raw A/D for debug
//  Serial.print(windADunits);
//  Serial.print("\n");

  int my_reading = windADunits - 300;
  my_reading = constrain(my_reading, 0, 255);
  Serial.println(my_reading); //raw reading is 330-500. To keep to within one byte 0-255.

  // wind formula derived from a wind tunnel data, annemometer and some fancy Excel regressions
  // this scalin doesn't have any temperature correction in it yet
  float windMPH =  pow((((float)windADunits - 264.0) / 85.6814), 3.36814);
  //    Serial.print(windMPH);
  //    Serial.print(" MPH\t");


  // temp routine and print raw and temp C
  int tempRawAD = analogRead(TempPin);
  //    Serial.print("RT ");    // print raw A/D for debug
  //    Serial.print(tempRawAD);
  //    Serial.print("\t");

  // convert to volts then use formula from datatsheet
  //    Vout = ( TempC * .0195 ) + .400
  //    tempC = (Vout - V0c) / TC   see the MCP9701 datasheet for V0c and TC

  float tempC = ((((float)tempRawAD * 5.0) / 1024.0) - 0.400) / .0195;
  //    Serial.print(tempC);
  //    Serial.println(" C");

  delay(50); //need to add delay for the sampling to work
}



