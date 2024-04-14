#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
int16_t ax, ay, az;
int16_t gx, gy, gz;

struct MyData {
  byte X;
  byte Y;
  byte Z;
};

MyData data;

void setup()
{
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();
}

void loop()
{
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  data.X = map(ax, -17000, 17000, 0, 255 ); // X axis data
  data.Y = map(ay, -17000, 17000, 0, 255); 
  data.Z = map(az, -17000, 17000, 0, 255);  // Y axis data
  // Serial.print("Axis X = ");
  // Serial.print(data.X);
  // Serial.print("  ");
  // Serial.print("Axis Y = ");
  // Serial.print(data.Y);
  // Serial.print("  ");
  // Serial.print("Axis Z  = ");
  // Serial.print(data.Z);
  // Serial.print("  ");

  String strx = String(data.X);
  String stry = String(data.Y);

  if(data.X<100){
    strx = "0"+strx;
  }
  if(data.X<10){
    strx = "0"+strx;
  }
  if(data.Y<100){
    stry = "0"+stry;
  }
  if(data.Y<10){
    stry = "0"+stry;
  }

  String out = strx + stry;
  Serial.println(out);
  delay(1100);
  
}