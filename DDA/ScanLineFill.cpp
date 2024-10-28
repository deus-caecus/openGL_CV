#include"pixelTool.h"

unsigned char* framebuffer;
int width = 800;
int height = 600;

void initFramebuffer() {
    framebuffer = new unsigned char[width * height * 3];
    for (int i = 0; i < width * height * 3; ++i) {
        framebuffer[i] = 255; // 白色背景
    }
}

void drawPixel(Point pt) 
{
    int index = (pt.y * width + pt.x) * 3;
    framebuffer[index] = pt.color.R;
    framebuffer[index + 1] = pt.color.G;
    framebuffer[index + 2] = pt.color.B;
}

COLOR getPixel(Point pt) {
    int index = (pt.y * width + pt.x) * 3;
    COLOR color;
    color.R = framebuffer[index];
    color.G = framebuffer[index + 1];
    color.B = framebuffer[index + 2];
    return color;
}

bool operator==(COLOR newColor, COLOR oldColor)
{
    return
        oldColor.R == newColor.R &&
        oldColor.G == newColor.G &&
        oldColor.B == newColor.B;
 }

int ScanLineFill(GLFWwindow* window, Seed seed, COLOR oldColor, COLOR newColor) {
    int xl, xr;
    bool spanNeedFill;
    std::stack<Point> stackPT;
    Point drawPT;
    stackPT.push(seed);

    while (!stackPT.empty()) {
        seed = stackPT.top();
        stackPT.pop();
        drawPT = seed;

        // 向右填充
        while (getPixel(drawPT) == oldColor) {
            drawPT.color = newColor;
            drawPixel(drawPT);
            drawPT.x++;
        }
        xr = drawPT.x - 1;

        // 向左填充
        drawPT = seed;
        drawPT.x--;
        while (getPixel(drawPT) == oldColor) {
            drawPT.color = newColor;
            drawPixel(drawPT);
            drawPT.x--;
        }
        xl = drawPT.x + 1;

        // 处理上方
        drawPT.x = xl;
        drawPT.y++;
        while (drawPT.x <= xr) {
            spanNeedFill = false;
            while (getPixel(drawPT) == oldColor) {
                spanNeedFill = true;
                drawPT.x++;
            }
            if (spanNeedFill) {
                Point newSeed(drawPT.x - 1, drawPT.y, newColor);
                stackPT.push(newSeed);
                spanNeedFill = false;
            }
            drawPT.x++;
        }

        // 处理下方
        drawPT.x = xl;
        drawPT.y -= 2;
        while (drawPT.x <= xr) {
            spanNeedFill = false;
            while (getPixel(drawPT) == oldColor) {
                spanNeedFill = true;
                drawPT.x++;
            }
            if (spanNeedFill) {
                Point newSeed(drawPT.x - 1, drawPT.y, newColor);
                stackPT.push(newSeed);
                spanNeedFill = false;
            }
            drawPT.x++;
        }
    }
    return 0;
}

int ScanLineFillMain() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, "OpenGL Scan Line Fill", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    initFramebuffer();

    // 画一个简单的多边形
    drawPixel(Point(100, 100, COLOR(0, 0, 0)));
    drawPixel(Point(200, 100, COLOR(0, 0, 0)));
    drawPixel(Point(150, 200, COLOR(0, 0, 0)));

    // 填充多边形
    COLOR oldColor = { 255, 255, 255 };
    COLOR newColor = { 0, 255, 0 }; // 绿色
    ScanLineFill(window, Point(150, 150, COLOR(0, 0, 0)), oldColor, newColor);

        // 将帧缓冲区数据绘制到屏幕上
        glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_BYTE, framebuffer);
        glfwSwapBuffers(window);
        glfwPollEvents();
    

    delete[] framebuffer;
    glfwTerminate();
    return 0;
}