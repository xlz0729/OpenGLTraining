//
//  Created by Lizio Xu on 2019/6/16.
//  Copyright © 2019 xulizi. All rights reserved.
//

#include <iostream>

#include "const.h"
#include "define.h"
#include "game.h"


int main(int argc, const char * argv[])
{
    GameMain my_game;
    
    my_game.InitGame();     // 在这里初始化窗口，图形API，摄像头
    
    my_game.InitScene();    // 在这里初始化渲染数据
    
    my_game.MainLoop();
    
    my_game.Terminate();

    return 0;
}
