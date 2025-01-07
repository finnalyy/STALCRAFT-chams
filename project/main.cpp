#pragma region Includes
#include <iostream>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <chrono>
#include <thread>
#include <cstdlib>
#include "memory.h"
#include "Setting.h"

#include "KeyAuth/skStr.h"
#include "KeyAuth/auth.hpp"
#include "KeyAuth/utils.hpp"
#pragma endregion

#pragma region KeyAuth
using namespace KeyAuth;

std::string name = skCrypt("").decrypt();
std::string ownerid = skCrypt("").decrypt();
std::string secret = skCrypt("").decrypt();
std::string version = skCrypt("").decrypt();
std::string url = skCrypt("https://keyauth.win/api/1.3/").decrypt();
std::string path = skCrypt("").decrypt();

api KeyAuthApp(name, ownerid, version, url, path);
#pragma endregion

#pragma region randomTitle
static const char rnum[] = "0123456789" "qwertyuiopasdfghjklzxcvbnm" "QWERTYUIOPASDFGHJKLZXCVBNM";
int staticLength = sizeof(rnum) - 1;
std::string RandomTitle;

char GetRandom() {
    return rnum[rand() % staticLength];
}
void SetRandomTitle() {
    RandomTitle.clear();
    for (unsigned int i = 0; i < 1; ++i) {
        RandomTitle += GetRandom();
    }
    SetConsoleTitle(RandomTitle.c_str());

}
void SetRandomTitleThread() {
    while (true) {
        SetRandomTitle();
        std::this_thread::sleep_for(std::chrono::seconds(0));
    }
}
#pragma endregion

