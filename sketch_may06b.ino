
// Definimos los pines digitales que usaremos
int boton = 8;
int motor_derecha_ad = 3;   // Con este pin, dirigimos el motor derecho hacia adelante
int motor_izquierda_ad = 12; // Con este pin, dirigimos el motor izquierdo hacia adelante
int motor_derecha_at = 4;    // Con este pin, dirigimos el motor derecho hacia atras
int motor_izquierda_at = 2;  // Con este pin, dirigimos el motor izquierdo hacia atras
int pwm_iz = 10;             // pin de manejo de velocidad del motor izquierdo
int pwm_der = 9;             // Pin de manejo de la velocidad del motor derecho
int ledOn = 6;
int ledPlay = 7;

// Pines analogos
int sensor1 = 0;
int sensor2 = 1;
int sensor3 = 2;
int sensor4 = 3;



// Variables iniciadas en cero
float proporcional = 0;
float proporcional_pasado = 0;
int posicion = 0;
int ultima_posicion = 0;
float integral = 0;
float derivativo = 0;
float valor_pwm = 0;

// Constantes del PID
float kp=0.20; //2,
float kd=12;
float ki=0.001;


void setup() {
  
  delay(2000);   // Hacemos una espera de 2 segundos

  Serial.begin(9600);  // iniciamos comunicacion serial con 9600 bouds


  // Configuramos los pines como entrada o salida
  pinMode(boton,INPUT_PULLUP);
  pinMode(motor_derecha_ad,OUTPUT);
  pinMode(motor_izquierda_ad,OUTPUT);
  pinMode(motor_derecha_at,OUTPUT);
  pinMode(motor_izquierda_at,OUTPUT);
  pinMode(ledOn,OUTPUT);
  pinMode(ledPlay,OUTPUT);
  pinMode(pwm_iz,OUTPUT);
  pinMode(pwm_der,OUTPUT);

  int b = digitalRead(boton); // Leemos el valor en el pin boton (8)

// Ciclo de espera del pulso del boton de inicio
   while(b==1){

    b = digitalRead(boton);
    digitalWrite(ledOn,255);
    delay(300);
    digitalWrite(ledOn,0);
    delay(300);
   }
}





void loop() {
  
 

digitalWrite(ledPlay,HIGH); // Led que indica inicio de lectura de sensores 

 // Lectura de los sensores en las entradas analogas
int s1 = analogRead(sensor1);
int s2 = analogRead(sensor2);
int s3 = analogRead(sensor3);
int s4 = analogRead(sensor4);


int s11 = 0; // Variables usadas para la conversion
int s12 = 0;
int s13 = 0;
int s14 = 0;


// Calibracion de sensores para convertirlos a binario
if(s1>10){
  s11=1;
}
if(s2>10){
  s12=1;
}
if(s3>10){
  s13=1;
}
if(s4>10){
  s14=1;
}
    
    posicion = (1*s11)+(2*s12)+(4*s13)+(8*s14);  // Convertimos los numeros binarios obtenidos de los sensores en decimales

if(posicion <= 14){
  ultima_posicion = posicion;   // Almacenamos las posiciones leidas
}

//Serial.println(ultima_posicion);  // Mostramos en pantalla el valor de la posicion leida por los sensores

Serial.println(s4);
   // Calculamos los valores proporcional, integral y derivativo
   proporcional = (posicion - 9);
   integral = (integral + proporcional_pasado);
   derivativo = (proporcional - proporcional_pasado);

   // Valor obtenidos del PID
   valor_pwm = (kp*proporcional)+(ki*integral)+(kd*derivativo);

   //Serial.println(valor_pwm);  // Mostramos el valor del PID obtenido

   // Limitamos el valor de la integral
   if(integral>200){
    integral=200;
   }
   if(integral<-200){
    integral=-200;
   }

   // Almacenamos el ultimo valor de proporcional
   proporcional_pasado = proporcional;

  
// Condiciones de la lectura de los sensores
if(posicion == 15){ // Si esta en linea, avanza
    digitalWrite(motor_derecha_ad,HIGH);
    digitalWrite(motor_derecha_at,LOW);
    analogWrite(pwm_der,255);
    digitalWrite(motor_izquierda_ad,HIGH);
    digitalWrite(motor_izquierda_at,LOW);
    analogWrite(pwm_iz,255);
   }
if(posicion == 8){ 
    digitalWrite(motor_derecha_ad,HIGH);
    digitalWrite(motor_derecha_at,LOW);
    analogWrite(pwm_der,255);
    digitalWrite(motor_izquierda_ad,LOW);
    digitalWrite(motor_izquierda_at,HIGH);
    analogWrite(pwm_iz,120+valor_pwm);
   }


if((posicion > 11 && posicion < 13)||(posicion > 13 && posicion < 15) || posicion < 8){  // Si los sensores estan en otra posicion 
   
   if(valor_pwm < 0){  // Gira para la derecha
    digitalWrite(motor_derecha_ad,LOW);
    digitalWrite(motor_derecha_at,HIGH);
    analogWrite(pwm_der,120+valor_pwm);
    digitalWrite(motor_izquierda_ad,HIGH);
    digitalWrite(motor_izquierda_at,LOW);
    analogWrite(pwm_iz,255);
   }
   if(valor_pwm > 0){ // Gira para la izquierda
    digitalWrite(motor_derecha_ad,HIGH);
    digitalWrite(motor_derecha_at,LOW);
    analogWrite(pwm_der,255);
    digitalWrite(motor_izquierda_ad,LOW);
    digitalWrite(motor_izquierda_at,HIGH);
    analogWrite(pwm_iz,120-valor_pwm);
   }
      
    if(posicion == 0){  // si todos los sensores estan sobre la linea negra, el carro frena.
    digitalWrite(motor_derecha_ad,LOW);
    digitalWrite(motor_derecha_at,LOW);
    analogWrite(pwm_der,0);
    digitalWrite(motor_izquierda_ad,LOW);
    digitalWrite(motor_izquierda_at,LOW);
    analogWrite(pwm_iz,0);
    }
 }
/* if(posicion == 15){  // Si los sensores se salieron de la linea negra, se lee el ultimo valor de la posicion leida por estos
     
  if(ultima_posicion < 9){  // Gira para la derecha 
    digitalWrite(motor_derecha_ad,LOW);
    digitalWrite(motor_derecha_at,HIGH);
    analogWrite(pwm_der,120-valor_pwm);
    digitalWrite(motor_izquierda_ad,HIGH);
    digitalWrite(motor_izquierda_at,LOW);
    analogWrite(pwm_iz,255);
  }
  if(ultima_posicion > 9){ // Gira para le izquierda
    digitalWrite(motor_derecha_ad,HIGH);
    digitalWrite(motor_derecha_at,LOW);
    analogWrite(pwm_der,255);
    digitalWrite(motor_izquierda_ad,LOW);
    digitalWrite(motor_izquierda_at,HIGH);
    analogWrite(pwm_iz,120-valor_pwm);
  }
 }*/

}
