// MRI-Loader.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <Windows.h>
#include "include/detours.h"

#pragma comment(lib,"Shlwapi.lib")
#pragma comment(lib,"detours.lib")

bool injectDLL(std::string a, std::string b);

int main(int argc, char *argv[]) {
	std::cout << "MRI Patch created by DeNial" << std::endl;
	std::cout << std::endl;

	std::string EXEPath;
	std::string DLLPath;
	TCHAR pwd[MAX_PATH];

	GetCurrentDirectory(MAX_PATH, pwd);
	EXEPath = pwd;
	DLLPath = pwd;
	DLLPath.append("\\MRI-Patch.dll");

	if (argc == 2) {
		EXEPath = argv[1];
	} else {
		std::cout << " To run a different program, just drag the desired program onto this" << std::endl;
		std::cout << " and it will automatically run!" << std::endl;
		std::cout << " To run via command line, use " << std::endl;
		std::cout << "    MRI-Loader.exe \"{PATH-TO-FILE}\"" << std::endl;
	}

	if (!injectDLL(EXEPath, DLLPath)) {
		std::cout << "Failed to load MRI patch." << std::endl;
		system("pause > nul");
	} else {
		std::cout << "Successfully loaded MRI patch." << std::endl;
	}
    return 0;
}

bool injectDLL(std::string processPath, std::string dllPath) {
	STARTUPINFOA _StartupInfo;
	PROCESS_INFORMATION _Information;

	ZeroMemory(&_StartupInfo, sizeof(STARTUPINFOA));
	ZeroMemory(&_Information, sizeof(PROCESS_INFORMATION));

	_StartupInfo.cb = sizeof(STARTUPINFOA);

	TCHAR pwd[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, pwd);

	if (DetourCreateProcessWithDllA(processPath.c_str(), NULL, NULL, NULL, TRUE,
		CREATE_DEFAULT_ERROR_MODE, NULL, pwd, &_StartupInfo, &_Information, dllPath.c_str(), NULL)) {
		return 1;
	} else {
		return 0;
	}
}