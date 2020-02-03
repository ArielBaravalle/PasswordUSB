

void WriteStringEE(byte addr,byte cant,String stri){
    for(byte n=0;n<cant;n++){
      EEPROM.update(addr+n, stri.charAt(n));
      }  
 }

String ReadStringEE(byte addr,byte cant){
  String mov="";
  for(byte n=0;n<cant;n++){
    mov.concat((char)EEPROM.read(addr+n));
     }  
  return mov;
 }


//This function will write a 2 byte integer to the eeprom at the specified address and address + 1
void EEPROMWriteInt(int p_address, int p_value)
     {
     byte lowByte = ((p_value >> 0) & 0xFF);
     byte highByte = ((p_value >> 8) & 0xFF);

     EEPROM.write(p_address, lowByte);
     EEPROM.write(p_address + 1, highByte);
     }

void EEPROMUpdateInt(int p_address, int p_value)
     {
     byte lowByte = ((p_value >> 0) & 0xFF);
     byte highByte = ((p_value >> 8) & 0xFF);

     EEPROM.update(p_address, lowByte);
     EEPROM.update(p_address + 1, highByte);
     }

//This function will read a 2 byte integer from the eeprom at the specified address and address + 1
unsigned int EEPROMReadInt(int p_address)
     {
     byte lowByte = EEPROM.read(p_address);
     byte highByte = EEPROM.read(p_address + 1);

     return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
     }


void ResetFactory(void){

  String txt1="Pass1";
  String txt2="user1	Pass1";
  String txt3="Pass2";
  String txt4="user2	Pass2";
  String txt5="Pass3";
  String txt6="Pass4";
  
  Serial.println("Reset Factory!" );
  // grabo los largos de los string a 1
    EEPROM.update(EE_TXTLEN1, txt1.length());
    EEPROM.update(EE_TXTLEN2, txt2.length());
    EEPROM.update(EE_TXTLEN3, txt3.length());
    EEPROM.update(EE_TXTLEN4, txt4.length());
    EEPROM.update(EE_TXTLEN5, txt5.length());
    EEPROM.update(EE_TXTLEN6, txt6.length());

    EEPROM.update(EE_ENAUTLOG, 0);
    EEPROM.update(EE_ENENTER1, 1);
    EEPROM.update(EE_ENENTER2, 1);
    EEPROM.update(EE_ENENTER3, 1);
    EEPROM.update(EE_ENENTER4, 1);
    EEPROM.update(EE_ENENTER5, 1);
    EEPROM.update(EE_ENENTER6, 1);
    EEPROMWriteInt(EE_DELAYTEC, 80);
    EEPROMWriteInt(EE_DELAYTECESP, 200);



// inicializo los string con " "
    WriteStringEE( EE_TXT_Pass_1,txt1.length(),txt1);
    WriteStringEE( EE_TXT_Pass_2,txt2.length(),txt2);
    WriteStringEE( EE_TXT_Pass_3,txt3.length(),txt3);
    WriteStringEE( EE_TXT_Pass_4,txt4.length(),txt4);
    WriteStringEE( EE_TXT_Pass_5,txt5.length(),txt5);
    WriteStringEE( EE_TXT_Pass_6,txt6.length(),txt6);

    ReadEEData();
    
    Serial.println();
    Serial.println(TXT_Pass_1);
    Serial.println(TXT_Pass_2);
    Serial.println(TXT_Pass_3);
    Serial.println(TXT_Pass_4);
    Serial.println(TXT_Pass_5);
    Serial.println(TXT_Pass_6);
    Serial.println();   
}

