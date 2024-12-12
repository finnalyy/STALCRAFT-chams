#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <Windows.h>
#include <string>
#include "memory.h"
#include "Setting.h"

#include "KeyAuth/skStr.h"
#include "KeyAuth/auth.hpp"
#include "KeyAuth/utils.hpp"

using namespace KeyAuth;

std::string name = skCrypt("killcheat").decrypt(); // App name - VaultCord.com FREE Discord backup bot for members & your entire server saved from terms and nukes!
std::string ownerid = skCrypt("E6lHRajllG").decrypt(); // Account ID
std::string secret = skCrypt("2cf746451d1c7d2aa7aabbab3473c0aa4cbf4b9cc2974af60e39003bd7e60a1a").decrypt(); // Application secret (not used in latest C++ example)
std::string version = skCrypt("1.2").decrypt(); // Application version. Used for automatic downloads see video here https://www.youtube.com/watch?v=kW195PLCBKs
std::string url = skCrypt("https://keyauth.win/api/1.3/").decrypt();
std::string path = skCrypt("").decrypt();

api KeyAuthApp(name, ownerid, version, url, path);

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

typedef enum WINDOWCOMPOSITIONATTRIB {
    WCA_UNDEFINED,
    WCA_NCRENDERING_ENABLED,
    WCA_NCRENDERING_POLICY,
    WCA_TRANSITIONS_FORCEDISABLED,
    WCA_ALLOW_NCPAINT,
    WCA_CAPTION_BUTTON_BOUNDS,
    WCA_NONCLIENT_RTL_LAYOUT,
    WCA_FORCE_ICONIC_REPRESENTATION,
    WCA_EXTENDED_FRAME_BOUNDS,
    WCA_HAS_ICONIC_BITMAP,
    WCA_THEME_ATTRIBUTES,
    WCA_NCRENDERING_EXILED,
    WCA_NCADORNMENTINFO,
    WCA_EXCLUDED_FROM_LIVEPREVIEW,
    WCA_VIDEO_OVERLAY_ACTIVE,
    WCA_FORCE_ACTIVEWINDOW_APPEARANCE,
    WCA_DISALLOW_PEEK,
    WCA_CLOAK,
    WCA_CLOAKED,
    WCA_ACCENT_POLICY,
    WCA_FREEZE_REPRESENTATION,
    WCA_EVER_UNCLOAKED,
    WCA_VISUAL_OWNER,
    WCA_LAST,
} WINDOWCOMPOSITIONATTRIB;

typedef struct WINDOWCOMPOSITIONATTRIBDATA {
    WINDOWCOMPOSITIONATTRIB Attrib;
    PVOID pvData;
    SIZE_T cbData;
} WINDOWCOMPOSITIONATTRIBDATA;

typedef enum ACCENT_STATE {
    ACCENT_DISABLED,
    ACCENT_ENABLE_GRADIENT,
    ACCENT_ENABLE_TRANSPARENTGRADIENT,
    ACCENT_ENABLE_BLURBEHIND,
    ACCENT_INVALID_STATE
} ACCENT_STATE;

typedef struct ACCENT_POLICY {
    ACCENT_STATE AccentState;
    DWORD AccentFlags;
    DWORD GradientColor;
    DWORD AnimationId;
} ACCENT_POLICY;

typedef BOOL(WINAPI* pfnSetWindowCompositionAttribute)(HWND, WINDOWCOMPOSITIONATTRIBDATA*);
static auto SetWindowCompositionAttribute = (pfnSetWindowCompositionAttribute)GetProcAddress(LoadLibrary("user32.dll"), "SetWindowCompositionAttribute");

bool AuthenticateUser() {
    std::string key;
    std::cout << skCrypt("[ AUTH ] Enter license: ");
    std::cin >> key;

    KeyAuthApp.init();

    KeyAuthApp.license(key);

    if (KeyAuthApp.response.success) {
        std::cout << skCrypt("[ AUTH ] Authorization successful.\n");
        Sleep(400);
        return true;
    }
    else {
        std::cerr << skCrypt("[ AUTH ] Invalid key or access has expired.\n");
        Sleep(1000);
        return false;
    }
}

