/******************************************************************************
 *    delve.cc
 *
 *    This file is part of Object Script Module
 *    Copyright (C) 2004 Tom N Harris <telliamed@whoopdedo.cjb.net>
 *
 *    Permission is hereby granted, free of charge, to any person obtaining
 *    a copy of this software and associated documentation files (the 
 *    "Software"), to deal in the Software without restriction, including 
 *    without limitation the rights to use, copy, modify, merge, publish, 
 *    distribute, sublicense, and/or sell copies of the Software, and to 
 *    permit persons to whom the Software is furnished to do so.
 *    
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 *    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES 
 *    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-
 *    INFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS 
 *    BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN 
 *    AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR 
 *    IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 *    THE SOFTWARE.
 *
 *****************************************************************************/

#include "delve.h"

#include <stdio.h>
#include <cstring>

#include <lg/scrmanagers.h>
#include <lg/malloc.h>

IMalloc *g_pMalloc = NULL;
IScriptMan *g_pScriptManager = NULL;
MPrintfProc g_pfnMPrintf = NULL;

extern "C" void explore_guids(void);
extern "C" void explore_sndmixer(void);

extern "C" __declspec(dllexport) __stdcall 
int ScriptModuleInit (const char* pszName, 
                      IScriptMan* pScriptMan,
                      MPrintfProc pfnMPrintf,
                      IMalloc* pMalloc,
                      IScriptModule** pOutInterface)
{
    printf("delve: ScriptModuleInit(%s, %p, %p, %p, %p)\n",
        pszName, pScriptMan, pfnMPrintf, pMalloc, pOutInterface);

    *pOutInterface = NULL;

    g_pScriptManager = pScriptMan;
#ifdef _DEBUG
    pMalloc->QueryInterface(IID_IDebugMalloc, reinterpret_cast<void**>(&g_pMalloc));
    if (!g_pMalloc)
        g_pMalloc = pMalloc;
#else
    g_pMalloc = pMalloc;
#endif

    g_pfnMPrintf = reinterpret_cast<MPrintfProc>(pfnMPrintf);

    if (!g_pScriptManager || !g_pMalloc)
        return 0;

    // Actually we don't want to load successfully! Just do some poking and
    // print the output to the monolog, then return failure.

    explore_guids();
    explore_sndmixer();

    return 0;
}

#define USE_CONSOLE 1
#define ALLOC_CONSOLE 0

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    switch (reason) {
    case DLL_PROCESS_ATTACH: {
#if USE_CONSOLE
#if ALLOC_CONSOLE
        // Allocate a console for handy viewing.
        AllocConsole();
#endif //ALLOC_CONSOLE
        freopen("CONOUT$", "w", stdout);

        // FIXME: for my convenience, let's put the console in
        //        a handy location.
        HWND hwnd = GetConsoleWindow();
        RECT rect;
        GetWindowRect(hwnd, &rect);
        int left = 1930;
        int top = 480;
        int width = (int)(rect.right - rect.left);
        int height = (int)(rect.bottom - rect.top);
        MoveWindow(hwnd, left, top, width, height, TRUE);
#endif //USE_CONSOLE

        printf("delve: DLL_PROCESS_ATTACH\n");
        printf("delve: EXE Base address: 0x%08x\n", (unsigned int)GetModuleHandle(NULL));
        printf("delve: DLL base address: 0x%08x\n", (unsigned int)hModule);
        printf("\n");
    } break;
    case DLL_PROCESS_DETACH: {
#if USE_CONSOLE
#if ALLOC_CONSOLE
        FreeConsole();
#endif //ALLOC_CONSOLE
#endif //USE_CONSOLE
    } break;
    }
    return true;
}
