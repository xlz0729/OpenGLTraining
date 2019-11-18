//
//  const.cpp
//  OpenGLTraining
//
//  Created by 许立子 on 2019/10/25.
//  Copyright © 2019 xulizi. All rights reserved.
//

#include "const.h"


std::string SHADER_DIR = "/Users/xulizi/code/OpenGLTraining/OpenGLTraining/shader/";
std::string VERTEX_SHADER = "simple.vs";
std::string FRAGMENT_SHADER = "simple.fs";


std::string TEXTURE_DIR = "/Users/xulizi/code/OpenGLTraining/OpenGLTraining/texture/";


std::unique_ptr<Camera> g_Camera;


float g_DeltaTime = 0.0f;   // 当前帧与上一帧的时间差
float g_LastFrame = 0.0f;   // 上一帧的时间
float g_FPS = 60.0;         // 帧率
