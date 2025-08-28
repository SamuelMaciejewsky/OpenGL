#include <glad/gl.h>
#include <GLFW/glfw3.h>

int main() {

    if(!gflw3Init()) {
        
        cout << "Eror to init glfw" << endl;
        return -1;

    }

    void error_callback(int error, const char* description) {
        cout << stderr << "Error " << description << endl;
    } 

    glfwSetErrorCallback(error_callback);

    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWinfowHint(GLFW_CONTEXT_VERSION_MAJOR, 0);
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Test", NULL, NULL);
    if(!window) { 

        cout << "Error to create window" << endl;
        return -2;

    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);

    glfwDestroyWindow(window);



    return 0;

}
