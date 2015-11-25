#include <SoftwareSerial.h> //Arduino UNO/Leonardo uses SoftwareSerial for the SmartThings Library
#include <SmartThings.h>    //Library to provide API to the SmartThings Shield
#include <avr/pgmspace.h>

#include <Constants.h>       //Constants.h is designed to be modified by the end user to adjust behavior of the ST_Anything library
#include <Device.h>          //Generic Device Class, inherited by Sensor and Executor classes
#include <Sensor.h>          //Generic Sensor Class, typically provides data to ST Cloud (e.g. Temperature, Motion, etc...)
#include <InterruptSensor2.h> //Generic Interrupt "Sensor" Class, waits for change of state on digital input 
#include <Everything.h>      //Master Brain of ST_Anything library that ties everything together and performs ST Shield communications

#include <IS2_Motion.h>       //Implements an Interrupt Sensor (IS) to detect motion via a PIR sensor
#include <IS_Contact.h>      //Implements an Interrupt Sensor (IS) to monitor the status of a digital input pin
#include <EX_Alarm2.h>

//******************************************************************************************
//  Notes: -Serial Communications Pins are defined in Constants.h (avoid pins 0,1,2,3
//          for inputs and output devices below as they may be used for communications)
//         -Always avoid Pin 6 as it is reserved by the SmartThings Shield
//
//******************************************************************************************
//"RESERVED" pins for SmartThings ThingShield - best to avoid 9,1,2,3,6
//#define PIN_O_RESERVED               0  //reserved by ThingShield for Serial communications OR USB Serial Monitor
//#define PIN_1_RESERVED               1  //reserved by ThingShield for Serial communications OR USB Serial Monitor
//#define PIN_2_RESERVED               2  //reserved by ThingShield for Serial communications
//#define PIN_3_RESERVED               3  //reserved by ThingShield for Serial communications
//#define PIN_6_RESERVED               6  //reserved by ThingShield (possible future use?)

//House Door Pins
//#define PIN_CONTACT_FRONT_DOOR       A1
//#define PIN_CONTACT_KITCHEN_DOOR     A2
//#define PIN_CONTACT_GARAGE_DOOR      A3
//#define PIN_CONTACT_BEDROOM_DOOR     A4

void setup()
{
 
  //when the input wire is connected to ground (interrupt==TRUE), the input pullup is bypassed and reads LOW
  static st::EX_Alarm2  executor1(F("alarmPin04"), 4, LOW, false, 60); //todo change to 5 minutes?=300
  
  static st::IS2_Motion sensor1(F("motionPin07"), 7, HIGH, true, 250, 15);
  static st::IS_Contact sensor2(F("contactPin08"), 8, LOW, true, 250);
  static st::IS_Contact sensor3(F("contactPin09"), 9, LOW, true, 250);
  static st::IS_Contact sensor4(F("contactPin10"), 10, LOW, true, 250);
  static st::IS_Contact sensor5(F("contactPin11"), 11, LOW, true, 250);
  static st::IS_Contact sensor6(F("contactPin12"), 12, LOW, true, 250);
  
  //*****************************************************************************
  //  -Note: Set these to "false" if using Hardware Serial on pins 0 & 1
  //         to prevent communication conflicts with the ST Shield communications
  //*****************************************************************************
  st::Everything::debug=false;
  st::Device::debug=false;
  st::InterruptSensor::debug=false;
  st::InterruptSensor2::debug=false;
  st::Executor::debug=false;
  
  st::Everything::init();
  
  st::Everything::addExecutor(&executor1);
  
  st::Everything::addSensor(&sensor1);
  st::Everything::addSensor(&sensor2);
  st::Everything::addSensor(&sensor3);
  st::Everything::addSensor(&sensor4); 
  st::Everything::addSensor(&sensor5); 
  st::Everything::addSensor(&sensor6);
  
  st::Everything::initDevices();
}

void loop()
{
  st::Everything::run();
}
