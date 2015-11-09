#define BUZZER_PIN 6
#define LDR 0
int LDRValue = 0;
int light_sensitivity = 50;

int length = 4; // the number of notes
char notes[] = "abcd";
int beats[] = {1, 1, 1, 1};
int tempo = 190;

int a;
int koko = 1;
int lighted = 0;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);   
}

void loop() {

  LDRValue = analogRead(LDR);
  delay(200);

  //*
  if (LDRValue > light_sensitivity) {

    if(lighted == 0) {
      koko = 0;
      lighted = 1;
    }
  }

  if(koko == 0) {

    for (int z = 0; z < 8; ++z) {

      for(int i = 0; i < length; i++) {

        if(notes[i] == ' ') {
          delay(beats[i] * tempo);
        } else {
          playNote(notes[i], beats[i] * tempo);
        }

        delay(tempo / 2);
      }

      tempo = tempo - 18;
      koko = 1;
    }

    delay(1000);
    tempo = 170;

    for(int i = 0; i < length; i++) {

      if(notes[i] == ' ') {
        delay(beats[i] * tempo);
      } else {

        if(i == 3) {
          playNote(notes[i], tempo * 5);
        } else {
          playNote(notes[i], beats[i] * tempo);
        }
      }

      delay(tempo / 2);
    }

    delay(5000);
    lighted = 0;
  }
  //*/
}

/* play tone */
void playTone(int tone, int duration) {
  for (long i = 0; i < duration * 1000L; i += tone * 2) {
    digitalWrite(BUZZER_PIN, HIGH);
    delayMicroseconds(tone);
    digitalWrite(BUZZER_PIN, LOW);
    delayMicroseconds(tone);
  }
}

void playNote(char note, int duration) {
  char names[] = {'a', 'b', 'c', 'd'};
  int tones[] = {2200, 2100, 1950, 1900};
  
  // play the tone corresponding to the note name
  for (int i = 0; i < 4; i++) {
    if (names[i] == note) {
      playTone(tones[i], duration);
    }
  }
}
