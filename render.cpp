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
void Render::mLoadTextureImg()
{
    int width, height, nrChannels;
    std::string texPath = TEXTURE_DIR + TEXTURE_NAME;
    unsigned char *data = stbi_load(texPath.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
}
