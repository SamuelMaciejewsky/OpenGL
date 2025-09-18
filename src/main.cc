// Standard libs
#include<iostream>

// Local libs
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<myLib/shader_s.h>

// Setup function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Window size settings
const unsigned int SRC_WIDTH = 1280;
const unsigned int SRC_HEIGHT = 720;

// Vertex configuration
// --------------------

// Buffers and Arrays
unsigned int VBOs[1], VAOs[1];

// Vertex data for a triangle
float vertices[] = {

    // First triangle
    // Positions         // Colors
    -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Bottom left
     0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom right
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // Top 

};

// ----------------------------------------------


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

    // Initialize GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

       std::cout << "Failed to initialize GLAD" << std::endl;
       return -1;

    }

    Shader ourShader("../src/shaders/shader.vs", "../src/shaders/shader.fs");

    // ..:: Initialization code ..:: //
    // ----------------------------- //

    glGenVertexArrays(1, VAOs);
    glGenBuffers(1, VBOs);

    // First triangle setup //
    // 1. Bind VAO first
    glBindVertexArray(VAOs[0]);

    // 2. Generate and bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 3. Set up vertex attributes
    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 4. Unbind to prevent accidental modification
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // ------------------------------------------------------------------------------

    // Engine loop - runs until the window is closed
    while(!glfwWindowShouldClose(window)) {

        // Input
        processInput(window);

        // Render here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw here
        ourShader.use();
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // Clean up and exit
    glDeleteVertexArrays(1, VAOs);
    glDeleteBuffers(1, VBOs);
    glfwTerminate();

    return 0;

}
