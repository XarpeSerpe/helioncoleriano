/*Estudio de la comunicacin UART usando los pines 0  RX y 1 TX

TODO uso de char, ojo a los espacios, interpretar las entradas con if , limitar las potencias y los tiempos 3000 milisegundos.

TODO que pueda dar el estado de la batería (ojo a hacer cortos al crear el circuito) con Serial.write (pero así necesito crear un entorno de lecturar de UART desde la terminal de Raspberry

equivalencia ascii
0 es 48
1 es 49
...
9 es 57
a es 97
b es 98  backward    
f es 102 forward
espacio es 32
    
Formato de comandos
f250 100 adelante a 250 durante 100 milisegundos    
b120 5000 atras a 120 durante 5000 milisegundos
a45 mover motores a 45 grados
d120 200 gira a 120 dextrógiro durate 200 milisegundos
l255 500 gira levógito a 255 durante 500 milisegundos
*/

int incomingByte = 0;

void setup()
{
Serial.begin(2400);
pinMode(13, OUTPUT);
digitalWrite(13, LOW);

}

void loop()
{
  if (Serial.available() > 0)//capacidad de 128 bytes
  {
    incomingByte = Serial.read();
    Serial.print("He recibido ");
    Serial.println(incomingByte, DEC); // se puede trabajar en caracter si se usa Serial.println(char(incomingByte)); pero puede dar problemas con los espacios.
    if (incomingByte == 32) { digitalWrite(13, HIGH); }
    else { digitalWrite(13, LOW); }
  }
  
}
