#define TRIGGER 0
#define ECHO 2

const float distanceLimit = 150;

bool isDoorOpen = true;
bool lastDoorStatus = true;

const int SIZE = 3;
float lastThreeDistances[SIZE] = { -1, -1, -1 };

void setup() {
  pinMode(TRIGGER, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(115200);
}

float addElement(float newElement) {
  float flag = -1;
  float correctedVal = 0;
  if (lastThreeDistances[0] != flag && lastThreeDistances[0] != 0 && newElement != 0) {

    float sum = 0;

    float oldDistanceArray[3];

    for (int i = 0; i < SIZE; i++) {
      oldDistanceArray[i] = lastThreeDistances[i];
      sum += lastThreeDistances[i];
    }

    // Shift all elements to the left
    for (int i = 0; i < SIZE - 1; i++) {
      lastThreeDistances[i] = lastThreeDistances[i + 1];
    }

    float average = sum / SIZE;
    float variance = 0;

    for (int i = 0; i < SIZE; i++) {
      variance += sq(oldDistanceArray[i] - average);
    }

    float sd = sqrt(variance / SIZE);
    float delta = abs(newElement - average);

    // if the deviation of the current values is more than the variance
    if (delta <= 3 * sd) {
      correctedVal = newElement;
    } else {
      float newValue = newElement > average ? average + sd : average - sd;
      correctedVal = newValue;
    }

  } else {
    for (int i = 0; i < SIZE - 1; i++) {
      lastThreeDistances[i] = lastThreeDistances[i + 1];
    }

    correctedVal = newElement;
  }
  lastThreeDistances[SIZE - 1] = newElement;
  return correctedVal;
}

void checkDoorStatus(float checkDistance) {

  isDoorOpen = checkDistance < distanceLimit;

  if (lastDoorStatus != isDoorOpen) {
    Serial.print("Door Status Changed. ");

    if (isDoorOpen) {
      Serial.println("The door is open.");
    } else {
      Serial.println("The door is closed.");
    }

    lastDoorStatus = isDoorOpen;
  }
}

float duration, distance;

void loop() {

  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW);

  duration = pulseIn(ECHO, HIGH);
  distance = (duration * 343) / 20000;
  float correctedDistance = addElement(distance);
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print("cm. Corrected Distance: ");
  Serial.print(correctedDistance);
  Serial.println("cm.");
  checkDoorStatus(correctedDistance);

  delay(100);
}
