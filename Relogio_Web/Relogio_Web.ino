#include <NTPClient.h>          
#include <ESP8266WiFi.h>        
#include <WiFiUdp.h>           

const char *ssid     = "Orion";       // nome do seu roteador WIFI (SSID)
const char *password = "Ananindeua@07";       // senha do roteador WIFI

WiFiUDP ntpUDP;
WiFiClient client;
// Definindo o Servidor de relogio NTP Brasil, ajusta relogio UTC -3 horas, intervalo de atualizacao em milisegundos
NTPClient timeClient(ntpUDP, "gps.ntp.br", -3 * 3600, 60000);
void FazConexaoWiFi(void);

void FazConexaoWiFi(void)
{
    client.stop();
    Serial.println("Conectando-se à rede WiFi...");
    Serial.println();  
    delay(1000);
    WiFi.begin(ssid, password);
 
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
 
    Serial.println("");
    Serial.println("WiFi connectado com sucesso!");  
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
 
    delay(1000);
}

void setup()
{
  Serial.begin(115200);                     // print no Serial Monitor da IDE
  FazConexaoWiFi();
}

void loop()
{
  timeClient.update();                              // atualiza o relogio
  Serial.println(timeClient.getFormattedTime());    // print do relogio da WEB
  delay(1000);                                      // atraso de um segundo
}
