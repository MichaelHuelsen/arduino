#ifndef _SEVEN_SEGMENT_H_
#define _SEVEN_SEGMENT_H_

void turnOffDisplay();
void toggleDot();
void displayDigit(byte digit);
void initSevenSegment(
    int a,
    int b,
    int c,
    int d,
    int e,
    int f,
    int g,
    int dot);

#include "seven-segment.cpp"

#endif