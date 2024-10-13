#ifndef QUADRATUREENCODER_H
#define QUADRATUREENCODER_H

#include <Arduino.h>

class QuadratureEncoder {
public:
    QuadratureEncoder(uint8_t* pinsA, uint8_t* pinsB, uint8_t count);
    void begin();
    long getPosition(uint8_t index);
    void setPosition(uint8_t index, long position);
    void reset(uint8_t index);
    int getDirection(uint8_t index);

private:
    uint8_t* pinsA;
    uint8_t* pinsB;
    uint8_t count;
    volatile long* positions;  
    volatile int* directions;
    volatile uint8_t* lastStates;

    int8_t* lookupTable;

    void update(uint8_t index);
    static void handleInterruptA0();
    static void handleInterruptA1();
    static void handleInterruptA2();
    static void handleInterruptA3();
    
    static void handleInterruptB0();
    static void handleInterruptB1();
    static void handleInterruptB2();
    static void handleInterruptB3();

    static QuadratureEncoder* instances[4]; // Array of encoder instances
};

#endif
