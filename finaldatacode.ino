
/* This code is to log data from the ASLglove's sensors to perform classification process in runtime */

#include <MPU6050_tockn.h>
#include <Wire.h>
MPU6050 mpu6050(Wire);

int c1, c2, c3, index, mSum[26], mini[2] = {29, 29};
int flex[4] = {}, flex1[4] = {};
int nobend[4] = {};
int  flag, fullbend[4] = {};
float range[4];
int state[4] = {};
int val;
long prevtime, prevtime_;
int yaw1, pitch1, roll1, yaw, pitch, roll;
int state_ = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Wire.begin();
  mpu6050.begin();
  mpu6050.calcGyroOffsets(true);
  flexinit(); // to calibrate flex sensors and map data within a common range of 0-100 for all fingers
}

void loop() {

  if (Serial.available() == 1)  {
    state_ = Serial.parseInt();  // press 1 every time to read the data.
    Serial.flush();
  }

  if (state_ == 1) {
    prevtime_ = millis(); flag = 1;
    while (millis() - prevtime_ <= 3000) {
      Read();

      Serial.print(flex1[0]); Serial.print(" "); Serial.print(flex1[1]); Serial.print(" "); Serial.print(flex1[2]); Serial.print(" "); Serial.print(flex1[3]); Serial.print(" "); Serial.print(c1); Serial.print(" "); Serial.print(c2); Serial.print(" "); Serial.print(c3); Serial.print(" ");
      Serial.print(yaw); Serial.print(" "); Serial.print(pitch); Serial.print(" "); Serial.println(roll);

    }
  }
}

void flexinit() //inital sensor calibration
{ //To record ADC values of flex sensors for unbent position
  Serial.println("RECORDING NO BEND: ");
  delay(100);
  prevtime = millis();
  while ((millis() - prevtime) < 3000) //log the data for 3 seconds
  { // read flex sensor data from analog pins
    nobend[0] = analogRead(A0);
    nobend[1] = analogRead(A1);
    nobend[2] = analogRead(A2);
    nobend[3] = analogRead(A3);
  }
  for (int  i = 0; i <= 3; i++) {
    Serial.print(nobend[i]); Serial.print("\t");
  }
  Serial.println(" ");
  //To record ADC values of flex sensor for Fully bent position
  Serial.println("RECORDING FULL BEND");
  delay(200);
  prevtime = millis();
  while ((millis() - prevtime) < 3000) {
    fullbend[0] = analogRead(A0);
    fullbend[1] = analogRead(A1);
    fullbend[2] = analogRead(A2);
    fullbend[3] = analogRead(A3);
  }
  for (int  i = 0; i <= 3; i++) {
    Serial.print(fullbend[i]); Serial.print("\t");
  }
  // calculate the range of a flex sensor's data from unbent to fully bent position
  for (int i = 0; i <= 3; i++)
  {
    range[i] = abs(fullbend[i] - nobend[i]);
  }
}

void Read() {
  //read flex sensors
  flex[0] = analogRead(A0);
  flex[1] = analogRead(A1);
  flex[2] = analogRead(A2);
  flex[3] = analogRead(A3);
  //read contact sensors
  c1 = digitalRead(7); c2 = digitalRead(6); c3 = digitalRead(5);
// read Inertial Measurement Unit (IMU) data
  mpu6050.update();
  yaw = mpu6050.getAngleX();
  pitch = mpu6050.getAngleY();
  roll = mpu6050.getAngleZ();
//  map the range of different flex sensor's data to a common 0-100 scale and constraint the values within this range
  for (int  i = 0; i <= 3; i++) {
    if ((flex[i] < nobend[i] * 1.2) || (flex[i] > fullbend[i] * 1.2)) {
      flex[i] = map(flex[i], fullbend[i], nobend[i], 0, 100);
      flex1[i] = constrain(flex[i], 0, 100);

    }
  }
}

