//
//  game.h
//  OpenGLTraining
//
//  Created by 许立子 on 2019/11/25.
//  Copyright © 2019 xulizi. All rights reserved.
//

#ifndef game_h
#define game_h

#include <memory>
#include <vector>

#include "renderer.h"
#include "windows_control.h"
#include "camera.h"
#include "render_unit.h"


extern std::unique_ptr<WindowsControl> g_window;

extern std::unique_ptr<Renderer> g_render;

extern Camera* g_master_camera;


class GameMain
{
public:
    GameMain()
    {}
    
    ~GameMain()
    {
        for (auto camera : m_camera_list) {
            camera.Release();
        }
        m_camera_list.clear();
        g_master_camera = nullptr;
    }
    
    void InitGame()
    {
        g_window->InitWindow();
        
        g_render->InitRenderer();
        
        // 一定有一个主摄像头
        Camera master_camera;
        m_camera_list.push_back(master_camera);
        g_master_camera = &m_camera_list[0];
    }
    
    void InitScene();
    
    void MainLoop()
    {
        // main loop
        while(!g_window->WindowShouldClose()) {
            // step 1. preprocess
            Preprocess();

            // step 2. logic loop
            LogicLoop();
            
            // step 3. render loop
            RenderLoop();
            
            // step 4. swap buffers
            g_window->Postprocess();
            
            // step 5. postprocess
            Postprocess();
        }
    }
    
    void Preprocess()
    {
        g_window->ProcessKeyboard();
    }
    
    void LogicLoop()
    {
        g_master_camera->UpdateViewMatrix();
        
        for (auto& unit : m_render_unit_list) {
            unit.UpdateData(glfwGetTime());
        }
    }
    
    void RenderLoop()
    {
        g_render->PreRender();
        
        g_render->ActiveTexture();
        
        g_render->ActiveShader();
        
        g_render->BindVertexArray();
        
        g_render->SetViewMatrix(g_master_camera->GetViewMatrix());
        
        for (auto unit : m_render_unit_list) {
            g_render->RenderOneUnit(unit);
        }
        
        float currentFrame = glfwGetTime();
        g_DeltaTime = currentFrame - g_LastFrame;
        g_LastFrame = currentFrame;
    }
    
    void Postprocess()
    {}
    
    void Terminate()
    {
        // glfw: terminate, clearing all previously allocated GLFW resources.
        glfwTerminate();
    }

private:
    std::vector<Camera>     m_camera_list;
    
    std::vector<RenderUnit> m_render_unit_list;
};

#endif /* game_h */
