//
//  const.h
//  OpenGLTraining
//
//  Created by 许立子 on 2019/10/24.
//  Copyright © 2019 xulizi. All rights reserved.
//

#ifndef const_h
#define const_h

#include <string>
#include <glm/glm.hpp>


// ------ shader attribute ------
// Shader source's absolute path depended on your own os.
extern std::string SHADER_DIR;

// ------ texture attribute ------
// texture's absolute path depended on your own os.
extern std::string TEXTURE_DIR;

// ------ 帧率的相关变量 ------
extern float g_DeltaTime;   // 当前帧与上一帧的时间差
extern float g_LastFrame;   // 上一帧的时间
extern float g_FPS;         // 帧率

// ------ 鼠标事件 ------
extern float g_Sensitivity; // 鼠标灵敏度
extern float g_LastX;       // 鼠标位置
extern float g_LastY;
extern bool  g_FirstMouse;  // 鼠标第一次被捕获

// ------ 摄像机 ------
extern glm::vec3    g_WorldUp;          // 世界坐标
extern float        g_CameraPitch;      // 默认俯仰角
extern float        g_CameraSpeed;      // 摄像机的默认移动速度
extern float        g_CameraFOV;        // 摄像机的默认FOV


#endif /* const_h */
