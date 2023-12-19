#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define  trig  D6
#define  echo  D7
#define ledred D4
#define ledgreen D3

long duration;
int distance;
int sensorData;
// You should get Auth Token in the Blynk App.
char auth[] = "4NInKBCA7qdXue0-ElCp7ULeJ0GXWAC8";
char ssid[] = "INNARASI";   // your ssid
char pass[] = "12345678"; // your wifi pass

BlynkTimer timer;

void setup()
{
  // Debug console
  pinMode(trig, OUTPUT);  // Sets the trigPin as an Output
  pinMode(echo, INPUT);   // Sets the echoPin as an Input
  pinMode(ledred,OUTPUT);
  pinMode(ledgreen,OUTPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, sendAnalog);
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run();
  timer.run();
}
void sendSensor()
{
  digitalWrite(trig, LOW);   // Makes trigPin low
  delayMicroseconds(2);       // 2 micro second delay
  digitalWrite(trig, HIGH);  // tigPin high
  delayMicroseconds(10);      // trigPin high for 10 micro seconds
  digitalWrite(trig, LOW);   // trigPin low

  duration = pulseIn(echo, HIGH);   //Read echo pin, time in microseconds
  distance = duration * 0.034 / 2;   //Calculating actual/real distance

  Serial.print("Distance = ");        //Output distance on arduino serial monitor
  Serial.println(distance);
  digitalWrite(ledgreen,HIGH);
  digitalWrite(ledred,LOW);
  
  if(distance <= 5)
  {
    //Blynk.tweet("My Arduino project is tweeting using @blynk_app and it’s awesome!\n #arduino #IoT #blynk");
    Blynk.notify("Dustbin is full");
    Blynk.email("Dustbin Status", "Dustbin is full");
    digitalWrite(ledred,HIGH);
    delay(2000);
    digitalWrite(ledgreen,LOW);
    delay(2000);
    Serial.println("led red is high");
    delay(1000);
  }
  Blynk.virtualWrite(V0, distance);
  delay(1000);                        //Pause for 3 seconds and start measuring distance again
}


void sendAnalog()
{
  sensorData = analogRead(A0); //reading the sensor on A0
  Blynk.virtualWrite(V5, sensorData); //sending to Blynk
  Blynk.notify("Dust detected");
  Blynk.email("Dust Status", "Dust Detected");
  Serial.print("mq135: ");
  Serial.println(sensorData);
}

//email to: innarasi95@gmail.com
