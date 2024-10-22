#include "pixelTool.h"
#include<iostream>

static int ScanLineFill(GLFWwindow* window,Seed seed, COLOR oldColor, COLOR newColor)
{
	int xl, xr;
	bool spanNeedFill;
	std::stack<Point> stackPT;
	Point drawPT;
	stackPT.push(seed);

	


	while (!stackPT.empty())
	{
		seed = stackPT.top();
		stackPT.pop();
		drawPT = seed;
		while (getPixel(drawPT) == oldColor)
		{
			drawPT.color = newColor;
			drawPixel(drawPT);
			drawPT.x++;
		}
		xr = drawPT.x - 1;
		drawPT = seed;
		drawPT.x--;
		while (getPixel(drawPT) == oldColor)
		{
			drawPT.color = newColor;
			drawPixel(drawPT);
			drawPT.x--;
		}
		xl = drawPT.x + 1;

		drawPT.x = xl;
		drawPT.y++;

		while (drawPT.x <= xr)
		{
			spanNeedFill = false;
			while (getPixel(drawPT) == oldColor)
			{
				spanNeedFill = true;
				drawPT.x++;
			}
			if (spanNeedFill)
			{
				seed.x = drawPT.x - 1;
				seed.y = drawPT.y ;
				stackPT.push(seed);
				spanNeedFill = false;
			}
			drawPT.x++;
		}
		drawPT.x = xl;
		drawPT.y -= 2;
		while (drawPT.x <= xr)
		{
			spanNeedFill = false;
			while (getPixel(drawPT) == oldColor)
			{
				spanNeedFill = true;
				drawPT.x++;
			}
			if (spanNeedFill)
			{
				seed.x = drawPT.x - 1;
				seed.y = drawPT.y;
				stackPT.push(seed);
				spanNeedFill = false;
			}
			drawPT.x++;
		}
	}
	glfwSwapBuffers(window);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
	}
	
}

int main()
{
	std::cout << "mainAreaFill" << std::endl;

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	GLFWwindow* window = glfwCreateWindow(800, 600, "DDA Line Drawing", nullptr, nullptr);
	if (!window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (err != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(err) << std::endl;
		return -1;
	}

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPointSize(3.0f);

	COLOR oldColor(0, 255, 255);

	glBegin(GL_POLYGON);
	while (glfwGetKey(window,GLFW_KEY_ESCAPE)!=GLFW_PRESS) {

		glfwPollEvents();
		drawPointMouseClick(window,oldColor);

	}
	glEnd();

	ScanLineFill(window, );
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}


