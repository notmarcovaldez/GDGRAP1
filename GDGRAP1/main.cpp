#include <GLFW/glfw3.h>
#include <math.h>
#include <iostream>


void rotatePoint(float points[3], float angle, float result[3]) {
    float pi = 2 * acos(0.0);
    // Convert angle from degrees to radians
    float radians = angle * pi / 180.0f;

    // Create rotation matrix
    float rotationMatrix[3][3] = {
        {cos(radians), -sin(radians), 0},
        {sin(radians),  cos(radians), 0},
        {0,             0,            1}
    };

    // Matrix multiplication
    for (int i = 0; i < 3; i++) {
        result[i] = 0;
        for (int j = 0; j < 3; j++) {
            result[i] += rotationMatrix[i][j] * points[j];
        }
    }
}

int main(void) {
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1000, 1000, "Marco Valdez", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
          
        // By default the shape fill the whole screen
        float scale = 0.5f; //Changes the overall size of the shape
        float offsetX = 0.0f; // Changes the position of the shape in X axis
        float offsetY = 0.5f; // Changes the position of the shape in the Y axis

        float shape = 8.0f; // Number of sides, only works for 3+
        float angle = 360.0f / shape; 
        float pi = 2 * acos(0.0);

        // makes use of trig with the given angle at the origin and the adjecent length of 1 because of opengls thing with a min of -1 and max of 1 to find the starting points for the first triangle 
        float point1x = (tan(angle / 2 * pi / 180)) * scale + offsetX; 
        float point2x = (-tan(angle / 2 * pi / 180)) * scale + offsetX;
        // starting triangle starts at the top of the screen
        float point1y = 1.0f * scale + offsetY;
        float point2y = 1.0f * scale + offsetY;

     
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        for (int i = 0; i < shape; i++) {
            // making sure the distance is the same
            //std::cout << "Distance: " << sqrt(pow((point1x - point2x),2) + pow((point1y - point2y), 2))<< std::endl;
            glBegin(GL_TRIANGLES);
            glVertex2f(point1x, point1y);
            glVertex2f(offsetX, offsetY); // middle point of shape
            glVertex2f(point2x, point2y);
            glEnd();

            // sets the first points to the second points
            point1x = point2x;
            point1y = point2y;

            // array of the second points for the rotation matrix
            float points[3] = { point2x - offsetX, point2y - offsetY, 1.0f };

            float result[3];
            rotatePoint(points, angle, result);

            // updates second points to the rotated points
            point2x = result[0] + offsetX;
            point2y = result[1] + offsetY;
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
