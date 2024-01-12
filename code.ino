const int pinTGS822 = A0; 
const int pinTGS2600 = A1;
const int pinTGS2610 = A2;
const int pinTGS2620 = A3;

int initialTGS822 = 0;
int initialTGS2600 = 0;
int initialTGS2610 = 0;
int initialTGS2620 = 0;

int valueTGS822;
int valueTGS2600;
int valueTGS2610;
int valueTGS2620;
const int breathThreshold = 5; 
unsigned long lastEventTime = 0;

enum State {
    READING,
    DELAY,
    PRINT,
    COOLDOWN
};

State currentState = READING;

void setup() {
  Serial.begin(9600);

  initialTGS822 = analogRead(pinTGS822);
  initialTGS2600 = analogRead(pinTGS2600);
  initialTGS2610 = analogRead(pinTGS2610);
  initialTGS2620 = analogRead(pinTGS2620);

}

void loop() {
  unsigned long currentTime = millis();

  if(currentState == READING) {
      valueTGS822 = analogRead(pinTGS822);
      valueTGS2600 = analogRead(pinTGS2600);
      valueTGS2610 = analogRead(pinTGS2610);
      valueTGS2620 = analogRead(pinTGS2620);

      if ((valueTGS822 - initialTGS822 >= breathThreshold) ||
          (valueTGS2600 - initialTGS2600 >= breathThreshold) ||
          (valueTGS2610 - initialTGS2610 >= breathThreshold) ||
          (valueTGS2620 - initialTGS2620 >= breathThreshold)) {
        currentState = DELAY;
        lastEventTime = currentTime;
      }
  }
    else if(currentState==DELAY){
      if (currentTime - lastEventTime >= 60000) {
        currentState = PRINT;
      }
     }
    else if(currentState==PRINT){
      valueTGS822 = analogRead(pinTGS822);
      valueTGS2600 = analogRead(pinTGS2600);
      valueTGS2610 = analogRead(pinTGS2610);
      valueTGS2620 = analogRead(pinTGS2620);
      Serial.print(valueTGS822);
      Serial.print(",");
      Serial.print(valueTGS2600);
      Serial.print(",");
      Serial.print(valueTGS2610);
      Serial.print(",");
      Serial.println(valueTGS2620);

      currentState = COOLDOWN;
      lastEventTime = currentTime;
    }

    else if(currentState == COOLDOWN){
      if (currentTime - lastEventTime >= 60000) {
        initialTGS822 = analogRead(pinTGS822);
        initialTGS2600 = analogRead(pinTGS2600);
        initialTGS2610 = analogRead(pinTGS2610);
        initialTGS2620 = analogRead(pinTGS2620);
        currentState = READING;
      }
  }
}