void ReadEEData(){
    txtlen1 = EEPROM.read(EE_TXTLEN1);
    txtlen2 = EEPROM.read(EE_TXTLEN2);
    txtlen3 = EEPROM.read(EE_TXTLEN3);
    txtlen4 = EEPROM.read(EE_TXTLEN4);
    txtlen5 = EEPROM.read(EE_TXTLEN5);
    txtlen6 = EEPROM.read(EE_TXTLEN6);    
    delaytec = EEPROMReadInt(EE_DELAYTEC);
    DelayTecEsp = EEPROMReadInt(EE_DELAYTECESP);
    
    EnAutLog = EEPROM.read(EE_ENAUTLOG);
    EnEnter1 = EEPROM.read(EE_ENENTER1);
    EnEnter2 = EEPROM.read(EE_ENENTER2);
    EnEnter3 = EEPROM.read(EE_ENENTER3);
    EnEnter4 = EEPROM.read(EE_ENENTER4);
    EnEnter5 = EEPROM.read(EE_ENENTER5);
    EnEnter6 = EEPROM.read(EE_ENENTER6);
  
    TXT_Pass_1 = ReadStringEE( EE_TXT_Pass_1,txtlen1);
    TXT_Pass_2 = ReadStringEE( EE_TXT_Pass_2,txtlen2);
    TXT_Pass_3 = ReadStringEE( EE_TXT_Pass_3,txtlen3);
    TXT_Pass_4 = ReadStringEE( EE_TXT_Pass_4,txtlen4);
    TXT_Pass_5 = ReadStringEE( EE_TXT_Pass_5,txtlen5);
    TXT_Pass_6 = ReadStringEE( EE_TXT_Pass_6,txtlen6);
  
}

/*

33 !
34 ¨
35 ·
36 $
37 %
38 /
39´
40)
=41
(42
¿43
,44
'45
.46
-47  
48-57 0123456789
Ñ58
ñ59
;60
¡61
:62
_63
"64
65-90 ABCDEFGHIJKLMNOPQRSTUVWXYZ
`91 
ç92
+93
&94
?95
º96
97-122 abcdefghijklmnopqrstuvwxyz
^123
Ç124
*125
ª126
ALT 130
win 131
140-165 abcdefghijklmnopqrstuvwxyz
166-176 1234567890
BACK 178
  TAB 179
 '181
¡182
`183
+184
ç185
ç186
ñ187
´188
º189
,190
.191
-192
F3 196
F10 203
printscreen 206

/ 220
*221
-222
+223
225- 1234567890
.235
<236
tecla menu 237

Key  Hexadecimal value Decimal value
KEY_LEFT_CTRL 0x80  128
KEY_LEFT_SHIFT  0x81  129
KEY_LEFT_ALT  0x82  130
KEY_LEFT_GUI  0x83  131
KEY_RIGHT_CTRL  0x84  132
KEY_RIGHT_SHIFT 0x85  133
KEY_RIGHT_ALT 0x86  134
KEY_RIGHT_GUI 0x87  135
KEY_UP_ARROW  0xDA  218
KEY_DOWN_ARROW  0xD9  217
KEY_LEFT_ARROW  0xD8  216
KEY_RIGHT_ARROW 0xD7  215
KEY_BACKSPACE 0xB2  178
KEY_TAB 0xB3  179
KEY_RETURN  0xB0  176
KEY_ESC 0xB1  177
KEY_INSERT  0xD1  209
KEY_DELETE  0xD4  212
KEY_PAGE_UP 0xD3  211
KEY_PAGE_DOWN 0xD6  214
KEY_HOME  0xD2  210
KEY_END 0xD5  213
KEY_CAPS_LOCK 0xC1  193
KEY_F1  0xC2  194
KEY_F2  0xC3  195
KEY_F3  0xC4  196
KEY_F4  0xC5  197
KEY_F5  0xC6  198
KEY_F6  0xC7  199
KEY_F7  0xC8  200
KEY_F8  0xC9  201
KEY_F9  0xCA  202
KEY_F10 0xCB  203
KEY_F11 0xCC  204
KEY_F12 0xCD  205


control ALT:
{39
|49
@50
#51
~52
€53
¬54
[91
}92
]93
\96
€101
|166
@167
#168
~169
€170
¬171
[183
]184
}185
}186
{188
\189
CTRL ALT delete 212

*/
