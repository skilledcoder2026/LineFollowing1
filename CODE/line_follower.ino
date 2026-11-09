const int PWMA = 5, AIN1 = 7, AIN2 = 8;
const int PWMB = 6, BIN1 = 9, BIN2 = 10;
const int STBY = 4;

const int SENSOR_PINS[5] = {A0, A1, A2, A3, A4};
const int WEIGHTS[5]     = {-2, -1, 0, 1, 2};

const int  THRESHOLD     = 500;
const bool BLACK_IS_HIGH = true;

const int MAX_SPEED    = 180;
const int BASE_SPEED   = 110;
const int SEARCH_SPEED = 90;

float Kp = 30;
float Kd = 20;

const unsigned long START_DELAY_MS  = 2000;
const unsigned long LOST_TIMEOUT_MS = 1500;

const bool PRINT_MODE = false;

float lastError = 0;
unsigned long lostSince = 0;
bool wasLost = false;

void setMotors(int left, int right) {
  left  = constrain(left,  -MAX_SPEED, MAX_SPEED);
  right = constrain(right, -MAX_SPEED, MAX_SPEED);

  digitalWrite(AIN1, left >= 0);
  digitalWrite(AIN2, left < 0);
  digitalWrite(BIN1, right >= 0);
  digitalWrite(BIN2, right < 0);

  analogWrite(PWMA, abs(left));
  analogWrite(PWMB, abs(right));
}

void stopMotors() {
  setMotors(0, 0);
}

bool readLine(float &error) {
  int sum = 0, count = 0;
  for (int i = 0; i < 5; i++) {
    bool high = analogRead(SENSOR_PINS[i]) > THRESHOLD;
    bool onLine = BLACK_IS_HIGH ? high : !high;
    if (onLine) {
      sum += WEIGHTS[i];
      count++;
    }
  }
  if (count == 0) return false;
  error = (float)sum / count;
  return true;
}

void setup() {
  pinMode(PWMA, OUTPUT); pinMode(AIN1, OUTPUT); pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT); pinMode(BIN1, OUTPUT); pinMode(BIN2, OUTPUT);
  pinMode(STBY, OUTPUT);

  Serial.begin(9600);
  stopMotors();
  digitalWrite(STBY, HIGH);

  if (!PRINT_MODE) delay(START_DELAY_MS);
}

void loop() {
  if (PRINT_MODE) {
    for (int i = 0; i < 5; i++) {
      Serial.print(analogRead(SENSOR_PINS[i]));
      Serial.print("\t");
    }
    Serial.println();
    delay(200);
    return;
  }

  float error;
  if (readLine(error)) {
    if (wasLost) {
      lastError = error;
      wasLost = false;
    }

    float correction = Kp * error + Kd * (error - lastError);
    lastError = error;

    setMotors((int)(BASE_SPEED + correction), (int)(BASE_SPEED - correction));
  } else {
    if (!wasLost) {
      wasLost = true;
      lostSince = millis();
    }
    if (millis() - lostSince > LOST_TIMEOUT_MS) {
      stopMotors();
      return;
    }
    if (lastError < 0) setMotors(-SEARCH_SPEED, SEARCH_SPEED);
    else               setMotors(SEARCH_SPEED, -SEARCH_SPEED);
  }
}
