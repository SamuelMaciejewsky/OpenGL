#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void error_callback(int error, const char* description){
    std::cout << stderr << "Error: " << description << std::endl;
}

int main() {

    GLFWwindow* window;
    

    glfwSetErrorCallback(error_callback);

    if(!glfwInit()) {
        
        std::cout << "Eror to init glfw" << std::endl;
        return -1;

    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 0);

    window = glfwCreateWindow(1280, 720, "Test", NULL, NULL);
    if(!window) { 

        std::cout << "Error to create window" << std::endl;
        return -2;

    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    glfwDestroyWindow(window);



    return 0;

}
