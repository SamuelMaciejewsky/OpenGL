#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>

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

// Vertex Array Object and Vertex Buffer Object
unsigned int VBO, VAO, EBO;
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;


// Vertex data for a triangle
float vertices[] = {

    // positions for rectangle
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left

};

unsigned int indices[] = {

    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle

};

// ----------------------------------------------


const char* vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main() {\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char* fragmentShaderSource = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";


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


    // Shader section
    // --------------

    // Vertex shader object
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }   
    
    // Fragment shader object
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    if(!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }  

    // Shader program object
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {

        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    
    }
    
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // ------------------------------------------------------------------------------


    // ..:: Initialization code ..:: //
    // ----------------------------- //

    // 1. Generate and bind VAO first
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // 2. Generate and bind VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    // 3. Generate and bind EBO (while VAO is still bound)
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 4. Set up vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 5. Unbind to prevent accidental modification (EBO should NOT be unbound while VAO is active)
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //------------------------------------------------------------------------------


    // Engine loop - runs until the window is closed // 
    // --------------------------------------------- //
    while(!glfwWindowShouldClose(window)) {

        // Input
        processInput(window);

        // Render here
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.
        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    // ------------------------------------------------------------------------------


    // Clean up and exit
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();

    return 0;

}
