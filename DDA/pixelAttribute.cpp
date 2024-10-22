#include"pixelAttribute.h"
COLOR::COLOR() {}

COLOR::COLOR(int R, int G, int B) 
{
	this->R = R;
	this->G = G;
	this->B = B;
}

point::point() {}

point::point(int x, int y)
{
	this->x = x;
	this->y = y;
	color = COLOR();
}

point::point(int x, int y, COLOR color)
{
	this->x = x;
	this->y = y;
	this->color = color;
}
