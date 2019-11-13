const int TrigPin = A2;
const int EchoPin = A3;
float distance;
void setup() {
	Serial.begin(9600);
	pinMode(TrigPin, OUTPUT);
	pinMode(EchoPin, INPUT);
	Serial.println("Ultrasonic sensor:");
}
void loop() {
	digitalWrite(TrigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(TrigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(TrigPin, LOW);
	distance = pulseIn(EchoPin, HIGH) / 58.00;
	Serial.print("distance is :");
	Serial.print(distance);
	Serial.print("cm");
	Serial.println();
	delay(1000);
}
