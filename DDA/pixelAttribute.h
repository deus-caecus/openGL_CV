#pragma once
#include<GL/glew.h>
#include<GLFW/glfw3.h>

struct COLOR
{
	int R, G, B;
	COLOR();
	COLOR(int R, int G, int B);
};

typedef struct point
{
	int x, y;
	COLOR color;
	point();
	point(int x, int y);
	point(int x, int y, COLOR color);
}Seed, Point;




