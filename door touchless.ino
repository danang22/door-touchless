#define BLYNK_PRINT Serial
#define trigPin D1
#define echoPin D2

#include <Servo.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

long durasi;
int jarak;

char auth[] = "";
char ssid[] = "";
char pass[] = "";

BlynkTimer timer;

Servo myservo;

void setup()
{
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  myservo.attach(D3);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  durasi = pulseIn(echoPin, HIGH);
  jarak = durasi * 0.034 / 2;
  Serial.print(jarak);
  Serial.println("cm");
  delay(500);

  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}

void myTimerEvent()
{
  durasi = digitalRead(echoPin);
  Blynk.virtualWrite(V1, durasi);

  if (jarak < 10){
    myservo.write(100);
    delay(5000);
    Blynk.notify("Pintu Terbuka");
  }else
  {
    myservo.write(0);
  }
}
