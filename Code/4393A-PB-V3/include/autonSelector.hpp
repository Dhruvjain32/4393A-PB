#pragma once

#include <string>

enum class Auton {
    redLeft,
    redRight,
    redSAWP,
    blueLeft,
    blueRight,
    blueSAWP,
    testTurn,
    testDrive,
    skills
};

std::string getAutonName(Auton mode);

extern Auton selectedAuton;
std::string getLeftDTTemp();
std::string getRightDTTemp();
void displaySelection();

void on_left_button();
void on_center_button();
void on_right_button();