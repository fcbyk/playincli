#include <iostream>
#include <windows.h>
using namespace std;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

int main() {
    SetConsoleOutputCP(65001);

    int currentOption = 0;
    const int numOptions = 3;
    string options[] = {"贪吃蛇", "俄罗斯方块", "坦克大战"};
    const string separator = "  ";

    const int defaultColor = 15;    // 白色
    const int selectedColor = 10;   // 绿色
    const int promptColor = 14;     // 黄色

    // 隐藏光标
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);

    // 添加操作提示
    setColor(promptColor);
    cout << "使用 ← → 键选择，Enter 确认\n\n";
    setColor(defaultColor);

    bool leftKeyPressed = false;
    bool rightKeyPressed = false;
    bool enterKeyPressed = false;

    // 清除所有按键状态
    while (GetAsyncKeyState(VK_RETURN) & 0x8000) Sleep(1);
    while (GetAsyncKeyState(VK_LEFT) & 0x8000) Sleep(1);
    while (GetAsyncKeyState(VK_RIGHT) & 0x8000) Sleep(1);

    // 初始显示
    for (int i = 0; i < numOptions; i++) {
        if (i == currentOption) {
            setColor(selectedColor);
        } else {
            setColor(defaultColor);
        }
        cout << options[i];
        if (i < numOptions - 1) cout << separator;
    }

    while (true) {
        // 左键检测
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            if (!leftKeyPressed) {
                currentOption = (currentOption - 1 + numOptions) % numOptions;
                leftKeyPressed = true;
            }
        } else {
            leftKeyPressed = false;
        }

        // 右键检测
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            if (!rightKeyPressed) {
                currentOption = (currentOption + 1) % numOptions;
                rightKeyPressed = true;
            }
        } else {
            rightKeyPressed = false;
        }

        // 返回行首并重新显示
        cout << "\r";
        for (int i = 0; i < numOptions; i++) {
            if (i == currentOption) {
                setColor(selectedColor);
            } else {
                setColor(defaultColor);
            }
            cout << options[i];
            if (i < numOptions - 1) cout << separator;
        }

        // 回车键检测
        if (GetAsyncKeyState(VK_RETURN) & 0x8000) {
            if (!enterKeyPressed) {  // 只在首次按下时响应
                cout << "\n\n";
                setColor(defaultColor);
                cout << "您已选择：" << options[currentOption] << "\n\n";
                setColor(promptColor);
                cout << "按任意键继续..." << endl;
                setColor(defaultColor);
                enterKeyPressed = true;
                break;
            }
        } else {
            enterKeyPressed = false;
        }

        Sleep(50);
    }

    cin.get();
    cin.get();
    return 0;
}