//NodeMCU
#include <ESP8266WiFi.h> // Library of ESP8266 .. 
#include "FirebaseESP8266.h"
#include <Keypad.h>


#define WIFI_SSID "ALML78 4G"
#define WIFI_PASSWORD "EnterPasswordHere"

#define FIREBASE_HOST "nodemcu-bid-default-rtdb.firebaseio.com"  // from firebase .. 
#define FIREBASE_AUTH "ZshkWmOZVYSdGjJtqb3AD23pPQnxjNpBkyRAhIxO" // private key from the database .. 

//Define FirebaseESP8266 data object
FirebaseData firebaseData;

//LED Pins
int greenPin = 12;

const byte ROWS = 4; // four rows .. 
const byte COLS = 4; // four columns .. 


char hexaKeys[ROWS][COLS] =
{              // defining the rows and columns and what each index have .. 
  {'.', '#', '0', '*'},
  {'.', '9', '8', '7'},
  {'.', '6', '5', '4'},
  {'.', '3', '2', '1'}
};

byte rowPins[ROWS] = {00, 04, 05, 16}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {15, 13, 14, 02}; //connect to the column pinouts of the keypad
Keypad KeyPad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// -------------------------------------------------------------------------------------

void setup() {
  Serial.begin(115200);

  //LED Set up
  pinMode(greenPin, OUTPUT);
  digitalWrite(greenPin, LOW);

  //Firebase internet connection configuration
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  digitalWrite(greenPin, HIGH);  // the LED will turn on if the Wi-Fi is connected .. 

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);


  Firebase.setString(firebaseData, "Bid Value: ", "None"); // show a message in the firebase showing there is no bid has been added .. 

}
// ..............................................................................................
void loop() {
  char key;
  String value;
  
  while (true)
  {
    delay(50);
    key = KeyPad.getKey();
    if (key == '*') break;

    value = value + key;
    Serial.print("Value: ");
    Serial.println(value);

    do
    {
      delay(50);
    }
    while (KeyPad.getKey() != NO_KEY); // wait until key is released
  }

  value = value + " SR";
  Firebase.setString(firebaseData, "Bid: ", value);
  //your value is stored in the "value" variable
}
