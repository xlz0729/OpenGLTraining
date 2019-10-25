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

#include "define.h"
#include "const.h"


class Shader
{
public:
    Shader(std::string vertexShaderName, std::string fragmentShaderName);
    
    ~Shader() {}
    
    inline bool GetStatus() { return m_status; }
    
    inline unit& GetShader() { return m_shader; }
    
private:
    // Read content from file and output it by const char*
    const char* mReadFileToStr(const char* file_path);

    void mCheckCompileErrors(uint shaderProgram, uint status);

private:
    bool m_status = true;
    unit m_shader = -1;
};


#endif /* Shader_h */
