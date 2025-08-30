#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

// Setup function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Window size settings
const unsigned int SRC_WIDTH = 1280;
const unsigned int SRC_HEIGHT = 720;

// Callback function to adjust the viewport when the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {

    /*  
    The GL Viewport function sets the viewport, which is the rectangular area of the window where OpenGL will draw.
    Here, we set it to cover the entire window (1280x720).   
    */
    glViewport(0, 0, width, height);

}

// Function to process input
void processInput(GLFWwindow *window) {

    // Check if the ESC key was pressed
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {

        // If ESC is pressed, set the window to close
        glfwSetWindowShouldClose(window, true);

    }

}

int main(void) {

    // Initialize GLFW
    if(!glfwInit()) {
 
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
 
    }
   
    // Configure GLFW versions and profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // GLFW window creation
    // ----------------------

    // Create a window object
    GLFWwindow* window;

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "OpenGL_Test", NULL, NULL);
    if (!window) {

        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;

    }

    // OpenGL context is where all OpenGL graphics operations are performed.
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ------------------------------------------------------------------------------

    // glad: load all OpenGL function pointers
    // ---------------------------------------

    // Initialize GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

       std::cout << "Failed to initialize GLAD" << std::endl;
       return -1;

    }

    // ------------------------------------------------------------------------------

    // Engine loop - runs until the window is closed
    // ---------------------------------------------
    while(!glfwWindowShouldClose(window)) {

        // Input
        processInput(window);

        // Render here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // ------------------------------------------------------------------------------

    // Clean up and exit
    glfwTerminate();

    return 0;

}
