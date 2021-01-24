#ifdef _MSC_VER
#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )
#endif

#include <stdio.h>
#include <Windows.h>
#include <iostream>
using namespace std;

int main()
{
	bool pauseflag = true;
	bool winFrontState = true;
	bool firstInit = true;
	int posLeft, posTop, width, height;
	RECT rectpos;
	HWND handle = FindWindow(NULL, "画中画");
	if (handle)
	{
		GetWindowRect(handle, &rectpos);

		posLeft = rectpos.left;
		posTop = rectpos.top;
		width = rectpos.right - rectpos.left;
		height = rectpos.bottom - rectpos.top;
		// cout << rectpos.left << "  " <<  rectpos.top << "  " << rectpos.right - rectpos.left << "  " << rectpos.bottom - rectpos.top << endl;

		MessageBox(NULL, "程序已运行，按住Ctrl键播放，松开Ctrl隐藏窗口并暂停。\n关闭请用任务管理器。", "提示", 0);

		while (true)
		{
			if (GetAsyncKeyState(VK_RSHIFT) && 0x8000)
			{
				if (!pauseflag)
				{
					if(!firstInit && winFrontState)
					{
						SetForegroundWindow(handle);
						PostMessage(handle, WM_KEYDOWN, VK_SPACE, 0);
						pauseflag = true;
						SetWindowPos(handle, HWND_TOPMOST, posLeft, posTop, width, height, SWP_SHOWWINDOW);
						winFrontState = false;
					}
					else 
					{
						firstInit = false;
					}
				}
			}
			else
			{
				if (pauseflag)
				{
					SetForegroundWindow(handle);
					PostMessage(handle, WM_KEYDOWN, VK_SPACE, 0);
					SetWindowPos(handle, HWND_TOPMOST, posLeft, posTop, width, height, SWP_HIDEWINDOW);
					pauseflag = false;
					winFrontState = true;
				}
			}
		}
	}
	else
	{
		MessageBox(NULL, "未发现画中画窗口句柄", "提示", 0);
		return 0;
	}

	return 0;
}