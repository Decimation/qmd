#pragma once

#pragma comment(lib,"Winmm.lib")
#include <cassert>
#include <iostream>
#include <Windows.h>

#include  <string>

#ifdef _UNICODE
#define _tcslen     wcslen
#else
#define _tcslen     strlen
#endif

int main();
int SendKeystrokes(const TCHAR* const text, const std::wstring& lpClassName);

