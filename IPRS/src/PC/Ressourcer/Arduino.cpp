/*
PROTOCOL TO MASTER
A,LOG = Send log from master
B,Adress,Type/Connection = New slave "B,45,2
C,Room,RoomConnections = Room connections "C,1,2"
D,CAL = Calibrate system
E,ROOM,USERS = Initialise system "E,10,10"
*/

#define led0 53
#define led1 52
#define led2 51
#define led3 50
#define led4 10

#define on (digitalWrite(led, HIGH))
#define off (digitalWrite(led, LOW))

void setup()
{
    Serial.begin(9600);
    pinMode(led0, OUTPUT);
    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
    pinMode(led4, OUTPUT);
}

void loop()
{
    String input;
    String string1 = "903 097 0 0 0 0 0 0 0 0";
    String string2 = "20 10 30 20 10 0 0 0 0 0";
    String string3 = "30 0 20 10 10 10 999 0 0 0";
    String string4 = "40 10 20 10 10 0 0 0 0 0";
    String string5 = "0 40 10 20 10 10 0 0 0 999";
    String string6 = "0 0 40 10 20 10 10 0 0 0";
    String string7 = "0 0 0 0 10 20 70 0 0 0";
    String string8 = "0 0 0 0 40 10 20 10 10 0";
    String string9 = "999 0 0 0 0 40 10 20 10 90";
    String string10 = "0 0 40 0 0 0 30 20 999 0";

    String string11 = "Calibrated";

    if (Serial.available() > 0)
    {
        input = Serial.readStringUntil('\n');
        if (input.equals("A,LOG"))
        {
            digitalWrite(led0, HIGH);
            Serial.println(string1);
            Serial.println(string2);
            Serial.println(string3);
            Serial.println(string4);
            Serial.println(string5);
            Serial.println(string6);
            Serial.println(string7);
            Serial.println(string8);
            Serial.println(string9);
            Serial.println(string10);
            delay(2000);
            digitalWrite(led0, LOW);
        }
        else if (input.equals("B,45,2"))
        {
            digitalWrite(led1, HIGH);
            delay(2000);
            digitalWrite(led1, LOW);
        }
        else if (input.equals("C,1,2"))
        {
            digitalWrite(led2, HIGH);
            delay(2000);
            digitalWrite(led2, LOW);
        }
        else if (input.equals("D,CAL"))
        {
            digitalWrite(led3, HIGH);
            Serial.println(string11);
            delay(2000);
            digitalWrite(led3, LOW);
        }
        else if (input.equals("E,10,10"))
        {
            digitalWrite(led4, HIGH);
            delay(2000);
            digitalWrite(led4, LOW);
        }
    }
}
