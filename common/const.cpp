//
//  const.cpp
//  OpenGLTraining
//
//  Created by 许立子 on 2019/10/25.
//  Copyright © 2019 xulizi. All rights reserved.
//

#include "const.h"


// ------ shader attribute ------
std::string SHADER_DIR = "/Users/xulizi/code/OpenGLTraining/OpenGLTraining/shader/";


// ------ texture attribute ------
std::string TEXTURE_DIR = "/Users/xulizi/code/OpenGLTraining/OpenGLTraining/texture/";


// ------ 帧率的相关变量 ------
float g_DeltaTime = 0.0f;   // 当前帧与上一帧的时间差
float g_LastFrame = 0.0f;   // 上一帧的时间
float g_FPS = 60.0;         // 帧率


// ------ 鼠标事件 ------
float g_Sensitivity = 0.05f;
float g_LastX = 400;
float g_LastY = 300;
bool  g_FirstMouse = true;

// ------ 摄像机 ------
glm::vec3 g_WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);
