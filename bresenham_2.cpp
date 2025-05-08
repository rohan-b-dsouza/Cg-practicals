#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

#define WIDTH  640
#define HEIGHT 480

// Global state
int xi = 0, yi = 0;    // Center of circle (set by click)
int r = 0;            // Radius (read once at startup)
int choice = 1;       // Color choice from menu
bool drawNow = false; // Flag to trigger drawing in display()

// Plot a single point in a color based on `choice`
void setpixel(int x, int y) {
    switch (choice) {
        case 1: glColor3f(1,0,0); break; // red
        case 2: glColor3f(0,0,0); break; // black
        case 3: glColor3f(1,1,0); break; // yellow
        case 4: glColor3f(0.4,0.9,0.2); break; // green
        case 5: glColor3f(0,0,1); break; // blue
    }
    glBegin(GL_POINTS);
      glVertex2i(x, y);
    glEnd();
}

// Draw coordinate axes through (0,0)
void drawAxes() {
    glColor3f(0.2f,0.2f,0.2f);
    glBegin(GL_LINES);
      glVertex2i(-WIDTH/2, 0);  glVertex2i( WIDTH/2, 0);
      glVertex2i(0, -HEIGHT/2); glVertex2i(0,  HEIGHT/2);
    glEnd();
}

// Bresenham’s circle with 8-way symmetry around (xi, yi)
void drawBresCircle() {
    int x = 0, y = r;
    int p = 3 - 2*r;
    while (x <= y) {
        setpixel(xi + x, yi + y);
        setpixel(xi - x, yi + y);
        setpixel(xi + x, yi - y);
        setpixel(xi - x, yi - y);
        setpixel(xi + y, yi + x);
        setpixel(xi - y, yi + x);
        setpixel(xi + y, yi - x);
        setpixel(xi - y, yi - x);

        if (p < 0) {
            p += 4*x + 6;
        } else {
            p += 4*(x - y) + 10;
            --y;
        }
        ++x;
    }
}

// Display callback: draws axes, and circle if requested
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    if (drawNow) {
        glPointSize(3.0f);
        drawBresCircle();
        drawNow = false;
    }
    glFlush();
}

// Mouse click to set circle center
void mouse(int button, int state, int mx, int my) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        xi = mx - WIDTH/2;
        yi = (HEIGHT - my) - HEIGHT/2;
        drawNow = false;           // Clear previous circle until menu selection
        glutPostRedisplay();
    }
}

// Menu callback: pick color & draw, or exit
void menu(int item) {
    if (item >= 1 && item <= 5) {
        choice = item;
        drawNow = true;
        glutPostRedisplay();
    }
    else if (item == 6) {
        exit(0);
    }
}

int main(int argc, char** argv) {
    // Read radius once before GLUT loop
    cout << "Enter circle radius: ";
    cin  >> r;
    if (r <= 0) return 0;

    glutInit(&argc, argv);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Circle - All Quadrants");

    // Set coordinate system so origin is window center
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-WIDTH/2, WIDTH/2, -HEIGHT/2, HEIGHT/2);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
    glPointSize(3.0f);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    // Middle-click menu: colors 1–5, then exit as 6
    glutCreateMenu(menu);
    glutAddMenuEntry("Draw Red Circle",    1);
    glutAddMenuEntry("Draw Black Circle",  2);
    glutAddMenuEntry("Draw Yellow Circle", 3);
    glutAddMenuEntry("Draw Green Circle",  4);
    glutAddMenuEntry("Draw Blue Circle",   5);
    glutAddMenuEntry("EXIT",               6);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);

    glutMainLoop();
    return 0;
}
