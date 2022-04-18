/*
  Library Repository : https://github.com/ckalpha/MQ135
  Author : Damrongwit Nusuk
  Email : jack@racksync.com
  Website : http://www.racksync.com
*/

#include "MQ135.h"
#define ANALOGPIN A7    //  Define Analog PIN on Arduino Board
#define RZERO 384.81    //  Define RZERO Calibration Value
MQ135 gasSensor = MQ135(A7);

// gas sensor resistance: 223.56

void setup()
{
  Serial.begin(9600);
  float rzero = gasSensor.getCorrectedRZero(20.0, 46.0);
  delay(3000);
  Serial.print("MQ135 RZERO Calibration Value : ");
  Serial.println(rzero);
}

void siren() {
  for (int i = 700; i < 800; i++) {
    tone(6, i);
    delay(15);
  }
  for (int i = 800; i > 700; i--) {
    tone(6, i);
    delay(15);
  }
}

// normale balkonluft: 15
// co2 ist merklich: 90
// hohe co2 dosi: 150
// alles über 160 fenster auf
void loop() {
  float ppm = gasSensor.getCorrectedPPM(20.0, 46.0);
  delay(1000);
  digitalWrite(13, HIGH);
  Serial.print("CO2 ppm value : ");
  Serial.println(ppm);
  if (ppm <= 300.0)
  {
    Serial.println("Air-Quality: CO perfect");
  }
  else if ((ppm > 300.0) && (ppm <= 2000.0)) // || = or
  {
    Serial.println("Air-Quality: CO normal");
  }
  else if ((ppm > 2000.0) && (ppm <= 5800.0))
  {
    Serial.println("Air-Quality: CO higher then normal");
    delay(5000);
  }
  else if (ppm > 5800.0)
  {
    Serial.println("Air-Quality: ALARM CO high, open the window!");
    delay(5000);
    siren();
  }
  else
  {
    Serial.println("MQ-135 - cant read any value - check the sensor!");
  }
}
