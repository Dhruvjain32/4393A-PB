
#include "api.h"
void moveStraight(float length, int timeout, lemlib::MoveToPointParams params);


// Define Scoring Methods
void scoreFront();
void scoreBack();
void scoreLow();
void heightHigh();
void heightMiddle();
void motorStore();
void stopScore();

// Define Autonomous Routes
void testDrive();
void testTurn();
void blueSAWP();
void blueLeft();
void blueRight();
void redSAWP();
void redLeft();
void redRight();
void skills();