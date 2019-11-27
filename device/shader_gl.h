//
//  shader_gl.h
//  OpenGLTraining
//
//  Created by 许立子 on 2019/10/25.
//  Copyright © 2019 xulizi. All rights reserved.
//

#ifndef SHADER_GL_H
#define SHADER_GL_H

#include <glad/glad.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "const.h"

class Shader
{
public:
    Shader(std::string vertexName, std::string fragmentName, std::string geometryName = "");

public:
    inline void UseProgram() { glUseProgram(ID); }

public:
    unsigned int ID;

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void mCheckCompileErrors(unsigned int shader, std::string type);
};

#endif /*SHADER_GL_H*/
