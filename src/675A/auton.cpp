#include "main.h"

using namespace pros;

void testMovePID(){
    chassis.moveTo(0, 10, 5000); //increment of x changes y for some reason, x doesnt change
}

void testTurnPID(){
    chassis.turnTo(30, 0, 5000);
}