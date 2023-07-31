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
		// socket_create		 创建socket		：成功返回socket id，否则返回错误码id
		EXPORTDLL(socket_create);


		// socket_bind			 绑定socket		：成功返回true ，否则返回错误码id
		EXPORTDLL(socket_bind);


		// socket_listen		 监听socket		：成功返回true ，否则返回错误码id
		EXPORTDLL(socket_listen);


		// socket_accept		 接受socket		：成功返回array  ，否则返回错误码id
		EXPORTDLL(socket_accept);


		// socket_connect		 连接socket		：成功返回true ，否则返回错误码id
		EXPORTDLL(socket_connect);


		// socket_send			 发送字段Tcp		：成功返回发送长度 ，否则返回错误码id
		EXPORTDLL(socket_send);


		// socket_recv			 接受字段Tcp		：成功返回接受字符串 ，否则返回错误码id
		EXPORTDLL(socket_recv);


		// socket_sendto		 发送字段Udp		：成功返回发送长度 ，否则返回错误码id
		EXPORTDLL(socket_sendto);


		// socket_recvfrom		 接受字段Udp		：成功返回array ，否则返回错误码id
		EXPORTDLL(socket_recvfrom);


		// socket_close			 关闭socket 		：成功返回true ，否则返回false
		EXPORTDLL(socket_close);

		// select 

		// socket_select		检测一组一维数组socket并返回 	：成功返回检测数组 ，否则返回错误码id
		EXPORTDLL(socket_select);


		// socket_gethostname	获取主机名 	：成功返回字符串 ，否则返回错误码id
		EXPORTDLL(socket_gethostname);


		// socket_gethostbyname 通过主机名获取ip 	：成功返回字符串 ，否则返回错误码id
		EXPORTDLL(socket_gethostbyname);
	}
}

#endif

