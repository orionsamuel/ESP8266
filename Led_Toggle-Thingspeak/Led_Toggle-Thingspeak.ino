#include <ESP8266WiFi.h>  //essa biblioteca já vem com a IDE. Portanto, não é preciso baixar nenhuma biblioteca adicional
 
//defines
#define SSID_REDE     "Nilton"  //coloque aqui o nome da rede que se deseja conectar
#define SENHA_REDE    "selfcare0101"  //coloque aqui a senha da rede que se deseja conectar
#define INTERVALO_ENVIO_THINGSPEAK  15000  //intervalo entre envios de dados ao ThingSpeak (em ms)


//constantes e variáveis globais
char EnderecoAPIThingSpeak[] = "api.thingspeak.com";
String ChaveEscritaThingSpeak = "P9RFLE8PQ8R8R2EA";
long lastConnectionTime; 
WiFiClient client;

void EnviaInformacoesThingspeak(String StringDados);
void FazConexaoWiFi(void);
int FazLeituraLed(void);
void AcendeLed(void);

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


int FazLeituraLed(void)
{
  int valorLed;
  if(digitalRead(5) == HIGH){
    valorLed = 1;
  }else{
    valorLed = 0;
  }

  return valorLed;
}

void AcendeLed(void){
  if(digitalRead(4) == LOW){
    digitalWrite(5, LOW);
  }else if(digitalRead(4) == HIGH){
    digitalWrite(5, HIGH);
  }
}

void setup() {

  Serial.begin(115200);
  pinMode(5, OUTPUT); // Initialize the LED pin as an output
  pinMode(4, INPUT); // Initialize the Button pin as an input
  lastConnectionTime = 0; 
  FazConexaoWiFi();
}
// the loop function runs over and over again forever
void loop() {

  int retornoLed;
  char FieldLed[11];
  AcendeLed();

  retornoLed = FazLeituraLed();

  if(!client.connected() && 
    (millis() - lastConnectionTime > INTERVALO_ENVIO_THINGSPEAK))
  {
      sprintf(FieldLed,"field1=%d",retornoLed);
      EnviaInformacoesThingspeak(FieldLed);
  }

  delay(1000);
  
}
