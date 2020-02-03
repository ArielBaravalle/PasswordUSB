#include <EEPROM.h>
#include <Keyboard.h>    // This is a "built-in" library no need to install

#define EE_EEFLAG      0
#define EE_TXTLEN1     1  // direccion donde almaceno el largo de las cadenas 1 byte 255 largo maximo
#define EE_TXTLEN2     2
#define EE_TXTLEN3     3
#define EE_TXTLEN4     4
#define EE_TXTLEN5     5
#define EE_TXTLEN6     6

#define EE_ENAUTLOG    7  // direccion donde almaceno si envia la pass 1 al encender
#define EE_ENENTER1    8  // direccion donde almaceno si llevan enter al final de cada pass
#define EE_ENENTER2    9
#define EE_ENENTER3    10
#define EE_ENENTER4    11
#define EE_ENENTER5    12
#define EE_ENENTER6    13

#define EE_DELAYTEC    14       // 2 bytes ! INT , es un int  //  el delay entre teclas enviadas
#define EE_DELAYTECESP 16       // 2 bytes ! INT , es un int  //  el delay entre teclas especiales enviadas

#define EE_TXT_Pass_1        30
#define EE_TXT_Pass_2        70
#define EE_TXT_Pass_3        110
#define EE_TXT_Pass_4        150
#define EE_TXT_Pass_5        190
#define EE_TXT_Pass_6        230

#define LONGPULSE      6


unsigned long tiempo = 0;
char c,chaT;
String TXT_Pass_1,TXT_Pass_2,TXT_Pass_3,TXT_Pass_4,TXT_Pass_5,TXT_Pass_6;
byte n=0,len=0,txtlen1,txtlen2,txtlen3,txtlen4,txtlen5,txtlen6,EnAutLog,EnEnter1,EnEnter2,EnEnter3,EnEnter4,EnEnter5,EnEnter6;
int delaytec=80,DelayTecEsp=80;
byte auexec=1;

//---------------------------------------------------------
//                           Setup
//---------------------------------------------------------
void setup() {

    pinMode(3,INPUT_PULLUP);  // sets pin 3 to input & pulls it high w/ internal resistor
    pinMode(20,INPUT_PULLUP);  // sets pin 4 to input & pulls it high w/ internal resistor
    Serial.begin(115200);
    Serial.setTimeout(3000);
 /*   if( EEPROM.read(EE_EEFLAG) != 0 ){ 
      ResetFactory();  
      EEPROM.update(EE_EEFLAG, 0);
      Serial1.println(F("Deafult Factory Restored !"));
      }
   */   

    ReadEEData();


    }

