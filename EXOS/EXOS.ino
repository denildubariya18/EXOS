#include <Servo.h>

#define SAMPLE_RATE 50
#define BAUD_RATE 115200
#define INPUT_PIN A0

// Thresholds for detecting spikes for each finger
#define SPIKE_THRESHOLD_SERVO1_LOW 70
#define SPIKE_THRESHOLD_SERVO1_HIGH 100

#define SPIKE_THRESHOLD_SERVO2_LOW 60
#define SPIKE_THRESHOLD_SERVO2_HIGH 70

#define SPIKE_THRESHOLD_SERVO3_LOW 130
#define SPIKE_THRESHOLD_SERVO3_HIGH 300

#define SPIKE_THRESHOLD_SERVO4_LOW 40
#define SPIKE_THRESHOLD_SERVO4_HIGH 50

#define SPIKE_THRESHOLD_SERVO5_LOW 55
#define SPIKE_THRESHOLD_SERVO5_HIGH 60

// Servo motor pins and range for each finger
#define SERVO_PIN_1 9
#define SERVO_MIN_ANGLE_1 0
#define SERVO_MAX_ANGLE_1 200

#define SERVO_PIN_2 10
#define SERVO_MIN_ANGLE_2 0
#define SERVO_MAX_ANGLE_2 200

#define SERVO_PIN_3 11
#define SERVO_MIN_ANGLE_3 0
#define SERVO_MAX_ANGLE_3 200

#define SERVO_PIN_4 12
#define SERVO_MIN_ANGLE_4 0
#define SERVO_MAX_ANGLE_4 200

#define SERVO_PIN_5 13
#define SERVO_MIN_ANGLE_5 0
#define SERVO_MAX_ANGLE_5 200

// Servo motor angle range for EMG signal
#define NORMAL_ANGLE 0
#define SPIKE_ANGLE 120

Servo myServo1;
Servo myServo2;
Servo myServo3;
Servo myServo4;
Servo myServo5;

// Variables to store the previous EMG values for each finger
float prevEMGValue1 = 0;
float prevEMGValue2 = 0;
float prevEMGValue3 = 0;
float prevEMGValue4 = 0;
float prevEMGValue5 = 0;

bool isSpikeDetected1 = false;
bool isSpikeDetected2 = false;
bool isSpikeDetected3 = false;
bool isSpikeDetected4 = false;
bool isSpikeDetected5 = false;

unsigned long spikeDetectedTime1 = 0;
unsigned long spikeDetectedTime2 = 0;
unsigned long spikeDetectedTime3 = 0;
unsigned long spikeDetectedTime4 = 0;
unsigned long spikeDetectedTime5 = 0;

unsigned long holdDuration = 100;  // Hold for 100 milliseconds

void setup() {
  // Serial connection begin
  Serial.begin(BAUD_RATE);

  // Attach servo motors
  myServo1.attach(SERVO_PIN_1);
  myServo2.attach(SERVO_PIN_2);
  myServo3.attach(SERVO_PIN_3);
  myServo4.attach(SERVO_PIN_4);
  myServo5.attach(SERVO_PIN_5);

  // Set initial servo positions
  myServo1.write(NORMAL_ANGLE);
  myServo2.write(NORMAL_ANGLE);
  myServo3.write(NORMAL_ANGLE);
  myServo4.write(NORMAL_ANGLE);
  myServo5.write(NORMAL_ANGLE);
}

