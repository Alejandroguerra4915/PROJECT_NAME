#include <Arduino.h>
#include "task2.h"
#include "events.h"

void task2()
{
    enum class TaskState
    {
        INIT,
        tiempoespera, 
        tiempo,
        reiniciotiempo 
    };
    static TaskState taskState = TaskState::INIT;
    static uint8_t lastButtonPressed;
    static uint32_t initStableTime;
    const uint8_t boton1 = 32;
    const uint8_t boton2 = 13;
    const uint32_t tiempo = 100; 

    switch (taskState)
    {
    case TaskState::INIT:
    {
        pinMode(boton1, INPUT_PULLUP);
        pinMode(boton2, INPUT_PULLUP);
        taskState = TaskState::tiempoespera; 
        break;
    }
    case TaskState::tiempo:
    {
        if(digitalRead(boton1) == LOW){
            lastButtonPressed = boton1;
            initStableTime = millis();
            taskState = TaskState::tiempo;
        }
        if(digitalRead(boton2) == LOW){
            lastButtonPressed = boton2;
            initStableTime = millis();
            taskState = TaskState::tiempo;
        }

        break;
    }
    case TaskState::tiempo:
    {
        if(digitalRead(lastButtonPressed) != LOW){
            taskState = TaskState::WAIT_PRESS;
        }
        else if ( (millis() - initStableTime) > tiempo){
            if(lastButtonPressed == boton1) buttonEvt.whichButton = BUTTONS::Boton1;
            else if(lastButtonPressed == boton2) buttonEvt.whichButton = BUTTONS::Boton2;
            buttonEvt.trigger = true;
            //printf("Button pressed: %d\n", lastButtonPressed);
            taskState = TaskState::WAIT_RELEASE;
        }
        break;
    }
    case TaskState::reiniciotiempo:{
        if(digitalRead(lastButtonPressed) == HIGH){
            taskState = TaskState::tiempoespera;
        }
        break;
    }

    default:
    {
    }
    }
}
