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

#include <Servo.h> 
#include <string.h>

int incomingByte = 0;
String command = "000000000";

int i = 0;
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  Serial.begin(2400); //posiblemente tenga que declarar los pines 0 y 1 para que funcione sin usb
  myservo.attach(6);  // attaches the servo on pin 9 to the servo object 
} 
 
 
void loop() 
{ 
  if (Serial.available() > 0)
  {
    incomingByte = Serial.read();
    command[i] = char(incomingByte);
    i = i + 1;
  }
 
  if (command[0] == 'f')
  {
    Serial.print("nueva orden ");
    Serial.println(command);
    borra();
  }

  else if (command[0] == 'b')
  {
    Serial.print("nueva orden ");
    Serial.println(command);
    borra();
    myservo.write(90);
    delay(1000);
  }
  
  else if (command[0] == 'a')
  {
    Serial.print("Nueva orden ");
    Serial.println(command);
    myservo.write(0);
    delay(1000);
  }
  
  else if(command == "000000000")
  {
   Serial.println("Stand by"); 
  }
  
  else { borra();}
  
  delay(2000);
    
} 


void borra()
{
  command = "000000000";
  i = 0;
}

/* codigo viejo de debug
if (incomingByte == "a")
    {
      myservo.write(0);             
      delay(1000);                        
     
   }
    else
    {
      myservo.write(90);              
      delay(1000);
    }
*/
