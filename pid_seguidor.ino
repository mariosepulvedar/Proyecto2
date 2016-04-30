

int boton = 8;
int motor_derecha_ad = 11;
int motor_izquierda_ad = 12;
int motor_derecha_at = 4;
int motor_izquierda_at = 2;
int pwm_iz = 10;
int pwm_der = 9;
int sensor1 = 0;
int sensor2 = 1;
int sensor3 = 2;
int sensor4 = 3;
int ledOn = 6;
float velocidad = 0;
float velocidad_max = 150;
float proporcional = 0;
float proporcional_pasado = 0;
int posicion = 0;

int ultima_posicion = 0;
float integral = 0;
float derivativo = 0;
float valor_pwm = 0; 
float kp=1,kd=0.1,ki=0.01;


void setup() {
  // put your setup code here, to run once:

  delay(2000);

  Serial.begin(9600);

  pinMode(boton,INPUT_PULLUP);
  pinMode(motor_derecha_ad,OUTPUT);
  pinMode(motor_izquierda_ad,OUTPUT);
  pinMode(motor_derecha_at,OUTPUT);
  pinMode(motor_izquierda_at,OUTPUT);
  pinMode(pwm_iz,OUTPUT);
  pinMode(pwm_der,OUTPUT);

int b = digitalRead(boton);
   while(b==1){

    b = digitalRead(boton);
    digitalWrite(ledOn,255);
    delay(300);
    digitalWrite(ledOn,0);
    delay(300);
   }
  

}

void loop() {
 
  
  // put your main code here, to run repeatedly:
 
  
 ultima_posicion =0;
 
 int s1 = analogRead(sensor1);
  int s2 = analogRead(sensor2);
  int s3 = analogRead(sensor3);
  int s4 = analogRead(sensor4);

int s11 = 0;
int s12 = 0;
int s13 = 0;
int s14 = 0;



if(s1>270){
  s11=1;
}
if(s2>360){
  s12=1;
}
if(s3>370){
  s13=1;
}
if(s4>250){
  s14=1;
}
    
  posicion = (1*s11)+(2*s12)+(4*s13)+(8*s14);
//Serial.println(s1);
  //Serial.println(s2);
  //Serial.println(s3);
 //Serial.println(s4);
Serial.println("___________________________________________");
 //Serial.println(posicion);
 
Serial.println("___________________________________________-");

if(posicion <= 14){
  ultima_posicion = posicion;
}
//Serial.println(ultima_posicion);
   proporcional = (posicion - 9);
   integral = (integral + proporcional_pasado);
   derivativo = (proporcional - proporcional_pasado);
   valor_pwm = (kp*proporcional)+(ki*integral)+(kd*derivativo);

   //Serial.println(valor_pwm);

   if(integral>200){
    integral=200;
   }
   if(integral<-200){
    integral=-200;
   }

   proporcional_pasado = proporcional;


   if(valor_pwm>velocidad){
    valor_pwm = velocidad;
   }
   if(valor_pwm<(-velocidad)){
    valor_pwm = (-velocidad);
   }

   if(posicion == 9){
    digitalWrite(motor_derecha_ad,HIGH);
    digitalWrite(motor_derecha_at,LOW);
     analogWrite(pwm_der,100);
     digitalWrite(motor_izquierda_ad,HIGH);
     digitalWrite(motor_izquierda_at,LOW);
     analogWrite(pwm_iz,100);
   }
   
 while(posicion == 15){

   if(ultima_posicion<9){
    digitalWrite(motor_derecha_ad,LOW);
    digitalWrite(motor_derecha_at,HIGH);
    analogWrite(pwm_der,50);
    digitalWrite(motor_izquierda_ad,HIGH);
    digitalWrite(motor_izquierda_at,LOW);
    analogWrite(pwm_iz,200);
    }
    if(ultima_posicion> 9){
    digitalWrite(motor_derecha_ad,HIGH);
    digitalWrite(motor_derecha_at,LOW);
    analogWrite(pwm_der,200);
    digitalWrite(motor_izquierda_ad,LOW);
    digitalWrite(motor_izquierda_at,HIGH);
    analogWrite(pwm_iz, 55);
    }
     s1 = analogRead(sensor1);
   s2 = analogRead(sensor2);
  s3 = analogRead(sensor3);
   s4 = analogRead(sensor4);

 s11 = 0;
 s12 = 0;
 s13 = 0;
 s14 = 0;



if(s1>270){
  s11=1;
}
if(s2>360){
  s12=1;
}
if(s3>370){
  s13=1;
}
if(s4>250){
  s14=1;
}
    
  posicion = (1*s11)+(2*s12)+(4*s13)+(8*s14);
}
  s1 = analogRead(sensor1);
   s2 = analogRead(sensor2);
  s3 = analogRead(sensor3);
   s4 = analogRead(sensor4);

 s11 = 0;
 s12 = 0;
 s13 = 0;
 s14 = 0;



if(s1>270){
  s11=1;
}
if(s2>360){
  s12=1;
}
if(s3>370){
  s13=1;
}
if(s4>250){
  s14=1;
}
    
  posicion = (1*s11)+(2*s12)+(4*s13)+(8*s14);

 if((posicion > 9)&&(posicion < 15)){
   digitalWrite(motor_derecha_ad,HIGH);
   digitalWrite(motor_derecha_at,LOW); 
  analogWrite(pwm_der,170);
  digitalWrite(motor_izquierda_ad,LOW);
  digitalWrite(motor_izquierda_at,HIGH);
  analogWrite(pwm_iz, 50 + valor_pwm);
 
 }
   s1 = analogRead(sensor1);
   s2 = analogRead(sensor2);
  s3 = analogRead(sensor3);
   s4 = analogRead(sensor4);

 s11 = 0;
 s12 = 0;
 s13 = 0;
 s14 = 0;



if(s1>270){
  s11=1;
}
if(s2>360){
  s12=1;
}
if(s3>370){
  s13=1;
}
if(s4>250){
  s14=1;
}
    
  posicion = (1*s11)+(2*s12)+(4*s13)+(8*s14);

  
 if((posicion < 9)&&(posicion >=1) ){
   digitalWrite(motor_derecha_ad,LOW);
   digitalWrite(motor_derecha_at,HIGH);
  analogWrite(pwm_der,50 - valor_pwm);
  digitalWrite(motor_izquierda_ad,HIGH);
  digitalWrite(motor_izquierda_at,LOW);
  analogWrite(pwm_iz,170);
 }



   s1 = analogRead(sensor1);
   s2 = analogRead(sensor2);
  s3 = analogRead(sensor3);
   s4 = analogRead(sensor4);

 s11 = 0;
 s12 = 0;
 s13 = 0;
 s14 = 0;



if(s1>270){
  s11=1;
}
if(s2>360){
  s12=1;
}
if(s3>370){
  s13=1;
}
if(s4>250){
  s14=1;
}
    
  posicion = (1*s11)+(2*s12)+(4*s13)+(8*s14);

 
  if(posicion==0){
  digitalWrite(motor_derecha_ad,LOW);
  digitalWrite(motor_derecha_at,LOW);
 analogWrite(pwm_der,-100);
  digitalWrite(motor_izquierda_ad,LOW);
  digitalWrite(motor_izquierda_at,LOW);
  analogWrite(pwm_iz,-100);
 }


}
