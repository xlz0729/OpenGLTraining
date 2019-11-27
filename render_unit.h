//
//  render_unit.h
//  OpenGLTraining
//
//  Created by 许立子 on 2019/11/26.
//  Copyright © 2019 xulizi. All rights reserved.
//

#ifndef render_unit_h
#define render_unit_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// 渲染的最小单元
// 每个render unit都包含顶点数据，shader，光照等信息
class RenderUnit
{
public:
    RenderUnit(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), float angle = 0)
    {
        m_position = position;
        m_angle = angle;
    }
    
    RenderUnit(float x = 0.0f, float y = 0.0f, float z = 0.0f, float angle = 0)
    {
        m_position = glm::vec3(x, y, z);
        m_angle = angle;
    }

    ~RenderUnit()
    {}

    void BindVertices(const float* vertices, unsigned int size, unsigned int start, unsigned int count)
    {
        m_vertices_size = size;
        m_vertices = vertices;
        m_vertices_start = start;
        m_vertices_count = count;
    }

    void BindIndices(const unsigned int* indices, unsigned int size)
    {
        m_indices_size = size;
        m_indices = indices;
    }
    
    void UpdateData(double current_time)
    {
        m_transformm_matrix = glm::mat4(1.0f);
        m_transformm_matrix = glm::rotate(m_transformm_matrix, (float)current_time, glm::vec3(0.0, 0.0, 1.0));
        
        m_model_matrix = glm::mat4(1.0f);
        m_model_matrix = glm::translate(m_model_matrix, m_position);
        m_model_matrix = glm::rotate(m_model_matrix, glm::radians(m_angle), glm::vec3(1.0f, 0.3f, 0.5f));
    }
    
public:
    inline void SetAngle(float angle) { m_angle = angle; }
    
    inline float GetAngle() { return m_angle; }
    
    inline glm::mat4 GetTransformMatrix() { return m_transformm_matrix; }
    
    inline glm::mat4 GetModelMatrix() { return m_model_matrix; }
    
    inline glm::vec3 GetPosition() { return m_position; }

    inline unsigned int GetVerticesStart() { return m_vertices_start; }

    inline unsigned int GetVerticesCount() { return m_vertices_count; }

//private:
    const float*        m_vertices = nullptr;
    unsigned int        m_vertices_size = 0;
    unsigned int        m_vertices_start = 0;
    unsigned int        m_vertices_count = 0;
    
    const unsigned int* m_indices = nullptr;
    unsigned int        m_indices_size = 0;
    
    float       m_angle = 0;
    glm::vec3   m_position = glm::vec3(0.0f, 0.0f, 0.0f);   // 每个物体的初始位置
    glm::mat4   m_transformm_matrix = glm::mat4(1.0f);
    glm::mat4   m_model_matrix = glm::mat4(1.0f);
};


#endif /* render_unit_h */
