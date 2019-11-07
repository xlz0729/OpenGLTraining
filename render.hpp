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
    
    ~Render()
    {
        // de-allocate all resources once they've outlived their purpose:
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);
        glDeleteBuffers(1, &m_EBO);
    }
    
    void SimpleInitBuffer()
    {
        // step 0: create a shader
        m_shader.reset(new Shader(VERTEX_SHADER, FRAGMENT_SHADER));
        
        // step 1: bind the Vertex Array Object
        glGenVertexArrays(1, &m_VAO);
        glBindVertexArray(m_VAO);
        
        // step 2: copy Vertex Array to Vertex Buffer
        glGenBuffers(1, &m_VBO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, m_vertices_size, m_vertices, GL_STATIC_DRAW);
        
        // step 3: copy Element Array to Element Buffer
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices_size, m_indices, GL_STATIC_DRAW);
        
        // step 4: set position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        // step 5: set color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
        glEnableVertexAttribArray(1);
        
        // step 6: set texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);
        
        // step 7: load and create a texture
        glGenTextures(1, &m_tex);
        glBindTexture(GL_TEXTURE_2D, m_tex);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        mLoadTextureImg();
    }
    
    void DoRender()
    {
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        // bind Texture
        glBindTexture(GL_TEXTURE_2D, m_tex);
        m_shader->UseProgram();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }
    
    void SetVertices(uint size, const float* vertices)
    {
        m_vertices_size = size;
        m_vertices = vertices;
    }

    void SetIndices(uint size, const uint* indices)
    {
        m_indices_size = size;
        m_indices = indices;
    }

    // 设置绘制模式
    inline void SetPolygonMod(GLenum face, GLenum mode) { glPolygonMode(face, mode); }

private:
    void mLoadTextureImg();
    
private:
    GLuint m_VBO;
    GLuint m_VAO;
    GLuint m_EBO;
    GLuint m_tex;
    
    std::shared_ptr<Shader> m_shader;
    
    const float*    m_vertices;
    const uint*     m_indices;
    uint            m_vertices_size;
    uint            m_indices_size;
};

#endif /* render_hpp */
