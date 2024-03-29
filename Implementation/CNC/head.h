#pragma once

#include<thread>
#include<cmath>
#include<iostream>
#include"motor.h"
#include"../Geometry/point.h"

/*
    ***Notes***
    penLiftDistance - visina na koju se podigne olovka u mm.
    motorMaxSpeed - 680 je broj stepova za koje motor ima max speed na 12V, 2000 je default
    
    - Kod lineTo i moveTo metoda, prvo se ceka da se zavrsi vertikalno kretanje olovke,
    pa se tek onda vrsi kretanje po canvasu. Pozitivni smjer motora je u smjeru olovke,
    tj. prema dole, pa kad se threadData[2].distance postavi na -, to je spustanje, a +
    podizanje olovke.

    - Predznak ThreadData::distance govori motoru u kojem smjeru da se okrece. ThreadData::speed
    je procenat brzine motora ogranicen (0, 1]. ThreadData::run je kontrolna varijabla koja pokazuje
    trenutno stanje motora; run se koristi da se pokrene motor, thread ne radi nista s motorom ako !run;

    Koristeno za testiranje ponasanja threadova:
        using namespace std::literals::chrono_literals;
        std::cout << "threadID: " << std::this_thread::get_id() << std::endl;
        std::this_thread::sleep_for(2s);

*/

constexpr double stepsPerMilimeter = 6001.465;
constexpr double penLiftDistance = 2;
constexpr double motorMaxSpeed = 2000;

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

    void motorThread(ThreadData *data);
    void move(Point targetPosition);

public:
    Head();
    bool isAvailable();
    void lineTo(Point target);
    void moveTo(Point target);
    void raise();
    void lower();
    Point getPosition();
    ~Head();
};



Head::Head() :
        xAxis(7, 11, 13, 15),
        yAxis(31, 33, 35, 37),
        zAxis(32, 36, 38, 40),
        currentPosition(0, 0)
{
    headActive = true;
    isLowered = false;
    
    threadData[0] = {&xAxis, 0, 1, false};
    threadData[1] = {&yAxis, 0, 1, false};
    threadData[2] = {&zAxis, 0, 1, false};

    std::thread xAxisThread(&Head::motorThread, this, &threadData[0]);
    std::thread yAxisThread(&Head::motorThread, this, &threadData[1]);
    std::thread zAxisThread(&Head::motorThread, this, &threadData[2]);

    xAxisThread.detach();
    yAxisThread.detach();
    zAxisThread.detach();
}

void Head::motorThread(ThreadData *data)  {
    while(headActive) {
        if(data->run) {
            double steps = std::fabs(data->distance) * stepsPerMilimeter;

            double speed = (data->speed <= 0 || data->speed > 1) ? 1 : data->speed;
            for(unsigned long long int i = 0; i < steps; i++) {
                data->motor->step(data->distance);
                data->motor->delay(motorMaxSpeed/speed);
            }

            data->run = false;
        }
    }
}

void Head::move(Point targetPosition) {
    double dx = targetPosition.x - currentPosition.x;
    double dy = targetPosition.y - currentPosition.y;
    
    currentPosition.x = targetPosition.x;
    currentPosition.y = targetPosition.y;

    threadData[0].distance = -dx;
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

bool Head::isAvailable() {
    return !threadData[0].run && !threadData[1].run && !threadData[2].run;
}

void Head::lineTo(Point target) {
    while(!isAvailable());
    lower();
    move(target);
}

void Head::moveTo(Point target){
    while(!isAvailable());
    raise();
    move(target);
}

void Head::raise() {
    while(!isAvailable());
    
    threadData[2].distance = isLowered ? penLiftDistance : 0;
    threadData[2].run = true;
    while(threadData[2].run);
    isLowered = false;
}

void Head::lower()  {
    while(!isAvailable());

    threadData[2].distance = isLowered ? 0 : -penLiftDistance;
    threadData[2].run = true;
    while(threadData[2].run);
    isLowered = true;
}

Point Head::getPosition(){
    return currentPosition;
}

Head::~Head() {
    moveTo(Point());
    while(!isAvailable());
    headActive = false;
}
