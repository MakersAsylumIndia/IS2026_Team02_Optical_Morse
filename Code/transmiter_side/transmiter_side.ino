int laserPin = 9;

int dot = 200;
int dash = 600;
int symbolGap = 200;
int letterGap = 600;

String letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

String morse[] = {
".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
"-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
"..-","...-",".--","-..-","-.--","--..",
".----","..---","...--","....-",".....",
"-....","--...","---..","----.","-----"
};

void sendDot(){
digitalWrite(laserPin,HIGH);
delay(dot);
digitalWrite(laserPin,LOW);
delay(symbolGap);
}

void sendDash(){
digitalWrite(laserPin,HIGH);
delay(dash);
digitalWrite(laserPin,LOW);
delay(symbolGap);
}

void setup(){
pinMode(laserPin,OUTPUT);
Serial.begin(9600);
}

void loop(){

if(Serial.available()){

String text = Serial.readStringUntil('\n');
text.toUpperCase();

for(int i=0;i<text.length();i++){

char c = text[i];

int index = letters.indexOf(c);

if(index>=0){

String code = morse[index];

for(int j=0;j<code.length();j++){

if(code[j]=='.') sendDot();
if(code[j]=='-') sendDash();

}

delay(letterGap);

}

}

}

}

