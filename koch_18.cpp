#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

struct Point { float x, y; };

static Point pts[2];
static int clickCount = 0;

// Draw X/Y axes
void drawAxes() {
    glColor3f(0.4f, 0.4f, 0.4f);
    glBegin(GL_LINES);
      glVertex2i(-300, 0); glVertex2i(300, 0);
      glVertex2i(0, -300); glVertex2i(0, 300);
    glEnd();
}

// Plot a single point
void plotPoint(const Point &p) {
    glColor3f(1, 0, 0);
    glPointSize(6.0f);
    glBegin(GL_POINTS);
      glVertex2f(p.x, p.y);
    glEnd();
}

// Draw line segment
void drawLine(const Point &a, const Point &b) {
    glColor3f(1, 1, 1);
    glBegin(GL_LINES);
      glVertex2f(a.x, a.y);
      glVertex2f(b.x, b.y);
    glEnd();
}

// Recursive Koch
void drawKoch(const Point &a, const Point &b, int depth) {
    if (depth == 0) {
        glColor3f(0, 1, 1);
        glBegin(GL_LINES);
          glVertex2f(a.x, a.y);
          glVertex2f(b.x, b.y);
        glEnd();
        return;
    }
    Point p1{(2*a.x + b.x)/3, (2*a.y + b.y)/3};
    Point p2{(a.x + 2*b.x)/3, (a.y + 2*b.y)/3};
    float dx = p2.x - p1.x, dy = p2.y - p1.y;
    Point p3{p1.x + 0.5f*dx - sqrtf(3)/2*dy,
             p1.y + 0.5f*dy + sqrtf(3)/2*dx};

    drawKoch(a,  p1, depth-1);
    drawKoch(p1, p3, depth-1);
    drawKoch(p3, p2, depth-1);
    drawKoch(p2, b,  depth-1);
}

// Redisplay everything
void redisplay() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    if (clickCount > 0) plotPoint(pts[0]);
    if (clickCount > 1) {
        plotPoint(pts[1]);
        drawLine(pts[0], pts[1]);
    }
    glFlush();
}

// Handle left-click to collect two points
void onMouse(int button, int state, int x, int y) {
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN && clickCount<2) {
        pts[clickCount] = {float(x-300), float(300-y)};
        ++clickCount;
        redisplay();
    }
}

// Menu selection
void onMenu(int choice) {
    if (choice == 1) {
        if (clickCount<2) {
            cout << "Click two points first.\n";
            return;
        }
        int depth;
        cout << "Enter recursion depth: ";
        cin  >> depth;
        drawKoch(pts[0], pts[1], depth);
        glFlush();
    }
    else if (choice == 2) {
        clickCount = 0;
        redisplay();
    }
    else {
        exit(0);
    }
}

// Initialization
void init() {
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-300,300,-300,300);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(200,100);
    glutCreateWindow("Interactive Koch Curve");

    init();
    glutDisplayFunc(redisplay);  // register display callback
    glutMouseFunc(onMouse);

    glutCreateMenu(onMenu);
    glutAddMenuEntry("Draw Koch Curve", 1);
    glutAddMenuEntry("Clear Screen",     2);
    glutAddMenuEntry("Exit",             3);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}
