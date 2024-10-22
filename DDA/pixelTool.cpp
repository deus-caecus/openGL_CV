#include"pixelTool.h"

COLOR getPixel(Point pt)
{
	COLOR colorPT(pt.color.R, pt.color.G, pt.color.B);
	return colorPT;
}

bool operator==(COLOR color1, COLOR color2)
{
	return
		color1.R == color2.R &&
		color1.G == color2.G &&
		color1.B == color2.B;
}

int drawPixel(Point point)
{
	glBegin(GL_POINT);
	glVertex2i(point.x, point.y);
	glColor3i(point.color.R, point.color.G, point.color.B);
	glEnd();
	return 0;
}

void drawPointMouseClick(GLFWwindow* window,COLOR oldColor) {
	if (glfwGetKey(window,GLFW_MOUSE_BUTTON_LEFT)  == GLFW_PRESS) {
		// 获取鼠标的窗口坐标
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		// 将窗口坐标转换为 OpenGL 坐标
		float xOpenGL = (xpos / width) * 2.0f - 1.0f;
		float yOpenGL = 1.0f - (ypos / height) * 2.0f;
		Point point(xOpenGL, yOpenGL,oldColor);
		glVertex2i(point.x, point.y);
		glColor3i(point.color.R, point.color.G, point.color.B);
	}
}

