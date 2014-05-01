/* Control de motores con funcion de parada suave.
   Programar cambio de potencia suave de old_PWM_A a new_PWM_B
*/
#include <Servo.h>


Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
const int bigote_a = 7;
const int bigote_b = 16; //asi el A2 trabaja como digital.
int DIR_A = 12;
int PWM_A = 3;
int BRAKE_A = 9;
int DIR_B = 13;
int PWM_B = 11;
int BRAKE_B = 8;

int pwm_max = 254; //-- Potencia maxima permitida a los motores 255 para 5V desde el ordenador no llegan a sustentar
int pwm_min = 200;  //-- Potencia minima de alimentacion

void setup()
{
  Serial.begin(2400); //posiblemente tenga que declarar los pines 0 y 1 para que funcione sin usb
  myservo.attach(6);  // attaches the servo on pin 9 to the servo object 
  pinMode(DIR_A, OUTPUT);
  pinMode(PWM_A, OUTPUT);
  pinMode(BRAKE_A, OUTPUT);
  pinMode(DIR_B, OUTPUT);
  pinMode(PWM_B, OUTPUT);
  pinMode(BRAKE_B, OUTPUT);
  //attachInterrupt(0, choque, LOW);

  digitalWrite(DIR_A, LOW); //-- Inicia hacia adelante
  digitalWrite(DIR_B, LOW); //-- Inicia hacia adelante
  digitalWrite(PWM_A, LOW); //-- Inicia parado
  digitalWrite(PWM_B, LOW); //-- Inicia parado
  digitalWrite(BRAKE_A, HIGH);//-- Comienzan frenados
  digitalWrite(BRAKE_B, HIGH); //-- Comienzan frenados
  myservo.write(90); //-- Inicia con helices tumbadas
}

void loop()//Ascenso inicial
{
 adiante(255);
 agarda(5000);
 parar();
 agarda(1000);
 derecha(254, HIGH);
 agarda(5000);
 parar();
 agarda(1000);
 izquierda(254, HIGH);
 agarda(5000);
 parar();
 agarda(1000);
 derecha(254, LOW);
 agarda(5000);
 parar();
 agarda(1000);
 izquierda(254, LOW);
 agarda(5000);
 parar();
 agarda(1000);
 derecha(254, LOW);
 agarda(5000);
 parar();
 agarda(1000);
 izquierda(254, HIGH);
 agarda(5000);
 parar();
 agarda(1000);
 derecha(254, HIGH);
 agarda(5000);
 parar();
 agarda(1000);
 izquierda(254, LOW);
 agarda(5000);
 parar();
 agarda(1000);

 
  
}


void agarda(int milisegundos)
{
  delay(milisegundos);
  parar();
}

void derecha(int potencia, int dir)
{
  digitalWrite(BRAKE_A, LOW);
  digitalWrite(DIR_A, dir);
  analogWrite(PWM_A, potencia);
}

void izquierda(int potencia, int dir)
{
  digitalWrite(BRAKE_B, LOW);
  digitalWrite(DIR_B, dir);
  analogWrite(PWM_B, potencia);
}

void adiante(int potencia) // Se llega a potencia en cuatro pasos, un segundo
{
  derecha(potencia, LOW);
  izquierda(potencia, LOW);
}
void parar() // Parada controlada 
{
  digitalWrite(BRAKE_A, HIGH);
  digitalWrite(BRAKE_B, HIGH);
}

void atras(int potencia)// Se llega a potencia en cuatro pasos, un segundo
{
  parar();
  digitalWrite(BRAKE_A, LOW);
  digitalWrite(DIR_A, HIGH);
  digitalWrite(BRAKE_B, LOW);
  digitalWrite(DIR_B, HIGH);
  analogWrite(PWM_A, potencia);
  analogWrite(PWM_B, potencia);
}
    
void choque()
  { /*Identificar cual es la colisin para dar tres comportamientos
    Derecha, apaga motor izquierdo y acelera el derecho.
    Izquierda, apaga el motor derecho y acelera el izquierdo.
    Ambos, invierte la marcha, se para y reanaliza el terreno.
    */
    int _bigote_a;
    int _bigote_b;
    
    _bigote_a = digitalRead(bigote_a);
    _bigote_b = digitalRead(bigote_b);
    if( _bigote_a == HIGH && _bigote_b == LOW)
      {
      atras(100);
      }
     else if( _bigote_b == HIGH && _bigote_a == LOW)
     {
       atras(100);
     }
     else // Este caso nunca se da
     
     {
       atras(100);
     }
  }
