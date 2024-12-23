#include <Servo.h>

Servo horizontal;
int servoh = 90;

int servohLimitHigh = 180;
int servohLimitLow = 0;

Servo vertical;
int servov = 45;

int servovLimitHigh = 180;
int servovLimitLow = 0;

int ldrlt = A2; //LDR top left - BOTTOM LEFT
int ldrrt = A3; //LDR top rigt - BOTTOM RIGHT
int ldrld = A1; //LDR down left - TOP LEFT
int ldrrd = A0; //ldr down rigt - TOP RIGHT

int buzz_pin = 10;
int buzz_tone = 20;

int tol = 50;

void setup()
{
    Serial.begin(9600);
    pinMode(buzz_pin, OUTPUT);
    horizontal.attach(31);
    vertical.attach(30);
    horizontal.write(servoh);
    vertical.write(servov);
}

void loop()
{
    int lt = analogRead(ldrlt); // top left
    int rt = analogRead(ldrrt); // top right
    int ld = analogRead(ldrld); // down left
    int rd = analogRead(ldrrd); // down rigt

    int avt = (lt + rt) / 2; // average value top
    int avd = (ld + rd) / 2; // average value down
    int avl = (lt + ld) / 2; // average value left
    int avr = (rt + rd) / 2; // average value right

    int dvert = abs(avt - avd); // check the diffirence of up and down
    int dhoriz = abs(avl - avr);// check the diffirence of left and right

    Serial.print("avt: ");
    Serial.print(avt);
    Serial.print(" ");
    Serial.print("avd: ");
    Serial.print(avd);
    Serial.print(" ");
    Serial.print("avl: ");
    Serial.print(avl);
    Serial.print(" ");
    Serial.print("avr: ");
    Serial.println(avr);

    Serial.print("h: ");
    Serial.print(servoh);
    Serial.print(" ");
    Serial.print("v: ");
    Serial.print(servov);
    Serial.print(" ");

    if (dhoriz > tol)
    {
        if (avl > avr)
        {
            if (servoh - 1 >= servohLimitLow) servoh--;
            else beep(150);
        }
        else if (avl < avr)
        {
            if (servoh + 1 <= servohLimitHigh) servoh++;
            else beep(150);
        }
        horizontal.write(servoh);
    }

    if (dvert > tol)
    {
        if (avt > avd)
        {
            if (servov + 1 <= servovLimitHigh) servov++;
            else beep(100);
        }
        else if (avt < avd)
        {
            if (servov - 1 >= servovLimitLow) servov--;
            else beep(100);
        }
        vertical.write(servov);
    }
}

void beep(unsigned char delayms) {
    analogWrite(buzz_pin, buzz_tone);
    delay(delayms);
    analogWrite(buzz_pin, 0);
    delay(delayms);
}