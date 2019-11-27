//
//  windows_control.h
//  OpenGLTraining
//
//  Created by 许立子 on 2019/11/25.
//  Copyright © 2019 xulizi. All rights reserved.
//

#ifndef windows_control_h
#define windows_control_h

#include <GLFW/glfw3.h>

#include <memory>
#include <iostream>

#include "define.h"
#include "const.h"

class Renderer;
class Camera;
extern std::unique_ptr<Renderer> g_render;
extern Camera* g_master_camera;


class WindowsControl
{
public:
    WindowsControl() : m_glfw_window(nullptr)
    {}
    
    ~WindowsControl()
    {
        glfwDestroyWindow(m_glfw_window);
        m_glfw_window = nullptr;
    }
    
    GLFWwindow* GetWindow()
    {
        return m_glfw_window;
    }
    
    int InitWindow()
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
        m_glfw_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGH, WINDOW_TITLE, NULL, NULL);
        if (m_glfw_window == nullptr) {
            std::cout << "ERROR::GLFW::WINDOW >>> Failed to create GLFW window\n";
            glfwTerminate();
            return -1;
        }
        
        // tell GLFW to capture our mouse
        glfwSetInputMode(m_glfw_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        glfwMakeContextCurrent(m_glfw_window);
        
        // glfw: register callback function
        glfwSetFramebufferSizeCallback(m_glfw_window, WindowsControl::CFramebufferSizeCallback);
        glfwSetCursorPosCallback(m_glfw_window, WindowsControl::CMouseCallback);
        glfwSetScrollCallback(m_glfw_window, WindowsControl::CScrollCallback);
        glfwSetKeyCallback(m_glfw_window, WindowsControl::CKeyboardCallback);
        
        return 0;
    }
    
    int WindowShouldClose()
    {
        return glfwWindowShouldClose(m_glfw_window);
    }
    
    void ProcessKeyboard()
    {
        if (glfwGetKey(m_glfw_window, GLFW_KEY_W) == GLFW_PRESS) {
            g_master_camera->MoveCameraForward(g_DeltaTime);
        }
        if (glfwGetKey(m_glfw_window, GLFW_KEY_S) == GLFW_PRESS) {
            g_master_camera->MoveCameraBackward(g_DeltaTime);
        }
        if (glfwGetKey(m_glfw_window, GLFW_KEY_A) == GLFW_PRESS) {
            g_master_camera->MoveCameraLeftward(g_DeltaTime);
        }
        if (glfwGetKey(m_glfw_window, GLFW_KEY_D) == GLFW_PRESS) {
            g_master_camera->MoveCameraRightward(g_DeltaTime);
        }
    }
    
    void Postprocess()
    {
        glfwSwapBuffers(m_glfw_window);
        glfwPollEvents();           // 检测是否触发什么事件，并调用对应的回调函数
    }

    static void CFramebufferSizeCallback(GLFWwindow* window, int width, int heigh)
    {
        g_render->Viewport(0, 0, width, heigh);
    }

    static void CMouseCallback(GLFWwindow* window, double xpos, double ypos)
    {
        if (g_FirstMouse) {
            g_LastX = xpos;
            g_LastY = ypos;
            g_FirstMouse = false;
            return;
        }

        float xoffset = xpos - g_LastX;
        float yoffset = g_LastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的
        g_LastX = xpos;
        g_LastY = ypos;

        xoffset *= g_Sensitivity;
        yoffset *= g_Sensitivity;
        
        g_master_camera->UpdateYawPitch(xoffset, yoffset);
    }

    static void CScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
    {
        g_master_camera->UpdateFOV(yoffset);
    }
    
    // 在每次循环会首先执行该函数，
    // 在这个函数中会处理外部输出，例如键盘鼠标
    static void CKeyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        // 检测键盘被按下
        if (action == GLFW_PRESS) {
            switch (key) {
                case GLFW_KEY_ESCAPE:
                    glfwSetWindowShouldClose(window, true);
                    break;
                default:
                    break;
            }
        }
    }
    
private:
    GLFWwindow* m_glfw_window = nullptr;
};


#endif /* windows_control_h */
