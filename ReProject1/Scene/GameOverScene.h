#pragma once
#include "BaseScene.h"
#include <memory>


class GameOverScene :
    public BaseScene
{
public:

    GameOverScene(unique_Base own);
    ~GameOverScene();
    
    unique_Base Update(unique_Base own) override;					// 更新
    void BaseDraw(void) override;					                // 更新
private:
    int cnt_;
    int playerSize_;
    unique_Base childScene_;
};

