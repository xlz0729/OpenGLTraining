//
//  shader_gl.cpp
//  OpenGLTraining
//
//  Created by 许立子 on 2019/10/25.
//  Copyright © 2019 xulizi. All rights reserved.
//

#include "shader_gl.h"


Shader::Shader(std::string vertexName, std::string fragmentName, std::string geometryName)
{
    // 0. get right file path
    std::string vertexPathStr = SHADER_DIR + vertexName;
    const char* vertexPath = vertexPathStr.c_str();
    std::string fragmentPathStr = SHADER_DIR + fragmentName;
    const char* fragmentPath = fragmentPathStr.c_str();
    const char* geometryPath;
    if (geometryName == "") {
        geometryPath = nullptr;
    }
    else {
        std::string geometryPathStr = SHADER_DIR + geometryName;
        geometryPath = geometryPathStr.c_str();
    }
    
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::string geometryCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    std::ifstream gShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    gShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    try {
        // open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
        // if geometry shader path is present, also load a geometry shader
        if(geometryPath != nullptr)
        {
            gShaderFile.open(geometryPath);
            std::stringstream gShaderStream;
            gShaderStream << gShaderFile.rdbuf();
            gShaderFile.close();
            geometryCode = gShaderStream.str();
        }
    }
    catch (std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();

    // 2. compile shaders
    // vertex shader
    uint vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    mCheckCompileErrors(vertex, "VERTEX");
    // fragment Shader
    uint fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    mCheckCompileErrors(fragment, "FRAGMENT");

    // if geometry shader is given, compile geometry shader
    uint geometry = 0;
    if(geometryPath != nullptr) {
        const char * gShaderCode = geometryCode.c_str();
        geometry = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry, 1, &gShaderCode, NULL);
        glCompileShader(geometry);
        mCheckCompileErrors(geometry, "GEOMETRY");
    }

    // shader Program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    if(geometryPath != nullptr) {
        glAttachShader(ID, geometry);
    }
    glLinkProgram(ID);
    mCheckCompileErrors(ID, "PROGRAM");

    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(geometryPath != nullptr) {
        glDeleteShader(geometry);
    }
}


// utility function for checking shader compilation/linking errors.
// ------------------------------------------------------------------------
void Shader::mCheckCompileErrors(unsigned int shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
