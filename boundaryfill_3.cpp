#include <GL/glut.h>
#include <iostream>
#include <math.h>
using namespace std;

void myInit(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(1.0);
    glLineWidth(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 500, 0, 500);
}

void display(void) {}

struct COLOR { float r, b, g; };

class polygon_fill
{
    int compare_color(COLOR a, COLOR b)
    {
        return (a.r==b.r && a.b==b.b && a.g==b.g);
    }
    void draw(int x, int y, COLOR c)
    {
        glColor3f(c.r, c.b, c.g);
        glBegin(GL_POINTS);
          glVertex2f(x, y);
        glEnd();
        glFlush();
    }
    COLOR getpixelcolor(int x, int y)
    {
        COLOR c;
        glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, &c);
        return c;
    }

  public:
    void bound_fill(int x, int y, COLOR fill, COLOR border_col)
    {
        COLOR color = getpixelcolor(x, y);
        if (!compare_color(color, border_col) && !compare_color(color, fill))
        {
            draw(x, y, fill);
            bound_fill(x+1, y,   fill, border_col);
            bound_fill(x,   y+1, fill, border_col);
            bound_fill(x-1, y,   fill, border_col);
            bound_fill(x,   y-1, fill, border_col);
            bound_fill(x-1, y-1, fill, border_col);
            bound_fill(x-1, y+1, fill, border_col);
            bound_fill(x+1, y-1, fill, border_col);
            bound_fill(x+1, y+1, fill, border_col);
        }
    }
};

int xc, yc, i = 0;
int xarr[100], yarr[100];

void menu(int value)
{
    polygon_fill p;
    COLOR fill    = { 0.0f, 0.0f, 1.0f };  // blue fill
    COLOR bcol    = { 1.0f, 0.0f, 0.0f };  // red border
    COLOR backcol = { 0.0f, 0.0f, 0.0f };  // background

    switch (value)
    {
      case 1:
        p.bound_fill(xc, 500-yc, fill, bcol);
        cout << "COMPLETED BOUNDARY FILL\n";
        break;
      case 2:
        glClear(GL_COLOR_BUFFER_BIT);
        i = 0;
        cout << "SCREEN CLEARED\n";
        break;
    }
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) exit(0);
}

void mouse(int button, int state, int x, int y)
{
    if (state != GLUT_DOWN) return;
    if (button == GLUT_LEFT_BUTTON)
    {
        xarr[i] = x; yarr[i] = y; i++;
        if (i > 1)
        {
            glColor3f(1,0,0);
            glBegin(GL_LINE_STRIP);
              glVertex2i(xarr[i-2], 500-yarr[i-2]);
              glVertex2i(xarr[i-1], 500-yarr[i-1]);
            glEnd();
            glFlush();
        }
    }
    else if (button == GLUT_RIGHT_BUTTON)
    {
        xc = x; yc = y;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Boundary Fill");
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);

    glutCreateMenu(menu);
    glutAddMenuEntry("BOUNDARY FILL", 1);
    glutAddMenuEntry("CLEAR SCREEN", 2);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);

    cout<<"1: Left-click to draw polygon\n";
    cout<<"2: Right-click to set seed\n";
    cout<<"3: Middle-click menu\n";

    myInit();
    glutMainLoop();
    return 0;
}
