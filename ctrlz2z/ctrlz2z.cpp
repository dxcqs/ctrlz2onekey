//code by dxcqs
#include <Windows.h>
#include <WinUser.h>
#include <stdio.h>

int total_num = 0;
HHOOK _hook;
KBDLLHOOKSTRUCT kbdStruct;
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode >= 0)
	{
		// the action is valid: HC_ACTION.
		if (wParam == WM_KEYDOWN && (*((KBDLLHOOKSTRUCT*)lParam)).vkCode == 192)//192 为 ` 键的代码,其余请到 https://www.cnblogs.com/xuandi/p/5362374.html 查询
		{
			INPUT keyEvent = { 0 };
			keyEvent.type = INPUT_KEYBOARD;
			keyEvent.ki.wVk = VK_CONTROL;
			keyEvent.ki.wScan = MapVirtualKey(VK_CONTROL, 0);
			::SendInput(1, &keyEvent, sizeof(keyEvent));

			keyEvent.ki.wVk = 0x5A;
			keyEvent.ki.wScan = MapVirtualKey(0x5A, 0);
			::SendInput(1, &keyEvent, sizeof(keyEvent));

			Sleep(100);
			keyEvent.ki.dwFlags = KEYEVENTF_KEYUP;//默认keyEvent.ki.dwFlags  = 0 ，即 KEYEVENTF_KEYDOWN
			::SendInput(1, &keyEvent, sizeof(keyEvent));
			keyEvent.ki.wVk = VK_CONTROL;
			keyEvent.ki.wScan = MapVirtualKey(VK_CONTROL, 0);
			::SendInput(1, &keyEvent, sizeof(keyEvent));

			printf("\rCtrl+Z : %d", total_num++);
		}
	}
	return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void SetHook()
{
	if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0)))
	{
		MessageBox(NULL, "Failed to install hook!", "Error", MB_ICONERROR);
	}
}

void ReleaseHook()
{
	UnhookWindowsHookEx(_hook);
}

int main(void)
{
	printf("code by dxcqs\n");
	printf("使用方法 : 点击键盘左上角的那个\"`\"键即可完成ctrl+z的输入\n");
	printf("请注意有0.1秒的延时哦,不要太大力了...也不要关闭这个黑色窗口\n\n");
	SetHook();
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
	}
	return 0;
}

