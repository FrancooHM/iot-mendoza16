#include <Ethernet.h>

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};

//Mi IP
IPAddress ip(192, 168, 2, 200);
IPAddress myDns(1, 1, 1, 1);

EthernetClient client;
//Server IP
IPAddress server(192,168,2,100);

unsigned long lastConnectionTime = 0;
const unsigned long postingInterval = 3L * 1000L;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
  }

  delay(1000);

  Ethernet.begin(mac, ip, myDns);
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  delay(500);

  if (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest();
  }

}

void httpRequest() {
  
  client.stop();

  if (client.connect(server, 3000)) {
    Serial.println("connecting...");
    client.println("GET /hello HTTP/1.1");
    client.println("Host: www.arduino.cc");
    client.println("User-Agent: arduino-ethernet");
    client.println("Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
    client.println("Connection: close");
    client.println();

    lastConnectionTime = millis();
  } else {
    Serial.println("connection failed");
  }
}
