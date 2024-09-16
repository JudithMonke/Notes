
#include <Servo.h> // include Servo library 

/****** Definisco le variabili globali del codice ******/

// 180 horizontal MAX
Servo horizontal; // motore servo orizzontale
int servoh = 45;   // posizione iniziale

int servohLimitHigh = 180; //limite massimo angolo orizzontale
int servohLimitLow = 0; //limite minimo angolo orizzontale

// 180 vertical MAX
Servo vertical;   // motore servo verticale 
int servov = 0;    //posizione iniziale

int servovLimitHigh = 180;  //limite massimo angolo verticale
int servovLimitLow = 0;//limite minimo angolo verticale


// LDR pin connections
//  name  = analogpin;
int ldrlt = 1; //LDR top left  -> pin analogico associato
int ldrrt = 0; //LDR top rigt  -> pin analogico associato
int ldrld = 3; //LDR down left -> pin analogico associato
int ldrrd = 2; //ldr down rigt -> pin analogico associato

/********** SETUP  ***********/
void setup()  
{
  //Attivo la comunicazione seriale
  Serial.begin(9600);   //set data rate
  
// servo connections
// name.attacht(pin);
  horizontal.attach(9); //motore orizzontale attaccato al pin 9
  vertical.attach(10);  //motore verticale attaccato al pin 10
  horizontal.write(45);  //posizione iniziale orizzontale    
  vertical.write(0);  //posizione iniziale verticale
  delay(3000);  //ritardo 3 secondi dalla partenza
}

/********* LOOP  ***********/
void loop()   
{
  //lettura dei valori dei sensori
  int lt = analogRead(ldrlt); // legge il valore dal sensore top left
  int rt = analogRead(ldrrt); // legge il valore dal sensore top right
  int ld = analogRead(ldrld); // legge il valore dal sensore down left
  int rd = analogRead(ldrrd); // legge il valore dal sensore down rigt

  //Converto i valori analogici  in valori interi
   //int dtime = analogRead(4)/20; // read potentiometers  
   //int tol = analogRead(5)/4;
  int dtime = 10;   //difference time
  int tol = 50;  //tolleranza 

  //media dei valori per trovare il punto più luminoso
  int avt = (lt + rt) / 2;  // average value top
  int avd = (ld + rd) / 2;  // average value down
  int avl = (lt + ld) / 2;  // average value left
  int avr = (rt + rd) / 2;  // average value right

  int dvert = avt - avd; // check the diffirence of up and down
  int dhoriz = avl - avr;// check the diffirence of left and right
  
  //Stampe che mostrano sul monitor seriale dell'ide di Arduino informazioni (per il debug)
  Serial.print(avt);
  Serial.print(" ");
  Serial.print(avd);
  Serial.print(" ");
  Serial.print(avl);
  Serial.print(" ");
  Serial.print(avr);
  Serial.print("   ");
  Serial.print(dtime);
  Serial.print("   ");
  Serial.print(tol);
  Serial.println(" ");
  
  //MOVIMENTO VERTICALE DEL MOTORE SERVO
    
  if (-1*tol > dvert || dvert > tol) // check if the diffirence is in the tolerance else change vertical angle 
  {
  if (avt > avd)   //se la media top>media down
  {
    servov = --servov;  //decremento posizione motore verticale 
     if (servov > servovLimitHigh)   //se la sua posizione è > del limite massimo 
     { 
      servov = servovLimitHigh;   //imposto la posizione al limite massimo
     }
  }
  else if (avt < avd)    //altrimenti se la media top<media down
  {
    servov= ++servov;   //incremento posizione motore verticale
    if (servov < servovLimitLow)  //se la sua posizione è < del limite minimo
  {
    servov = servovLimitLow;  //imposto la posizione al limite minimo
  }
  }
  vertical.write(servov);  //imposto la posizione del motore 
  }
  
  if (-1*tol > dhoriz || dhoriz > tol) // check if the diffirence is in the tolerance else change horizontal angle
  {
  if (avl > avr)   //se la media left>media right
  {
    servoh = --servoh;   //decremento posizione motore orizzontale
    if (servoh < servohLimitLow)  //se la sua posizione è < del limite minimo
    {
    servoh = servohLimitLow;  //imposto la posizione al limite minimo
    }
  }
  else if (avl < avr)   //altrimenti se la media left<media right
  {
    servoh = ++servoh;  //incremento posizione motore orizzontale
     if (servoh > servohLimitHigh)  //se la sua posizione è > del limite massimo 
     {
     servoh = servohLimitHigh;  //imposto la posizione al limite massimo
     }
  }
  else if (avl = avr)  //altrimenti se la media left =media right  (luce è al centro)
  {
    // nothing 
    delay(5000);    //imposto un ritardo di 5 secondi
  }
  horizontal.write(servoh);   //imposto la posizione del motore 

  
  }
   delay(dtime);   //imposto un ritardo prima di ricominciare il ciclo in modo che la successiva lettura avvenga dopo un certo periodo di tempo.
                   //Questo ritardo definisce il tempo di campionamento
 
}
