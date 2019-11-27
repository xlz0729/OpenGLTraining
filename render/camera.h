//
//  camera.h
//  OpenGLTraining
//
//  Created by 许立子 on 2019/11/18.
//  Copyright © 2019 xulizi. All rights reserved.
//

#ifndef camera_h
#define camera_h

#include <memory>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "define.h"


class Camera;


class Camera
{
public:
    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), float yaw = CAMERA_YAW, float pitch = CAMERA_PITCH, float speed = CAMERA_SPEED, float fov = CAMERA_FOV);
    
    ~Camera() {}
    
    void Release() {}
    
    void UpdateViewMatrix();
    
    void UpdateYawPitch(float xoffset, float yoffset);
    
    void UpdateFOV(float yoffset);

public:
    inline void SetCameraPos(float x, float y, float z) { m_cameraPos = glm::vec3(x, y, z); }
    
    inline void SetCameraFront(float x, float y, float z) { m_cameraFront = glm::normalize(glm::vec3(x, y, z)); }
    
    inline void SetCameraUp(float x, float y, float z) { m_cameraUp = glm::normalize(glm::vec3(x, y, z)); }
    
    inline void MoveCameraForward(float deltaTime) { m_cameraPos += deltaTime * m_cameraSpeed * m_cameraFront; }
    
    inline void MoveCameraBackward(float deltaTime) { m_cameraPos -= deltaTime * m_cameraSpeed * m_cameraFront; }
    
    inline void MoveCameraLeftward(float deltaTime) { m_cameraPos -= deltaTime * m_cameraRight * m_cameraSpeed; }
    
    inline void MoveCameraRightward(float deltaTime) { m_cameraPos += deltaTime * m_cameraRight * m_cameraSpeed; }
    
    inline glm::mat4 GetViewMatrix() { return m_view; }
    
    inline float GetFOV() { return m_FOV; }


private:
    void mUpdateCameraVectors();
    
    glm::mat4 mMyLookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp);

private:
    glm::mat4 m_view = glm::mat4(1.0f);

    glm::vec3 m_cameraPos;      // 摄像机的位置
    glm::vec3 m_cameraFront;    // 摄像机的朝向
    glm::vec3 m_cameraRight;    // 相机的右向量
    glm::vec3 m_cameraUp;       // 摄像机的up向量
    
    float m_cameraSpeed;
    float m_cameraYaw;     // 偏航角
    float m_cameraPitch;   // 俯仰角
    float m_FOV;
};

#endif /* camera_h */
