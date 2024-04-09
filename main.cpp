/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "PwmOut.h"
#include "ThisThread.h"
#include "Thread.h"
#include "UnbufferedSerial.h"
#include "cmsis_os2.h"
#include "mbed.h"
#include "serial_api.h"
#include "string.h"
#include "thread_bootstrap.h"
#include <cstdio>
#include <cstring>
#include <cwchar>


// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
#define cero 400
#define maximo 2230


//Prototipos de las funciones
void manejo_servo(void);
void recibir_serie(void);

//Tareas 
Thread hilo_manejo_servo(osPriorityNormal, 2048);
Thread hilo_recibir_serie(osPriorityNormal, 2048);

// pines y puertos
BufferedSerial pc(USBTX, USBRX);
DigitalOut led (LED1);
PwmOut servo(D3);

// variables globales
 int angulo=0; 



int main()
{
    servo.period_ms(20);
    servo.pulsewidth_us(cero); // enviarlo a cero grados
    hilo_manejo_servo.start(manejo_servo);
   
    while (true) {
        led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
    
    }
}


void manejo_servo(void)
{
    int paso;
    int ancho;
    char men[20];    
    while(true)
    {
        paso +=10;
        if (paso==(maximo-cero)) paso=0;
        ancho= cero + paso;
        servo.pulsewidth_us(ancho);
        sprintf(men, "%4u micros\n\r", ancho);
        pc.write(men, strlen(men));
        ThisThread::sleep_for(100ms);

    }
}
