/*

  ADXL3xx

  Reads an Analog Devices ADXL3xx accelerometer and communicates the

  acceleration to the computer. The pins used are designed to be easily

  compatible with the breakout boards from SparkFun, available from:

  http://www.sparkfun.com/commerce/categories.php?c=80

  The circuit:

  - analog 0: accelerometer self test

  - analog 1: z-axis

  - analog 2: y-axis

  - analog 3: x-axis

  - analog 4: ground

  - analog 5: vcc

  created 2 Jul 2008

  by David A. Mellis

  modified 30 Aug 2011

  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cchttps://www.arduino.cc/en/Tutorial/ADXL3xx

*/

// these constants describe the pins. They won't change:

const int groundpin = 18;             // analog input pin 4 -- ground

const int powerpin = 19;              // analog input pin 5 -- voltage

const int xpin = A3;                  // x-axis of the accelerometer

const int ypin = A2;                  // y-axis

const int zpin = A1;                  // z-axis (only on 3-axis models)

const int SMOOTHING_WINDOW_SIZE = 6; // 10 samples

int _samples[SMOOTHING_WINDOW_SIZE];  // the readings from the analog input
int _curReadIndex = 0;                // the index of the current reading
int _sampleTotal = 0;                 // the running total
int _sampleAvg = 0;                   // the average
int sensorVal = 0;

const float alpha=0.1;
double lastAvg=0.0;
void setup() {

  // initialize the serial communications:

  Serial.begin(115200);

  // Provide ground and power by using the analog inputs as normal digital pins.

  // This makes it possible to directly connect the breakout board to the

  // Arduino. If you use the normal 5V and GND pins on the Arduino,

  // you can remove these lines.

  //pinMode(groundpin, OUTPUT);

  //pinMode(powerpin, OUTPUT);

  //digitalWrite(groundpin, LOW);

  //digitalWrite(powerpin, HIGH);

    for (int i = 0; i < SMOOTHING_WINDOW_SIZE; i++) {
    _samples[i] = 0;
  }
  delay(300);
}

void MovingAverage(){
    _sampleTotal = _sampleTotal - _samples[_curReadIndex];
  
  // read the sensor value
   sensorVal = analogRead(zpin);
  _samples[_curReadIndex] = sensorVal;
  
  // add the reading to the total:
  _sampleTotal = _sampleTotal + _samples[_curReadIndex];
  
  // advance to the next position in the array:
  _curReadIndex = _curReadIndex + 1;

  // if we're at the end of the array...
  if (_curReadIndex >= SMOOTHING_WINDOW_SIZE) {
    // ...wrap around to the beginning:
    _curReadIndex = 0;
  }

  // calculate the average:
  _sampleAvg = _sampleTotal / SMOOTHING_WINDOW_SIZE;
    Serial.print("AnalogIn:");
  Serial.println(sensorVal);
  Serial.print(", ");
  Serial.print("Smoothed:");
  //Serial.print(analogRead(zpin));
  Serial.println(_sampleAvg);
  
}

void ExpoMovAvg(){
  int cur_sample=0;
  double cur_avg=0.0;
  cur_sample= analogRead(zpin);
  cur_avg= (cur_sample*alpha) + ((lastAvg)*(1-alpha)) ;
  //Serial.print(cur_avg);
  lastAvg=cur_avg;
 // Serial.println(cur_sample);
  
  Serial.print("cur_sample:");
  Serial.println(cur_sample);
  Serial.print(", ");
  Serial.print("cur_avg:");
  //Serial.print(analogRead(zpin));
  Serial.println(cur_avg);
  lastAvg=cur_avg;
  
}

void loop() {


  //MovingAverage();

  int cur_sample=0;
  double cur_avg=0.0;
  cur_sample= analogRead(zpin);
  cur_avg= (cur_sample*alpha) + ((lastAvg)*(1-alpha)) ;
  //Serial.print(cur_avg);
  lastAvg=cur_avg;
 // Serial.println(cur_sample);
  
  Serial.print("cur_sample:");
  Serial.println(cur_sample);
  Serial.print(", ");
  Serial.print("cur_avg:");
  //Serial.print(analogRead(zpin));
  Serial.println(cur_avg);
  lastAvg=cur_avg;
  /*
  Serial.print("AnalogIn:");
  Serial.println(sensorVal);
  Serial.print(", ");
  Serial.print("Smoothed:");
  //Serial.print(analogRead(zpin));
  Serial.println(_sampleAvg);
*/

  //Serial.println();

  // delay before next reading:
  
  delay(10);
  
}
