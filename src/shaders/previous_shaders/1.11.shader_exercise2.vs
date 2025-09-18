#version 460 core 

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 ourColor; 

void main() {

    gl_Position = vec4(aPos.x - 0.3, aPos.y + 0.3, aPos.z - 0.3, 1.0);
    ourColor = aColor;

}