#include <SoftwareSerial.h>
#define CONSOLE_BAUDRATE 9600
#define AT_BAUDRATE 38400
#define BT_BAUDRATE 57600
#define NAME "BIKE"
#define PASSWORD 6666
#define RXPIN 10
#define TXPIN 11

// Swap RX/TX connections on bluetooth chip
//   Pin 10 --> Bluetooth TX
//   Pin 11 --> Bluetooth RX
SoftwareSerial mySerial(RXPIN, TXPIN);

void waitForResponse()
{
    delay(1000);
    while (mySerial.available()) {
        Serial.write(mySerial.read());
    }
    Serial.write("\n");
}

void setup()
{
    Serial.begin(CONSOLE_BAUDRATE);
    while (!Serial) {
        ; // wait for serial port to connect. Needed for Leonardo only
    }
    Serial.println("Starting config");
    mySerial.begin(AT_BAUDRATE);
    delay(1000);

    // Should respond with OK
    mySerial.print("AT\r\n");
    waitForResponse();

    // Should respond with its version
    mySerial.print("AT+VERSION\r\n");
    waitForResponse();

    // Set baudrate
    String arg_baudrate = "AT+UART=" + String(BT_BAUDRATE) + ",0,0\r\n";
    mySerial.print(arg_baudrate);
    waitForResponse();

    // Set name
    String arg_name = "AT+NAME=" + String(NAME) + "\r\n";
    mySerial.print(arg_name);
    waitForResponse();

    // Set pairing password
    String arg_pswd = "AT+PSWD=" + String(PASSWORD) + "\r\n";
    mySerial.print(arg_pswd);
    waitForResponse();

    // Query state
    mySerial.print("AT+STATE\r\n");
    waitForResponse();

    Serial.println("Done!");
}

void loop() {}
