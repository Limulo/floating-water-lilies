

// TribeBots 2.0
// last update: 06.10.2015 Moreno Pet.
// http://dev.hacklabetrni.org

/*
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */
#include <IRremote.h>



/*
ArduinoThreads is a library for managing the periodic execution of multiple tasks.
https://github.com/ivanseidel/ArduinoThread
*/
#include <Thread.h>


 
Thread myThread = Thread();
Thread myThread2 = Thread();
Thread myThread3 = Thread();
Thread myThread4 = Thread();
Thread myThread5 = Thread();

int RECV_PIN = 11;

IRrecv irrecv(RECV_PIN);
IRsend irsend;

boolean right;
boolean left;
boolean stopped;
boolean temp = false;

byte ID_tribu = 0xA70; // ID Trasmesso nel modo funzionamento TRIBU'


boolean play_1;
boolean play_2;
boolean play_3;
boolean play_4;
boolean play_5;

//-----------------------Variabili Game of Life ----------------------------
int nr_vicini;
int stato = 0; // 0 = morto -  1 = vivo
int elenco_tb[20]; // Vettore contenente elenco TribeBots vicini
boolean game_of_life = false;
long randomID; // Numero casuale identificatore
byte id_gol = 0xA82; // ID Trasmesso nella modalità funzionamento Game Of Life
int rnd_seed = 82; // Numero necessario per la funzione RandomSeed
//-----------------------------------------------------------------

boolean ch_free; // Canale libero o occupato

unsigned long previousMillis = 0;
unsigned long previousMillis_2 = 0;
unsigned long previousMillisTimer = 0;
const long interval = 8000; // Ogni 8 sec TX  
const long interval_2 = 10000; // Tempo durata stato agitato
const long interval_timer = 0;

// RGB Led Control
const int yellowLEDPin = 10;    // LED connected to digital pin 9
const int redLEDPin = 9;     // LED connected to digital pin 8
const int blueLEDPin = 8; 

decode_results results;





void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  
  pinMode(6, OUTPUT); // Motor 2
  pinMode(5, OUTPUT); // Motor 1
  pinMode(13, OUTPUT); //Led (opzionale)
  
  // pin RGB Led
  pinMode(yellowLEDPin,OUTPUT);
  pinMode(redLEDPin,OUTPUT);
  pinMode(blueLEDPin,OUTPUT);

 ch_free = true; // Canale libero/occupato per trasmettere
 
 // Thread utilizzati per eseguire in parallelo più istruzioni
 myThread.onRun(p3);
 myThread.setInterval(2000);// Esegue la funzione ogni 2 secondi
 
 myThread2.onRun(p4);
 myThread2.setInterval(4000);// Esegue la funzione ogni 4 secondi
 
 
 /* ********************************* Game of Life *****************************************
  Viene generato un numero casuale per trasmettere ogni tot secondi il proprio ID
  questo per non far verificare collisioni,
  altrimenti quando inizia il gioco tutti trasmetterebbero contemporaneamente.
  La variabile "rnd_seed" ha il valore dato in sede di dichiarazione e corrisponde al numero INTEGER
  identificativo del TribeBot
  Questa funzione viene utilizzata per inizializzare il generatore di numeri pseudo-casuali
  Ogni TribeBot ha un proprio "rnd_seed"
 */
 randomSeed(rnd_seed); 
 
 // Trasmette identificativo Game of Life --> ID_GOL
 myThread4.onRun(gol);
 // Ogni nr. millisec casuale da 500 a 1500 trasmette ID
 // questo in modo tale che ogni singolo TribeBot trasmette in momenti differenti, evitando collisioni nelle trasmissioni
 myThread4.setInterval(random(500,1500));
 
 // Ogni 2 sec conta i vicini
 myThread5.onRun(conta_vicini);
 myThread5.setInterval(2000);
 
}

