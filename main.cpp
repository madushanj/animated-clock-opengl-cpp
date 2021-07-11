#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>
#include <windows.h>

using namespace std;

void drawcircle(double radius, float c1, float c2, float c3);
void drawtriangle(float c1, float c2, float c3, float lstart, float lend, float halfwidth, float angle);
void drawclockface();
void drawbox(float coord[8], float c1, float c2, float c3);
void drawboxwithangle(float c1, float c2, float c3, float lstart, float lend, float halfwidth, float angle);
void drawsecondhand(float angle);
void drawminutehand(float angle);
void drawhourhand(float angle);

int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit()) return -1;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(600, 600, "Clock v1.0 (CSC2020)", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window))
    {   
        //set background color
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.50f, 0.79f, 0.61f, 1.0f);

        int count = 0;
        int secondangle = 90;
        int minuteangle = 90;
        int mcount = 0;
        int hourangle = 30;
        while (true)
        {
            //draw clock face without handles
            drawclockface();
            
            drawhourhand(hourangle);
            drawminutehand(minuteangle);
            drawsecondhand(secondangle);

            if (count == 60) {
                minuteangle -= 6;
                count = 0;
                mcount++;
            }
            if (mcount == 5) {
                hourangle -= 6;
                mcount = 0;
            }
            secondangle-=6;

            //set back buffer to front
            glfwSwapBuffers(window);
            glfwPollEvents();
            count++;
            Sleep(1000);
        }
    }
    

    glfwTerminate();
    return 0;
}

void drawclockface()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.50f, 0.79f, 0.61f, 1.0f);
    drawcircle(0.8, 0.0, 0.0, 0.0);
    drawcircle(0.78, 1.0, 1.0, 1.0);

    //for hours indicators
    for (int i = 0; i < 12; i++) {
        drawboxwithangle(0.0, 0.0, 0.0, 0.7, 0.8, 0.01, 30 * i);
    }
    //for minutes indicators
    for (int i = 0; i < 60; i++) {
       drawboxwithangle(0.0, 0.0, 0.0, 0.75, 0.8, 0.01, 6*i);
    }
}

void drawcircle(double radius, float c1,float c2, float c3)
{
    glBegin(GL_POLYGON);
    glColor3f(c1, c2, c3);
    double ori_x = 0.0;
    double ori_y = 0.0;
    for (int i = 0; i <= 300; i++) {
        double angle = 2 * 3.14 * i / 300;
        double x = cos(angle) * radius;
        double y = sin(angle) * radius;
        glVertex2d(ori_x + x, ori_y + y);
    }
    glEnd();
}

void drawbox(float coord[8], float c1, float c2, float c3)
{
    glBegin(GL_QUADS);
    glColor3f(c1, c2, c3);
    glVertex2f(coord[0], coord[1]);
    glVertex2f(coord[2], coord[3]);
    glVertex2f(coord[4], coord[5]);
    glVertex2f(coord[6], coord[7]);
    glEnd();
}

void drawboxwithangle(float c1, float c2, float c3, float lstart, float lend, float halfwidth, float angle)
{
    angle = angle * 3.14 / 180;
    float box[8];
    float l1 = sqrt(lstart * lstart + halfwidth * halfwidth);
    float d1 = atan(halfwidth/lstart);
    float d2 = atan(halfwidth / lend);
    float l2 = sqrt(lend * lend + halfwidth * halfwidth);
    box[0] = l1 * cos(angle - d1);
    box[1] = l1 * sin(angle - d1);
    box[2] = l2 * cos(angle - d2);
    box[3] = l2 * sin(angle - d2);
    box[4] = l2 * cos(angle + d2);
    box[5] = l2 * sin(angle + d2);
    box[6] = l1 * cos(angle + d1);
    box[7] = l1 * sin(angle + d1);
    drawbox(box, c1, c2, c3);
}


void drawtriangle(float c1, float c2, float c3, float lstart, float l2, float halfwidth, float angle)
{
    angle = angle * 3.14 / 180;
    float l1 = sqrt(lstart * lstart + halfwidth * halfwidth);
    float d = atan(halfwidth / lstart);
    float x1 = l1 * cos(angle - d);
    float y1 = l1 * sin(angle - d);
    float x2 = l2 * cos(angle);
    float y2 = l2 * sin(angle);
    float x3 = l1 * cos(angle + d);
    float y3 = l1 * sin(angle + d);

    glBegin(GL_TRIANGLES);
    glColor3f(c1, c2, c3);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}

void drawsecondhand(float angle)
{
    drawboxwithangle(1.0, 0.0, 0.0, 0.0, 0.6, 0.01, angle);
    drawboxwithangle(1.0, 0.0, 0.0, 0.0, 0.15, 0.01, angle + 180);
    drawtriangle(1.0, 0.0, 0.0, 0.6, 0.69, 0.04, angle);
    drawcircle(0.05, 1.0, 0.0, 0.0);
}

void drawminutehand(float angle)
{
    drawboxwithangle(0.0, 0.0, 1.0, 0.0, 0.55, 0.02, angle);
    drawtriangle(0.0, 0.0, 1.0, 0.55, 0.6, 0.02, angle);
}

void drawhourhand(float angle)
{
    drawboxwithangle(0.0, 1.0, 0.0, 0.0, 0.4, 0.03, angle);
    drawtriangle(0.0, 1.0, 0.0, 0.4, 0.45, 0.03, angle);
}
