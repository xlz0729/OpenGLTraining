//
//  const.h
//  OpenGLTraining
//
//  Created by 许立子 on 2019/10/24.
//  Copyright © 2019 xulizi. All rights reserved.
//

#ifndef const_h
#define const_h

#include <iostream>

#include "camera.h"


// ------ shader attribute ------
// Shader source's absolute path depended on your own os.
extern std::string SHADER_DIR;
extern std::string VERTEX_SHADER;
extern std::string FRAGMENT_SHADER;

// ------ texture attribute ------
// texture's absolute path depended on your own os.
extern std::string TEXTURE_DIR;

// ------ 主摄像机 ------
extern std::unique_ptr<Camera> g_Camera;

// ------ 帧率的相关变量 ------
extern float g_DeltaTime;   // 当前帧与上一帧的时间差
extern float g_LastFrame;   // 上一帧的时间
extern float g_FPS;         // 帧率

// ------ 鼠标事件 ------
extern float g_Sensitivity; // 鼠标灵敏度
extern float g_LastX;       // 鼠标位置
extern float g_LastY;
extern bool  g_FirstMouse;  // 鼠标第一次被捕获


#endif /* const_h */
