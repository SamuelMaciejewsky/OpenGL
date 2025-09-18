#version 460 core 

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

// out vec3 ourColor;
out vec3 ourPosition; 

void main() {

    gl_Position = vec4(aPos, 1.0);
    // ourColor = aColor;
    ourPosition = aPos;

}

/*  if the vertices use are:                                   *
 *                                                             *
 *  // Positions         // Colors                             *
 *  -0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // Bottom left     *
 *   0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Bottom right    *
 *   0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // Top             *
 *                                                             *
 *  ourPosition variable recive:                               *
 *  -0.5f, -0.5f, 0.0f -> black                                *
 *   0.5f, -0.5f, 0.0f -> red                                  *
 *   0.0f,  0.5f, 0.0f -> green                                *
 *                                                             */