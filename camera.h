//
//  camera.h
//  OpenGLTraining
//
//  Created by 许立子 on 2019/11/18.
//  Copyright © 2019 xulizi. All rights reserved.
//

#ifndef camera_h
#define camera_h

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera
{
public:
    Camera()
    {
        // 先生成默认的 view 矩阵
        m_view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
    }
    
    ~Camera() {}
    
    inline void SetCameraPos(float x, float y, float z) { m_cameraPos = glm::vec3(x, y, z); }
    
    inline void SetCameraFront(float x, float y, float z) { m_cameraFront = glm::normalize(glm::vec3(x, y, z)); }
    
    inline void SetCameraUp(float x, float y, float z) { m_cameraUp = glm::normalize(glm::vec3(x, y, z)); }
    
    inline void MoveCameraForward(float deltaTime) { m_cameraPos += deltaTime * m_cameraSpeed * m_cameraFront; }
    
    inline void MoveCameraBackward(float deltaTime) { m_cameraPos -= deltaTime * m_cameraSpeed * m_cameraFront; }
    
    inline void MoveCameraLeftward(float deltaTime) { m_cameraPos -= deltaTime * glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraSpeed; }
    
    inline void MoveCameraRightward(float deltaTime) { m_cameraPos += deltaTime * glm::normalize(glm::cross(m_cameraFront, m_cameraUp)) * m_cameraSpeed; }
    
    inline void UpdateViewMatrix() { m_view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp); }
    
    inline glm::mat4 GetViewMatrix() { return m_view; }
    
private:
    glm::vec3 m_cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f); // 摄像机的位置
    glm::vec3 m_cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); // 摄像机的朝向
    glm::vec3 m_cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f); // 摄像机的up向量
    glm::mat4 m_view        = glm::mat4(1.0f);
    
    float m_cameraSpeed = 2.5f;
};

#endif /* camera_h */
