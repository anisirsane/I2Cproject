#define flameSensor A1
#define pushButton 6
#define soundSensor A2
#define tiltSensor 7
#include <Arduino.h>
#include <Wire.h>
#include <string>

 #include <SPI.h>

void setup() {
  //initialisation de nos broches
  pinMode(pushButton, INPUT);
  pinMode(tiltSensor, INPUT); 
  Wire.begin();
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);
}

void loop() {
  // flame sensor:
  //lecture des valeurs de flame sensor puis ajout d'un caractere au debut qu'on va utiliser comme un identifiant lors l'envoie 
  //au esclave
  //donc on ajoute un f pour flame, an p pour pushbutton, un t pout tilt et un s pour sound 
  //donc on aura nos resultats comme si de suit: t.... ou p.... ou s.... ou f....
  int reading = analogRead(flameSensor);
  std::string flame = "f"+std::to_string(reading);
 Wire.beginTransmission(9); // transmettre a l'adresse #9
 Wire.write(flame.c_str()); // envoyer la variable valeur sous forme du string
 Wire.endTransmission();
 //Serial.println(flame.c_str());
  
  delay(1000);
  //pushbutton
  
  int val = digitalRead(pushButton); 
  std::string push = "p"+std::to_string(val);
  Wire.beginTransmission(9); // transmettre a l'adresse #9
  Wire.write(push.c_str()); // envoyer la variable valeur
  Wire.endTransmission(); 
  Serial.println(push.c_str());
  delay(1000);

  //vibration sensor

  int val3=digitalRead(tiltSensor);
  std::string tilt = "t"+std::to_string(val3);
  Wire.beginTransmission(9); // transmettre a l'adresse #9
  Wire.write(tilt.c_str()); // envoyer la variable valeur
  Wire.endTransmission();
    Serial.println(tilt.c_str());

  delay(1000);

  //sound sensor
  int val2=analogRead(soundSensor);   //connect mic sensor to Analog 0
  std::string sound = "s"+std::to_string(val2);
  Wire.beginTransmission(9); // transmettre a l'adresse #9
  Wire.write(sound.c_str()); // envoyer la variable valeur
  Wire.endTransmission();
   Serial.println(sound.c_str());
  delay(1000);
  //j'ai ajoute des delay pour chaque lecture puis envoie parceque j'ai eu un probleme 
  //avec l'envoie de plusieurs donnees a la fois au esclave.
  //si c'est possible d'envoyer plusieurs donnees a la fois, svp informez mois sur la facon.


}
