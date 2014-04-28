/*Estudio de la comunicacin UART usando los pines 0  RX y 1 TX
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
    Serial.println(incomingByte, DEC);
    if (incomingByte == 32) { digitalWrite(13, HIGH); }
    else { digitalWrite(13, LOW); }
  }
  
}
