#include <GL\glut.h>

void init()
{
    glClearColor(0.560784, 0.560784, 0.737255, 0.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glShadeModel(GL_SMOOTH);

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.2, 0.4);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.4, 0.3);

    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.7, 0.0);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.4, -0.3);

    glEnd();

    glFlush();
}

int main(int argc, char *argv[])
{
    //glutInitWindowPosition(200,0);
    glutInitWindowSize(400, 400);
    glutInitDisplayMode(GLUT_RGB);
    glutInit(&argc, argv);

    glutCreateWindow("Okno OpenGL");

    init();
    glutDisplayFunc(display);


    glutMainLoop();
    return 0;
}
