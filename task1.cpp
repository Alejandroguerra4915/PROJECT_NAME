#include <Arduino.h>
#include "task1.h"


void task1()
{
    enum class Task1States
    {
        INIT,
        WAIT_DATA
    };
    static Task1States task1State = Task1States::INIT;

    switch (task1State)
    {
    case Task1States::INIT:
    {
        Serial.begin(115200);
        task1State = Task1States::WAIT_DATA;
        break;
    }

    case Task1States::WAIT_DATA:
    {
        // evento 1:
        // Ha llegado al menos un dato por el puerto serial?
        if (Serial.available() > 0)
        {
            Serial.read();
            Serial.print("Hola computador\n");
        }
        break;
    }

    default:
    {
        break;
    }
    }
}

    
}