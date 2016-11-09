//
// Created by Joel Schmidt on 23/10/2016.
//

#ifndef ENGINIMUS_INPUT_HPP
#define ENGINIMUS_INPUT_HPP


enum Action {
    PRIMARY_ACTION,
    SECONDARY_ACTION,
    QUIT,
    NUM_ACTIONS
};

enum State {
    MOVE_FORWARD,
    MOVE_BACKWARD,
    TURN_LEFT,
    TURN_RIGHT,
    NUM_STATES
};

struct FrameInput {
    bool actions[NUM_ACTIONS];
    bool states[NUM_STATES];
};

#endif //ENGINIMUS_INPUT_HPP
