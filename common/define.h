//
//  define.h
//  OpenGLTraining
//
//  Created by 许立子 on 2019/10/24.
//  Copyright © 2019 xulizi. All rights reserved.
//

#ifndef define_h
#define define_h


typedef unsigned int unit;

// ------ window attribute ------
#define WINDOW_WIDTH    800  // Width of window

#define WINDOW_HEIGH    600  // Heigh of window

#define WINDOW_TITLE    "Lizio Xu's window"   // Title of window


// ------ camera attribute ------
#define CAMERA_YAW      -90.0f  // 摄像机偏航角

#define CAMERA_PITCH    0.0f    // 摄像机俯仰角

#define CAMERA_SPEED    2.5     // 摄像机移动速度

#define CAMERA_FOV      45.0

// 默认偏航角
extern float g_CameraPitch;       // 默认俯仰角
extern float g_CameraSpeed;       // 摄像机的默认移动速度
extern float g_CameraFOV;         // 摄像机的默认FOV


#endif /* define_h */
