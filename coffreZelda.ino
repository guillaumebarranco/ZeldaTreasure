// First we define the pins of the buzzer which will emit the sounds and the light sensor which will detect light changements
#define BUZZER_PIN 6
#define LDR 0

/*
* Then we set our variables to prepare the script 
*/

// Var relative to the light sensor
int LDRValue = 0;
int light_sensitivity = 50;

// Var relative to the music
int length = 4; // the number of notes
char notes[] = "abcd";
int tempo = 190;

// Var relative to stop/restart and block the script
int can_begin = 1;
int lighted = 0;

/*
*   FUNCTIONS
*/

void setup() {
    pinMode(BUZZER_PIN, OUTPUT);   
}

void loop() {

    // We read the value of the light sensor
    LDRValue = analogRead(LDR);
    delay(200);

    // If the light value is > at 50 (which is the sensor in the dark maximum)
    if (LDRValue > light_sensitivity) {

        // We set that the script song can be executed
        if(lighted == 0) {
            can_begin = 0;
            lighted = 1;
        }
    }

    // If the song can be executed
    if(can_begin == 0) {

        for (int z = 0; z < 8; ++z) {

            for(int i = 0; i < length; i++) {

                if(notes[i] == ' ') {
                    delay(tempo);
                } else {
                    playNote(notes[i], tempo);
                }

                delay(tempo / 2);
            }

            tempo = tempo - 18;
            can_begin = 1;
        }

        delay(1000);
        tempo = 170;

        for(int i = 0; i < length; i++) {

            if(notes[i] == ' ') {
                delay(tempo);
            } else {

                if(i == 3) {
                    playNote(notes[i], tempo * 5);
                } else {
                    playNote(notes[i], tempo);
                }
            }

            delay(tempo / 2);
        }

        // We wait at least 5 seconds to rexecute the script if still enlighted
        delay(5000);
        lighted = 0;
    }
}

// Function that plays the tone => one sound
void playTone(int tone, int duration) {
    for (long i = 0; i < duration * 1000L; i += tone * 2) {
        digitalWrite(BUZZER_PIN, HIGH);
        delayMicroseconds(tone);
        digitalWrite(BUZZER_PIN, LOW);
        delayMicroseconds(tone);
    }
}

// Fonction that plays a "partition", few notes (4 actually)
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
