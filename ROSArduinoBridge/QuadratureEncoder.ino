#include "QuadratureEncoder.h"

// Static array of instances
QuadratureEncoder* QuadratureEncoder::instances[4] = {nullptr, nullptr, nullptr, nullptr};

QuadratureEncoder::QuadratureEncoder(uint8_t* pinsA, uint8_t* pinsB, uint8_t count)
    : pinsA(pinsA), pinsB(pinsB), count(count) {
    positions = new volatile long[count]();
    directions = new volatile int[count]();
    lastStates = new volatile uint8_t[count]();
    lookupTable = new int8_t[16]{
        0, -1, 1, 0,
        1, 0, 0, -1,
        -1, 0, 0, 1,
        0, 1, -1, 0
    };

    // Assign the current instance to the static array
    for (uint8_t i = 0; i < count; i++) {
        instances[i] = this;
    }
}

void QuadratureEncoder::begin() {
    for (uint8_t i = 0; i < count; i++) {
        pinMode(pinsA[i], INPUT);
        pinMode(pinsB[i], INPUT);
        
        lastStates[i] = (digitalRead(pinsA[i]) << 1) | digitalRead(pinsB[i]);  // Initial state of both pins

        // Attach interrupts to the pins, use static ISR functions
        if (i == 0) {
            attachInterrupt(digitalPinToInterrupt(pinsA[0]), handleInterruptA0, CHANGE);
            attachInterrupt(digitalPinToInterrupt(pinsB[0]), handleInterruptB0, CHANGE);
        } else if (i == 1) {
            attachInterrupt(digitalPinToInterrupt(pinsA[1]), handleInterruptA1, CHANGE);
            attachInterrupt(digitalPinToInterrupt(pinsB[1]), handleInterruptB1, CHANGE);
        } else if (i == 2) {
            attachInterrupt(digitalPinToInterrupt(pinsA[2]), handleInterruptA2, CHANGE);
            attachInterrupt(digitalPinToInterrupt(pinsB[2]), handleInterruptB2, CHANGE);
        } else if (i == 3) {
            attachInterrupt(digitalPinToInterrupt(pinsA[3]), handleInterruptA3, CHANGE);
            attachInterrupt(digitalPinToInterrupt(pinsB[3]), handleInterruptB3, CHANGE);
        }
    }
}

void QuadratureEncoder::update(uint8_t index) {
    uint8_t currentState = (digitalRead(pinsA[index]) << 1) | digitalRead(pinsB[index]);
    int8_t movement = lookupTable[(lastStates[index] << 2) | currentState];

    if (movement != 0) {
        // Critical section
        noInterrupts();
        positions[index] += movement;
        directions[index] = movement;
        interrupts();
    }
    lastStates[index] = currentState;
}

long QuadratureEncoder::getPosition(uint8_t index) {
    return positions[index];
}

void QuadratureEncoder::setPosition(uint8_t index, long newPosition) {
    positions[index] = newPosition;
}

void QuadratureEncoder::reset(uint8_t index) {
    positions[index] = 0;
}

int QuadratureEncoder::getDirection(uint8_t index) {
    return directions[index];
}

// Static ISR Implementations
void QuadratureEncoder::handleInterruptA0() { if (instances[0]) instances[0]->update(0); }
void QuadratureEncoder::handleInterruptA1() { if (instances[1]) instances[1]->update(1); }
void QuadratureEncoder::handleInterruptA2() { if (instances[2]) instances[2]->update(2); }
void QuadratureEncoder::handleInterruptA3() { if (instances[3]) instances[3]->update(3); }

void QuadratureEncoder::handleInterruptB0() { if (instances[0]) instances[0]->update(0); }
void QuadratureEncoder::handleInterruptB1() { if (instances[1]) instances[1]->update(1); }
void QuadratureEncoder::handleInterruptB2() { if (instances[2]) instances[2]->update(2); }
void QuadratureEncoder::handleInterruptB3() { if (instances[3]) instances[3]->update(3); }
