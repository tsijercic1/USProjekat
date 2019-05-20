#pragma once

#include<thread>
#include<cmath>
#include"motor.h"
#include"point.h"

/*
    ***Notes***
    penLiftDistance - visina na koju se podigne olovka u mm.
    motorMaxSpeed - 680 je broj stepova za koje motor ima max speed na 12V
    
    - Kod lineTo i moveTo metoda, prvo se ceka da se zavrsi vertikalno kretanje olovke,
    pa se tek onda vrsi kretanje po canvasu. Pozitivni smjer motora je u smjeru olovke,
    tj. prema dole, pa kad se threadData[2].distance postavi na +, to je spustanje, a -
    podizanje olovke.

    - Predznak ThreadData::distance govori motoru u kojem smjeru da se okrece. ThreadData::speed
    je procenat brzine motora ogranicen (0, 1]. ThreadData::run je kontrolna varijabla koja pokazuje
    trenutno stanje motora: run se koristi da se pokrene motor, thread ne radi nista s motorom ako !run;

*/

constexpr double stepsPerMilimeter = 4096*2.0;
constexpr double penLiftDistance = 20;
constexpr double motorMaxSpeed = 680;

class Head {
    struct ThreadData {
        Motor* motor = nullptr;
        double distance = 0;
        double speed = 1;
        bool run = false;
    };

    Motor xAxis, yAxis, zAxis;
    Point currentPosition;
    bool isLowered;
    ThreadData threadData[3];

    void motorThread(ThreadData data) {
        while(true) {
            if(data.run) {
                double steps = std::abs(data.distance) * data.motor->getStepsPerMilimeter();
                int dir = std::abs(data.distance);
                double speed = (data.speed <= 0 || data.speed > 1) ? 1 : data.speed;

                for(double i = 0; i < steps; i++) {
                    data.motor->step(dir);
                    delayMicroseconds(motorMaxSpeed/speed);
                }

                data.run = false;
            }
        }
    }

    void move(Point targetPosition) {
        double dx = targetPosition.x - currentPosition.x;
        double dy = targetPosition.y - currentPosition.y;

        if(std::abs(dx) >= std::abs(dy)) {
            threadData[0].speed = 1;
            threadData[1].speed = dy/dx;
        }else {
            threadData[0].speed = dx/dy;
            threadData[1].speed = 1;
        }

        threadData[0].distance = dx;
        threadData[1].distance = dy;

        threadData[0].run = true;
        threadData[1].run = true;
    }

    void raise() {
        threadData[2].distance = isLowered ? -penLiftDistance : 0;
        isLowered = false;
        threadData[2].run = true;
    }

    void lower() {
        threadData[2].distance = isLowered ? 0 : penLiftDistance;
        isLowered = true;
        threadData[2].run = true;
    }

public:
    Head() :
        xAxis(7, 11, 13, 15, stepsPerMilimeter),
        yAxis(33, 35, 37, 39, stepsPerMilimeter),
        zAxis(36, 40, 42, 44, stepsPerMilimeter),
        currentPosition(0, 0)
    {
        threadData[0] = {&xAxis, 0, 1, false};
        threadData[1] = {&yAxis, 0, 1, false};
        threadData[2] = {&zAxis, 0, 1, false};
        isLowered = false;

        std::thread xAxisThread(&Head::motorThread, this, threadData[0]);
        std::thread yAxisThread(&Head::motorThread, this, threadData[1]);
        std::thread zAxisThread(&Head::motorThread, this, threadData[2]);

        // Pripazi kad ce se threadovi terminirati!!!
        // xAxisThread.join();
        // yAxisThread.join();
        // zAxisThread.join();
    }

    bool isAvailable() {
        return !threadData[0].run && !threadData[1].run && !threadData[2].run;
    }

    void lineTo(Point target) {
        if(!isAvailable())
            return;
        
        lower();
        while(threadData[2].run);
        move(target);
    }

    void moveTo(Point target) {
        if(!isAvailable())
            return;
        
        raise();
        while(threadData[2].run);
        move(target);
    }

};