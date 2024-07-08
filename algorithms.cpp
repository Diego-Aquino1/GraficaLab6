#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

// Estructura para almacenar un punto
struct Point {
    int x, y;
};

// Función para dibujar un punto
void drawPoint(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Algoritmo DDA para dibujar una línea
void DDA(int x1, int y1, int x2, int y2, const char* style) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = std::max(abs(dx), abs(dy));

    float Xinc = dx / (float) steps;
    float Yinc = dy / (float) steps;

    float X = x1;
    float Y = y1;

    for (int i = 0; i <= steps; i++) {
        if (strcmp(style, "solid") == 0 || 
           (strcmp(style, "dotted") == 0 && i % 2 == 0) ||
           (strcmp(style, "dashed") == 0 && i % 10 < 5)) {
            drawPoint(round(X), round(Y));
        }
        X += Xinc;
        Y += Yinc;
    }
}

// Algoritmo Bresenham para dibujar una línea
void Bresenham(int x1, int y1, int x2, int y2, const char* style) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx - dy;

    while (true) {
        if (strcmp(style, "solid") == 0 || 
           (strcmp(style, "dotted") == 0 && (x1 + y1) % 2 == 0) ||
           (strcmp(style, "dashed") == 0 && (x1 + y1) % 10 < 5)) {
            drawPoint(x1, y1);
        }
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    DDA(50, 50, 200, 200, "solid");
    DDA(50, 200, 200, 50, "dotted");
    DDA(50, 100, 200, 150, "dashed");

    Bresenham(300, 50, 450, 200, "solid");
    Bresenham(300, 200, 450, 50, "dotted");
    Bresenham(300, 100, 450, 150, "dashed");

    glfwSwapBuffers(glfwGetCurrentContext());
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Error initializing GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Líneas DDA y Bresenham", NULL, NULL);
    if (!window) {
        glfwTerminate();
        std::cerr << "Error creating GLFW window" << std::endl;
        return -1;
    }

    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error initializing GLEW" << std::endl;
        return -1;
    }

    init();

    while (!glfwWindowShouldClose(window)) {
        display();
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
