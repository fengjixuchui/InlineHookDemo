// HookCreateProcess.cpp : Defines the entry point for the DLL application.
//
#include "windows.h"
#include "stdafx.h"
#include "InlineHook.h"

// ����һ����ΪCreateProcessHook��CInlineHook��
CInlineHook CreateProcessHook;

// ����ʵ�ֵ�Hook����
BOOL WINAPI MyCreateProcessW(
    LPCWSTR               lpApplicationName,
    LPWSTR                lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL                  bInheritHandles,
    DWORD                 dwCreationFlags,
    LPVOID                lpEnvironment,
    LPCWSTR               lpCurrentDirectory,
    LPSTARTUPINFOW        lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
    )
{
    BOOL bRet = FALSE;
	// ��������ĳ�����wscript.exe����ֱ�ӷ���
	BOOL bFind = FALSE;
	if (lpApplicationName)
	{
		if( wcsicmp(lpApplicationName, L"c:\\windows\\system32\\wscript.exe") == 0 )
			bFind = TRUE;
	}
	if (lpCommandLine)
	{
		if(wcsstr(wcslwr(lpCommandLine), L"c:\\windows\\system32\\wscript.exe"))
			bFind = TRUE;
	}
	if (bFind == FALSE)
    {	
		CreateProcessHook.UnHook();
        bRet = CreateProcessW(lpApplicationName,
                        lpCommandLine,
                        lpProcessAttributes,
                        lpThreadAttributes,
                        bInheritHandles,
                        dwCreationFlags,
                        lpEnvironment,
                        lpCurrentDirectory,
                        lpStartupInfo,
                        lpProcessInformation);
         CreateProcessHook.ReHook();
    } 
	else
    {
		if(MessageBox(NULL, "��⵽�ű������Ѿ��������Ƿ����أ�", "��Ҫ��ʾ", MB_YESNO) == IDNO)
		{
			CreateProcessHook.UnHook();
			bRet = CreateProcessW(lpApplicationName,
                        lpCommandLine,
                        lpProcessAttributes,
                        lpThreadAttributes,
                        bInheritHandles,
                        NULL,  // �Թ���ķ�ʽ����wscript.exe����
                        lpEnvironment,
                        lpCurrentDirectory,
                        lpStartupInfo,
                        lpProcessInformation);
			CreateProcessHook.ReHook();
		}
		else
		{
			MessageBox(NULL, "�ű�����������", "��Ҫ��ʾ",MB_OK);
		}
    }
    
    return bRet;
}

BOOL APIENTRY DllMain( HANDLE hModule, 
                      DWORD  ul_reason_for_call, 
                      LPVOID lpReserved
                      )
{
    switch ( ul_reason_for_call )
    {
    case DLL_PROCESS_ATTACH:
        {
            // Hook CreateProcessW()����
            CreateProcessHook.Hook("kernel32.dll",
                "CreateProcessW",
                (PROC)MyCreateProcessW);
            break;
        }
    case DLL_PROCESS_DETACH:
        {
            CreateProcessHook.UnHook();
            break;
        }
    }
    
    return TRUE;
}