#pragma region ASCII
void SetConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void AsciiName() {
    std::cout << skCrypt(R"(
           __ _                   _                         
          / _(_)                 | |                        
         | |_ _ _ __  _ __   __ _| |_   _ _ __   ___  _ __  
         |  _| | '_ \| '_ \ / _` | | | | | '_ \ / _ \| '_ \ 
         | | | | | | | | | | (_| | | |_| | | | | (_) | |_) |
         |_| |_|_| |_|_| |_|\__,_|_|\__, |_| |_|\___/| .__/ 
                                     __/ |           | |    
                                    |___/            |_|                                                                                                             
    )") << std::endl;

    // Blue line
    SetConsoleColor(8);
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~https://github.com/finnalynop~~~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
    SetConsoleColor(7); // Reset to default color
}
#pragma endregion

//#pragma region Auth
//bool AuthenticateUser() {
//    AsciiName();
//    std::string key;
//    std::cout << skCrypt("[ AUTH ] Enter license: ");
//    std::cin >> key;
//
//    KeyAuthApp.init();
//
//    KeyAuthApp.license(key);
//
//    if (KeyAuthApp.response.success) {
//        std::cout << skCrypt("[ AUTH ] Authorization successful.\n");
//        Sleep(400);
//        return true;
//    }
//    else {
//        std::cerr << skCrypt("[ AUTH ] Invalid key or access has expired.\n");
//        Sleep(1000);
//        return false;
//    }
//}
//#pragma endregion

#pragma region Menu
void cheatMenu() {
    AsciiName();
    std::cout << skCrypt("\n[ F ] WallHack [ TEST ]") << std::endl;
    std::cout << skCrypt("\n[ Z ] Chams [ CRASH GAME ]") << std::endl;
    std::cout << skCrypt("\n[ X ] Delete Effects") << std::endl;
    std::cout << skCrypt("\n[ C ] WallHack") << std::endl;
}
#pragma endregion


int main()
{
    HWND hWnd = GetConsoleWindow();
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);

    // Remove scroll bar
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStd, &csbi);
    COORD scrollbar = { csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1 };
    SetConsoleScreenBufferSize(hStd, scrollbar);

    std::thread titleThread(SetRandomTitleThread);
    titleThread.detach();

    //if (!AuthenticateUser()) {
    //    std::cout << skCrypt("[ DEBUG ] Login ERROR") << std::endl;
    //    Sleep(1000);
    //    return 0;
    //}

    DWORD pid = pidder::get_process_id("stalcraft.exe");
    if (!pid) {
        std::cout << skCrypt("[ INFO ] Trying to find game..\n");
        do {
            pid = pidder::get_process_id("stalcraft.exe");
            Sleep(200UL);
        } while (!pid);
    }

    Memory memory;
    memory.processId = pid;
    memory.processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

    if (!memory.processHandle) {
        std::cerr << skCrypt("\n\t[ ERROR ] Failed to open process!") << std::endl;
        return -1;
    }

    std::uintptr_t baseAddress = memory.GetModuleAddress("nvoglv64.dll");
    
    const std::string spinner = "|/-\\";
    int attempt = 0;

    do {
        uintptr_t baseAddress = memory.GetModuleAddress("nvoglv64.dll");
        bool baseAddressFound = (baseAddress != 0);
        ++attempt;
        std::cout << "\r" << "[ INFO ] Loading [" << spinner[attempt % spinner.length()] << "]";
        std::cout.flush();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));

        if (baseAddressFound) break;
    } while (true);

    
    /* OFFSETS */
    /* https://youtu.be/j9dK4v_z8WA */
    
    std::uintptr_t wallhackAddress = baseAddress + 0x7BC5B8;
    std::uintptr_t chamsAddress = baseAddress + 0x7BBEB8;

    system("cls");
    cheatMenu();
    while (true)
    {
        if (GetAsyncKeyState(0x5A) & 0x8000) // - Z
        {
            BOOL result;
            SIZE_T bytesWritten;

            if (wallhackEnabled)
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)wallhackAddress, wallhackInstruction, sizeof(wallhackInstruction), &bytesWritten);
                if (result && bytesWritten == sizeof(wallhackInstruction))
                {
                    //std::cout << "modified" << std::endl;
                }
                else
                {
                    std::cerr << "Failed to modify. Error: " << GetLastError() << std::endl;
                }
            }
            else
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)wallhackAddress, newWallHackInstruction, sizeof(newWallHackInstruction), &bytesWritten);

                if (result && bytesWritten == sizeof(newWallHackInstruction))
                {
                    //std::cout << "modified" << std::endl;
                }
                else
                {
                    std::cerr << "Failed to modify. Error: " << GetLastError() << std::endl;
                }
            }
            wallhackEnabled = !wallhackEnabled;
        }
        Sleep(50);
        if (GetAsyncKeyState(0x58) & 0x8000) // - X
        {
            BOOL result;
            SIZE_T bytesWritten;

            if (chamsEnabled)
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)chamsAddress, chamsInstruction, sizeof(chamsInstruction), &bytesWritten);
                if (result && bytesWritten == sizeof(chamsInstruction))
                {
                    //std::cout << "modified" << std::endl;
                }
                else
                {
                    std::cerr << skCrypt("Failed to modify. Error: ") << GetLastError() << std::endl;
                }
            }
            else
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)chamsAddress, newChamsInstruction, sizeof(newChamsInstruction), &bytesWritten);

                if (result && bytesWritten == sizeof(newChamsInstruction))
                {
                    //std::cout << "modified" << std::endl;
                }
                else
                {
                    std::cerr << skCrypt("Failed to modify. Error: ") << GetLastError() << std::endl;
                }
            }
            chamsEnabled = !chamsEnabled;
        }
        Sleep(50);
        if (GetAsyncKeyState(0x43) & 0x8000) // - C
        {
            BOOL result;
            SIZE_T bytesWritten;

            if (wallhackEnabledv2)
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)wallhackAddress, wallhackInstruction, sizeof(wallhackInstruction), &bytesWritten);
                if (result && bytesWritten == sizeof(wallhackInstruction))
                {
                    //std::cout << "modified" << std::endl;
                }
                else
                {
                    std::cerr << "Failed to modify. Error: " << GetLastError() << std::endl;
                }
            }
            else
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)wallhackAddress, newWallhackInstructionv2, sizeof(newWallhackInstructionv2), &bytesWritten);

                if (result && bytesWritten == sizeof(newWallhackInstructionv2))
                {
                    //std::cout << "modified" << std::endl;
                }
                else
                {
                    std::cerr << "Failed to modify. Error: " << GetLastError() << std::endl;
                }
            }
            wallhackEnabledv2 = !wallhackEnabledv2;
        }
        Sleep(50);
        if (GetAsyncKeyState(0x46) & 0x8000) // - F
        {
            BOOL result;
            SIZE_T bytesWritten;

            if (deleteEffects)
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)chamsAddress, chamsInstruction, sizeof(chamsInstruction), &bytesWritten);
                if (result && bytesWritten == sizeof(chamsInstruction))
                {
                    //std::cout << "modified" << std::endl;
                }
                else
                {
                    std::cerr << skCrypt("Failed to modify. Error: ") << GetLastError() << std::endl;
                }
            }
            else
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)chamsAddress, deleteEffectsInstruction, sizeof(deleteEffectsInstruction), &bytesWritten);

                if (result && bytesWritten == sizeof(deleteEffectsInstruction))
                {
                    //std::cout << "modified" << std::endl;
                }
                else
                {
                    std::cerr << skCrypt("Failed to modify. Error: ") << GetLastError() << std::endl;
                }
            }
            deleteEffects = !deleteEffects;
        }
    }

    return 0;
}
