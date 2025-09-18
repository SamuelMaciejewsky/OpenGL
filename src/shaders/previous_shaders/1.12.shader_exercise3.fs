#version 460 core

out vec4 FragColor;
// in vec3 ourColor; 
in vec3 ourPosition;

void main () {

    FragColor = vec4(ourPosition, 1.0);

}

// READ 1.12.shader_exercise3.vs