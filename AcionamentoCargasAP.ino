#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>

#define carga1 16
#define carga2 17
#define carga3 18
#define carga4 19

const char* ssid = "MYESP32";      //crie uma rede WiFi e insira aqui o nome da rede ou use uma rede já existente
const char* password = "SENAI2023";  //coloque a senha da rede WiFi 

IPAddress local_IP(192, 168, 0, 200);
// Set your Gateway IP address
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  pinMode(carga1, OUTPUT);
  pinMode(carga2, OUTPUT);
  pinMode(carga3, OUTPUT);
  pinMode(carga4, OUTPUT);

  WiFi.mode(WIFI_AP_STA); 

  if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
    Serial.println("AP Config Failed");
    return;
  }

  delay(10);

  if (!WiFi.softAP(ssid, password)) {
    Serial.println("AP Failed");
    return;
  }

  Serial.println("Server started");
  Serial.print("AP IP address: ");
  IPAddress IP = WiFi.softAPIP();
  Serial.println(IP);
  server.begin();
}

void loop() {
  WiFiClient client = server.available();   

  if (client) {                            
    Serial.println("New Client.");           
    String currentLine = "";               
    while (client.connected()) {           
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                    
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            // HTTP 
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            client.println("<head><meta content=\"width=device-width, initial-scale=1\">");
            client.println("<style>html{ magin:0px auto; text-align: center;}");
            client.println(".botao_liga {background-color: #00FF00; color: white; padding: 15px 40px; border-radius: 10px; width: 60%}");
            client.println(".botao_desliga {background-color: #FF0000; color: white; padding: 15px 40px; border-radius: 10px;width: 60%}");
            client.println(".buttons {display:flex; flex-direction: row; flex-wrap: wrap; justify-content: space-around}");
            client.println(".button {width: 48%; margin-top:1rem}</style></head>");
            client.println("<body><h1>WEBSERVER COM ESP32 SENAI</h1>");

            client.println("<br><br>");

            client.println("<div class=\"buttons\">");
              client.println("<div class =\"button\">");
                client.println("<h1>CARGA 01</h1>");
                client.println("<p><a href=\"/C1-ON\"><button class=\"botao_liga\">LIGA</button></a></p>");
                client.println("<p><a href=\"/C1-OFF\"><button class=\"botao_desliga\">DESLIGA</button></a></p>");
              client.println("</div>");

              client.println("<div class =\"button\">");
                client.println("<h1>CARGA 02</h1>");
                client.println("<p><a href=\"/C2-ON\"><button class=\"botao_liga\">LIGA</button></a></p>");
                client.println("<p><a href=\"/C2-OFF\"><button class=\"botao_desliga\">DESLIGA</button></a></p>");
              client.println("</div>");

              client.println("<div class =\"button\">");
                client.println("<h1>CARGA 03</h1>");
                client.println("<p><a href=\"/C3-ON\"><button class=\"botao_liga\">LIGA</button></a></p>");
                client.println("<p><a href=\"/C3-OFF\"><button class=\"botao_desliga\">DESLIGA</button></a></p>");
              client.println("</div>");

              client.println("<div class =\"button\">");
                client.println("<h1>CARGA 04</h1>");
                client.println("<p><a href=\"/C4-ON\"><button class=\"botao_liga\">LIGA</button></a></p>");
                client.println("<p><a href=\"/C4-OFF\"><button class=\"botao_desliga\">DESLIGA</button></a></p>");
              client.println("</div>");

            client.println("</div>");
            client.println("</body></html>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Acionamento dos Cliente web
        
        if (currentLine.endsWith("GET /C1-ON")) {
          digitalWrite(carga1, HIGH);               
        }
        if (currentLine.endsWith("GET /C1-OFF")) {
          digitalWrite(carga1, LOW);                
        }

        // CARGA  2
        if (currentLine.endsWith("GET /C2-ON")) {
          digitalWrite(carga2, HIGH);               
        }
        if (currentLine.endsWith("GET /C2-OFF")) {
          digitalWrite(carga2, LOW);                
        }

        // CARGA  3
        if (currentLine.endsWith("GET /C3-ON")) {
          digitalWrite(carga3, HIGH);               
        }
        if (currentLine.endsWith("GET /C3-OFF")) {
          digitalWrite(carga3, LOW);                
        }

        // CARGA  4
        if (currentLine.endsWith("GET /C4-ON")) {
          digitalWrite(carga4, HIGH);               
        }
        if (currentLine.endsWith("GET /C4-OFF")) {
          digitalWrite(carga4, LOW);                
        }
      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
