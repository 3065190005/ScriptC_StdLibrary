#pragma once
#ifndef __CERVER_STD_STD_SOCKET__
#define __CERVER_STD_STD_SOCKET__

#define Fname(var) void __system__socket__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllimport) Fname(var)

#include "Public/AutoObject/LetManager.h"
#include "Public/AutoObject/LetObject.h"



namespace ScriptC {
	namespace Obj {
		using namespace AutoMem::Obj;
		// socket_create		 ����socket		���ɹ�����socket id�����򷵻ش�����id
		EXPORTDLL(socket_create);


		// socket_bind			 ��socket		���ɹ�����true �����򷵻ش�����id
		EXPORTDLL(socket_bind);


		// socket_listen		 ����socket		���ɹ�����true �����򷵻ش�����id
		EXPORTDLL(socket_listen);


		// socket_accept		 ����socket		���ɹ�����array  �����򷵻ش�����id
		EXPORTDLL(socket_accept);


		// socket_connect		 ����socket		���ɹ�����true �����򷵻ش�����id
		EXPORTDLL(socket_connect);


		// socket_send			 �����ֶ�Tcp		���ɹ����ط��ͳ��� �����򷵻ش�����id
		EXPORTDLL(socket_send);


		// socket_recv			 �����ֶ�Tcp		���ɹ����ؽ����ַ��� �����򷵻ش�����id
		EXPORTDLL(socket_recv);


		// socket_sendto		 �����ֶ�Udp		���ɹ����ط��ͳ��� �����򷵻ش�����id
		EXPORTDLL(socket_sendto);


		// socket_recvfrom		 �����ֶ�Udp		���ɹ�����array �����򷵻ش�����id
		EXPORTDLL(socket_recvfrom);


		// socket_close			 �ر�socket 		���ɹ�����true �����򷵻�false
		EXPORTDLL(socket_close);

		// select 

		// socket_select		���һ��һά����socket������ 	���ɹ����ؼ������ �����򷵻ش�����id
		EXPORTDLL(socket_select);


		// socket_gethostname	��ȡ������ 	���ɹ������ַ��� �����򷵻ش�����id
		EXPORTDLL(socket_gethostname);


		// socket_gethostbyname ͨ����������ȡip 	���ɹ������ַ��� �����򷵻ش�����id
		EXPORTDLL(socket_gethostbyname);
	}
}

#endif

