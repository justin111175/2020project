#pragma once
#include "BaseScene.h"


class MingameScene :
    public BaseScene
{
public:

    MingameScene(unique_Base own, int no);
    ~MingameScene();

    unique_Base Update(unique_Base own) override;					// 更新

    void BaseDraw(void) override;					                // 更新


private:
    unique_Base childScene_;

    bool isClear(void);
    int cnt_;
    int divTable[3] = { 2,3,4 };									// 分割数を格納したテーブル

    std::vector<int> DivBase_;
    std::vector<int*> Div_;

    int classCnt_;
    int Size_;
    int blackID_;
    void SwapNum(int* num1, int* num2);
    void PanelCtl(InputID id);
    Vector2 Panel_;
    Vector2 NextPanel_;
};

