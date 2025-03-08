# Receiver

Cette combinaison d'une Arduino UNO R3 pour toute la partie logique et d'une ESP8266 afin de communiquer avec le reseau à pour but d'ecouter les topics "Humidity" et "Temperature" sur le serveur et d'afficher les valeurs sur un ecran LCD1602.

## Mise en place

Pour mettre en place le code dans "Uno.ino" doit se mettre dans l'Arduino UNO R3 et le code dans ESP8266.ino doit se mettre dans l'ESP8266. 
Attention l'Uno a besoin de la librairie LiquidCrystal et l'ESP de la libraire PubSubClient et ESP8266Wifi.