int main()
{

    HWND hWnd = GetConsoleWindow();
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);

    if (SetWindowCompositionAttribute) {
        ACCENT_POLICY accent = { ACCENT_ENABLE_BLURBEHIND, 0, 0, 0 };
        WINDOWCOMPOSITIONATTRIBDATA data;
        data.Attrib = WCA_ACCENT_POLICY;
        data.pvData = &accent;
        data.cbData = sizeof(accent);
        SetWindowCompositionAttribute(hWnd, &data);
    }
    //remove scroll bar
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStd, &csbi);
    COORD scrollbar = { csbi.srWindow.Right - csbi.srWindow.Left + 1, csbi.srWindow.Bottom - csbi.srWindow.Top + 1 };
    SetConsoleScreenBufferSize(hStd, scrollbar);

    std::thread titleThread(SetRandomTitleThread);
    titleThread.detach();
    if (!AuthenticateUser()) {
        std::cout << skCrypt("[ DEBUG ] Login ERROR") << std::endl;
        Sleep(1000);
        return 0;
    }

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
        std::cerr << skCrypt("\n\t[ ERROR ] Failed to open process with sufficient privileges!") << std::endl;
        return -1;
    }

    std::uintptr_t baseAddress = memory.GetModuleAddress("nvoglv64.dll");
    
    int attempt = 0;
    do {
        baseAddress = memory.GetModuleAddress("nvoglv64.dll");
        if (!baseAddress) {
            std::cout << "\r\t [ ATTEMPT " << ++attempt << " ] Still searching..." << std::flush;
            Sleep(200);
        }
    } while (!baseAddress);

    std::uintptr_t wallhackAddress = baseAddress + 0x7BC5B8;
    std::uintptr_t chamsAddress = baseAddress + 0x7BBEB8;

    system("cls");
    std::cout << skCrypt("\t\tDISCORD: https://discord.gg/Q7vHdgcb\n") << std::endl;
    std::cout << skCrypt("\n[ VK_NUMPAD1 ] WallHack") << std::endl;
    std::cout << skCrypt("\n[ VK_NUMPAD2 ] Chams") << std::endl;
    std::cout << skCrypt("\n[ VK_NUMPAD3 ] WallHack v2") << std::endl;
    std::cout << skCrypt("\n[ VK_NUMPAD4 ] Delete Effects on screen") << std::endl;
    while (true)
    {
        if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
        {
            BOOL result;
            SIZE_T bytesWritten;

            if (wallhackEnabled)
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)wallhackAddress, wallhackInstruction, sizeof(wallhackInstruction), &bytesWritten);
                if (result && bytesWritten == sizeof(wallhackInstruction))
                {
                    //std::cout << "Instruction reverted to original." << std::endl;
                }
                else
                {
                    std::cerr << "Failed to revert. Error: " << GetLastError() << std::endl;
                }
            }
            else
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)wallhackAddress, newWallHackInstruction, sizeof(newWallHackInstruction), &bytesWritten);

                if (result && bytesWritten == sizeof(newWallHackInstruction))
                {
                    //std::cout << "Instruction modified to shl r9d,04." << std::endl;
                }
                else
                {
                    std::cerr << "Failed to modify. Error: " << GetLastError() << std::endl;
                }
            }
            wallhackEnabled = !wallhackEnabled;
        }
        Sleep(50);
        if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
        {
            BOOL result;
            SIZE_T bytesWritten;

            if (chamsEnabled)
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)chamsAddress, chamsInstruction, sizeof(chamsInstruction), &bytesWritten);
                if (result && bytesWritten == sizeof(chamsInstruction))
                {
                    //std::cout << "Instruction reverted to original." << std::endl;
                }
                else
                {
                    std::cerr << skCrypt("Failed to revert. Error: ") << GetLastError() << std::endl;
                }
            }
            else
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)chamsAddress, newChamsInstruction, sizeof(newChamsInstruction), &bytesWritten);

                if (result && bytesWritten == sizeof(newChamsInstruction))
                {
                    //std::cout << "Instruction modified to shl r9d,04." << std::endl;
                }
                else
                {
                    std::cerr << skCrypt("Failed to modify. Error: ") << GetLastError() << std::endl;
                }
            }
            chamsEnabled = !chamsEnabled;
        }
        Sleep(50);
        if (GetAsyncKeyState(VK_NUMPAD3) & 0x8000)
        {
            BOOL result;
            SIZE_T bytesWritten;

            if (wallhackEnabledv2)
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)wallhackAddress, wallhackInstruction, sizeof(wallhackInstruction), &bytesWritten);
                if (result && bytesWritten == sizeof(wallhackInstruction))
                {
                    //std::cout << "Instruction reverted to original." << std::endl;
                }
                else
                {
                    std::cerr << "Failed to revert. Error: " << GetLastError() << std::endl;
                }
            }
            else
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)wallhackAddress, newWallhackInstructionv2, sizeof(newWallhackInstructionv2), &bytesWritten);

                if (result && bytesWritten == sizeof(newWallhackInstructionv2))
                {
                    //std::cout << "Instruction modified to shl r9d,04." << std::endl;
                }
                else
                {
                    std::cerr << "Failed to modify. Error: " << GetLastError() << std::endl;
                }
            }
            wallhackEnabledv2 = !wallhackEnabledv2;
        }
        Sleep(50);
        if (GetAsyncKeyState(VK_NUMPAD4) & 0x8000)
        {
            BOOL result;
            SIZE_T bytesWritten;

            if (deleteEffects)
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)chamsAddress, chamsInstruction, sizeof(chamsInstruction), &bytesWritten);
                if (result && bytesWritten == sizeof(chamsInstruction))
                {
                    //std::cout << "Instruction reverted to original." << std::endl;
                }
                else
                {
                    std::cerr << skCrypt("Failed to revert. Error: ") << GetLastError() << std::endl;
                }
            }
            else
            {
                result = WriteProcessMemory(memory.processHandle, (LPVOID)chamsAddress, deleteEffectsInstruction, sizeof(deleteEffectsInstruction), &bytesWritten);

                if (result && bytesWritten == sizeof(deleteEffectsInstruction))
                {
                    //std::cout << "Instruction modified to shl r9d,04." << std::endl;
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
