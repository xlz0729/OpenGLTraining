//
//  render.hpp
//  OpenGLTraining
//
//  Created by 许立子 on 2019/11/4.
//  Copyright © 2019 xulizi. All rights reserved.
//

#ifndef renderer_h
#define renderer_h

#include <math.h>

#include <vector>
#include <iostream>

#include "define.h"
#include "camera.h"

#include "device_gl.h"
#include "render_unit.h"


// 渲染循环的入口
class Renderer
{
public:
    Renderer()
    {
        m_device.reset(new DeviceGL());
    }
    
    ~Renderer()
    {
    }
    
    void InitRenderer()
    {
        m_device->InitDevice();
    }
    
    void BindVertexArray()
    {
        m_device->BindVertexArray();
    }
    
    // 将顶点数据装载到图形API里面
    void BindVerticeData(const float* vertices, unsigned int vertices_size, const unsigned int* indices, unsigned int indices_size)
    {
        m_device->BindVertices(vertices, vertices_size);
        
        m_device->BindIndices(indices, indices_size);
    }
    
    void VertexAttribPointer(unsigned int index, int size, int stride, unsigned int start)
    {
        m_device->VertexAttribPointer(index, size, stride, start);
    }
    
    void LoadTexture(std::string texture_name, bool is_rgb = true)
    {
        m_device->LoadDeviceTexture(texture_name, is_rgb);
    }
    
    void CompileShader(std::string vertexName, std::string fragmentName, std::string geometryName = "", bool store = false)
    {
        m_device->CompileShader(vertexName, fragmentName, geometryName, store);
    }
    
    void ActiveShader()
    {
        m_device->ActiveShader();
    }
    
    void BindTexShader(std::vector<std::string>& tex_uniform)
    {
        ActiveShader();
        
        int i = 0;
        for (auto item : tex_uniform) {
            m_device->Uniform1i(m_device->GetUniformLocation(item), i++);
        }
    }
    
    void SetOrthographicProjection(float near, float far)
    {
        m_device->ActiveShader();
        m_device->SetOrthographicProjection(near, far);
    }
    
    void SetPerspectiveProjection(float fov, float near, float far)
    {
        m_device->ActiveShader();
        m_device->SetPerspectiveProjection(fov, near, far);
    }
    
    void SetViewMatrix(const glm::mat4 &mat)
    {
        m_device->SetMat4(SHADER_VIEW, mat);
    }
    
    void PreRender()
    {
        m_device->ClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        m_device->ClearBuff();
    }
    
    void ActiveTexture()
    {
        m_device->ActiveTexture();
    }
    
    void RenderOneUnit(RenderUnit& unit)
    {
//        glm::mat4 transform = glm::mat4(1.0f);
//        transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
//
//        m_device->SetMat4(SHADER_TRANSFORM, transform);
//
//        glm::mat4 model = glm::mat4(1.0f);
//        model = glm::translate(model, unit.GetPosition());
//        float angle = unit.GetAngle();
//        model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//
//        m_device->SetMat4(SHADER_MODEL, model);
        
        m_device->SetMat4(SHADER_TRANSFORM, unit.GetTransformMatrix());

        m_device->SetMat4(SHADER_MODEL, unit.GetModelMatrix());
        
        m_device->DrawArrays(unit.GetVerticesStart(), unit.GetVerticesCount());
    }
    
    void SetMat4(const std::string &name, const glm::mat4 &mat)
    {
        m_device->SetMat4(name, mat);
    }

    // 设置绘制模式
    void PolygonMod(GLenum face, GLenum mode) { m_device->PolygonMode(face, mode); }
    
    void Viewport(int x, int y, int width, int height) { m_device->Viewport(x, y, width, height); }

    void EnableDepthTest() { m_device->EnableDepthTest(); }
    
private:
    std::unique_ptr<DeviceInterface> m_device;
};

#endif /* renderer_h */