//---------------------------------------------------------
//                           Loop
//---------------------------------------------------------
void loop() {
  char carac;
  int count20,count3;
  String cadeTMP="";
  if ( Serial.available() > 0) {     
    c = Serial.read(); 
    switch(c){
      //case 13: 
      case 'h': 
      case 'H': 
        ReadEEData();
        Serial.println("Lista de Opciones:");     
        Serial.println("------------------");     
        Serial.println("M - Muestra cadenas");     //
        Serial.println("1 - Cambia texto 1: "+TXT_Pass_1);     //
        Serial.println("2 - Cambia texto 2: "+TXT_Pass_2);   // 
        Serial.println("3 - Cambia texto 3: "+TXT_Pass_3);     //
        Serial.println("4 - Cambia texto 4: "+TXT_Pass_4);   //     
        Serial.println("5 - Cambia texto 5: "+TXT_Pass_5);   //     
        Serial.println("6 - Cambia texto 6: "+TXT_Pass_6);   //     
        Serial.print("A - Autologin al conectar: ");  Serial.println(EnAutLog); //     
        Serial.print("B - Enter despues de la texto 1 : ");  Serial.println(EnEnter1); //     
        Serial.print("C - Enter despues de la texto 2 : ");  Serial.println(EnEnter2); //     
        Serial.print("D - Enter despues de la texto 3 : ");  Serial.println(EnEnter3); //     
        Serial.print("E - Enter despues de la texto 4 : ");  Serial.println(EnEnter4); //     
        Serial.print("F - Enter despues de la texto 5 : ");  Serial.println(EnEnter5); //     
        Serial.print("G - Enter despues de la texto 6 : ");  Serial.println(EnEnter6); //     
 //       Serial.println("Z - set caracteres : ");  //     
        Serial.println("H - Help ");    //     
        Serial.print("I - delay entre teclas: "); Serial.println(delaytec);   //     
        Serial.print("J - delay entre teclas especiales: "); Serial.println(DelayTecEsp);   //     
        break;           
   
      case 'M': 
      case 'm': 
         ReadEEData();
         Serial.println();
         Serial.println(TXT_Pass_1);
         Serial.println(TXT_Pass_2);
         Serial.println(TXT_Pass_3);
         Serial.println(TXT_Pass_4);
         Serial.println(TXT_Pass_5);
         Serial.println(TXT_Pass_6);
         Serial.println();
        break;
      case '1': 
        Serial.println(F("Ingrese texto 1"));
        TXT_Pass_1=Serial.readString();
        Serial.println("Txt 1: " + TXT_Pass_1);       
        WriteStringEE( EE_TXT_Pass_1,TXT_Pass_1.length(),TXT_Pass_1); 
        EEPROM.update(EE_TXTLEN1, TXT_Pass_1.length());   
      break;
      case '2': 
        Serial.println(F("Ingrese texto 2:"));
        TXT_Pass_2=Serial.readString();
        Serial.println("Txt 2: " + TXT_Pass_2);  
        WriteStringEE( EE_TXT_Pass_2,TXT_Pass_2.length(),TXT_Pass_2); 
        EEPROM.update(EE_TXTLEN2, TXT_Pass_2.length());           
      break;
      case '3': 
        Serial.println(F("Ingrese texto 3"));
        TXT_Pass_3=Serial.readString();
        Serial.println("Txt 3: " + TXT_Pass_3);  
        WriteStringEE( EE_TXT_Pass_3,TXT_Pass_3.length(),TXT_Pass_3);
        EEPROM.update(EE_TXTLEN3, TXT_Pass_3.length());            
      break;
      case '4': 
        Serial.println(F("Ingrese texto 4"));
        TXT_Pass_4=Serial.readString();
        Serial.println("Txt 4: " + TXT_Pass_4); 
        WriteStringEE( EE_TXT_Pass_4,TXT_Pass_4.length(),TXT_Pass_4); 
        EEPROM.update(EE_TXTLEN4, TXT_Pass_4.length());            
      break;
      case '5': 
        Serial.println(F("Ingrese texto 5"));
        TXT_Pass_5=Serial.readString();
        Serial.println("Txt 5: " + TXT_Pass_5); 
        WriteStringEE( EE_TXT_Pass_5,TXT_Pass_5.length(),TXT_Pass_5); 
        EEPROM.update(EE_TXTLEN5, TXT_Pass_5.length());            
      break;
      case '6': 
        Serial.println(F("Ingrese texto 6"));
        TXT_Pass_6=Serial.readString();
        Serial.println("Txt 6: " + TXT_Pass_6); 
        WriteStringEE( EE_TXT_Pass_6,TXT_Pass_6.length(),TXT_Pass_6); 
        EEPROM.update(EE_TXTLEN6, TXT_Pass_6.length());            
      break;
 /*     case 'T': 
      case 't': 
        Serial.print(F("Ingrese texto (max 30) "));
        cadeTMP=""; 
        for(n=0;n<30;n++){
            while ( Serial.available() == 0);
                carac = Serial.read();
                if(carac==13 || carac==10 || carac==27){ n=31; continue;}
                Serial.print(carac);
                cadeTMP +=  carac;
                } 
        Serial.print(F("\r\ntexto: ")); Serial.println(cadeTMP); 
        break;
*/
      case 'a': 
      case 'A': 
        Serial.print(F("Enable autologin Y/N"));
        while ( Serial.available() == 0);
            carac = Serial.read();
            if(carac=='Y' || carac=='y') EnAutLog=1; else if(carac=='N' || carac=='n') EnAutLog=0;
            EEPROM.update(EE_ENAUTLOG,EnAutLog);
            Serial.print(F(": ")); Serial.println(carac); 
            auexec =0;
            break;      
 
      case 'b': 
      case 'B': 
        Serial.print(F("Enter despues de texto 1 Y/N"));
        while ( Serial.available() == 0);
            carac = Serial.read();
            if(carac=='Y' || carac=='y') EnEnter1=1; else if(carac=='N' || carac=='n') EnEnter1=0;
            EEPROM.update(EE_ENENTER1,EnEnter1);
            Serial.print(F(": ")); Serial.println(carac); 
            auexec =0;
            break;      
    
      case 'c': 
      case 'C': 
        Serial.print(F("Enter despues de texto 2 Y/N"));
        while ( Serial.available() == 0);
            carac = Serial.read();
            if(carac=='Y' || carac=='y') EnEnter2=1; else if(carac=='N' || carac=='n') EnEnter2=0;
            EEPROM.update(EE_ENENTER2,EnEnter2);
            Serial.print(F(": ")); Serial.println(carac); 
            auexec =0;
            break;  
                
      case 'd': 
      case 'D': 
        Serial.print(F("Enter despues de texto 3 Y/N"));
        while ( Serial.available() == 0);
            carac = Serial.read();
            if(carac=='Y' || carac=='y') EnEnter3=1; else if(carac=='N' || carac=='n') EnEnter3=0;
            EEPROM.update(EE_ENENTER3,EnEnter3);
            Serial.print(F(": ")); Serial.println(carac); 
            auexec =0;
            break;  
                
      case 'e': 
      case 'E': 
        Serial.print(F("Enter despues de texto 4 Y/N"));
        while ( Serial.available() == 0);
            carac = Serial.read();
            if(carac=='Y' || carac=='y') EnEnter4=1; else if(carac=='N' || carac=='n') EnEnter4=0;
            EEPROM.update(EE_ENENTER4,EnEnter4);
            Serial.print(F(": ")); Serial.println(carac); 
            auexec =0;
            break;  
      case 'f': 
      case 'F': 
        Serial.print(F("Enter despues de texto 5 Y/N"));
        while ( Serial.available() == 0);
            carac = Serial.read();
            if(carac=='Y' || carac=='y') EnEnter5=1; else if(carac=='N' || carac=='n') EnEnter5=0;
            EEPROM.update(EE_ENENTER5,EnEnter5);
            Serial.print(F(": ")); Serial.println(carac); 
            auexec =0;
            break;  
      case 'g': 
      case 'G': 
        Serial.print(F("Enter despues de texto 6 Y/N"));
        while ( Serial.available() == 0);
            carac = Serial.read();
            if(carac=='Y' || carac=='y') EnEnter6=1; else if(carac=='N' || carac=='n') EnEnter6=0;
            EEPROM.update(EE_ENENTER6,EnEnter6);
            Serial.print(F(": ")); Serial.println(carac); 
            auexec =0;
            break;  
 /*     case 'z': 
      case 'Z': 
         delay(3000);
          for(int y=0;y<255;y++){ Serial.println(y); delay(200); Keyboard.write(y); delay(400); while(digitalRead(3) == 1); }
          break;  
 */         
      case 'i': 
      case 'I': 
         Serial.print(" Ingrese el delay entre teclas:" );
         delaytec = Serial.parseInt();
         EEPROMUpdateInt( EE_DELAYTEC,delaytec);
         Serial.println(delaytec);
         break;  
      case 'j': 
      case 'J': 
         Serial.print(" Ingrese el delay entre teclas especiales:" );
         DelayTecEsp = Serial.parseInt();
         EEPROMUpdateInt( EE_DELAYTECESP,DelayTecEsp);
         Serial.println(DelayTecEsp);
         break;  
      case '?': 
         
         ResetFactory();
         break;  

                
      }
    }
  

  // despues de conectar alimentacion envia la pass 1 ( si está configurado)
  if(EnAutLog == 1 && auexec==1){
      delay(2000);      
      Keyboard.begin();  Keyboard.print(KEY_ESC);  Keyboard.end();
      Keyboard.begin();         //begin keyboard 
      Keyboard.write(KEY_ESC);         // send Hex value 
      Keyboard.end();               
      delay(2000);          SacaPorKEY( TXT_Pass_1,KEY_RETURN);
      auexec =0;
      
  }

  

   
   count3=0;
   while(digitalRead(3) == 0) { 
      count3++; delay(100); 
      if(digitalRead(20) == 0){
        TXT_Pass_6 = ReadStringEE( EE_TXT_Pass_6,EEPROM.read(EE_TXTLEN6));
        if(EnEnter6) SacaPorKEY( TXT_Pass_6,KEY_RETURN); else SacaPorKEY( TXT_Pass_6,0); 
        delay(1000); count3=0;
        } 
      }     //  cuento el tiempo de la pulsacion   
   if(count3>0 && count3 <= LONGPULSE ){  
      TXT_Pass_3 = ReadStringEE( EE_TXT_Pass_3,EEPROM.read(EE_TXTLEN3));  
       if(EnEnter3) SacaPorKEY( TXT_Pass_3,KEY_RETURN); else SacaPorKEY( TXT_Pass_3,0);
     }  else if(count3 > LONGPULSE ) {  
        TXT_Pass_4 = ReadStringEE( EE_TXT_Pass_4,EEPROM.read(EE_TXTLEN4));  
        if(EnEnter4) SacaPorKEY( TXT_Pass_4,KEY_RETURN); else SacaPorKEY( TXT_Pass_4,0);
        }

//segun el tiempo que tenga pulsado y el que pulse despues , lanzo el texto 1 / 2 / 5
   count20=0;
   while(digitalRead(20) == 0) { 
      count20++; delay(100); 
      if(digitalRead(3) == 0){
        TXT_Pass_5 = ReadStringEE( EE_TXT_Pass_5,EEPROM.read(EE_TXTLEN5));  
        if(EnEnter5) SacaPorKEY( TXT_Pass_5,KEY_RETURN); else SacaPorKEY( TXT_Pass_5,0);
        delay(1000); count20=0;
        } 
      }    //  cuento el tiempo de la pulsacion   
   if(count20>0 && count20 <= LONGPULSE ){   
     TXT_Pass_1 = ReadStringEE( EE_TXT_Pass_1,EEPROM.read(EE_TXTLEN1));   
     if(EnEnter1) SacaPorKEY( TXT_Pass_1,KEY_RETURN); else SacaPorKEY( TXT_Pass_1,0);
     }  else if(count20 > LONGPULSE ) {  
          TXT_Pass_2 = ReadStringEE( EE_TXT_Pass_2,EEPROM.read(EE_TXTLEN2));  
          if(EnEnter2) SacaPorKEY( TXT_Pass_2,KEY_RETURN); else SacaPorKEY( TXT_Pass_2,0);
        }


}
//saca la cadena de teclas cade   y le pone el Endchart al final
void SacaPorKEY(String cade,int EndChar){
  Keyboard.begin();         //begin keyboard 
  //cade.replace("*", "}" );
  for(int ch = 0;ch < cade.length(); ch++){
    if(cade.charAt(ch) >= 65 && cade.charAt(ch) <= 90 ) { // si es mayusculas presiono el shift antes
      Keyboard.press(KEY_LEFT_SHIFT);         // send Hex value 
      delay(delaytec);
      }
    switch( cade.charAt(ch) ){
      case '@':  
          Keyboard.press(KEY_LEFT_CTRL);         // send Hex value 
          delay(DelayTecEsp);
          Keyboard.press(KEY_LEFT_ALT);         // send Hex value    switch(caracter){
          delay(DelayTecEsp);
          Keyboard.write(50); 
          break;
      case '!':  
          Keyboard.press(KEY_LEFT_SHIFT);         // send Hex value 
          delay(DelayTecEsp);
          Keyboard.write('1'); 
          break;
      case '{':  
          Keyboard.press(KEY_LEFT_CTRL);         // send Hex value 
          delay(DelayTecEsp);
          Keyboard.press(KEY_LEFT_ALT);         // send Hex value    switch(caracter){
          delay(DelayTecEsp);
          Keyboard.write(39); 
          break;
      case '}':  
          Keyboard.press(KEY_LEFT_CTRL);         // send Hex value 
          delay(DelayTecEsp);
          Keyboard.press(KEY_LEFT_ALT);         // send Hex value    switch(caracter){
          delay(DelayTecEsp);
          Keyboard.write(92); 
          break;
      case 92:  //  "\"
          Keyboard.press(KEY_LEFT_CTRL);         // send Hex value 
          delay(DelayTecEsp);
          Keyboard.press(KEY_LEFT_ALT);         // send Hex value    switch(caracter){
          delay(DelayTecEsp);
          Keyboard.write(96); 
          break;      
      case '/':  
          Keyboard.write(38); 
          break;      
      case '(':  
          Keyboard.write(42); 
          break;      
      case ')':  
          Keyboard.write(40); 
          break;      
      case '*':  
          Keyboard.write('}'); 
          break;      
    

      default:
        Keyboard.print(cade.charAt(ch)); 
      break;
    }
    delay(delaytec);
    Keyboard.releaseAll();
    delay(delaytec);
  }
  if(EndChar > 0) Keyboard.write(EndChar);         // send Hex value 
  Keyboard.end();                 //stops keybord
  delay(delaytec); 
}



  
