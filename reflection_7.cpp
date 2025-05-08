#include <iostream>
#include <GL/glut.h>
using namespace std;

int m[20][3], n = 0;

// Plot a point in blue
void setpixel(int x, int y) {
    glColor3f(0,0,1);
    glBegin(GL_POINTS); glVertex2i(x,y); glEnd();
    glFlush();
}

// Draw axes
void choice() {
    glPointSize(2);
    for(int i=-350;i<=350;i++){
        setpixel(i,0);
        setpixel(0,i);
    }
}

// Draw polygon edge
void conect(int x,int y,int px,int py){
    glColor3f(1,0,0);
    glBegin(GL_LINE_STRIP);
      glVertex2i(x,y);
      glVertex2i(px,py);
    glEnd(); glFlush();
}

// Translation
void translation(int tx,int ty){
    for(int i=0;i<n;i++){
        m[i][0]+=tx;
        m[i][1]+=ty;
    }
    glColor3f(1,1,0);
    for(int i=0;i<n;i++){
        conect(m[i][0],m[i][1], m[(i+1)%n][0], m[(i+1)%n][1]);
    }
}

// Reflection about X or Y axis
void reflect(char axis){
    for(int i=0;i<n;i++){
        if(axis=='X'||axis=='x') m[i][1] = -m[i][1];
        else                    m[i][0] = -m[i][0];
    }
    glColor3f(1,1,0);
    for(int i=0;i<n;i++){
        conect(m[i][0],m[i][1], m[(i+1)%n][0], m[(i+1)%n][1]);
    }
}

void init(){
    glClearColor(0,0,0,0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-350,350,-350,350);
    glClear(GL_COLOR_BUFFER_BIT);
}

void mouse(int b,int s,int x,int y){
    if(s==GLUT_DOWN && b==GLUT_LEFT_BUTTON){
        int cx = x-350, cy = 350-y;
        m[n][0]=cx; m[n][1]=cy; m[n][2]=1; n++;
        if(n>1) conect(m[n-2][0],m[n-2][1], m[n-1][0],m[n-1][1]);
    }
}

void menu(int c){
    if(c==1) choice();
    else if(c==2){
        int tx,ty; cout<<"tx ty? ";cin>>tx>>ty;
        translation(tx,ty);
    }
    else if(c==3){
        char ax; cout<<"Axis (X/Y)? ";cin>>ax;
        reflect(ax);
    }
    else exit(0);
}

int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitWindowSize(700,700);
    glutCreateWindow("Translate + Reflect");
    init();
    glutDisplayFunc(choice);
    glutMouseFunc(mouse);
    glutCreateMenu(menu);
      glutAddMenuEntry("Show Axes",1);
      glutAddMenuEntry("Translate",2);
      glutAddMenuEntry("Reflect",3);
      glutAddMenuEntry("Exit",4);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutMainLoop();
    return 0;
}
