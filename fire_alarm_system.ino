#define BLYNK_TEMPLATE_ID "TMPLSO-aWPeq"
#define BLYNK_DEVICE_NAME "fire detection"
#define BLYNK_AUTH_TOKEN "tntXg720mItvMB2tD3RA1fkZ1d75XZuV"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "vedant"; // Change your Wifi/ Hotspot Name
char pass[] = "vedant112233"; // Change your Wifi/ Hotspot Password

BlynkTimer timer;

#define fire D2
#define GREEN D3
#define RED D6
#define buzzer  D7
int fire_Val = 0;

WidgetLED led(V1);

void setup() //Setup function - only function that is run in deep sleep mode
{
  Serial.begin(9600); //Start the serial output at 9600 baud
  pinMode(GREEN, OUTPUT);
  pinMode(fire, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  Blynk.begin(auth, ssid, pass);
  delay(2000);
  timer.setInterval(500L, mySensor);
}

void loop() //Loop function
{
  Blynk.run();
  timer.run();
}

void mySensor()
{
  fire_Val = digitalRead(fire);
   
  if (fire_Val == LOW)
  {
    Blynk.logEvent("fire_alert");
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    digitalWrite(buzzer, HIGH);
    Blynk.virtualWrite(V0, 1);
    Serial.print("fIRE Level: ");
    Serial.println(fire_Val);
    led.on();
  }

  else
  {
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
    digitalWrite(buzzer, LOW);
    Blynk.virtualWrite(V0, 0);
    Serial.print("fIRE Level: ");
    Serial.println(fire_Val);
    led.off();
  }    
}
