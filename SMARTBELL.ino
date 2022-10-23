/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Pitch & Roll Accelerometer Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup()
{
  Serial.begin(115200);
//  pinMode(3, INPUT);

  //  Serial.println("Initialize MPU6050");
  while
  (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    //    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}

void loop()
{

//  if (digitalRead(3) == HIGH){
//    Serial.println("RESET");
//    delay(1000);
//  }

  int maxVal = -1;
  int increments = 0;
  boolean repConfirmed;

  Vector normAccel = mpu.readNormalizeAccel();
  int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis * normAccel.YAxis + normAccel.ZAxis * normAccel.ZAxis)) * 180.0) / M_PI;

  if (pitch >= 10) {
//    Serial.println("start rep count");
    while (true) {
      delay(9.6);

      increments++;
      // Read normalized values
      Vector normAccel = mpu.readNormalizeAccel();

      // Calculate Pitch & Roll
      int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis * normAccel.YAxis + normAccel.ZAxis * normAccel.ZAxis)) * 180.0) / M_PI;
      //    int roll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;

      // Output
      //  Serial.print(" Pitch = ");
//      Serial.println(pitch);
      //  Serial.print(" Roll = ");
      //  Serial.print(roll);
      //  Serial.print((roll+(abs(pitch)))/2);
      //  Serial.println();

      if (pitch > maxVal){
        maxVal = pitch;
      }

      if (pitch < 11) {
        if (maxVal > 50) {
          repConfirmed = true;
          Serial.println(increments*0.01);

        }
        break;
      }
    }
  }






  delay(100);
}
