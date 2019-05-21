#pragma once

#include<thread>
#include<cmath>
#include<iostream>
#include"motor.h"
#include"point.h"

/*
    ***Notes***
    penLiftDistance - visina na koju se podigne olovka u mm.
    motorMaxSpeed - 680 je broj stepova za koje motor ima max speed na 12V
    
    - Kod lineTo i moveTo metoda, prvo se ceka da se zavrsi vertikalno kretanje olovke,
    pa se tek onda vrsi kretanje po canvasu. Pozitivni smjer motora je u smjeru olovke,
    tj. prema dole, pa kad se threadData[2].distance postavi na -, to je spustanje, a +
    podizanje olovke.

    - Predznak ThreadData::distance govori motoru u kojem smjeru da se okrece. ThreadData::speed
    je procenat brzine motora ogranicen (0, 1]. ThreadData::run je kontrolna varijabla koja pokazuje
    trenutno stanje motora: run se koristi da se pokrene motor, thread ne radi nista s motorom ako !run;

    Koristeno za testiranje ponasanja threadova:
        using namespace std::literals::chrono_literals;
        std::cout << "threadID: " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(2s);

*/

constexpr double stepsPerMilimeter = 6001.465;
constexpr double penLiftDistance = 5;
constexpr double motorMaxSpeed = 680;

struct ThreadData {
    Motor* motor = nullptr;
    double distance = 0;
    double speed = 1;
    bool run = false;
};

class Head {
    Motor xAxis, yAxis, zAxis;
    Point currentPosition;
    bool isLowered;
    ThreadData threadData[3];
    bool headActive;

    void motorThread(ThreadData *data) {
        while(headActive) {
            if(data->run) {
                double steps = std::fabs(data->distance) * stepsPerMilimeter;
                
                double speed = (data->speed <= 0 || data->speed > 1) ? 1 : data->speed;

                for(double i = 0; i < steps; i++) {
                    data->motor->step(data->distance);
                    delayMicroseconds(motorMaxSpeed/speed);
                }

                data->run = false;
            }
        }
    }

    void move(Point targetPosition) {
        double dx = targetPosition.x - currentPosition.x;
        double dy = targetPosition.y - currentPosition.y;
        
        threadData[0].distance = dx;
        threadData[1].distance = dy;
        
        dx = std::fabs(dx);
        dy = std::fabs(dy);
        
        if(dx >= dy) {
            threadData[0].speed = 1;
            threadData[1].speed = dy/dx;
        }else {
            threadData[0].speed = dx/dy;
            threadData[1].speed = 1;
        }

        threadData[0].run = true;
        threadData[1].run = true;
    }

public:
    Head() :
        xAxis(7, 11, 13, 15),
        yAxis(31, 33, 35, 37),
        zAxis(32, 36, 38, 40),
        currentPosition(0, 0)
    {
        headActive = true;
        
        threadData[0] = {&xAxis, 0, 1, false};
        threadData[1] = {&yAxis, 0, 1, false};
        threadData[2] = {&zAxis, 0, 1, false};

        std::thread xAxisThread(&Head::motorThread, this, &threadData[0]);
        std::thread yAxisThread(&Head::motorThread, this, &threadData[1]);
        std::thread zAxisThread(&Head::motorThread, this, &threadData[2]);

        xAxisThread.detach();
        yAxisThread.detach();
        zAxisThread.detach();
        
        isLowered = false;
        raise();
    }

    bool isAvailable() {
        return !threadData[0].run && !threadData[1].run && !threadData[2].run;
    }

    void lineTo(Point target) {
        if(!isAvailable())
            return;
        
        lower();
        move(target);
    }

    void moveTo(Point target) {
        if(!isAvailable())
            return;
        
        raise();
        move(target);
    }
    
    void raise() {
        if(!isAvailable())
            return;
                    
        threadData[2].distance = isLowered ? penLiftDistance : 0;
        threadData[2].run = true;
        while(threadData[2].run);
        isLowered = false;
    }

    void lower() {
        if(!isAvailable())
            return;
        
        threadData[2].distance = isLowered ? 0 : -penLiftDistance;
        threadData[2].run = true;
        while(threadData[2].run);
        isLowered = true;
    }

    Point getPosition() {
        return currentPosition;
    }

    ~Head() {
        while(!isAvailable());
        headActive = false;
    }
};
