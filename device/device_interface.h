//
//  device_interface.h
//  OpenGLTraining
//
//  Created by 许立子 on 2019/11/26.
//  Copyright © 2019 xulizi. All rights reserved.
//

#ifndef device_interface_h
#define device_interface_h

#


class DeviceInterface
{
public:
    virtual int InitDevice() = 0;
    
    virtual void BindVertices(const float* vertices, unsigned int size) = 0;
    
    virtual void BindIndices(const unsigned int* indices, unsigned int size) = 0;
    
    virtual void VertexAttribPointer(unsigned int index, int size, int stride, unsigned int start) = 0;
    
    virtual void LoadDeviceTexture(std::string texture_name, bool is_rgb = true) = 0;
    
    virtual void CompileShader(std::string vertexName, std::string fragmentName, std::string geometryName = "", bool store = false) = 0;
    
    virtual void ActiveShader() = 0;
    
    virtual void ChangeShader(std::string vertexName) = 0;
    
    virtual void SetOrthographicProjection(float near, float far) = 0;
    
    virtual void SetPerspectiveProjection(float fov, float near, float far) = 0;
    
    virtual void ClearBuff() = 0;
    
    virtual void ActiveTexture() = 0;
    
// 以下为API接口封装
public:
    virtual void BindVertexArray() = 0;
    
    virtual void Viewport(int x, int y, int width, int height) = 0;
    
    virtual void PolygonMode(unsigned int face, unsigned int mode) = 0;
    
    virtual void EnableDepthTest() = 0;
    
    virtual void ClearColor(float red, float green, float blue, float alpha) = 0;
    
    virtual int  GetUniformLocation(const std::string &name) = 0;
    
    virtual void DrawArrays(int first, unsigned int count) = 0;
    
    virtual void Uniform1i(int location, const int value) = 0;
    
    virtual void UniformMatrix4f(int location, const glm::mat4 &mat) = 0;
    
    virtual void SetMat4(const std::string &name, const glm::mat4 &mat) = 0;
};


#endif /* device_interface_h */
