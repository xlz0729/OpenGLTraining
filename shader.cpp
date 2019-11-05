//
//  shader.cpp
//  OpenGLTraining
//
//  Created by 许立子 on 2019/10/25.
//  Copyright © 2019 xulizi. All rights reserved.
//

#include "shader.h"


// --------- public ---------
Shader::Shader(std::string vertexShaderName, std::string fragmentShaderName)
{
    // Create vertex shader
    unit vertexShader = glCreateShader(GL_VERTEX_SHADER);
    std::string vertexPath = SHADER_DIR + vertexShaderName + ".vs";
    const GLchar* vertexShaderSource = (const GLchar*)mReadFileToStr(vertexPath.c_str());
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    mCheckCompileErrors(vertexShader, GL_COMPILE_STATUS);
    
    // Create fragment shader
    unit fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    std::string fragmentPath = SHADER_DIR + fragmentShaderName + ".fs";
    const GLchar* fragmentShaderSource = (const GLchar*)mReadFileToStr(fragmentPath.c_str());
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    mCheckCompileErrors(fragmentShader, GL_COMPILE_STATUS);

    // Link shader program
    m_shader = glCreateProgram();
    glAttachShader(m_shader, vertexShader);
    glAttachShader(m_shader, fragmentShader);
    glLinkProgram(m_shader);
    mCheckCompileErrors(m_shader, GL_LINK_STATUS);

    // delete the shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


// --------- private ---------
const char* Shader::mReadFileToStr(const char* file_path)
{
    std::string fileStr;
    std::ifstream fileStream;

    fileStream.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        fileStream.open(file_path);
        
        std::stringstream strStream;

        strStream << fileStream.rdbuf();

        fileStream.close();  // close file stream

        fileStr = strStream.str();
    }
    catch(std::ifstream::failure e) {
        std::cout << "ERROR::FILE >>> File path: " << file_path << ", reason: " << e.code().message() << std::endl;
    }

    return fileStr.c_str();
}

void Shader::mCheckCompileErrors(uint shaderProgram, uint status)
{
    int success;
    char infoLog[512];

    glGetProgramiv(shaderProgram, status, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER >>> log info: " << infoLog << std::endl;
    }
}
