//
//  Shader.h
//  OpenGLTraining
//
//  Created by 许立子 on 2019/10/24.
//  Copyright © 2019 xulizi. All rights reserved.
//

#ifndef Shader_h
#define Shader_h

#include <glad/glad.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "common/define.h"
#include "common/const.h"


class Shader
{
public:
    Shader(std::string vertexShaderName, std::string fragmentShaderName);
    
    ~Shader() {}
    
    inline void UseProgram() { glUseProgram(m_shader); }
    
    inline int GetUniformLocation(const char* name) { return glGetUniformLocation(m_shader, name); }
    
private:
    // Read content from file and output it by const char*
    const char* mReadFileToStr(const char* file_path);

    void mCheckCompileErrors(uint shaderProgram, uint status);

private:
    unit m_shader = -1;
};


#endif /* Shader_h */
