#ifndef __DEBUG_WINDOW_H
#define __DEBUG_WINDOW_H

#include "sstring.hpp"
#pragma warning(disable:4530) //we don't do exception handling
#include <list>
#pragma warning(default:4530)

using namespace std;

class DebugWindow  
{
public:
	DebugWindow();
	~DebugWindow();
	
	static bool create();
	static void destroy();
	static DebugWindow* get();
	void append(const char* str);

private:
	HWND hwnd;
	HWND hList;
	HANDLE hThread;
	int max_entries;
	static DebugWindow* instance;
	CRITICAL_SECTION cs;
	HMENU menu;
	list<sstring> includes;
	list<sstring> excludes;

	static BOOL CALLBACK DebugDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static BOOL CALLBACK FilterDlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	void InitDialog(HWND hwnd);
	void HandleMenu();
	void AppendLog(char* msg);
	void WriteToFile();
	static DWORD WINAPI thread(void* param);
};

#endif
