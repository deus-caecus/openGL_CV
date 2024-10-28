#include"pixelTool.h"

int DDALine(int x0, int y0, int x1, int y1, COLOR color)
{
	int x;
	float dx, dy, y, k;
	dx = x1 - x0;
	dy = y1 - y0;
	if (fabs(dy) >fabs( dx))
	{
		//swap
		std::swap(x0, y0);
		std::swap(x1, y1);
		std::swap(dx, dy);
	}
	k = dy / dx;
	y = y0;

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return -1;
	}
	GLFWwindow* window = glfwCreateWindow(800, 600, "DDA", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		return -1;
	}
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPointSize(3.0f);

	glClear(GL_COLOR_BUFFER_BIT);
	
	for (x = x0; x <= x1; x++, y += k)
	{
		glBegin(GL_POINTS);
		std::cout << "x: " << x << " y: " << y << std::endl;
		glColor3i(color.R, color.G, color.B);
		glVertex2i(x, int(y + 0.5));
		glEnd();
	}
	
	glfwSwapBuffers(window);

	
	while (!glfwWindowShouldClose(window))
	{			
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}

int DDALineMain()
{
	
	int x1, y1,x2,y2;
	std::cout << "point P1:x1 y1" << std::endl;
	std::cin >> x1 >> y1;
	std::cout << "point P2:x2 y2" << std::endl;
	std::cin >> x2 >> y2;
	
	COLOR color(0,128 ,255 );
	
	DDALine(x1,y1 ,x2,y2 , color);
	return 0;
}