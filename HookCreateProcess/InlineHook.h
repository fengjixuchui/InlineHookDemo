#include <windows.h>

class CInlineHook
{
public:
        CInlineHook();      // ���캯�������ڳ�ʼ��
        ~CInlineHook();     // �����������û������������Դ���ͷ�

        // Hook����
        BOOL Hook(LPSTR pszModuleName, LPSTR pszFuncName, PROC pfnHookFunc);
        // ȡ��Hook����
        void UnHook();
		// ���½���Hook����
		BOOL ReHook();

private:
        PROC m_pfnOrig;         // �Զ���ĺ����ĵ�ַ
        BYTE m_bOldBytes[5];    // ԭʼ������ڴ���
        BYTE m_bNewBytes[5];    // �������תָ��Ĵ���
};