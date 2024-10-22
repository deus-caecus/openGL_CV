#pragma once
#include "pixelAttribute.h"
#include <stack>

COLOR getPixel(Point pt);

bool operator==(COLOR color1, COLOR color2);

int drawPixel(Point point);

void drawPointMouseClick(GLFWwindow* window,COLOR color);

