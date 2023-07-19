#pragma once
#ifndef __SOCKET_CLASS__FOR__SCRIPTC__
#define __SOCKET_CLASS__FOR__SCRIPTC__

#include <list>
#include <string>
#include <tuple>
#include <WS2tcpip.h>
#include <WinSock2.h>
#include "SelectClass.h";

#pragma comment(lib,"ws2_32.lib")

class SocketClass final
{
public:
	static SocketClass* getInstance();

public:
	enum family {
		ipv4 = AF_INET,
		ipv6 = AF_INET6
	};

	enum type {
		tcp = SOCK_STREAM,
		udp = SOCK_DGRAM
	};

	struct SocketType {
		SOCKET sock{ 0 };
		int family{ 0 };
		int port{ 0 };
		int type{ 0 };
		char ip[255]{ 0 };
	};

	struct IpType {
		char ip[255]{ 0 };
		int port{ 0 };
	};

public:
	SOCKET create(int family, int type);
	int bind(SOCKET socket, std::string ip, int port);
	int listen(SOCKET socket, int count);
	std::tuple<SOCKET, struct IpType> accept(SOCKET socket);

	int connect(SOCKET socket, std::string ip, int port);

	int send(SOCKET socket, std::string buf, long lens);
	std::tuple<std::string, int> recv(SOCKET socket, long lens);

	int sendto(SOCKET socket, std::string buf, int lens, std::string ip, int port);
	std::tuple<std::string, int, struct IpType> recvfrom(SOCKET socket, int lens);

	bool close(SOCKET socket);

	// ----

	SelectClass& getSelect() { return m_select; }

private:
	SocketClass();
	~SocketClass();

	bool init();
	void onDestory();

public:


private:
	static SocketClass* m_instance;
	std::list<struct SocketType> m_sockets;
	SelectClass m_select;

	class Gc {
	public:
		~Gc();
	};
};

#endif
