#include <GL/glut.h>
#include <math.h>

// Define the window dimensions
const GLint WIDTH = 800, HEIGHT = 600;

// Ball properties
float ballRadius = 0.1f;
float ballX = 0.0f, ballY = 0.0f;
float ballSpeedX = 0.005f, ballSpeedY = 0.005f;

// Function to initialize OpenGL
void initOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  // Set the clear color to black
    glEnable(GL_BLEND);                      // Enable blending for smooth rendering
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

// Function to draw a circle (ball)
void drawBall() {
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 0.0f, 0.0f);  // Red color

    // Draw the circle (ball)
    for (int i = 0; i <= 360; i++) {
        float angle = i * 3.14159f / 180.0f;  // Convert degree to radian
        float x = ballX + ballRadius * cos(angle);
        float y = ballY + ballRadius * sin(angle);
        glVertex2f(x, y);
    }

    glEnd();
}

// Function to handle ball movement and bouncing
void updateBallPosition() {
    ballX += ballSpeedX;
    ballY += ballSpeedY;

    // Check if the ball hits the left or right wall
    if (ballX + ballRadius > 1.0f || ballX - ballRadius < -1.0f) {
        ballSpeedX = -ballSpeedX;  // Reverse the horizontal direction
    }

    // Check if the ball hits the top or bottom wall
    if (ballY + ballRadius > 1.0f || ballY - ballRadius < -1.0f) {
        ballSpeedY = -ballSpeedY;  // Reverse the vertical direction
    }
}

// Display function for OpenGL rendering
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the color buffer

    // Update ball position
    updateBallPosition();

    // Draw the ball
    drawBall();

    // Swap buffers (render to the screen)
    glutSwapBuffers();
}

// Timer function to control the frame rate
void timer(int value) {
    glutPostRedisplay(); // Redraw the scene
    glutTimerFunc(16, timer, 0); // Call the timer function every 16 milliseconds (~60 FPS)
}

// Reshape function to handle window resizing
void reshape(int w, int h) {
    glViewport(0, 0, w, h);  // Set the viewport to match the window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // Set 2D orthographic projection
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Double buffering and RGB color mode
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Bouncing Ball");

    // Initialize OpenGL settings
    initOpenGL();

    // Register GLUT callbacks
    glutDisplayFunc(display); // Display callback
    glutReshapeFunc(reshape); // Reshape callback
    glutTimerFunc(25, timer, 0); // Start the timer callback (for controlling the frame rate)

    // Enter the GLUT main loop
    glutMainLoop();

    return 0;
}
