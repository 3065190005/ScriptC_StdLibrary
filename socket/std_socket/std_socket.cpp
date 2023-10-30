#define _WINSOCK_DEPRECATED_NO_WARNINGS 1
#include "std_socket.h"
#include "QuickLib/quicklib.h"

#define Fname(var) void __system__socket__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllexport) Fname(var)
#define RESULT(var) auto_c*var = (auto_c*)ret; *var = auto_c()
#define PARAMS(var) std::vector<auto_c>* var = (std::vector<auto_c>*)param
#define PTR(var) (*var)

#include <algorithm>
#include "Socket/SocketClass.h"

namespace {
	class Funcs {
	public:
		template<typename T>
		static T getParam(std::vector<T>* param);

		template<typename T, typename ... Args>
		static void getParams(std::vector<T>* params, T* pam, Args ...pams);
	};


	template<typename T>
	T Funcs::getParam(std::vector<T>* param)
	{
		T ret;
		ret = param->back();
		param->pop_back();
		return ret;
	}

	template<typename T, typename ... Args>
	void Funcs::getParams(std::vector<T>* params, T* pam, Args ...pams)
	{
		auto call = [&](std::vector<T>* param) {
			T ret;
			ret = param->back();
			param->pop_back();
			return ret;
		};

		(*pam) = call(params);
		(((*pams) = call(params)), ...);
	}
}


namespace ScriptC {
	namespace Obj {
		using namespace AutoMem::Obj;

		// socket_create		 创建socket		：成功返回socket id，否则返回错误码id
		EXPORTDLL(socket_create)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::number ||
				value2.getType() != LetObject::ObjT::number)
			{
				PTR(rets) << 0;
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			numberT va2 = LetObject::cast<numberT>(value2);

			auto hinst = SocketClass::getInstance();
			numberT result = hinst->create(va1, va2);
			

			PTR(rets) << result;

			return;
		}


		// socket_bind			 绑定socket		：成功返回true ，否则返回错误码id
		EXPORTDLL(socket_bind)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2, value3;
			Funcs::getParams<LetObject>(params, &value3, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::number ||
				value2.getType() != LetObject::ObjT::string ||
				value3.getType() != LetObject::ObjT::number)
			{
				PTR(rets) << 0;
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			std::string va2 = LetObject::cast<std::string>(value2);
			numberT va3 = LetObject::cast<numberT>(value3);

			auto hinst = SocketClass::getInstance();
			numberT result = hinst->bind(va1, va2, va3);

			if (result == 0)
				PTR(rets) << true;
			else
				PTR(rets) << result;

			return;
		}