void loop() {

  /* Prove motori
    analogWrite(6, 100);
    analogWrite(5, 0);
  */
  
 if (left) {turn_left();}
 if (right) {turn_right();}
 if (stopped) { stop_motor();}
 if (play_1) { p1();}
 if (play_2) { p2();}
 if (play_3 && myThread.shouldRun()){ myThread.run();}
 if (play_4 && myThread2.shouldRun()) {myThread2.run();}
 if (play_5) { p5();} 
 
 
 
 // Ogni nr. millisec casuale da 500 a 1500 trasmette ID
 if (game_of_life && myThread4.shouldRun()) {myThread4.run(); }

  // Continuamente controlla se ci sono messaggi con ID di qualche TribeBot vicino
 if (game_of_life) {leggi_msg_gol(); }
 
 // Ogni 2 sec conta i vicini
 if (game_of_life && myThread5.shouldRun()) {myThread5.run(); }
 
 

 
 unsigned long currentMillis = millis();
 
  // Ogni 8 sec. trasmette il proprio ID nel modo funzionamento TRIBU'
  if( (currentMillis - previousMillis >= interval) && ch_free == false &&  game_of_life == false) {
        previousMillis = currentMillis; 
        ch_free = true;
        // Trasmetti solo se il canale è libero
       if (ch_free) { trasmetti_id(ID_tribu);}   
  }
  

  if (play_2) {stato_agitato(currentMillis);}
  

   ascolto_canale();

   
   
}

/* Trasmette il proprio ID per funzionamento modalità TRIBU'
 @param whoiam Valore esadecimale ID del TribeBot

*/
void trasmetti_id(byte whoiam) {
  
       for (int i = 0; i < 3; i++) {
          irsend.sendSony(whoiam, 12); // Codifica Sony TV power code
          delay(40);
       }
       irrecv.enableIRIn(); // Riabilita la ricezione
       
       ch_free = false;
       
       digitalWrite(redLEDPin, HIGH);
       digitalWrite(yellowLEDPin, LOW);
       digitalWrite(blueLEDPin, HIGH);

       delay(260);

}

/* Continuamente si è in attesa di ricevere messaggi dagli altri TribeBot
   Alla ricezione di dati inviati tramite infrarosso la funzione "irrecv.decode(&results)" diventa TRUE
*/

void ascolto_canale() {

    // Se il canale è libero -> LED Verde altrimenti ROSSO
  if (ch_free) {
      digitalWrite(redLEDPin, LOW);
      digitalWrite(yellowLEDPin, HIGH);
      digitalWrite(blueLEDPin, HIGH);
  } else {
      digitalWrite(redLEDPin, LOW);
      digitalWrite(yellowLEDPin, HIGH);
      digitalWrite(blueLEDPin, HIGH);
  }
  
   // Ricezione dati IR
  if (irrecv.decode(&results)) {
    
      ch_free = false;
    
      Serial.println(results.value, HEX);
      
      // Led diventa rosso quando si ricevono dati
      digitalWrite(redLEDPin, HIGH);
      digitalWrite(yellowLEDPin, LOW);
      digitalWrite(blueLEDPin, LOW);   

    // Controllo il valore esadecimale in ricezione
    switch(results.value) {
    
        //Alcuni codici sono inviati da telecomando SONY
        case (0x39C): // Vai a destra  FF BUTTON
          left = false;
          right = true;
          stopped = false;
          play_1 = false;
          play_2 = false;
          play_4 = false;
          play_3 = false;
          break;
        case (0xD9C): // Vai a sinistra REW BUTTON
          left = true;
          right = false;
          stopped = false;
          play_1 = false;
          break;
        case (0x19C): // stop  STOP BUTTON
          left = false;
          right = false;
          stopped = true;
          play_1 = false;
          play_2 = false;
          play_4 = false;
          play_3 = false;
          game_of_life = false;
          break;
        case (0x59C): // movimento tranquillo PLAY BUTTON
          play_4 = false;
          play_3 = false;
          play_1 = true;
          stopped = false;
          left = false;
          right = false;
          break;
        case (0x4C9D): // movimento agitato RED BUTTON
          play_4 = false;
          play_3 = false;
          play_2 = true;
          play_1 = false;
          stopped = false;
          left = false;
          right = false;
          break;
        case (0x60): // movimento agitato Ricevuto da un TribeBot "diverso - di un altra Tribù ;-) "
          if (stopped) {break;}
          play_2 = true;
          play_1 = false;
          stopped = false;
          left = false;
          right = false;
          digitalWrite(redLEDPin, HIGH);
          digitalWrite(yellowLEDPin, HIGH);
          digitalWrite(blueLEDPin, HIGH);
          break;
       case (0x549D): // play 3 (tasto photo telecomando SONY)
          play_4 = false;
          play_3 = true;
          play_2 = false;
          play_1 = false;
          stopped = false;
          left = false;
          right = false;
          break;
        case (0x5BC): // play 4 (tasto display telecomando SONY)
          play_4 = true;
          play_3 = false;
          play_2 = false;
          play_1 = false;
          stopped = false;
          left = false;
          right = false;
          break;
        case (0x199D): // Game of Life (tasto DATA CODE telecomando SONY)
          play_4 = false;
          play_3 = false;
          play_2 = false;
          play_1 = false;
          stopped = false;
          left = false;
          right = false;
          game_of_life = true;
          break;
    
    }
        irrecv.resume(); // Riceve il successivo valore IR
  }
  delay(100);

}


