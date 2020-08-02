#include <GL\glut.h>

void init()
{
    glClearColor(0.560784, 0.560784, 0.737255, 0.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINE_STRIP);
    glVertex2f(1.0, 0.0);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.1, 0.1);
    glEnd();

    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(3);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-0.9, 0.9);
    glVertex2f(-0.6, 0.1);
    glVertex2f(-0.1, 0.8);
    glEnd();    

    glColor3f(1.0, 1.0, 1.0);
    glPointSize(10);
    glBegin(GL_POINTS);
    glVertex2f(-0.9, 0.9);
    glVertex2f(-0.1, 0.8);
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
