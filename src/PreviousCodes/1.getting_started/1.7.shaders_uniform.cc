// Standard libs
#include<iostream>
#include<cmath>

// Local libs
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<myLib/logcomponent.h>


// Setup function declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Window size settings
const unsigned int SRC_WIDTH = 1280;
const unsigned int SRC_HEIGHT = 720;

// Error handling variables
int success;
char infoLog[512];

// Vertex configuration
// --------------------

// Buffers and Arrays
unsigned int VBOs[1], VAOs[1];
unsigned int vertexShader;
unsigned int fragmentShaders[1];
unsigned int shaderPrograms[1];


// Vertex data for a triangle
float vertices[] = {

    // First triangle
    -0.5f, -0.5, 0.0f,  // Bottom left
     0.5f, -0.5f, 0.0f,  // Bottom right
     0.0f,  0.5f, 0.0f   // Top 

};

// ----------------------------------------------


// Shader variables
// ----------------

float timeValue;
float greenValue;

int vertexColorLocation;

const char* vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"

    "out vec4 vertexColor;\n"

    "void main() {\n"

    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "   vertexColor = vec4(1.0f, 0.0, 0.20, 1.0f);\n"

    "}\0";

const char* fragmentShaderSource = "#version 460 core\n"

    "out vec4 FragColor;\n"
    "uniform vec4 ourColor;\n"

    "void main() {\n"

    "   FragColor = ourColor;\n"

    "}\n\0";

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


    // glad: load all OpenGL function pointers
    // ---------------------------------------

    // Initialize GLAD
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

       std::cout << "Failed to initialize GLAD" << std::endl;
       return -1;

    }

    // ------------------------------------------------------------------------------
    

    LogComponent *logPtr = new LogComponent(); // logPtr - 1 //


    // Shader section
    // --------------

    // Vertex shader object
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    logPtr->checkVertexInfoLog(vertexShader, 512, infoLog, success);

    
    // ..:: Fragment shader object ::.. //
    // -------------------------------- //

    // Fragment shader 1
    fragmentShaders[0] = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaders[0], 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShaders[0]);
    glGetShaderiv(fragmentShaders[0], GL_COMPILE_STATUS, &success);  // Check fragment shader status

    logPtr->checkFragmentInfoLog(fragmentShaders[0], 512, infoLog, success);

    // -------------------------------------------------------------- //


    // ..:: Shader program object ::.. //
    // -------------------------------- //

    // Shader program 1
    shaderPrograms[0] = glCreateProgram();
    glAttachShader(shaderPrograms[0], vertexShader);
    glAttachShader(shaderPrograms[0], fragmentShaders[0]);
    glLinkProgram(shaderPrograms[0]);

    glGetProgramiv(shaderPrograms[0], GL_LINK_STATUS, &success);

    logPtr->checkProgramInfoLog(shaderPrograms[0], 512, infoLog, success);
    
    glDeleteShader(fragmentShaders[0]);

    // -------------------------------------------------------------- //


    delete logPtr; // logPtr - 1 //
    glDeleteShader(vertexShader);

    // ------------------------------------------------------------------------------


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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 4. Unbind to prevent accidental modification
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // ------------------------------------------------------------------------------


    // Engine loop - runs until the window is closed
    // ---------------------------------------------
    while(!glfwWindowShouldClose(window)) {

        // Input
        processInput(window);

        // Render here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Draw here
        glUseProgram(shaderPrograms[0]);

        timeValue = glfwGetTime();
        greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        vertexColorLocation = glGetUniformLocation(shaderPrograms[0], "ourColor");

        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // ------------------------------------------------------------------------------


    // Clean up and exit
    glDeleteVertexArrays(1, VAOs);
    glDeleteBuffers(1, VBOs);
    glDeleteProgram(shaderPrograms[0]);
    glfwTerminate();

    return 0;

}
