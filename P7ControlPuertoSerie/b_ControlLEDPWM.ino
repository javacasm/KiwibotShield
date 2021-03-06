/*
Codigo que permite controlar el valor pwm de un led desde puerto serie

 Hay que mirar el codigo ASCII
 Los caracteres se envian como codigo decimal del codigo ASCII
 Por ejemplo el 0 se envia como 48, el > como 62
 Jose Pujol

 */

const int ledPin = 9; // pin al que el LED esta conectado

int incomingByte; // variable para leer los bytes de entrada
int value = 0;  // variable para almacenar el valor numerico
int pwmValue = 0; // variable para enviar el codigo pwm al led

void setup() {
  // inicializamos la comunicacion serie
  Serial.begin(9600);
}

void loop() {
  // comprueba si hay datos entrantes en el puerto serie
  if (Serial.available() > 0) {
    // lectura del byte mas antiguo del buffer serial
    incomingByte = Serial.read();
    // si es un caracter ASCII entre 0 y 9
    if (incomingByte >= '0' && incomingByte <= '9') {
      //Acumula los datos numericos multiplicando por 10 el valor acumulado
      value = (value * 10) + (incomingByte - '0'); // Resta 48 que es el valor decimal del 0 ASCII
    }
    else if (incomingByte == '>') // uso > como finalizador
    {
      pwmValue = value;   // Guarda el valor en la variable pwmValue
      Serial.println(pwmValue);     // Lo imprime por monitor serie
      value = 0;  // Dejamos lista la variable para volver a escribir en ella
    }
  }
  analogWrite(ledPin, pwmValue);   // Escribimos el valor PWM en el LED
}
