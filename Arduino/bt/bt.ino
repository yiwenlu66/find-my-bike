#include "pitches.h"
#define LEDPIN 13
#define SOUNDPIN 8
#define ARG_LEDON "1"
#define ARG_LEDOFF "2"
#define ARG_SOUNDON "3"
#define BAUDRATE 9600

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
    Serial1.begin(BAUDRATE);
    pinMode(LEDPIN, OUTPUT);
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
        if (inputString == ARG_LEDON) {
            digitalWrite(LEDPIN, HIGH);
        } else if (inputString == ARG_LEDOFF) {
            digitalWrite(LEDPIN, LOW);
        } else if (inputString == ARG_SOUNDON) {
            for (int thisNote = 0; thisNote < sizeof(melody) / sizeof(int); thisNote++) {

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