void loop() {
  // Calculate elapsed time
  static unsigned long past = 0;
  unsigned long present = micros();
  unsigned long interval = present - past;
  past = present;

  // Run timer
  static long timer = 100;
  timer -= interval;

  // Sample
  if (timer < 0) {
    timer += 1000000 / SAMPLE_RATE;
    float sensor_value = analogRead(INPUT_PIN);
    float signal1 = EMGFilter(sensor_value);

    // Detect spikes for the first finger
    if (signal1 > SPIKE_THRESHOLD_SERVO1_LOW && signal1 < SPIKE_THRESHOLD_SERVO1_HIGH && prevEMGValue1 <= SPIKE_THRESHOLD_SERVO1_LOW) {
      // Output the spike value
      Serial.println("Spike detected for Finger 1: " + String(signal1));

      // Adjust servo angle based on the spike
      myServo1.write(SPIKE_ANGLE);

      // Set flags to indicate spike detection and record the time
      isSpikeDetected1 = true;
      spikeDetectedTime1 = millis();
    }

    // Check if the hold duration has passed after spike detection for the first finger
    if (isSpikeDetected1 && (millis() - spikeDetectedTime1 >= holdDuration)) {
      // Return the servo to the normal position for the first finger
      myServo1.write(NORMAL_ANGLE);
      isSpikeDetected1 = false;  // Reset spike detection flag
    }

    // Sample for the second finger
    float signal2 = EMGFilter(sensor_value);

    // Detect spikes for the second finger
    if (signal2 > SPIKE_THRESHOLD_SERVO2_LOW && signal2 < SPIKE_THRESHOLD_SERVO2_HIGH && prevEMGValue2 <= SPIKE_THRESHOLD_SERVO2_LOW) {
      // Output the spike value
      Serial.println("Spike detected for Finger 2: " + String(signal2));

      // Adjust servo angle based on the spike
      myServo2.write(SPIKE_ANGLE);

      // Set flags to indicate spike detection and record the time
      isSpikeDetected2 = true;
      spikeDetectedTime2 = millis();
    }

    // Check if the hold duration has passed after spike detection for the second finger
    if (isSpikeDetected2 && (millis() - spikeDetectedTime2 >= holdDuration)) {
      // Return the servo to the normal position for the second finger
      myServo2.write(NORMAL_ANGLE);
      isSpikeDetected2 = false;  // Reset spike detection flag
    }

    // Sample for the third finger
    float signal3 = EMGFilter(sensor_value);

    // Detect spikes for the third finger
    if (signal3 > SPIKE_THRESHOLD_SERVO3_LOW && signal3 < SPIKE_THRESHOLD_SERVO3_HIGH && prevEMGValue3 <= SPIKE_THRESHOLD_SERVO3_LOW) {
      // Output the spike value
      Serial.println("Spike detected for Finger 3: " + String(signal3));

      // Adjust servo angle based on the spike
      myServo3.write(SPIKE_ANGLE);

      // Set flags to indicate spike detection and record the time
      isSpikeDetected3 = true;
      spikeDetectedTime3 = millis();
    }

    // Check if the hold duration has passed after spike detection for the third finger
    if (isSpikeDetected3 && (millis() - spikeDetectedTime3 >= holdDuration)) {
      // Return the servo to the normal position for the third finger
      myServo3.write(NORMAL_ANGLE);
      isSpikeDetected3 = false;  // Reset spike detection flag
    }

    // Sample for the fourth finger
    float signal4 = EMGFilter(sensor_value);

    // Detect spikes for the fourth finger
    if (signal4 > SPIKE_THRESHOLD_SERVO4_LOW && signal4 < SPIKE_THRESHOLD_SERVO4_HIGH && prevEMGValue4 <= SPIKE_THRESHOLD_SERVO4_LOW) {
      // Output the spike value
      Serial.println("Spike detected for Finger 4: " + String(signal4));

      // Adjust servo angle based on the spike
      myServo4.write(SPIKE_ANGLE);

      // Set flags to indicate spike detection and record the time
      isSpikeDetected4 = true;
      spikeDetectedTime4 = millis();
    }

    // Check if the hold duration has passed after spike detection for the fourth finger
    if (isSpikeDetected4 && (millis() - spikeDetectedTime4 >= holdDuration)) {
      // Return the servo to the normal position for the fourth finger
      myServo4.write(NORMAL_ANGLE);
      isSpikeDetected4 = false;  // Reset spike detection flag
    }

    // Sample for the fifth finger
    float signal5 = EMGFilter(sensor_value);

    // Detect spikes for the fifth finger
    if (signal5 > SPIKE_THRESHOLD_SERVO5_LOW && signal5 < SPIKE_THRESHOLD_SERVO5_HIGH && prevEMGValue5 <= SPIKE_THRESHOLD_SERVO5_LOW) {
      // Output the spike value
      Serial.println("Spike detected for Finger 5: " + String(signal5));

      // Adjust servo angle based on the spike
      myServo5.write(SPIKE_ANGLE);

      // Set flags to indicate spike detection and record the time
      isSpikeDetected5 = true;
      spikeDetectedTime5 = millis();
    }

    // Check if the hold duration has passed after spike detection for the fifth finger
    if (isSpikeDetected5 && (millis() - spikeDetectedTime5 >= holdDuration)) {
      // Return the servo to the normal position for the fifth finger
      myServo5.write(NORMAL_ANGLE);
      isSpikeDetected5 = false;  // Reset spike detection flag
    }

    // Store the current EMG values for comparison in the next iteration
    prevEMGValue1 = signal1;
    prevEMGValue2 = signal2;
    prevEMGValue3 = signal3;
    prevEMGValue4 = signal4;
    prevEMGValue5 = signal5;
  }
}

float EMGFilter(float input) {
  float output = input;
  {
    static float z1, z2; // filter section state
    float x = output - 0.05159732 * z1 - 0.36347401 * z2;
    output = 0.01856301 * x + 0.03712602 * z1 + 0.01856301 * z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -0.53945795 * z1 - 0.39764934 * z2;
    output = 1.00000000 * x + -2.00000000 * z1 + 1.00000000 * z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - 0.47319594 * z1 - 0.70744137 * z2;
    output = 1.00000000 * x + 2.00000000 * z1 + 1.00000000 * z2;
    z2 = z1;
    z1 = x;
  }
  {
    static float z1, z2; // filter section state
    float x = output - -1.00211112 * z1 - 0.74520226 * z2;
    output = 1.00000000 * x + -2.00000000 * z1 + 1.00000000 * z2;
    z2 = z1;
    z1 = x;
  }
  return output;
}