/* Mantiene la velocità elevata dei motori quando un TribeBot di una tribù diversa si avvicina
  @param currentMillis  rappresenta l'intervallo di tempo per la durata dello stato agitato
*/
void stato_agitato(unsigned long currentMillis) {
  
  // Durata di 10 sec. per stato agitato, dopo 10 sec. torna calmo
  if( (currentMillis - previousMillis_2 >= interval_2) && play_2 == true) {
          previousMillis_2 = currentMillis; 
          play_2 = false;   
          play_1 = true;
  }

}


void turn_left() {
          analogWrite(5, 200);
          analogWrite(6, 0);
}

void turn_right() {
          analogWrite(6, 200);
          analogWrite(5, 0);
}

void stop_motor() {
          analogWrite(6, 0);
          analogWrite(5, 0);
}

void p1() { // avanti piano
          analogWrite(6, 90);
          //delay(1000);
          analogWrite(5, 90);
          //delay(1000);
}

void p2() { // avanti veloce random
          analogWrite(6, random(140,220));
          analogWrite(5, random(140,220));
}

void p3() {
          
            temp = !temp;
            
            if (temp) {
              analogWrite(6, 110);
              analogWrite(5, 110);
            }
            else {
              analogWrite(6, 10);
              analogWrite(5, 10);
            }
}

void p4() {
            temp = !temp;
            
            if (temp) {
              analogWrite(6, 210);
              analogWrite(5, 10);
         
            }
            else {
              analogWrite(6, 10);
              analogWrite(5, 210);
            
            }
}

void p5() {
  

}


// Game of Life - implementazione logica di funzionamento

/* *********************************************** GAME OF LIFE IN TRIBEBOT ***********************************************************
      
      -- Trasmetti ID_GOL ogni nr_casuale secondi in modo che non si generino collisioni nelle trasmissioni
      
      -- leggi i messaggi IR in ingresso continuamente
      
      -- Viene creato un elenco per memorizzare la presenza dei TribeBots vicini (vettore 'elenco_tb[]').
      
      -- Questo vettore contiene numeri interi [0 o 1]. Quando si riceve un messaggio da un TribeBot vicino, nell'indice corrispondente 
         del vettore si memorizza il nr. 1 (ad es. SE ricevo 0x81 ALLORA metto  elenco_tb[1] = 1, mentre SE ricevo 0x83 ALLORA metto  elenco_tb[3] = 1)
         
      -- Ogni 2 sec si contano il numero di vicini :
           --- Il conteggio viene effettuato incrementando di un unità una variabile "nr_vicini" ogni volta che nell'elenco vettore "elenco_tb" viene 
           letto un nr. maggiore di 0.
           
           --- Si controllano i numeri presenti nel VETTORE elenco TribeBot,se il numero è maggiore di 0 allora lo si decrementa di un unità, questo per resettare l'elenco di nr. 1 nel vettore

      -- Se il nr dei vicini è maggiore di 1 e minore di 4, quindi si hanno 2 o 3 TribeBots vicini, allora il TribeBot "VIVE" (ad es. aumenta velocità motori), altrimenti STOP motori (MORTO).
    
  ********************************************************************************************************************************************/
  
      
void gol() {
  
     trasmetti_id(id_gol); 
  
    // Se il nr. dei vicini è 2 o 3 allora muoviti altrimenti fermo
    if (nr_vicini > 1 && nr_vicini <= 3) {
    
        analogWrite(5,100);
        analogWrite(6,100);
    } 
    else 
    {
        analogWrite(5,0);
        analogWrite(6,0);
    
    }
  
}

