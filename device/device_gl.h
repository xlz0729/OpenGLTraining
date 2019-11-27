//
//  device_gl.h
//  OpenGLTraining
//
//  Created by 许立子 on 2019/11/26.
//  Copyright © 2019 xulizi. All rights reserved.
//

#ifndef device_gl_h
#define device_gl_h

#include "shader_gl.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <map>

#include "device_interface.h"
#include "define.h"


class DeviceGL : public DeviceInterface
{
public:
    DeviceGL()
    {}
    
    ~DeviceGL()
    {
        // de-allocate all resources once they've outlived their purpose:
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }
    
    int InitDevice() override
    {
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
        
        return 0;
    }
    
    void BindVertices(const float* vertices, unsigned int size) override
    {
        // bind the Vertex Array Object
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);
        
        // copy Vertex Array to Vertex Buffer
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    }
    
    void BindIndices(const unsigned int* indices, unsigned int size) override
    {
        // copy Element Array to Element Buffer
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    }
    
    void VertexAttribPointer(unsigned int index, int size, int stride, unsigned int start) override
    {
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(start * sizeof(float)));
        glEnableVertexAttribArray(index);
    }
    
    // load and create a texture
    void LoadDeviceTexture(std::string texture_name, bool is_rgb = true) override
    {
        GLuint tex1;
        glGenTextures(1, &tex1);
        glBindTexture(GL_TEXTURE_2D, tex1);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        if (is_rgb) {
            mLoadTextureImg(texture_name);
        }
        else {
            mLoadTextureImg(texture_name, GL_RGBA);
        }
        m_texs.push_back(tex1);
    }
    
    void CompileShader(std::string vertexName, std::string fragmentName, std::string geometryName = "", bool store = false) override
    {
        m_shader = new Shader(vertexName, fragmentName, geometryName);
        
        if (store) {
            m_shader_set[vertexName] = m_shader;
        }
    }
    
    void ActiveShader() override
    {
        m_shader->UseProgram();
    }
    
    void ChangeShader(std::string vertexName) override
    {
        m_shader = m_shader_set[vertexName];
    }
    
    void SetOrthographicProjection(float near, float far) override
    {
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGH, near, far); // 正交矩阵
        glUniformMatrix4fv(glGetUniformLocation(m_shader->ID, SHADER_PROJECTION), 1, GL_FALSE, &projection[0][0]);
    }
    
    void SetPerspectiveProjection(float fov, float near, float far) override
    {
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(fov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGH, near, far); // 透视矩阵
        glUniformMatrix4fv(glGetUniformLocation(m_shader->ID, SHADER_PROJECTION), 1, GL_FALSE, &projection[0][0]);
    }
    
    void ClearBuff() override
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    void ActiveTexture() override
    {
        for (int i = 0; i < m_texs.size(); ++i) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, m_texs[i]);
        }
    }
    
public:
    void BindVertexArray() override
    {
        glBindVertexArray(m_VAO);
    }
    
    void Viewport(int x, int y, int width, int height) override
    {
        glViewport(x, y, width, height);
    }
    
    void PolygonMode(unsigned int face, unsigned int mode) override
    {
        glPolygonMode(face, mode);
    }
    
    void EnableDepthTest() override
    {
        glEnable(GL_DEPTH_TEST);
    }
    
    void ClearColor(float red, float green, float blue, float alpha) override
    {
        glClearColor(red, green, blue, alpha);
    }
    
    void DrawArrays(int first, unsigned int count) override
    {
        glDrawArrays(GL_TRIANGLES, first, count);
    }
    
    int GetUniformLocation(const std::string &name) override
    {
        return glGetUniformLocation(m_shader->ID, name.c_str());
    }
    
    void Uniform1i(int location, const int value) override
    {
        glUniform1i(location, value);
    }
    
    void UniformMatrix4f(int location, const glm::mat4 &mat) override
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]);
    }
    
    void SetMat4(const std::string &name, const glm::mat4 &mat) override
    {
        glUniformMatrix4fv(glGetUniformLocation(m_shader->ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    
private:
    void mLoadTextureImg(std::string texture_name, GLenum format = GL_RGB);
    
private:
    GLuint m_VBO;
    GLuint m_VAO;
    GLuint m_EBO;
    std::vector<GLuint> m_texs;
    Shader* m_shader;   // 当前活跃的shader
    std::map<std::string, Shader*> m_shader_set;
};


#endif /* device_gl_h */
