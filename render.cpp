//
//  render.cpp
//  OpenGLTraining
//
//  Created by 许立子 on 2019/11/4.
//  Copyright © 2019 xulizi. All rights reserved.
//

#include "render.hpp"

// 这个头文件只可以放在cpp文件下
#define STB_IMAGE_IMPLEMENTATION // 将下面的头文件转成cpp文件
#include "external/stb_image.h"


// load image, create texture and generate mipmaps
void Render::mLoadTextureImg(std::string texture_name, GLenum format)
{
    stbi_set_flip_vertically_on_load(true);
    int width, height, nrChannels;
    std::string texPath = TEXTURE_DIR + texture_name;
    unsigned char *data = stbi_load(texPath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}

// 坐标变换
void Render::mCoordinateTransformation()
{
    // create transformations
    // local transformation
    glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0, 0.0, 1.0));
    
    m_shader->SetMat4("transform", transform);
}

// 视窗变换，这里决定了是透视矩阵还是正交矩阵，透视矩阵的FOV也应当在这里设置
void Render::mProjectionTransformation()
{
    // projection transformation
    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(g_Camera->GetFOV()), (float)WINDOW_WIDTH / (float)WINDOW_HEIGH, 0.1f, 100.0f); // 透视矩阵
    // projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f); // 正交矩阵
    m_shader->SetMat4("projection", projection);
}
