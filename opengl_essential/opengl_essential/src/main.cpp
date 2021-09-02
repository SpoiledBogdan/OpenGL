#define GLEW_STATIC
#define M_PI       3.14159265358979323846

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <gl/gl.h>
#include <Windows.h>
#include <math.h>
#include <iostream>


float vert[] = { 1,1,0,  1,-1,0,  -1,-1,0,  -1,1,0 };  

float xAlpha = 20;  
float zAlpha = 0;
POINTFLOAT pos = { 0,0 };

void ShowWorld()
{
    glEnableClientState(GL_VERTEX_ARRAY);  
    glVertexPointer(3, GL_FLOAT, 0, &vert);  
    for (int i = -10; i < 10; i++)
        for (int j = -10; j < 10; j++) {
            glPushMatrix();
            if ((i + j) % 2 == 0) glColor3f(0.0f, 0.5f, 0.0f);
            else glColor3f(1, 1, 1);
            glTranslatef(i * 2, j * 2, 0);
            glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
            glPopMatrix();
        }
    glColor3f(0.5f, 0.0f, 0.0f);  
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);  
    glDisableClientState(GL_VERTEX_ARRAY);  
}


void MoveCamera() {
    if (GetKeyState(VK_UP) < 0) xAlpha = ++xAlpha > 180 ? 180 : xAlpha; 
    if (GetKeyState(VK_DOWN) < 0) xAlpha = --xAlpha < 0 ? 0 : xAlpha;

    if (GetKeyState(VK_LEFT) < 0) zAlpha++;
    if (GetKeyState(VK_RIGHT) < 0) zAlpha--;

    float ugol = -zAlpha / 180 * M_PI;
    float speed = 0;
    if (GetKeyState('W') < 0) speed = 0.1;
    if (GetKeyState('S') < 0) speed = -0.1;
    if (GetKeyState('A') < 0) { speed = 0.1; ugol -= M_PI * 0.5; }
    if (GetKeyState('D') < 0) { speed = 0.1; ugol += M_PI * 0.5; }
    if (speed != 0) {
        pos.x += sin(ugol) * speed;
        pos.y += cos(ugol) * speed;
    }

    glRotatef(-xAlpha, 1, 0, 0);  
    glRotatef(-zAlpha, 0, 0, 1);
    glTranslatef(-pos.x, -pos.y, -3); 
}

int main(void)
{
    GLFWwindow* window;
    GLfloat rtriangle = 2;

   
   

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(600, 600, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cout << "Error" << std::endl;
    }

    srand(time(NULL));
    int Seed = rand();

    glFrustum(-1,1, -1,1, 2,80);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);
  
        glPushMatrix();
        MoveCamera();
        ShowWorld();
        glPopMatrix();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
     
        /* Poll for and process events */
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}