#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define TOPICO_SUBSCRIBE "MQTTSamuelOliveiraEnvia"
#define TOPICO_PUBLISH   "MQTTSamuelOliveiraRecebe"

#define ID_MQTT  "orionsamuel"

const char* SSID = "Nilton";
const char* PASSWORD = "selfcare0101";

const char* BROKER_MQTT = "broker.mqtt-dashboard.com";
int BROKER_PORT = 1883;

WiFiClient espClient;
PubSubClient MQTT(espClient);
char EstadoSaida = '0'; 

void initSerial();
void initWiFi();
void initMQTT();
void reconectWiFi(); 
void mqtt_callback(char* topic, byte* payload, unsigned int length);
void VerificaConexoesWiFIEMQTT(void);
void InitOutput(void);

void setup() {
  InitOutput();
  initSerial();
  initWiFi();
  initMQTT();
}

void initSerial() 
{
    Serial.begin(115200);
}

void initWiFi() 
{
    delay(10);
    Serial.println("------Conexao WI-FI------");
    Serial.print("Conectando-se na rede: ");
    Serial.println(SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
    Serial.println("Aguarde");
     
    reconectWiFi();
}

void initMQTT() 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);
    MQTT.setCallback(mqtt_callback);
}

void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    String msg;
 
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
    
    if (msg.equals("L"))
    {
        digitalWrite(4, HIGH);
        EstadoSaida = '1';
    }
 
    if (msg.equals("D"))
    {
        digitalWrite(4, LOW);
        EstadoSaida = '0';
    }
}

void reconnectMQTT() 
{
    while (!MQTT.connected()) 
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT)) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");
            MQTT.subscribe(TOPICO_SUBSCRIBE); 
        } 
        else
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(2000);
        }
    }
}

void reconectWiFi() 
{
    //se já está conectado a rede WI-FI, nada é feito. 
    //Caso contrário, são efetuadas tentativas de conexão
    if (WiFi.status() == WL_CONNECTED)
        return;
         
    WiFi.begin(SSID, PASSWORD); // Conecta na rede WI-FI
     
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(100);
        Serial.print(".");
    }
   
    Serial.println();
    Serial.print("Conectado com sucesso na rede ");
    Serial.print(SSID);
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
}

void VerificaConexoesWiFIEMQTT(void)
{
    if (!MQTT.connected()) 
        reconnectMQTT(); //se não há conexão com o Broker, a conexão é refeita
     
     reconectWiFi(); //se não há conexão com o WiFI, a conexão é refeita
}

void EnviaEstadoOutputMQTT(void)
{
    if (EstadoSaida == '0')
      MQTT.publish(TOPICO_PUBLISH, "D");
 
    if (EstadoSaida == '1')
      MQTT.publish(TOPICO_PUBLISH, "L");
 
    Serial.println("- Estado da saida do pino 4 enviado ao broker!");
    delay(1000);
}

void InitOutput(void)
{
    pinMode(4, OUTPUT);
    digitalWrite(4, LOW);          
}

void loop() {
  VerificaConexoesWiFIEMQTT();
  EnviaEstadoOutputMQTT();
  MQTT.loop();
}
