/*
On utilise pour ce programme 5 LED connectées sur les pins 2,4,6,8 et 10. Ces LED simuleront différents capteurs.

Un bouton, sur le pin 12, pressé manuellement pour simuler l'activation d'un capteur de mouvement.

On utilisera aussi le moniteur de l'arduino pour simuler l'envoie d'un message au Raspberry.
*/

int pinLed[5]={2,4,6,8,10}; // Tableau listant les pins
int pinBouton;

//Tableau à double entrée listant l’état (booléen 1 allumé, 0 éteint) des LED à chaque séquence
boolean affichage[25][5]={
  0,0,0,0,0,
  0,0,0,0,1,
  0,0,0,1,0,
  0,0,1,0,0,
  0,1,0,0,0,
  1,0,0,0,0,
  0,0,0,0,0,
  1,0,0,0,0,
  0,1,0,0,0,
  0,0,1,0,0,
  0,0,0,1,0,
  0,0,0,0,1,
  0,0,0,0,0,
  1,1,1,1,1,
  1,1,1,1,0,
  1,1,1,0,0,
  1,1,0,0,0,
  1,0,0,0,0,
  0,0,0,0,0,
  1,1,1,1,1,
  0,1,1,1,1,
  0,0,1,1,1,
  0,0,0,1,1,
  0,0,0,0,1,
  0,0,0,0,0};

void setup() {
  for (int i=0;i<5;i++)
  {
    pinMode(pinLed[i],OUTPUT);
    digitalWrite(pinLed[i],LOW);
  }
  pinBouton=12;
  pinMode(pinBouton,INPUT_PULLUP);//INPUT_PULLUP, la résistance interne de l'arduino

  //Affichage dans la console pour simuler l'envoie d'un e-mail
  Serial.begin(9600);
}

void loop() {
  //lecture de l'etat du bonton
  boolean etatBouton = digitalRead(pinBouton);
  //test si le bouton est appuyé
  if(etatBouton == HIGH)
  {
    
    //éteindre toute les led
    for(int i=0;i<5;i++)
    {
      digitalWrite(pinLed[i],LOW);
    }
    
  }
  
  // Sinon le bouton est appuyé
  else if ( etatBouton == LOW)
  {
    //message envoyé au Raspberry
    Serial.println("Capteur activé");
    //
    for (int i=0;i<25;i++) // boucle de séquence d'affichage
    {
      for (int p=0;p<5;p++) // boucle pour chaque pin
      {
        boolean etat=affichage[i][p]; // on va chercher l'état pour le pin
        digitalWrite(pinLed[p],etat); // on met le pin concerné à l'état
      }
      //tous les pins sont dans l'état de la séquence en cours
      delay(300); //petite pause d'affichage
      // on passe à la séquence suivante
    }
  }
}
