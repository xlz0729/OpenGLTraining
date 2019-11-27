//
//  camera.cpp
//  OpenGLTraining
//
//  Created by 许立子 on 2019/11/18.
//  Copyright © 2019 xulizi. All rights reserved.
//

#include "camera.h"
#include "const.h"



Camera::Camera(glm::vec3 position, float yaw, float pitch, float speed, float fov)
{
    m_cameraPos = position;
    m_cameraYaw = yaw;
    m_cameraPitch = pitch;
    m_cameraSpeed = speed;
    m_FOV = fov;
    
    mUpdateCameraVectors();
}

void Camera::UpdateYawPitch(float xoffset, float yoffset)
{
    m_cameraYaw   += xoffset;
    m_cameraPitch += yoffset;
    
    if(m_cameraPitch > 89.0f) {
      m_cameraPitch =  89.0f;
    }
    if(m_cameraPitch < -89.0f) {
      m_cameraPitch = -89.0f;
    }
    
    mUpdateCameraVectors();
}

void Camera::UpdateFOV(float yoffset)
{
    if (m_FOV >= 1.0f && m_FOV <= 45.0f) {
        m_FOV -= yoffset;
    }
    if (m_FOV <= 1.0f) {
        m_FOV = 1.0f;
    }
    if (m_FOV >= 45.0f) {
        m_FOV = 45.0f;
    }
}

void Camera::mUpdateCameraVectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(m_cameraPitch)) * cos(glm::radians(m_cameraYaw));
    front.y = sin(glm::radians(m_cameraPitch));
    front.z = cos(glm::radians(m_cameraPitch)) * sin(glm::radians(m_cameraYaw));
    
    m_cameraFront = glm::normalize(front);
    m_cameraRight = glm::normalize(glm::cross(m_cameraFront, g_WorldUp));
    m_cameraUp    = glm::normalize(glm::cross(m_cameraRight, m_cameraFront));
}

void Camera::UpdateViewMatrix()
{
    m_view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp);
}

glm::mat4 Camera::mMyLookAt(glm::vec3 position, glm::vec3 target, glm::vec3 worldUp)
{
    // 1. Position = known
    // 2. Calculate cameraDirection
    glm::vec3 zaxis = glm::normalize(position - target);
    // 3. Get positive right axis vector
    glm::vec3 xaxis = glm::normalize(glm::cross(glm::normalize(worldUp), zaxis));
    // 4. Calculate camera up vector
    glm::vec3 yaxis = glm::cross(zaxis, xaxis);

    // Create translation and rotation matrix
    // In glm we access elements as mat[col][row] due to column-major layout
    glm::mat4 translation = glm::mat4(1.0f); // Identity matrix by default
    translation[3][0] = -position.x; // Third column, first row
    translation[3][1] = -position.y;
    translation[3][2] = -position.z;
    glm::mat4 rotation = glm::mat4(1.0f);
    rotation[0][0] = xaxis.x; // First column, first row
    rotation[1][0] = xaxis.y;
    rotation[2][0] = xaxis.z;
    rotation[0][1] = yaxis.x; // First column, second row
    rotation[1][1] = yaxis.y;
    rotation[2][1] = yaxis.z;
    rotation[0][2] = zaxis.x; // First column, third row
    rotation[1][2] = zaxis.y;
    rotation[2][2] = zaxis.z;

    // Return lookAt matrix as combination of translation and rotation matrix
    return rotation * translation; // Remember to read from right to left (first translation then rotation)
}
