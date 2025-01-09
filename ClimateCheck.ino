#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include "DHT.h" 
#include <TridentTD_LineNotify.h>
#define LINE_TOKEN  "rL0CJgCJgYzJQgetHIhwc6oI7YFIpXpsdtbNwKGObjw"

DHT dht;

char ssid[] = "Abcd";
char pass[] = "abcd0987654321";
String GAS_ID = "AKfycbzcAzmCAo2_aIxx2nFseHDR7P0cAuGnYNXrzPtKsDV6m4WBRVYjFJznF_MjV4BZJA2t"; 
const char* host = "script.google.com";

#define DHT_PIN               2  
#define LED_BUILTIN           13            
#define UPDATE_INTERVAL_HOUR  (0) 
#define UPDATE_INTERVAL_MIN   (0) 
#define UPDATE_INTERVAL_SEC   (30) 
#define UPDATE_INTERVAL_MS    ( ((UPDATE_INTERVAL_HOUR*60*60) + (UPDATE_INTERVAL_MIN * 60) + UPDATE_INTERVAL_SEC ) * 1000 ) 

int Temperature; 
int Humidity;

void update_google_sheet()
{
    Serial.print("connecting to ");
    Serial.println(host);
  
    WiFiClientSecure client;
    const int httpPort = 443; 
    
    client.setInsecure(); 
    if (!client.connect(host, httpPort)) { 
      Serial.println("connection failed");
      return;
    }
       
    String url = "/macros/s/" + GAS_ID + "/exec?temperature=";
   
    url += String(Temperature);
    
    url += "&humidity=";
    url += String(Humidity);
    
    Serial.print("Requesting URL: ");
    Serial.println(url);
  
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" + 
                 "Connection: close\r\n\r\n");
  
    Serial.println();
    Serial.println("closing connection");  
}

void setup()
{
  Serial.begin(115200); 

  pinMode(LED_BUILTIN, OUTPUT); 

  dht.setup(DHT_PIN); 

  Serial.print("Connecting");
  WiFi.begin(ssid, pass); 
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    digitalWrite(LED_BUILTIN, LOW);
    delay(50);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(50);
  }
  LINE.setToken(LINE_TOKEN);

  LINE.notify("System is ready.");

  LINE.notifySticker("We'll be sending temperature and humidity data to you every 30 minutes.", 11539, 52114110); 


}

unsigned long curr_time;
unsigned long last_print_time;
unsigned long last_sheet_update_time;
unsigned long time_since_last_print;

void loop()
{

  curr_time = millis();
  time_since_last_print = curr_time - last_print_time;


  if ( time_since_last_print >= 30000 ) 
  {
    last_print_time = curr_time;
    Temperature = dht.getTemperature();
    Humidity = dht.getHumidity();
  
    Serial.print("Humidity: " + String(Humidity) + " %");
    Serial.print("\t");
    Serial.println("Temperature: " + String(Temperature) + " C");
    
  
  }

  curr_time = millis();
  time_since_last_print = curr_time - last_sheet_update_time;  
  if ( time_since_last_print >= UPDATE_INTERVAL_MS ) // 30 sec 
  {
    last_sheet_update_time = curr_time;
    update_google_sheet();
  }


if (Temperature<18)
{
   LINE.notify("Temperature is TOO LOW.");
   LINE.notifySticker("The current temperature is "+String(Temperature)+" C, "+"which is "+String(18-Temperature)+" C"+" lower than the deadline of 18 C",11539,52114127);
   LINE.notify("Please take appropriate measures to upper the temperature levels in the affected area. ");
   digitalWrite(LED_BUILTIN, HIGH);
   delay(1000);
   digitalWrite(LED_BUILTIN, LOW);
   delay(5000);
}else if(Temperature>=18&&Temperature<=21)
{
   LINE.notify("Temperature is OPTIMAL.");
   LINE.notifySticker("The current temperature is "+String(Temperature)+" C",11538,51626501);
   digitalWrite(LED_BUILTIN, HIGH);
   delay(1000);
   digitalWrite(LED_BUILTIN, LOW);
   delay(5000);
}else
{
   LINE.notify("Temperature is TOO HIGH.");
   LINE.notifySticker("The current temperature is "+String(Temperature)+" C, "+"which is "+String(Temperature-21)+" C"+" higher than the deadline of 21 C",11537,52002767);
   LINE.notify("Please take appropriate measures to lower the temperature levels in the affected area. ");
   digitalWrite(LED_BUILTIN, HIGH);
   delay(1000);
   digitalWrite(LED_BUILTIN, LOW);
   delay(5000);
}

if (Humidity<30)
{
   LINE.notify("Humidity is TOO DRY.");
   LINE.notifySticker("The current humidity is "+String(Humidity)+" %,"+" which is "+String(30-Humidity)+" %"+" lower than the deadline of 30 %",11539,52114139);
   LINE.notify("Please take appropriate measures to upper the humidity levels in the affected area.");
   digitalWrite(LED_BUILTIN, HIGH);
   delay(1000);
   digitalWrite(LED_BUILTIN, LOW);
   delay(30000);
}else if(Humidity>=30&&Humidity<=50)
{
   LINE.notify("Humidity is OPTIMAL.");
   LINE.notifySticker("The current humidity is "+String(Humidity)+" %",11539,52114121);
   digitalWrite(LED_BUILTIN, HIGH);
   delay(1000);
   digitalWrite(LED_BUILTIN, LOW);
   delay(30000);
}else
{
   LINE.notify("Humidity is TOO HUMID.");
   LINE.notifySticker("The current humidity is "+String(Humidity)+" %,"+" which is "+String(Humidity-50)+" %"+" highter than the deadline of 50 %",11539,52114141);
   LINE.notify("Please take appropriate measures to lower the humidity levels in the affected area.");
   digitalWrite(LED_BUILTIN, HIGH);
   delay(1000);
   digitalWrite(LED_BUILTIN, LOW);
   delay(30000);
}

 if(Temperature >=50)
{
 LINE.notify("Temperature is TOO HIGH.");
 LINE.notify("Humidity is TOO LOW.");
 LINE.notify("The current temperature is "+String(Temperature)+" C, "+"which is "+String(Temperature-21)+" C"+" higher than the deadline of 21 C");
 LINE.notifySticker("The current humidity is "+String(Humidity)+" %,"+" which is "+String(Humidity-50)+" %"+" highter than the deadline of 50 %",6362,11087921);
 LINE.notify("Please take appropriate measures to higher the humidity and lower the Temperature in the affected area.");
 LINE.notify("Fire: 119 Medical emergency: 1669 Police: 191");
 LINE.notify("Remember to stay calm and evacuate if possible before making the call.");
   digitalWrite(LED_BUILTIN, HIGH);
   delay(1000);
   digitalWrite(LED_BUILTIN, LOW);
   delay(30000);
}
}
