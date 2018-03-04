#include "stdafx.h"
#include "InlineHook.h"

CInlineHook::CInlineHook()
{
        // �Գ�Ա�����ĳ�ʼ��
        m_pfnOrig = NULL;
        ZeroMemory(m_bOldBytes, 5);
        ZeroMemory(m_bNewBytes, 5);
}

CInlineHook::~CInlineHook()
{
        // ȡ��Hook
        UnHook();
}

//�ҹ���������������Ϊģ�����ơ����������Լ��Զ���Ĺ��Ӻ���
BOOL CInlineHook::Hook(LPSTR pszModuleName, LPSTR pszFuncName, PROC pfnHookFunc)
{
        BOOL bRet = FALSE;
    
        // ��ȡָ��ģ���к����ĵ�ַ
        m_pfnOrig = (PROC)GetProcAddress(GetModuleHandle(pszModuleName), pszFuncName);

        if ( m_pfnOrig != NULL )
        {
                // ����õ�ַ��ǰ5���ֽڵ�����
                DWORD dwNum = 0;
                ReadProcessMemory(GetCurrentProcess(), m_pfnOrig, m_bOldBytes, 5, &dwNum);

                // ����JMPָ�"\xe9"Ϊjmp��Opcode
                m_bNewBytes[0] = '\xe9';    
                // pfnHookFunc��Hook��ĵ�ַ��m_pfnOrig��ԭ���ĵ�ַ��5��ָ���
                *(DWORD *)(m_bNewBytes + 1) = (DWORD)pfnHookFunc - (DWORD)m_pfnOrig - 5;

                // ������õĵ�ַд��õ�ַ��
                WriteProcessMemory(GetCurrentProcess(), m_pfnOrig, m_bNewBytes, 5, &dwNum);

                bRet = TRUE;
        }
    
        return bRet;
}

//ȡ�������Ĺҹ�
void CInlineHook::UnHook()
{
        if ( m_pfnOrig != 0 )
        {
                DWORD dwNum = 0;
                WriteProcessMemory(GetCurrentProcess(), m_pfnOrig, m_bOldBytes, 5, &dwNum);
        }
}

//���¶Ժ������йҹ�  
BOOL CInlineHook::ReHook()  
{  
        BOOL bRet = FALSE;  
  
        if ( m_pfnOrig != 0 )  
        {  
                DWORD dwNum = 0;  
                WriteProcessMemory(GetCurrentProcess(), m_pfnOrig, m_bNewBytes, 5, &dwNum);  
  
                bRet = TRUE;  
        }  
  
        return bRet;  
}  