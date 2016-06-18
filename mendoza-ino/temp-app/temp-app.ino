#include <DHT.h>
#include <Ethernet.h>

/////////////////////////////////////////////
/////////////// DHT PARAMETERS //////////////
/////////////////////////////////////////////

#define DHTPIN 8
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

/////////////////////////////////////////////
/////// CLIENT ETHERNET PARAMETERS //////////
/////////////////////////////////////////////

// assign a MAC address for the ethernet controller.
// fill in your address here:
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
// fill in an available IP address on your network here,
// for manual configuration:
IPAddress ip(192, 168, 2, 200);

// fill in your Domain Name Server address here:
IPAddress myDns(1, 1, 1, 1);

// initialize the library instance:
EthernetClient client;

//char server[] = "www.arduino.cc";
IPAddress server(192,168,2,100);

unsigned long lastConnectionTime = 0;             // last time you connected to the server, in milliseconds
const unsigned long postingInterval = 3L * 1000L; // delay between updates, in milliseconds
// the "L" is needed to use long type numbers

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // give the ethernet module time to boot up:
  delay(1000);
  // start the Ethernet connection using a fixed IP address and DNS server:
  Ethernet.begin(mac, ip, myDns);
  // print the Ethernet board/shield's IP address:
  Serial.print("My IP address: ");
  Serial.println(Ethernet.localIP());
}

void loop() {
  delay(500);

  float h,t;
  getDataDHT11(h, t);
  showDataDHT11(h, t);

  // if there's incoming data from the net connection.
  // send it out the serial port.  This is for debugging
  // purposes only:
  if (client.available()) {
    char c = client.read();
    Serial.write(c);
  }

  // if ten seconds have passed since your last connection,
  // then connect again and send data:
  if (millis() - lastConnectionTime > postingInterval) {
    httpRequest(h, t, 11);
  }

}

// this is the temperature method
void getDataDHT11(float &h, float &t){
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  h = dht.readHumidity();
  // Read temperature as Celsius
  t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

}

void showDataDHT11(float h, float t){
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");
}

// this method makes a HTTP connection to the server:
void httpRequest(float h,float t, int id) {
  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();
//  String PostData="temp=";
//  PostData = String(PostData+temp);

//  String PostData = "data={";
//  PostData = "\"t\":";
//  PostData = String(PostData+t);
//  PostData = PostData + ", ";
//  PostData = "\"h\":";
//  PostData = String(PostData+h);
//  PostData = PostData + "}";  

String PostData="data={\"arduino_id\":";
  PostData=String(PostData+id);
  PostData=PostData+",";

  PostData=PostData+"\"t";
  PostData=PostData+"\":";
  PostData=String(PostData + t);
  PostData=PostData+",";

  PostData=PostData+"\"h";
  PostData=PostData+"\":";
  PostData=String(PostData + h);
  PostData=PostData+"}"; 

  // if there's a successful connection:
  if (client.connect(server, 3000)) {
    Serial.println("connecting...");
    // send the HTTP POST request:
    client.println("POST /set-temperature HTTP/1.1");
    client.println("Host: www.arduino.cc");
    client.println("User-Agent: arduino-ethernet");
    client.println("Content-Type: application/x-www-form-urlencoded; charset=UTF-8");
    client.print("Content-Length: ");
    client.println(PostData.length());
    client.println();
    client.println(PostData);
    client.println("Connection: close");
    client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  } else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}
