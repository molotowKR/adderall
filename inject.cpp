#include <iostream>
#include "memory.hpp"
#include "xorstr.hpp"

#pragma warning(disable : 4996).

Injector inj;
DWORD pid;

LPVOID ntOpenFile = GetProcAddress(LoadLibraryW(L"ntdll"), "NtOpenFile");

bool DoesFileExist(const char* name) {
	if (FILE* file = fopen(name, "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}

void bypass()
{
	if (ntOpenFile) {
		char originalBytes[5];
		memcpy(originalBytes, ntOpenFile, 5);
		WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 5, NULL);
	}
	else
	{
		std::cout << xorstr_("Unable to bypass :(\n"); Sleep(2000); exit(-1);
	}
}

void Backup()
{
	if (ntOpenFile) {
		char originalBytes[5];
		memcpy(originalBytes, ntOpenFile, 5);
		WriteProcessMemory(inj.process, ntOpenFile, originalBytes, 0, NULL);
	}
	else
	{
		std::cout << xorstr_("Unable to backup :(\n"); Sleep(2000); exit(-1);
	}
}

int main()
{
	SetConsoleTitleA(xorstr_("DLL Injector by molotowKR"));

	int s{ 0 }; int t{ 0 }; std::string window{ xorstr_("") }; std::string module{ xorstr_("") }; std::string dllname{ xorstr_("") };
	system(xorstr_("cls")); std::cout << xorstr_("KETAMINE injector  \n"); std::cout << xorstr_("--------------------------------------- \n"); std::cout << xorstr_("1) Continue to injection\n2) Exit\n3) How to use\n command: "); std::cin >> t;

	system(xorstr_("cls")); switch (t)
	{
	case 1:
		std::cout << xorstr_("1) CS:GO\n2) VAC-BYPASS\n3) Steam\n command: "); std::cin >> s;

		if (s == 1)
		{
			std::cout << xorstr_("DLL name:  "); std::cin >> dllname;
			window = xorstr_("Counter-Strike: Global Offensive - Direct3D 9"); module = xorstr_("KETAMINE.dll"); dllname;
			ShellExecute(NULL, "open", "Methylenedioxymethamphetamine.exe", NULL, NULL, SW_SHOWDEFAULT);
		}
		if (s == 2) 
		{
			system("taskkill /F /T /IM steam.exe");
			std::cout << xorstr_("closing steam if open\n");			
			Sleep(6000);
			std::cout << xorstr_("loading vac bypass\n");
			ShellExecute(NULL, "open", "VAC-Bypass-Loader.exe", NULL, NULL, SW_SHOWDEFAULT);
			Sleep(14000);
			std::cout << xorstr_("lauching steam\n");
			Sleep(7000);
			std::cout << xorstr_("loading csgo\n");
			ShellExecute(NULL, "open", "steam://rungameid/730", NULL, NULL, SW_SHOWDEFAULT);
			Sleep(12000);
			std::cout << xorstr_("relaunching injector\n");
			Sleep(10000);
			ShellExecute(NULL, "open", "Methylenedioxymethamphetamine.exe", NULL, NULL, SW_SHOWDEFAULT);
			return 0; break;
		}
		if (s == 3) 
		{
			std::cout << xorstr_("DLL name:  "); std::cin >> dllname;
			window = xorstr_("Steam"); module = xorstr_("KETAMINE.dll"); dllname;
			ShellExecute(NULL, "open", "Methylenedioxymethamphetamine.exe", NULL, NULL, SW_SHOWDEFAULT);
		}

		inj.hwndproc = FindWindowA(0, window.c_str());

		GetWindowThreadProcessId(inj.hwndproc, &pid);
		inj.process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

		inj.clientDLL = inj.GetModule(pid, module.c_str());

		if (DoesFileExist(dllname.c_str())) {
			bypass();

			if (inj.inject(pid, dllname.c_str())) {
				std::cout << xorstr_("\nInjected, enjoy :)") << std::endl;
				Backup(); Sleep(1500); return 0;
			}
			else { std::cout << xorstr_("\nInjection failed") << std::endl; Backup(); Sleep(2000); return 0; }
		}
		break;

	case 2: return 0; break;

	case 3: MessageBoxA(NULL, (LPCSTR)"1. Make sure the dll you want to inject is in the same folder as the injector\n2. Select function 1.\n3. Select game\n4. Enjoy!\n", (LPCSTR)"help", MB_OK); Sleep(100); main(); break;

	default: std::cout << xorstr_("Unknown command"); break;
	}
	Sleep(2000); main();
}

//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this softwareand associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies of the Software, and to permit persons to whom the Software is
//furnished to do so, subject to the following conditions :
//
//The above copyright noticeand this permission notice shall be included in all
//copies or substantial portions of the Software.
//
//THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
//AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//SOFTWARE.


