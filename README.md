# Arduino-Sketch

En este repositorio encontramos el sketch que, cargado en nuestro Arduino YUN, nos permite obtener valores de temperatura y humedad y los sube al servidor.

## Componentes necesarios

- Arduino YUN

<img src="http://i.imgur.com/9AarnLS.jpg" data-canonical-src="http://i.imgur.com/9AarnLS.jpg" width="280" height="250" />

- Sensor de temperatura y humedad DHT11

<img src="http://i.imgur.com/yx1x1KK.jpg" data-canonical-src="http://i.imgur.com/yx1x1KK.jpg" width="200" height="200" />

- Cable micro USB
- Cable de red con RJ45


## Conexiones

Conectamos la señal del sensor al pin 12 del Arduino YUN, el positivo a 3.3V y el negativo a tierra.

<img src="http://i.imgur.com/6SWgQ62.png" data-canonical-src="http://i.imgur.com/6SWgQ62.png" width="400" height="500" />

## Sketch

El sketch es muy sencillo, en el bucle principal realizamos los siguientes pasos:

- Obtenemos la temperatura y la humedad:

```c
dht11.read(humidity, temperature)
```

- Si la llamada se realizar correctamente, tenemos los valores en las variable ```humidity``` y ```temperature```. El siguiente paso es enviar dichos valores a nuestro servidor:

```c
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
```

Este script intenta conectar con el servidor, y después ejecuta una petición POST con los valores obtenidos del sensor como parámetros. Cuando se suban los valores, esperamos dos segundos para volver a obtener información del sensor.

# Como cargar el sketch en el Arduino YUN

1. Clonar el repositorio.
2. Abrir Arduino IDE. [Enlace de descarga](https://www.arduino.cc/en/main/software).
3. Abrimos el sketch desde la carpeta clonada.
4. Conectamos el Arduino YUN al PC.
5. Herramientas > Placa > Arduino YUN.
6. Herramientas > Puerto > COMXX.
7. Subir.

Cuando termine la carga, podremos conectar el arduino al router por cable y en ese momento el servidor empezará a recibir las peticiones POST enviadas desde el mismo con los valores de temperatura y humedad.

Al usar un Arduino YUN, también podríamos [conectar el arduino al router por WIFI](https://www.arduino.cc/en/Guide/ArduinoYun).
