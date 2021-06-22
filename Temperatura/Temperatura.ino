#include <DHT.h>
 
 
#define DHTTYPE DHT11 // DHT 11 (AM2302)
 
#define DHTPIN 5 // GPIO = porta D1 do NodeMCU
 
DHT dht(DHTPIN, DHTTYPE); //Criação do objeto de leitura DHT
 
float t,h; //variáveis que armazenarão os valores lidos de temperatura e umidade;
 
 
void setup(){
 
dht.begin(); //Inicia o sensor
Serial.begin(115200);
 
}
 
void loop(){
 
t=dht.readTemperature(); //Função de leitura da temperatura

Serial.print("Temperatura: ");

Serial.println(t);
 
h=dht.readHumidity();//Função de leitura da umidade

Serial.print("Humidade: ");

Serial.println(h);

delay(1000);
 
}
