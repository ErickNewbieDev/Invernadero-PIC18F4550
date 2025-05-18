# Invernadero-PIC18F4550
Este es un programa desarrollado en MikroC para una PIC18F4550/PIC18F4455 el cual tiene el fin de emular un invernadero y con base a la lectura de un sensor de temperatura (O en su defecto un potenciómetro que simule al sensor) determina si el invernadero se encuentra en una temperatura promedio, por debajo del promedio o en caso critico superior al promedio. Toda esta información es mostrada a través un LCD de 16 pines el cual muestra la temperatura actual y el estado de la misma (Debajo, sobre o dentro del promedio).
El sistema cuenta con un par de botones los cuales funcionan uno para hacerle saber al programa que en modo lectura y otro que le hará saber al programa que debe leer el input del dip switch que le permiten cambiar entre dos modos personalizables, determinando rangos de temperaturas para cada uno de estos. Igualmente cuenta con un tercer modo de reposo el cual le permite al sistema descansar y evitar la lectura de la temperatura.
Cuando el sistema detecta una temperatura sobre el promedio, además de avisarlo en el LCD también es acompañado por un LED el cual se ilumina y solo se apagará cuando se regrese a la temperatura optima.

El programa fue desarrollado en MikroC PRO For PIC v.7.6.0. Se usaron las librerias:
•	Button
•	Conversions
•	Lcd Ya incluidas con la instalacion de MikroC.
Para el armado del circuito unicamente ser requieren los siguientes materiales:
•	1 PIC18F4550 / PIC18F4455
•	1 LCD 16 pines
•	2 Push button
•	1 LED
• 1 potenciometro 10 kOhms / 1 Sensor de temperatura LM35
•	1 Dip Switch (De al menos 4 interruptores)
