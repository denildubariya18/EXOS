#include <Servo.h>

#define SAMPLE_RATE 100
#define BAUD_RATE 115200
#define INPUT_PIN A0

// Threshold for detecting spikes
#define SPIKE_THRESHOLD 70

// Servo motor pins and range
#define SERVO_PIN 9
#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 180

// Servo motor angle range for EMG signal
#define EMG_MIN_ANGLE 74
#define EMG_MAX_ANGLE 125

Servo myServo;

// Variable to store the previous EMG value
float prevEMGValue = 0;

void setup() {
  // Serial connection begin
  Serial.begin(BAUD_RATE);

  // Attach servo motor
  myServo.attach(SERVO_PIN);
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
    float signal = EMGFilter(sensor_value);

    // Detect spikes
    if (signal > SPIKE_THRESHOLD && prevEMGValue <= SPIKE_THRESHOLD) {
      // Output the spike value
      Serial.println(signal);

      // Map EMG signal to servo angle within the desired range
      int servoAngle = map(signal, SPIKE_THRESHOLD, 1023, EMG_MIN_ANGLE, EMG_MAX_ANGLE);
      myServo.write(constrain(servoAngle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE));
    }

    // Store the current EMG value for comparison in the next iteration
    prevEMGValue = signal;
  }
}

// Band-Pass Butterworth IIR digital filter, generated using filter_gen.py.
// Sampling rate: 500.0 Hz, frequency: [74.5, 149.5] Hz.
// Filter is order 4, implemented as second-order sections (biquads).
// Reference: 
// https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.butter.html
// https://courses.ideate.cmu.edu/16-223/f2020/Arduino/FilterDemos/filter_gen.py
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
