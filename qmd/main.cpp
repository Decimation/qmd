// qmd.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "main.h"

#include <format>

int main()
{
	// PlaySound(TEXT("C:\\Library\Audio\\bottlecap.wav"), NULL, SND_FILENAME | SND_SYNC | SND_NODEFAULT);
	// std::cout << "Hello World!\n";

	SendKeystrokes(L"hello", L"Notepad");
}


int SendKeystrokes(const TCHAR* const text, const std::wstring lpClassName)
{
	assert(text != NULL);

	HWND hWnd = FindWindow(lpClassName.c_str(), nullptr);

	if (hWnd == nullptr)
		return 0;

	HWND fw = GetForegroundWindow();
	std::string sz = std::format("{} {}", (void*)fw, (void*)hWnd);
	OutputDebugStringA(sz.c_str());

	if (!SetForegroundWindow(hWnd))
		return 0;

	//Fill in the array of keystrokes to send.
	const UINT characterCount = _tcslen(text);
	const UINT keystrokesToSend = characterCount * 2;

	auto keystroke = new INPUT[keystrokesToSend];

	for (UINT i = 0; i < characterCount; ++i) {
		keystroke[i * 2].type = INPUT_KEYBOARD;
		keystroke[i * 2].ki.wVk = 0;
		keystroke[i * 2].ki.wScan = text[i];
		keystroke[i * 2].ki.dwFlags = KEYEVENTF_UNICODE;
		keystroke[i * 2].ki.time = 0;
		keystroke[i * 2].ki.dwExtraInfo = GetMessageExtraInfo();

		keystroke[i * 2 + 1].type = INPUT_KEYBOARD;
		keystroke[i * 2 + 1].ki.wVk = 0;
		keystroke[i * 2 + 1].ki.wScan = text[i];
		keystroke[i * 2 + 1].ki.dwFlags = KEYEVENTF_UNICODE | KEYEVENTF_KEYUP;
		keystroke[i * 2 + 1].ki.time = 0;
		keystroke[i * 2 + 1].ki.dwExtraInfo = GetMessageExtraInfo();
	}

	//Send the keystrokes.
	const UINT keystrokesSent = SendInput((UINT)keystrokesToSend, keystroke, sizeof(*keystroke));

	delete[] keystroke;

	// SetForegroundWindow(fw);
	Sleep(1000);
	SetForegroundWindow(fw);

	return keystrokesSent == keystrokesToSend;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
