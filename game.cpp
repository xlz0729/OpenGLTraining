//
//  game.h
//  OpenGLTraining
//
//  Created by 许立子 on 2019/11/25.
//  Copyright © 2019 xulizi. All rights reserved.
//


#include "game.h"
#include "cube_data.h"


std::unique_ptr<WindowsControl> g_window(new WindowsControl());

std::unique_ptr<Renderer> g_render(new Renderer());

Camera* g_master_camera = nullptr;


void GameMain::InitScene()
{
    g_render->EnableDepthTest();
    
    // 编译shader
    g_render->CompileShader("simple.vs", "simple.fs");

    unsigned int vertices_size = sizeof(data_vertices);
    unsigned int indices_size = sizeof(data_indices);

    // 将顶点数据装载到图形API里面
    g_render->BindVerticeData(data_vertices, vertices_size, data_indices, indices_size);
    // set position attribute
    g_render->VertexAttribPointer(0, 3, 5, 0);
    // set texture coord attribute
    g_render->VertexAttribPointer(1, 2, 5, 3);
    
    // 将纹理数据装载到图形API里面
    g_render->LoadTexture("container.jpg");
    g_render->LoadTexture("awesomeface.png", false);
    
    std::vector<std::string> tex_uniform = {
        "texture1", "texture2"
    };
    g_render->BindTexShader(tex_uniform);

    g_render->SetPerspectiveProjection(g_master_camera->GetFOV(), 0.1f, 100.0f);
    
    for (int i = 0; i < data_model_list.size(); i += 3) {
        RenderUnit unit(data_model_list[i], data_model_list[i+1], data_model_list[i+2], (float)i * 20.0f);
        unit.BindVertices(data_vertices, vertices_size, 0, 36);
        unit.BindIndices(data_indices, indices_size);
        
        m_render_unit_list.push_back(unit);
    }
}
