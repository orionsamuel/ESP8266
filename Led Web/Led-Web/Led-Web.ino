#include <ESP8266WiFi.h>

const char* ssid = "Nilton";

const char* password = "selfcare0101";

WiFiServer server(80); 

int ledPin = 4;
void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Comunicação com a rede WiFi

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // Servidor

  server.begin();
  Serial.println("Servidor iniciado");

  // Impressão do endereço IP

  Serial.print("Use o seguinte URL para a comunicação: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void loop() {
  // Verificação se o cliente está conectado
  WiFiClient client = server.available();

  if (!client) {
    return;    
  }

  // Espera até o cliente enviar dados

  Serial.println("novo cliente");
  while(!client.available()){
    delay(1);
  }

  // Ler a primeira linha do pedido
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  // Operação do pedido
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1){
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }

  if (request.indexOf("/LED=OFF") != -1){
    digitalWrite(ledPin, LOW);
    value = LOW;
  }

  // Inicialização da página HTML
  // Retorno do resposta
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("Estado do LED: ");
  if(value == HIGH) {
    client.print("On");
  }else{
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");
  client.println("</html>");

  delay(1);
  Serial.println("Cliente desconectado");
  Serial.println("");
}