		// socket_listen		 监听socket		：成功返回true ，否则返回错误码id
		EXPORTDLL(socket_listen)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::number ||
				value2.getType() != LetObject::ObjT::number)
			{
				PTR(rets) << 0;
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			numberT va2 = LetObject::cast<numberT>(value2);

			auto hinst = SocketClass::getInstance();
			numberT result = hinst->listen(va1, va2);

			if (result == 0)
				PTR(rets) << true;
			else
				PTR(rets) << result;

			return;
		}


		// socket_accept		 接受socket		：成功返回array  ，否则返回错误码id
		EXPORTDLL(socket_accept)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::number)
			{
				PTR(rets) << 0;
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);

			auto hinst = SocketClass::getInstance();
			auto result = hinst->accept(va1);

			numberT id = std::get<0>(result);

			if (id > 0)
			{
				SocketClass::IpType ip = std::get<1>(result);

				PTR(rets)[0] << id;				// socket
				PTR(rets)[1] << ip.ip;			// ip
				PTR(rets)[2] << ip.port;		// port

			}
			else
				PTR(rets) << id;				// error id

			return;
		}


		// socket_connect		 连接socket		：成功返回0 ，否则返回错误码id
		EXPORTDLL(socket_connect)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2, value3;
			Funcs::getParams<LetObject>(params, &value3, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::number ||
				value2.getType() != LetObject::ObjT::string ||
				value3.getType() != LetObject::ObjT::number)
			{
				PTR(rets) << 0;
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			std::string va2 = LetObject::cast<std::string>(value2);
			numberT va3 = LetObject::cast<numberT>(value3);

			auto hinst = SocketClass::getInstance();
			numberT result = hinst->connect(va1, va2, va3);

			if (result == 0)
				PTR(rets) << true;
			else
				PTR(rets) << result;

			return;
		}


		// socket_send			 发送字段Tcp		：成功返回发送长度 ，否则返回错误码id
		EXPORTDLL(socket_send)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2, value3;
			Funcs::getParams<LetObject>(params, &value3, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::number ||
				value2.getType() != LetObject::ObjT::string ||
				value3.getType() != LetObject::ObjT::number)
			{
				PTR(rets) << 0;
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			std::string va2 = LetObject::cast<std::string>(value2);
			numberT va3 = LetObject::cast<numberT>(value3);

			auto hinst = SocketClass::getInstance();
			numberT result = hinst->send(va1, va2, va3);
			
			PTR(rets) << result;

			return;
		}


		// socket_recv			 接受字段Tcp		：成功返回接受字符串 ，否则返回错误码id
		EXPORTDLL(socket_recv)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::number ||
				value2.getType() != LetObject::ObjT::number)
			{
				PTR(rets) << 0;
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			numberT va2 = LetObject::cast<numberT>(value2);

			auto hinst = SocketClass::getInstance();
			auto result = hinst->recv(va1, va2);

			numberT id = std::get<1>(result);

			if (id == 0)
				PTR(rets) << std::get<0>(result);
			else
				PTR(rets) << id;

			return;
		}


		// socket_sendto		 发送字段Udp		：成功返回发送长度 ，否则返回错误码id
		EXPORTDLL(socket_sendto)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2, value3, value4, value5;
			Funcs::getParams<LetObject>(params, &value5, &value4, &value3, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::number ||
				value2.getType() != LetObject::ObjT::string ||
				value3.getType() != LetObject::ObjT::number ||
				value4.getType() != LetObject::ObjT::string ||
				value5.getType() != LetObject::ObjT::number)
			{
				PTR(rets) << 0;
				return;
			}

			numberT socket = LetObject::cast<numberT>(value1);
			std::string buf = LetObject::cast<std::string>(value2);
			numberT lens = LetObject::cast<numberT>(value3);
			std::string ip = LetObject::cast<std::string>(value4);
			numberT port = LetObject::cast<numberT>(value5);

			auto hinst = SocketClass::getInstance();
			auto result = hinst->sendto(socket, buf, lens, ip, port);

			PTR(rets) << result;

			return;
		}


		// socket_recvfrom		 接受字段Udp		：成功返回数组 ，否则返回错误码id
		EXPORTDLL(socket_recvfrom)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::number ||
				value2.getType() != LetObject::ObjT::number)
			{
				PTR(rets) << 0;
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);
			numberT va2 = LetObject::cast<numberT>(value2);

			auto hinst = SocketClass::getInstance();
			auto result = hinst->recvfrom(va1, va2);

			numberT id = std::get<1>(result);

			if (id == 0)
			{
				std::string buf = std::get<0>(result);
				auto ip = std::get<2>(result);
				PTR(rets)[0] << buf;
				PTR(rets)[1] << ip.ip;
				PTR(rets)[2] << ip.port;

			}
			else
				PTR(rets) << id;

			return;
		}


		// socket_close			 关闭socket 		：成功返回true ，否则返回falsle
		EXPORTDLL(socket_close)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::number)
			{
				PTR(rets) << 0;
				return;
			}

			numberT va1 = LetObject::cast<numberT>(value1);

			auto hinst = SocketClass::getInstance();
			auto result = hinst->close(va1);
			
			PTR(rets) << result;

			return;
		}

		// select 

		// socket_select		检测一组一维数组socket并返回 	：成功返回检测数组 ，否则返回错误码id
		EXPORTDLL(socket_select)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);

			if (value1.getType() != LetObject::ObjT::array ||
				value2.getType() != LetObject::ObjT::number)
			{
				PTR(rets) << 0;
				return;
			}

			std::list<numberT> array_socket;

			auto num_vec_ptr = value1.getNumArrayPtr();
			auto str_vec_ptr = value1.getStrArrayPtr();
			for (auto i = num_vec_ptr->begin() ; i != num_vec_ptr->end() ; i ++)
			{
				if (i->second.getType() != LetObject::ObjT::number)
				{
					PTR(rets) << -1;
					return;
				}
				array_socket.push_back(LetObject::cast<numberT>(i->second));
			}

			for (auto i = str_vec_ptr->begin(); i != str_vec_ptr->end(); i++)
			{
				if (i->second.getType() != LetObject::ObjT::number)
				{
					PTR(rets) << -1;
					return;
				}
				array_socket.push_back(LetObject::cast<numberT>(i->second));
			}

			// 获取所有socket
			

			numberT va2 = LetObject::cast<numberT>(value2);
			long us = ((long long)va2 % 1000) * 1000;
			long se = va2 /= 1000;

			struct timeval tv;
			tv.tv_sec = se;
			tv.tv_usec = us;

			auto hinst = SocketClass::getInstance();
			auto select_c = hinst->getSelect();

			std::list<SelectClass::tagUnit_type> sockets;
			for (auto& i : array_socket) 
			{
				auto unit = select_c.initUnit(i);
				select_c.Join(unit);
				sockets.push_back(unit);
			}

			auto result = select_c.Select(sockets, tv);

			for (auto& i : sockets)
			{
				select_c.Leave(i);
			}

			SelectClass::unit_list read_list;
			SelectClass::unit_list write_list;
			SelectClass::unit_list error_list;

			int code = std::get<3>(result);

			int index = 0;

			if (code == -1)
			{
				PTR(rets) << -2;
				return;
			}

			read_list = std::get<0>(result);
			write_list = std::get<1>(result);
			error_list = std::get<2>(result);
			
			for (auto& i : read_list)
			{
				auto_c element;
				element["s"] << (numberT)i.socket;
				element["r"] << true;

				PTR(rets)[index] = std::move(element);
				index++;
			}

			for (auto& i : write_list)
			{
				auto_c element;
				element["s"] << (numberT)i.socket;
				element["w"] << true;

				PTR(rets)[index] = std::move(element);
				index++;
			}

			for (auto& i : error_list)
			{
				auto_c element;
				element["s"] << (numberT)i.socket;
				element["e"] << true;

				PTR(rets)[index] = std::move(element);
				index++;
			}

			return;
		}


		// socket_gethostname	获取主机名 	：成功返回字符串 ，否则返回错误码id
		EXPORTDLL(socket_gethostname)
		{
			PARAMS(params);
			RESULT(rets);

			auto hinst = SocketClass::getInstance();

			char name[4096] = { 0 };

			auto result = gethostname(name, 4095);
			if (result == SOCKET_ERROR)
			{
				PTR(rets) << -1;
				return;
			}

			PTR(rets) << name;

			return;
		}


		// socket_gethostbyname 通过主机名获取ip 	：成功返回字符串 ，否则返回错误码id
		EXPORTDLL(socket_gethostbyname)
		{
			PARAMS(params);
			RESULT(rets);

			auto hinst = SocketClass::getInstance();

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);

			if (value1.getType() != LetObject::ObjT::string)
			{
				PTR(rets) << 0;
				return;
			}

			std::string va1 = LetObject::cast<std::string>(value1);

			struct addrinfo* result = NULL;
			struct addrinfo* ptr = NULL;
			struct addrinfo hints;

			ZeroMemory(&hints, sizeof(hints));
			hints.ai_family = AF_UNSPEC;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_protocol = IPPROTO_TCP;


			auto ipaddress = getaddrinfo(va1.c_str(), NULL, &hints, &result);

			struct sockaddr_in* sockaddr_ipv4;
			LPSOCKADDR sockaddr_ip;
			char ipstringbuffer[46];
			DWORD ipbufferlength = 46;


			INT iRetval;

			int index = 0;

			if (ipaddress == 0)
			{
				for (ptr = result; ptr != NULL; ptr = ptr->ai_next)
				{
					ZeroMemory(ipstringbuffer, 46);
					switch (ptr->ai_family)
					{
					case AF_INET:
						sockaddr_ipv4 = (struct sockaddr_in*)ptr->ai_addr;
						InetNtopA(sockaddr_ipv4->sin_family, &sockaddr_ipv4->sin_addr, ipstringbuffer, 45);
						PTR(rets)[index] << ipstringbuffer;
						index += 1;
						break;
					case AF_INET6:
						sockaddr_ip = (LPSOCKADDR)ptr->ai_addr;
						ipbufferlength = 46;
						iRetval = WSAAddressToStringA(sockaddr_ip, (DWORD)ptr->ai_addrlen, NULL,
							ipstringbuffer, &ipbufferlength);
						
						PTR(rets)[index] << ipstringbuffer;
						index += 1;
						break;
					}
				}
			}
			else
			{
				PTR(rets) << ipaddress;
			}

			freeaddrinfo(result);
			return;
		}
	}
}