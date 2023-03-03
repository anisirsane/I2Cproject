#include <Arduino.h>
#include <WiFi101.h> // Inclure la bibliothèque WiFi101
#include <SPI.h>
#include <Wire.h>
#include<string>
std::string flame,tilt,sound,push, value;
char ssid[] = "Ste-adele 2"; // Nom du réseau WiFi
char pass[] = "abcd1234"; // Mot de passe du réseau WiFi
int status = WL_IDLE_STATUS; // Statut du module WiFi
WiFiServer server(80); // Créer un serveur sur le port 80
std::string val;
//fonction pour recevoir des dinnes du maitre
void receiveEvent(int numBytes){
  while (Wire.available()) {
    //int qiima = Wire.read();
    //value = std::to_string(qiima);
    char c = Wire.read();
    value += c;
  }
}


void setup() { 
Serial.begin(9600); // Démarrer la communication série à 9600 bauds
// Initialise le bus I2C comme esclave sur l'adresse 9
Wire.begin(9);
// Initialiser la fonction à utiliser quand un message est reçu
Wire.onReceive(receiveEvent);
// Connexion au réseau WiFi
while (status != WL_CONNECTED) { // Tant que la connexion n'est pas établie
Serial.print("Tentative de connexion au réseau WiFi : ");
Serial.println(ssid);
status = WiFi.begin(ssid, pass); // Tenter de se connecter au réseau avec le nom d'utilisateur et le mot de passe fournis
delay(10000); // Attendre 10 secondes avant de réessayer
}
// Afficher l'adresse IP du module WiFi
IPAddress ip = WiFi.localIP(); // Récupérer l'adresse IP locale
Serial.print("Adresse IP : ");
Serial.println(ip);
// Démarrer le serveur
server.begin(); // Démarrer le serveur sur le port 80
Serial.println("Serveur démarré");
}
void loop() {

// Obtenir les données des capteurs
//on fait la lecture de la premiere caractere de la chaine du caractere
//qu'on a recu, qu'on a ajoute qome un identifiant pour distinguer les donnees qu'on a eu

    if (value.length() > 0 && value[0] == 'f') {
    // Process flame data
    flame = value.substr(1); // remove first character ('f')
    value = ""; // clear the received data buffer
  } else if (value.length() > 0 && value[0] == 'p') {
    // Process push data
    push = value.substr(1); // remove first character ('p')
    value = ""; // clear the received data buffer
  } else if (value.length() > 0 && value[0] == 't') {
    // Process tilt data
    tilt = value.substr(1); // remove first character ('t')
    value = ""; // clear the received data buffer
  } else if (value.length() > 0 && value[0] == 's') {
    // Process sound data
    sound = value.substr(1); // remove first character ('s')
    value = ""; // clear the received data buffer
  }
//Serial.println(value.c_str());

// Vérifier les nouvelles connexions de clients
WiFiClient client = server.available();
if (client) {
// Attendre les données du client
while (client.connected() && !client.available()) {
delay(1);
}
// Lire la requête
String request = client.readStringUntil('\r');
client.flush();
// Envoyer la réponse
client.println("HTTP/1.1 200 OK");
client.println("Content-Type: text/html");
client.println("Connection: close");
client.println();




////affichage sur la page web
String response = "<html><body>";
response += "<meta http-equiv='refresh' content='5'>";
response += "<h1>Donnees des capteurs</h1>";
response += "<p>Capteur du flame  : " + arduino::String(flame.c_str()) + "</p>";
response += "<p>boutton poussoire: " + arduino::String(push.c_str()) + "</p>";
response += "<p>tilt sensor : " + arduino::String(tilt.c_str()) + "</p>";
response += "<p>Capteur du son : " + arduino::String(sound.c_str()) + "</p>";
response += "</body></html>";
// Envoyer la réponse au client
client.print(response);
// Fermer la connexion
delay(1);
client.stop();
}
}