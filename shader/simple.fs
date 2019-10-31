#version 330 core

//uniform vec4 ourColor;  // we set this variable in the OpenGL code.

in vec4 vertexColor;

out vec4 FragColor;

void main()
{
    FragColor = vertexColor;
}
