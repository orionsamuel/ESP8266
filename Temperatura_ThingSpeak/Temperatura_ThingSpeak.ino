#include <DHT.h>
#include <ESP8266WiFi.h>  //essa biblioteca já vem com a IDE. Portanto, não é preciso baixar nenhuma biblioteca adicional
 
//defines
#define SSID_REDE     "Nilton"  //coloque aqui o nome da rede que se deseja conectar
#define SENHA_REDE    "selfcare0101"  //coloque aqui a senha da rede que se deseja conectar
#define INTERVALO_ENVIO_THINGSPEAK  120000  //intervalo entre envios de dados ao ThingSpeak (em ms)
 
//constantes e variáveis globais
char EnderecoAPIThingSpeak[] = "api.thingspeak.com";
String ChaveEscritaThingSpeak = "VNB7TARXYOQIO3W1";
long lastConnectionTime; 
WiFiClient client;
 
//prototypes
void EnviaInformacoesThingspeak(String StringDados);
void FazConexaoWiFi(void);
float FazLeituraUmidade(void);
float FazLeituraTemperatura(void);

void EnviaInformacoesThingspeak(String StringDados)
{
    if (client.connect(EnderecoAPIThingSpeak, 80))
    {         
        //faz a requisição HTTP ao ThingSpeak
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: "+ChaveEscritaThingSpeak+"\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(StringDados.length());
        client.print("\n\n");
        client.print(StringDados);
   
        lastConnectionTime = millis();
        Serial.println("- Informações enviadas ao ThingSpeak!");
     }   
}

void FazConexaoWiFi(void)
{
    client.stop();
    Serial.println("Conectando-se à rede WiFi...");
    Serial.println();  
    delay(1000);
    WiFi.begin(SSID_REDE, SENHA_REDE);
 
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

 
#define DHTTYPE DHT11 // DHT 11 (AM2302)
 
#define DHTPIN 5 // GPIO ou porta D1 do NodeMCU
 
DHT dht(DHTPIN, DHTTYPE); //Criação do objeto de leitura DHT
 
float t,h; //variáveis que armazenarão os valores lidos de temperatura e umidade;


void setup(){
 
  dht.begin(); //Inicia o sensor
  Serial.begin(115200);
  lastConnectionTime = 0; 
  FazConexaoWiFi();
 
}
 
void loop(){
  int UmidadePercentualTruncada;
  int TemperaturaPercentualTruncada;
  char FieldUmidade[11];
  char FieldTemperatura[11];

  //Força desconexão ao ThingSpeak (se ainda estiver desconectado)
  if (client.connected())
  {
    client.stop();
    Serial.println("- Desconectado do ThingSpeak");
    Serial.println();
  }

  Serial.println("Temperatura");
  t=dht.readTemperature(); //Função de leitura da temperatura

  Serial.println(t);

  Serial.println("Umidade");
  h=dht.readHumidity();//Função de leitura da umidade

  Serial.println(h);
  
  UmidadePercentualTruncada = (int)h; //trunca umidade como número inteiro
  TemperaturaPercentualTruncada = (int)t; //trunca temperatura como número inteiro
   
  //verifica se está conectado no WiFi e se é o momento de enviar dados ao ThingSpeak
  if(!client.connected() && 
    (millis() - lastConnectionTime > INTERVALO_ENVIO_THINGSPEAK))
  {
      //sprintf(FieldUmidade,"field2=%d",UmidadePercentualTruncada);
      //EnviaInformacoesThingspeak(FieldUmidade);
      sprintf(FieldTemperatura,"field1=%d",TemperaturaPercentualTruncada);
      EnviaInformacoesThingspeak(FieldTemperatura);
  }

  delay(1000);
 
}
