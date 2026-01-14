#pragma once
//----------------------------
// 生命周期Hook, 需要手动实现
//----------------------------
void Setup();
void Draw();
void Close();
//----------------------------
// 全局状态
//----------------------------
namespace WowState {
    // 缩放比例
    extern float scale;
    // 实时窗口尺寸
    extern int width;
    extern int height;
}
