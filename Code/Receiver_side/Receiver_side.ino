// -------------------- Optical Morse: Send + Receive --------------------
int laserPin = 9;   // Laser via MOSFET
int ldrPin = A0;    // 3-pin LDR module signal pin

int dotTime = 200;       // Duration of dot
int threshold = 500;     // LDR module threshold

bool laserOn = false;
unsigned long startTime;
unsigned long lastChange;

String currentMorse = "";

// Morse code table
String morse[] = {
  ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---",
  "-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-",
  "..-","...-",".--","-..-","-.--","--..",
  ".----","..---","...--","....-",".....","-....","--...","---..","----.","-----",
  "--..--",".-.-.-","..--.."
};

char letters[] = {
'A','B','C','D','E','F','G','H','I','J',
'K','L','M','N','O','P','Q','R','S','T',
'U','V','W','X','Y','Z',
'1','2','3','4','5','6','7','8','9','0',
',','.','?'
};

void setup() {
  Serial.begin(9600);
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, HIGH);  // Laser OFF initially (MOSFET active LOW)
  Serial.println("Optical Morse Ready: Send + Receive");
}

// ---------------- Send Morse ----------------
void sendDot() {
  digitalWrite(laserPin, LOW);   // Laser ON
  delay(dotTime);
  digitalWrite(laserPin, HIGH);  // Laser OFF
  delay(dotTime);
}

void sendDash() {
  digitalWrite(laserPin, LOW);   // Laser ON
  delay(dotTime*3);
  digitalWrite(laserPin, HIGH);  // Laser OFF
  delay(dotTime);
}

void sendText(String text) {
  text.toUpperCase();
  for(int i = 0; i < text.length(); i++) {
    char c = text[i];
    for(int k = 0; k < 39; k++) {
      if(c == letters[k]) {
        String code = morse[k];
        for(int j = 0; j < code.length(); j++) {
          if(code[j] == '.') sendDot();
          else sendDash();
        }
        delay(dotTime*2); // letter spacing
      }
    }
    if(c == ' ') delay(dotTime*7); // word spacing
  }
}

// ---------------- Decode Morse ----------------
void decodeMorse(String code) {
  for(int i = 0; i < 39; i++) {
    if(code == morse[i]) {
      char letter = letters[i];
      Serial.print(letter);
      return;
    }
  }
}

// ---------------- Main Loop ----------------
void loop() {
  unsigned long currentTime = millis();

  // -------- SEND via Serial --------
  if(Serial.available()) {
    String text = Serial.readStringUntil('\n');
    sendText(text);
    Serial.println();
    delay(50);
  }

  // -------- RECEIVE via LDR Module --------
  int value = analogRead(ldrPin);

  if(value > threshold && !laserOn) {
    laserOn = true;
    startTime = currentTime;
  }

  if(value < threshold && laserOn) {
    laserOn = false;
    unsigned long duration = currentTime - startTime;
    if(duration < 300) currentMorse += ".";
    else currentMorse += "-";
    lastChange = currentTime;
  }

  // Letter gap detection
  if(!laserOn && currentMorse.length() > 0 && (currentTime - lastChange) > 400) {
    decodeMorse(currentMorse);
    currentMorse = "";
    lastChange = currentTime;
  }

  // Word gap detection
  if(!laserOn && (currentTime - lastChange) > 1500) {
    Serial.print(" ");
    lastChange = currentTime;
  }
}