#include "robot.h"

Robot::Robot() {
    currentState = IDLE;
    prevState = IDLE;
}

Robot::State Robot::getCurrentState() {
    return currentState;
}

Robot::State Robot::getPrevState() {
    return prevState;
}

void Robot::setCurrentState(State newCurrentState) {
    currentState = newCurrentState;
}

void Robot::setPrevState(State newPrevState) {
    prevState = newPrevState;
}