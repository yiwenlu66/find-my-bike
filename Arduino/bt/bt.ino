#include "pitches.h"

char junk;
String inputString = "";

int melody[] = {
    NOTE_E6, NOTE_C6, NOTE_D6, NOTE_A5,
    NOTE_E6, NOTE_D6, NOTE_C6, NOTE_D6, NOTE_A5,
    NOTE_E6, NOTE_C6, NOTE_D6, NOTE_D6,
    NOTE_G6, NOTE_E6, NOTE_B5, NOTE_C6, NOTE_C6, NOTE_B5,
    NOTE_A5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_G5,
    NOTE_A6, NOTE_G6, NOTE_E6, NOTE_E6, NOTE_D6,
    NOTE_C6, NOTE_D6, NOTE_E6, NOTE_D6, NOTE_E6, NOTE_D6, NOTE_E6, NOTE_G6,
    NOTE_G6, NOTE_G6, NOTE_G6, NOTE_G6, NOTE_G6, NOTE_G6,

    NOTE_E6, NOTE_C6, NOTE_D6, NOTE_A5,
    NOTE_E6, NOTE_D6, NOTE_C6, NOTE_D6, NOTE_A5,
    NOTE_E6, NOTE_C6, NOTE_D6, NOTE_D6, NOTE_D6,
    NOTE_G6, NOTE_E6, NOTE_B5, NOTE_C6, NOTE_C6, NOTE_B5,
    NOTE_A5, NOTE_B5, NOTE_C6, NOTE_D6, NOTE_G5,
    NOTE_A6, NOTE_G6, NOTE_E6, NOTE_E6, NOTE_D6,
    NOTE_C6, NOTE_D6, NOTE_E6, NOTE_D6, NOTE_G5,
    NOTE_A5, NOTE_A5, NOTE_C6, NOTE_A5
};

int noteDurations[] = {
    4, 4, 4, 4,
    8, 8, 8, 8, 2,
    4, 4, 4, 4,
    8, 8, 4, 4, 8, 8,
    4, 8, 8, 4, 4,
    8, 8, 4, 3, 8,
    4, 8, 8, 8, 8, 8, 16, 16,
    4, 8, 8, 8, 8, 4,

    4, 4, 4, 4,
    8, 8, 8, 8, 2,
    4, 4, 4, 8, 8,
    8, 8, 4, 4, 8, 8,
    4, 8, 8, 4, 4,
    8, 8, 4, 3, 8,
    4, 8, 8, 4, 4,
    4, 8, 8, 2
};

void setup()
{
    Serial1.begin(9600);
    pinMode(13, OUTPUT);
}

void loop()
{
    if (Serial1.available()) {
        while (Serial1.available()) {
            char inChar = (char)Serial1.read();
            inputString += inChar;
        }
        Serial1.println(inputString);
        while (Serial1.available() > 0) {
            junk = Serial1.read() ;
        }
        if (inputString == "a") {
            digitalWrite(13, HIGH);
        } else if (inputString == "b") {
            digitalWrite(13, LOW);
        } else if (inputString == "c") {
            for (int thisNote = 0; thisNote < 82; thisNote++) {

                int noteDuration = 1000 / noteDurations[thisNote];
                tone(SOUNDPIN, melody[thisNote], noteDuration);

                int pauseBetweenNotes = noteDuration * 1.30;
                delay(pauseBetweenNotes);

                noTone(SOUNDPIN);
            }
        }
        inputString = "";
    }
}

