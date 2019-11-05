//
//  render.hpp
//  OpenGLTraining
//
//  Created by 许立子 on 2019/11/4.
//  Copyright © 2019 xulizi. All rights reserved.
//

#ifndef render_hpp
#define render_hpp

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <math.h>

#include "common/define.h"
#include "shader.h"

class Render
{
public:
    Render()
    {
        m_VBO = -1;
        m_VAO = -1;
        m_EBO = -1;
    }
    
    ~Render() {}
    
    void SimpleInitBuffer() {
        GenBuffer();
        BindVertexArray();
        BindVertexBuffer();
        BindElementBuffer();
        SetPositionAttr();
        SetColorAttr();
        
        CreateShader();
    }
    
    //
    inline void GenBuffer() {
        // init OpenGL
        glGenBuffers(1, &m_VBO);
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_EBO);
    }
    // step 1: bind the Vertex Array Object
    inline void BindVertexArray () { glBindVertexArray(m_VAO); }
    // step 2: copy Vertex Array to Vertex Buffer
    inline void BindVertexBuffer() {
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_vertices_size, m_vertices, GL_STATIC_DRAW);
    }
    // step 3: copy Element Array to Element Buffer
    inline void BindElementBuffer() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices_size, m_indices, GL_STATIC_DRAW);
    }
    // step 4: set position attribute
    inline void SetPositionAttr() {
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }
    // step 5: set color attribute
    inline void SetColorAttr() {
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
        glEnableVertexAttribArray(1);
    }
        
    // Create shader program
    inline void CreateShader() { m_shader.reset(new Shader("simple", "simple")); }
    
    //
    void DoRender()
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        m_shader->UseProgram();
        mRenderEBO();
    }
    
    //
    inline void SetVertices(uint size, const float* vertices) {
        m_vertices_size = size;
        m_vertices = vertices;
    }
    //
    inline void SetIndices(uint size, const uint* indices) {
        m_indices_size = size;
        m_indices = indices;
    }
    // 设置绘制模式
    inline void SetPolygonMod(GLenum face, GLenum mode) { glPolygonMode(face, mode); }

    // de-allocate all resources once they've outlived their purpose:
    inline void DeleteVertexArrays() { glDeleteVertexArrays(1, &m_VAO); }
    //
    inline void DeleteBuffers() { glDeleteBuffers(1, &m_VBO); }
    
private:
    void UpdateShaderUniform() {
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        float redValue = (cos(timeValue) / 2.0f) + 0.5f;
        float blueValue = (sin(timeValue + M_PI/4.0f) / 2.0f) + 0.5f;

        // Note that finding the uniform location does not require you to use the shader program first.
        int vertexColorLocation = m_shader->GetUniformLocation("ourColor");
        
        // Note that updating a uniform does require you to first use the program (by calling glUseProgram),
        // because it sets the uniform on the currently active shader program.
        glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);
    }
    
    void mRenderVAO() {
        glBindVertexArray(m_VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    
    void mRenderEBO() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    }

private:
    GLuint m_VBO;
    GLuint m_VAO;
    GLuint m_EBO;
    
    std::shared_ptr<Shader> m_shader;
    
    const float*    m_vertices;
    const uint*     m_indices;
    uint            m_vertices_size;
    uint            m_indices_size;
};

#endif /* render_hpp */
