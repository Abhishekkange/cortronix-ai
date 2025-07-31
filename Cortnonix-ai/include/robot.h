#ifndef ROBOT_H
#define ROBOT_H

class Robot {
public:
    Robot();

    enum State {
        IDLE,
        HAPPY,
        SAD,
        ANGRY,
        LISTENING,
        DEEP_SLEEP,
        LOOK_UP,
        SLEEP,
        SUDDEN_WAKEUP
    };

    State currentState, prevState;

    State getCurrentState();
    State getPrevState();
    void setCurrentState(State newCurrentState);
    void setPrevState(State newPrevState);
};

#endif