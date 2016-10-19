#include <WirelessIoT.h>
WirelessIoT iot(1);

void setup() {
  Serial.begin(115200);
  iot.begin();
  delay(1000);
  iot.startIoT();
}

void loop() {
  int res_sensor;
  String sensorDATA = "";
  String jsonDATA = "";
  byte v1, v2;
  
  //溫溼度模組----------------------------------------------------
  if(jsonDATA != "") jsonDATA += ", ";
  int deviceID_TempHum = 0;
  
  res_sensor = iot.rdTemperature(deviceID_TempHum, &v1);
  if (res_sensor == ST_OK) {
    iot.rdHumidity(deviceID_TempHum, &v2);
    //Serial.print("Temp="); Serial.print(v1); Serial.print(" / "); Serial.print("Humi="); Serial.println(v2);      
    sensorDATA = " \"statusTH\": 1, \"Temperature\":"+String(v1) + ", \"Humidity\":" + String(v2);
  }else{
    sensorDATA = "\"statusTH\": 0";   
  }
  //Serial.println(sensorDATA);
  jsonDATA += sensorDATA;
  
  
  //門匙模組----------------------------------------------------
  if(jsonDATA != "") jsonDATA += ", ";
  int deviceID_Door = 0;
  
  res_sensor = iot.rdDoor(deviceID_Door, &v1);
  if (res_sensor == ST_OK) {
    //Serial.print("Door="); Serial.print(v1);      
    sensorDATA = " \"statusDOOR\": 1, \"Open\":"+String(v1);
  }else{
    sensorDATA = "\"statusDOOR\": 0";   
  }
  //Serial.println(sensorDATA);
  jsonDATA += sensorDATA;
  

  //LED模組----------------------------------------------------
  if(jsonDATA != "") jsonDATA += ", ";
  int deviceID_LED = 0;
  
  res_sensor = iot.rdBrightness(deviceID_LED, &v1);
  if (res_sensor == ST_OK) {
    iot.rdColorTemp(deviceID_LED, &v2);   
    sensorDATA = " \"statusLED\": 1, \"Brightness\":"+String(v1)+", \"Color\":"+String(v2);    
  }else{
    sensorDATA = "\"statusLED\": 0";   
  }
  //Serial.println(sensorDATA);
  jsonDATA += sensorDATA;

  //PIR模組----------------------------------------------------
  if(jsonDATA != "") jsonDATA += ", ";
  int deviceID_PIR = 0;
  
  res_sensor = iot.rdPIR(deviceID_PIR, &v1);
  if (res_sensor == ST_OK) {
    //Serial.print("Door="); Serial.print(v1);      
    sensorDATA = " \"statusPIR\": 1, \"PIR\":"+String(v1);
  }else{
    sensorDATA = "\"statusPIR\": 0";   
  }
  //Serial.println(sensorDATA);
  jsonDATA += sensorDATA;  

  Serial.println("{ " + jsonDATA + " }");

  String recieved;
  while (Serial.available() > 0)
    {
        recieved = Serial.readStringUntil('\n');
        Serial.print(recieved);
    }  
  
  delay(1000);
}
