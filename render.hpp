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

#include <vector>

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
        
        m_cube_positions.push_back(glm::vec3( 0.0f,  0.0f,  0.0f));
        m_cube_positions.push_back(glm::vec3( 2.0f,  5.0f, -15.0f));
        m_cube_positions.push_back(glm::vec3(-1.5f, -2.2f, -2.5f));
        m_cube_positions.push_back(glm::vec3(-3.8f, -2.0f, -12.3f));
        m_cube_positions.push_back(glm::vec3( 2.4f, -0.4f, -3.5f));
        m_cube_positions.push_back(glm::vec3(-1.7f,  3.0f, -7.5f));
        m_cube_positions.push_back(glm::vec3( 1.3f, -2.0f, -2.5f));
        m_cube_positions.push_back(glm::vec3( 1.5f,  2.0f, -2.5f));
        m_cube_positions.push_back(glm::vec3( 1.5f,  0.2f, -1.5f));
        m_cube_positions.push_back(glm::vec3(-1.3f,  1.0f, -1.5f));
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
        glEnable(GL_DEPTH_TEST);
        
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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        
        // step 5: set color attribute
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3* sizeof(float)));
//        glEnableVertexAttribArray(1);
        
        // step 6: set texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        
        // step 7: load and create a texture
        // first texture
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
        mLoadTextureImg("container.jpg");
        m_texs.push_back(tex1);
        
        // second texture
        GLuint tex2;
        glGenTextures(1, &tex2);
        glBindTexture(GL_TEXTURE_2D, tex2);
        // set the texture wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        // set texture filtering parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // load image, create texture and generate mipmaps
        mLoadTextureImg("awesomeface.png", GL_RGBA);
        m_texs.push_back(tex2);
        
        // have to use the shader before setting uniforms!
        m_shader->UseProgram();
        m_shader->SetInt("texture1", 0);
        m_shader->SetInt("texture2", 1);
        
        mProjectionTransformation();
    }
    
    void DoRender()
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_texs[0]);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, m_texs[1]);

        m_shader->UseProgram();
        
        // transform
        mCoordinateTransformation();
        
        // render container
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(m_VAO);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
        
        int i = 0;
        for(auto position : m_cube_positions)
        {
          glm::mat4 model = glm::mat4(1.0f);
          model = glm::translate(model, position);
          float angle = 20.0f * i++;
          model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
          m_shader->SetMat4("model", model);

          glDrawArrays(GL_TRIANGLES, 0, 36);
        }
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
    void mLoadTextureImg(std::string texture_name, GLenum format = GL_RGB);
    
    void mCoordinateTransformation();
    
    void mProjectionTransformation();
    
private:
    GLuint m_VBO;
    GLuint m_VAO;
    GLuint m_EBO;
    std::vector<GLuint> m_texs;
    
    std::shared_ptr<Shader> m_shader;
    
    const float*    m_vertices;
    const uint*     m_indices;
    uint            m_vertices_size;
    uint            m_indices_size;
    
    // 暂时用于输出多个矩形，之后会删除
    std::vector<glm::vec3> m_cube_positions;
};

#endif /* render_hpp */
