#include "AS5600.h"
#include "Wire.h"

AS5600 as5600;   //  use default Wire

const int btn = 8;
const int btn_src = 9;

int st_btn = 0;
float rawang = 0.0;
float offset = 0.0;
float measang = 0.0;

void setup() {
  pinMode(btn, INPUT);
  pinMode(btn_src, OUTPUT);

  Serial.begin(115200);
  Serial.println(__FILE__);
  Serial.print("AS5600_LIB_VERSION: ");
  Serial.println(AS5600_LIB_VERSION);

  as5600.begin(4);  //  set direction pin.
  as5600.setDirection(AS5600_CLOCK_WISE);  // default, just be explicit.
  int b = as5600.isConnected();
  Serial.print("Connect: ");
  Serial.println(b);
  delay(1000);
  digitalWrite(btn_src,HIGH);
}
void loop() {
  st_btn = digitalRead(btn);
  if (st_btn == HIGH) {
    offset = as5600.readAngle()*AS5600_RAW_TO_DEGREES;
  }
  rawang = as5600.readAngle()*AS5600_RAW_TO_DEGREES;
  if (rawang - offset < 0) {
    measang = 360.0 + rawang - offset;
  }
  else {
    measang = rawang - offset;
  }
  
  
  Serial.print(rawang);
  Serial.print("\t");
  Serial.print(measang);
  Serial.print("\t");
  Serial.println(offset);
  
  //  Serial.println(as5600.rawAngle() * AS5600_RAW_TO_DEGREES);

  delay(1000);
}
