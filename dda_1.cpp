#include<GL/glut.h>
#include<GL/glu.h>
#include<iostream>
#include<math.h>
#define h 700
#define w 700

using namespace std;

GLint xi, xii, yi, yii;

void setpixel(GLint x, GLint y)
{
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
    glFlush();
}

void initialize()
{
    glClearColor(0.6, 0.6, 0.6, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-w / 2, w / 2, -h / 2, h / 2);
}

void choice()
{
    int i;
    glPointSize(2.0);
    for (i = -w; i < w; i++)
    {
        setpixel(0, i);
        setpixel(i, 0);
    }
}

class line
{
public:
    void dda(int item)
    {
        GLfloat dx, dy, step, x, y;
        GLfloat xinc, yinc;
        int i;
        dx = xii - xi;
        dy = yii - yi;
        if (abs(dx) >= abs(dy))
            step = abs(dx);
        else
            step = abs(dy);
        xinc = (float)dx / step;
        yinc = (float)dy / step;

        x = xi;
        y = yi;

        setpixel(x, y);
        for (i = 1; i <= step; i++)
        {
            x = x + xinc;
            y = y + yinc;

            xi = x + 0.5;
            yi = y + 0.5;
            if (item == 1)
            {
                setpixel(xi, yi);
            }
            if (item == 2)
            {
                if (i % 10 < 5)
                {
                    setpixel(xi, yi);
                }
            }
            if (item == 3)
            {
                if (i % 9 >= 2 && i % 9 != 7)
                {
                    setpixel(xi, yi);
                }
            }
            if (item == 4)
            {
                glPointSize(4.0);
                setpixel(xi, yi);
            }
        }
    }
};

line l;

void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        if (button == GLUT_LEFT_BUTTON)
        {
            xi = x - 350;
            yi = 350 - y;
            glPointSize(2.0);
            glBegin(GL_POINTS);
            glVertex2i(xi, yi);
            glEnd();
            glFlush();
        }
        if (button == GLUT_RIGHT_BUTTON)
        {
            xii = x - 350;
            yii = 350 - y;
            glPointSize(2.0);
            glBegin(GL_POINTS);
            glVertex2i(xii, yii);
            glEnd();
            glFlush();
        }
    }
}

void menu(int item)
{
    if (item == 1)
    {
        l.dda(1);
    }
    if (item == 2)
    {
        l.dda(2);
    }
    if (item == 3)
    {
        l.dda(3);
    }
    if (item == 4)
    {
        l.dda(4);
    }
    if (item == 9)
    {
        exit(0);
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(h, w);
    glutInitWindowPosition(100, 0);
    glutCreateWindow("DDA Line Drawing");
    initialize();
    glutDisplayFunc(choice);
    glutMouseFunc(mouse);
    glutCreateMenu(menu);
    glutAddMenuEntry("DDA_SIMPLE", 1);
    glutAddMenuEntry("DDA_DASH", 2);
    glutAddMenuEntry("DDA_DASH DOT", 3);
    glutAddMenuEntry("DDA_THICK", 4);
    glutAddMenuEntry("EXIT", 9);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
    glutMainLoop();
    return 0;
}
