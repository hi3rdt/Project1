#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "Your Template ID"
#define BLYNK_TEMPLATE_NAME "Dieu khien tu dong tuoi cay"
#define BLYNK_AUTH_TOKEN "Your Token"


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;



char ssid[] = "WIFI 5";
char pass[] = "0987654322";
#define analogPin A0
#define relay D2

int analogVal,Ref1,Ref2;
int percent;
void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  pinMode(relay, OUTPUT);
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);
  
}
BLYNK_WRITE(V2)
  {
    Ref1 = param.asInt();
  }    
BLYNK_WRITE(V3)
  {
    Ref2 = param.asInt();
  } 
void loop()
{
  Blynk.run();
  timer.run();
  analogVal = analogRead(analogPin);
  percent = map(analogVal, 0 , 1023, 100,0 );
  
  Blynk.virtualWrite(V1, percent);
    if(percent <  Ref2 )
    {
      digitalWrite(relay, HIGH);
      Serial.println("Bat bom tuoi");
    }
    else if(percent > Ref1)
    {
      digitalWrite(relay, LOW);
      Serial.println("Tat bom tuoi");
    }
    else
    {
      digitalWrite(relay, LOW);
      Serial.println("Do am binh thuong");
    }
  }


