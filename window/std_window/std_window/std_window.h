#pragma once
#ifndef _CERVER_STD_STD_DIALOG_
#define _CERVER_STD_STD_DIALOG_

#define Fname(var) void __system__dialog__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"

namespace ScriptC {
	namespace Obj {
		using namespace AutoMem::Obj;

		// msgbox		 �����Ի���		���ɹ����ذ�ťid�����򷵻�false
		EXPORTDLL(msgBox);

		// edgeBox		 ���������		���ɹ����������ı������򷵻�false
		EXPORTDLL(editBox);


		// bowserBox	 ����ѡ���		: �ɹ�����·�������򷵻�false
		EXPORTDLL(bowserBox);


		// ieHtml		 ����html����	: �ɹ�����true�����򷵻�false
		EXPORTDLL(ieHtml);


		// ieUrl		 ����url����	: �ɹ�����true�����򷵻�false
		EXPORTDLL(ieUrl);


		// edgeHtml		 ����webview2 html����	: �ɹ�����true�����򷵻�false
		EXPORTDLL(edgeHtml);


		// edgeUrl		 ����webview2 url����	: �ɹ�����true�����򷵻�false
		EXPORTDLL(edgeUrl);


		// setWebStyle   ������ʽ	: �ɹ�����true�����򷵻�false
		EXPORTDLL(setWebBoxStyle);


		// getWebStyle   ��ȡ��ʽ	: �ɹ�����numberT�����򷵻�false
		EXPORTDLL(getWebBoxStyle);


		// setWebBoxSize  ���ô�С	: �ɹ�����true�����򷵻�false
		EXPORTDLL(setWebBoxSize);


		// getWebBoxSize   ��ȡ��С	: �ɹ�����array�����򷵻�false
		EXPORTDLL(getWebBoxSize);



		// hideConsole    ���ؿ���̨		: �ɹ��򷵻�true�����򷵻�false
		EXPORTDLL(hideConsole);


		// showConsole    ��ʾ����̨		: �ɹ��򷵻�true�����򷵻�false
		EXPORTDLL(showConsole);

	}
}


#endif