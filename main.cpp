//
//  Created by Lizio Xu on 2019/6/16.
//  Copyright © 2019 xulizi. All rights reserved.
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "render.hpp"
#include "common/const.h"
#include "common/define.h"


float vertices[] = {
    // positions         // colors
     0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
     0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // top
}; 

uint indices[] = {
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
    
    Render render;
    
    render.SetVertices(sizeof(vertices), vertices);
    render.SetIndices(sizeof(indices), indices);
    render.SimpleInitBuffer();
    
    // main loop
    while(!glfwWindowShouldClose(window)) {
        // input
        ProcessInput(window);

        // render
        render.DoRender();

        glfwSwapBuffers(window);
        glfwPollEvents();           // 检测是否触发什么事件，并调用对应的回调函数
    }
    
    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();

    return 0;
}
