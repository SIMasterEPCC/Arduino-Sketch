#include <Bridge.h>
#include <Console.h>
#include <FileIO.h>
#include <HttpClient.h>
#include <Mailbox.h>
#include <Process.h>
#include <YunClient.h>
#include <YunServer.h>
#include <SPI.h>
#include <DHT11.h>

IPAddress server(158,49,112,86);

YunClient client;

int pin=12;

DHT11 dht11(pin); 

String params ="";           //POST parameters

void setup()
{
       Bridge.begin();
       Serial.begin(9600);
}

void loop()
{
    int err;
    float temperature, humidity;
    if((err=dht11.read(humidity, temperature))==0)
    {
      if (client.connect(server, 1521)) {
                Serial.println("connected");
                delay(2500);
                params="temp="+String(temperature) + "&hum="+ String(humidity);
                client.println("POST /medidas HTTP/1.1");
                client.println("Host: http://158.49.112.86");
                client.print("Content-length:");
                client.println(params.length());
                Serial.println(params);
                client.println("Connection: Close");
                client.println("Content-Type: application/x-www-form-urlencoded;");
                client.println();
                client.println(params);  
       }else{
              Serial.println("connection failed");
              delay(1000);
       }
       if(client.connected()){
                   client.stop();
       }
       delay(2000);
    }
    else
    {
      Serial.println();
      Serial.print("Error No :");
      Serial.print(err);
      Serial.println();    
    }
    
    delay(DHT11_RETRY_DELAY); //delay for reread
      
}
