
// Variables utilizadas en el controlador PID.
unsigned long lastTime;
double Input, Output, Setpoint;
double errSum, lastErr;
double kp, ki, kd;
int SampleTime = 1000; // Seteamos el tiempo de muestreo en 1 segundo.

void Compute()
{
unsigned long now = millis();
int timeChange = (now - lastTime);
// Determina si hay que ejecutar el PID o retornar de la función.
if(timeChange>=SampleTime)
{
// Calcula todas las variables de error.
double error = Setpoint - Input;
errSum += error;
double dErr = (error - lastErr);
// Calculamos la función de salida del PID.
Output = kp * error + ki * errSum + kd * dErr;
// Guardamos el valor de algunas variables para el próximo ciclo de cálculo.
lastErr = error;
lastTime = now;
}
}

/* Establecemos los valores de las constantes para la sintonización.
Debido a que ahora sabemos que el tiempo entre muestras es constante,
no hace falta multiplicar una y otra vez por el cambio de tiempo; podemos
ajustar las constantes Ki y Kd, obteniendose un resultado matemático equivalente
pero más eficiente que en la primera versión de la función. */
void SetTunings(double Kp, double Ki, double Kd)
{
double SampleTimeInSec = ((double)SampleTime)/1000;
kp = Kp;
ki = Ki * SampleTimeInSec;
kd = Kd / SampleTimeInSec;
}
void SetSampleTime(int NewSampleTime)
{
if (NewSampleTime > 0)
{
/* si el usuario decide cambiar el tiempo de muestreo durante el funcionamiento, Ki y Kd tendrán
que ajustarse para reflejar este cambio. */
double ratio = (double)NewSampleTime / (double)SampleTime;
ki *= ratio;
kd /= ratio;
SampleTime = (unsigned long)NewSampleTime; }}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
