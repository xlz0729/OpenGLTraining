//
//  Created by Lizio Xu on 2019/6/16.
//  Copyright © 2019 xulizi. All rights reserved.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <math.h>

#include <iostream>

#include "shader.h"
#include "const.h"
#include "define.h"


float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
}; 

unsigned int indices[] = {
    0, 1, 2,
};


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int heigh)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, heigh);
}


// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void ProcessInput(GLFWwindow *window)
{
    // 检测键盘输入
    // 检测按键 GLFW_KEY_ESCAPE 是否被按下
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}


// render
void DoRender(uint& object, uint& shaderProgram)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Note that finding the uniform location does not require you to use the shader program first.
//    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

    glUseProgram(shaderProgram);
    
//    float timeValue = glfwGetTime();
//    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
//    float redValue = (cos(timeValue) / 2.0f) + 0.5f;
//    float blueValue = (sin(timeValue + M_PI/4.0f) / 2.0f) + 0.5f;
    // Note that updating a uniform does require you to first use the program (by calling glUseProgram),
    // because it sets the uniform on the currently active shader program.
//    glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);

//    glBindVertexArray(object);
//    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
}


int main(int argc, const char * argv[])
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);    // uncomment this statement to fix compilation on OS X
#endif
    
    // glfw: window creation
    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGH, WINDOW_TITLE, NULL, NULL);
    if (window == NULL) {
        std::cout << "ERROR::GLFW::WINDOW >>> Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERROR::GLAD::INIT >>> Failed to initialize GLAD\n";
        return -1;
    }

    // GPU INFO
    std::cout << "-------------------- GPU INFO -----------------------" << std::endl;
    std::cout << "OpenGL Vendor:" << glGetString(GL_VENDOR) << std::endl;
    std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL Version:" << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "-----------------------------------------------------" << std::endl;
    
    // Create shader program
    Shader shader("simple", "simple");
    if (!shader.GetStatus()) {
        return -1;
    }

    // init OpenGL
    unit VBO, VAO, EBO;
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &EBO);

    // step 1: bind the Vertex Array Object
    glBindVertexArray(VAO);

    // step 2: copy Vertex Array to Vertex Buffer
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // step 3: copy Element Array to Element Buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // step 4: set position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // step 5: set color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);
    
    // 设置绘制模式
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    
    // main loop
    while(!glfwWindowShouldClose(window)) {
        // input
        ProcessInput(window);

        // render
        DoRender(EBO, shader.GetShader());

        glfwSwapBuffers(window);
        glfwPollEvents();           // 检测是否触发什么事件，并调用对应的回调函数
    }
    
    // de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();

    return 0;
}
