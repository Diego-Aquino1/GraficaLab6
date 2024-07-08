#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

struct Casa {
    int x;
    int y;
    int altura;
    int ancho;
    float color[3];
};

struct Carro {
    int x;
    int y;
    int largo;
    int alto;
    float color[3];
};

void drawRectangle(int x, int y, int width, int height, float color[3]) {
    glColor3fv(color);
    glBegin(GL_POLYGON);
    glVertex2i(x, y);
    glVertex2i(x + width, y);
    glVertex2i(x + width, y + height);
    glVertex2i(x, y + height);
    glEnd();
}

void drawTriangle(int x, int y, int width, int height, float color[3]) {
    glColor3fv(color);
    glBegin(GL_POLYGON);
    glVertex2i(x, y);
    glVertex2i(x + width / 2, y + height);
    glVertex2i(x + width, y);
    glEnd();
}

void crearCasa(Casa& C) {
    drawRectangle(C.x, C.y, C.ancho, C.altura, C.color);
    float roofColor[3] = {0.5, 0.25, 0.0}; // Color del techo
    drawTriangle(C.x, C.y + C.altura, C.ancho, C.altura / 2, roofColor);
}

void crearCarro(Carro& C) {
    drawRectangle(C.x, C.y, C.largo, C.alto, C.color);
    float wheelColor[3] = {0.0, 0.0, 0.0}; // Color de las ruedas
    drawRectangle(C.x + C.largo / 8, C.y - C.alto / 4, C.largo / 4, C.alto / 4, wheelColor);
    drawRectangle(C.x + 5 * C.largo / 8, C.y - C.alto / 4, C.largo / 4, C.alto / 4, wheelColor);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    Casa miCasa = {100, 100, 100, 200, {0.5, 0.35, 0.05}};
    crearCasa(miCasa);

    Carro miCarro = {300, 100, 100, 50, {0.0, 0.0, 1.0}};
    crearCarro(miCarro);

    glfwSwapBuffers(glfwGetCurrentContext());
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}

int main() {
    if (!glfwInit()) {
        std::cerr << "Error initializing GLFW" << std::endl;
        return -1;
    }

    GLFWwindow* window = glfwCreateWindow(640, 480, "Casa y Carro", NULL, NULL);
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