void leggi_msg_gol() {

  /*
    ESEGUI OGNI SECONDO LE SEGUENTI AZIONI:
    - SE RICEVI IN INGRESO UN MESSAGGIO ALLORA LEGGI IN INGRESSO L'IDENTIFICATIVO DEL TRIBEBOT VICINO 
    */
      if (irrecv.decode(&results)) {
    
      ch_free = false;
    
      Serial.println(results.value, HEX);
      Serial.println("GAME OF LIFE");
      // Led rosso quando si ricevono dati
      digitalWrite(redLEDPin, HIGH);
      digitalWrite(yellowLEDPin, LOW);
      digitalWrite(blueLEDPin, LOW);   

      // reset vettore contenente l'elenco dei TribeBots vicini - 0 assente 1 presente
//      for (int i = 0; i < 20; i++) {
//            elenco_tb[i] = 0;
//      }

      
//      for (int i = 0; i < 20; i++) {
//           if (elenco_tb[i] > 0) {elenco_tb[i]--; } ;
//      }

    // Se ricevo un messaggio in ingresso , leggo il valore in BYTE, se corrisponde metto a 1 (presente) l'indice corrispondente
    switch(results.value) {
      case (0x80):elenco_tb[1] = 1;
        break;
      case (0x81):elenco_tb[2] = 1;
        break;
      case (0x83):elenco_tb[3] = 1;
        break;
      case (0x84):elenco_tb[4] = 1;
        break;
      case (0x85):elenco_tb[5] = 1;
        break;
      case (0x86):elenco_tb[6] = 1;
        break;
      case (0x87):elenco_tb[7] = 1;
        break;
      case (0x88):elenco_tb[8] = 1;
        break;
      case (0x89):elenco_tb[9] = 1;
        break;
      case (0x90):elenco_tb[10] = 1;
        break;
      case (0x91):elenco_tb[11] = 1;
        break;
      case (0x92):elenco_tb[12] = 1;
        break;
      case (0x93):elenco_tb[13] = 1;
        break;
      case (0x94):elenco_tb[14] = 1;
        break;
      case (0x95):elenco_tb[15] = 1;
        break;
      case (0x96):elenco_tb[16] = 1;
        break;
      case (0x97):elenco_tb[17] = 1;
        break;
      case (0x98):elenco_tb[18] = 1;
        break;
      case (0x99):elenco_tb[19] = 1;
        break;
 
    }
    
}
}


void conta_vicini(){
      
   nr_vicini = 0; // azzero la variabile che conta il nr. di vicini
   
   

   for (int i = 0; i < 20; i++) {
     
      // Incremento di un unità la variabile "nr_vicini" solo se il valore contenuto nel singolo vettore è > di 0.
      if (elenco_tb[i] > 0) { nr_vicini++; }
      
      // Reset vettore contenente lo stato 1 se vi è un TribeBot vicino
      if (elenco_tb[i] > 0) 
      {
          // Decremento di un unità il numero contenuto in ogni singolo vettore, solo se > 0
          elenco_tb[i]--;           
      } 
     
               

      
   }
  
     
//   // conto il nr. di vicini
//   for (int i = 0; i < 20; i++) {
//          if (elenco_tb[i] > 0) {
//              nr_vicini++;
//            }
//    }
    
//    Serial.println("nr. dei  vicini %k",nr_vicini);
//    ardprintf(

    Serial.println(nr_vicini, DEC);
    
//    if (nr_vicini <= 1) {
//    
//    }
//    
//    if (nr_vicini > 1 && nr_vicini <= 3) {
//    
//        analogWrite(5,40);
//        analogWrite(10,40);
//    } 
//    else 
//    {
//        analogWrite(5,0);
//        analogWrite(10,0);
//    
//    }
    
    
      

  }


// Funzione di prova - Non utilizzata nel codice

boolean timer(int interval_timer)
{
     unsigned long currentMillis = millis();
     
     if  (currentMillis - previousMillisTimer >= interval_timer)  
     {
       previousMillisTimer = currentMillis;
       return true;
     } 
     else
     {
       return false;
     }
     
}
