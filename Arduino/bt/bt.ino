char junk;
String inputString = "";

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
        }
        inputString = "";
    }
}

