#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(128,64,&Wire,-1);

#define LDR A0

int threshold = 600;

unsigned long startTime;
unsigned long pulseLength;

String morseBuffer="";
String message="";

String letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";

String morse[] = {
".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
"-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
"..-","...-",".--","-..-","-.--","--..",
".----","..---","...--","....-",".....",
"-....","--...","---..","----.","-----"
};

char decode(String code){

for(int i=0;i<36;i++){

if(code == morse[i])
return letters[i];

}

return '?';

}

void setup(){

Serial.begin(9600);

display.begin(SSD1306_SWITCHCAPVCC,0x3C);
display.clearDisplay();

display.setTextSize(1);
display.setTextColor(WHITE);

display.setCursor(0,0);
display.println("Receiver Ready");
display.display();

}

void loop(){

int light = analogRead(LDR);

if(light > threshold){

startTime = millis();

while(analogRead(LDR) > threshold);

pulseLength = millis() - startTime;

if(pulseLength < 300)
morseBuffer += ".";
else
morseBuffer += "-";

}

if(morseBuffer.length()>0 && analogRead(LDR) < threshold){

delay(600);

char letter = decode(morseBuffer);

message += letter;

display.clearDisplay();
display.setCursor(0,20);
display.println(message);
display.display();

morseBuffer="";

}

}