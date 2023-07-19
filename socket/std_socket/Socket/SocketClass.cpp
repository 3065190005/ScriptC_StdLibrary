#include "SocketClass.h"
SocketClass* SocketClass::m_instance = nullptr;

SocketClass::SocketClass()
{

}

SocketClass::~SocketClass()
{
	
}

bool SocketClass::init()
{
	bool ret = false;
	
	do
	{
		WSADATA wsaData;
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		{
			break;
		}

		ret = true;
	} while (false);

	return ret;
}

void SocketClass::onDestory()
{
	for (struct SocketType &i : m_sockets)
	{
		closesocket(i.sock);
	}

	WSACleanup();
}


SocketClass* SocketClass::getInstance()
{
	static Gc _gc;
	if (m_instance == nullptr) 
	{
		m_instance = new SocketClass();
		if (!m_instance || !m_instance->init())
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

	return m_instance;
}

SocketClass::Gc::~Gc()
{
	if (m_instance)
	{
		m_instance->onDestory();
		delete m_instance;
		m_instance = nullptr;
	}
}

SOCKET SocketClass::create(int family, int type)
{
	struct SocketType sock;
	sock.sock = ::socket(family, type, 0);
	if (INVALID_SOCKET == sock.sock) {
		return -1;
	}

	sock.family = family;
	sock.type = type;

	m_sockets.push_back(sock);
	return sock.sock;
}

int SocketClass::bind(SOCKET socket, std::string ip, int port)
{
	auto iter = std::find_if(m_sockets.begin(), m_sockets.end(),[socket](struct SocketType & one) ->bool {
		if (one.sock == socket)
			return true;
		return false;
		});

	if (iter == m_sockets.end())
		return -1;

	int result = SOCKET_ERROR;
	if (iter->family == (int)family::ipv4) 
	{
		sockaddr_in addr;
		addr.sin_family = iter->family;
		addr.sin_port = htons(port);
		InetPtonA(iter->family, ip.c_str(), &addr.sin_addr);
		result = ::bind(socket, (sockaddr*)&addr, sizeof(addr));
	}
	else if (iter->family == (int)family::ipv6)
	{
		sockaddr_in6 addr;
		addr.sin6_family = iter->family;
		addr.sin6_port = htons(port);
		addr.sin6_scope_id = 0;
		InetPtonA(iter->family, ip.c_str(),(PVOID)&addr.sin6_addr);
		result = ::bind(socket, (sockaddr*)&addr, sizeof(addr));
	}
	else {
		return -2;
	}

	if (result == SOCKET_ERROR)
	{
		return -3;
	}
	
	strcpy_s(iter->ip, ip.c_str());
	iter->port = port;

	return 0;
}

int SocketClass::listen(SOCKET socket, int count)
{
	auto iter = std::find_if(m_sockets.begin(), m_sockets.end(), [socket](struct SocketType& one) ->bool {
		if (one.sock == socket)
			return true;
		return false;
		});

	if (iter == m_sockets.end())
		return -1;

	int result = ::listen(iter->sock, count);
	if (result == SOCKET_ERROR) 
	{
		return -2;
	}

	return 0;
}

std::tuple<SOCKET, struct SocketClass::IpType>
	SocketClass::accept(SOCKET socket)
{

	std::tuple<SOCKET, struct IpType> ret;
	auto iter = std::find_if(m_sockets.begin(), m_sockets.end(), [socket](struct SocketType& one) ->bool {
		if (one.sock == socket)
			return true;
		return false;
		});

	if (iter == m_sockets.end())
	{
		std::get<0>(ret) = -1;
		return ret;
	}

	int result = INVALID_SOCKET;

	struct SocketType client_struct;
	client_struct.family = iter->family;
	client_struct.type = iter->type;

	if (iter->family == (int)family::ipv4)
	{
		sockaddr_in client;

		int client_len = sizeof(client);
		result = ::accept(iter->sock, (sockaddr*)&client, &client_len);

		InetNtopA(iter->family, (PVOID)&client.sin_addr, client_struct.ip, 254);
		client_struct.port = ntohs(client.sin_port);
		client_struct.sock = result;
	}
	else if (iter->family == (int)family::ipv6)
	{
		sockaddr_in6 client;

		int client_len = sizeof(client);
		result = ::accept(iter->sock, (sockaddr*)&client, &client_len);

		InetNtopA(iter->family, (PVOID)&client.sin6_addr, client_struct.ip, 254);
		client_struct.port = ntohs(client.sin6_port);
		client_struct.sock = result;
	}
	else {
		std::get<0>(ret) = -2;
		return ret;
	}

	if (result == INVALID_SOCKET) {
		std::get<0>(ret) = -3;
		return ret;
	}

	m_sockets.push_back(client_struct);
	IpType ip;
	strcpy_s(ip.ip, client_struct.ip);
	ip.port = client_struct.port;
	std::get<0>(ret) = result;
	std::get<1>(ret) = ip;
	return ret;
}

int SocketClass::connect(SOCKET socket, std::string ip, int port)
{
	auto iter = std::find_if(m_sockets.begin(), m_sockets.end(), [socket](struct SocketType& one) ->bool {
		if (one.sock == socket)
			return true;
		return false;
		});

	if (iter == m_sockets.end())
		return -1;

	int result = SOCKET_ERROR;

	if (iter->family == (int)family::ipv4)
	{
		sockaddr_in addr;
		addr.sin_family = iter->family;
		addr.sin_port = htons(port);
		InetPtonA(iter->family, ip.c_str(), &addr.sin_addr);
		result = ::connect(socket, (sockaddr*)&addr, sizeof(addr));
	}
	else if (iter->family == (int)family::ipv6)
	{
		sockaddr_in6 addr;
		addr.sin6_family = iter->family;
		addr.sin6_port = htons(port);
		addr.sin6_scope_id = 0;
		InetPtonA(iter->family, ip.c_str(), (PVOID)&addr.sin6_addr);
		result = ::connect(socket, (sockaddr*)&addr, sizeof(addr));
	}
	else {
		return -2;
	}

	if (result == SOCKET_ERROR)
	{
		return -3;
	}

	return 0;
}

int SocketClass::send(SOCKET socket, std::string buf, long lens)
{
	auto iter = std::find_if(m_sockets.begin(), m_sockets.end(), [socket](struct SocketType& one) ->bool {
		if (one.sock == socket)
			return true;
		return false;
		});

	if (iter == m_sockets.end())
		return -1;

	int result = ::send(socket, buf.c_str(), lens, 0);

	if (result == SOCKET_ERROR)
		return -2;

	return result;
}

std::tuple<std::string,int>
	SocketClass::recv(SOCKET socket, long lens)
{
	std::tuple<std::string, int > ret;
	auto iter = std::find_if(m_sockets.begin(), m_sockets.end(), [socket](struct SocketType& one) ->bool {
		if (one.sock == socket)
			return true;
		return false;
		});

	if (iter == m_sockets.end())
	{
		std::get<1>(ret) = -1;
		return ret;
	}

	char buf[4096];
	int result = SOCKET_ERROR;
	while (true)
	{
		result = SOCKET_ERROR;
		ZeroMemory(buf, 4096);

		result = ::recv(socket, buf, lens, 0);

		if (result == SOCKET_ERROR)
		{
			std::get<1>(ret) = -2;
			return ret;
		}
		else {
			lens -= result;
			std::get<0>(ret).append(buf);
			if (result == 0 || lens == 0)
				break;
		}
	}
	std::get<1>(ret) = 0;
	return ret;
}

int SocketClass::sendto(SOCKET socket, std::string buf, int lens, std::string ip, int port)
{
	auto iter = std::find_if(m_sockets.begin(), m_sockets.end(), [socket](struct SocketType& one) ->bool {
		if (one.sock == socket)
			return true;
		return false;
		});

	if (iter == m_sockets.end())
		return -1;

	int result = SOCKET_ERROR;
	if (iter->family == (int)family::ipv4)
	{
		sockaddr_in addr;
		addr.sin_family = iter->family;
		addr.sin_port = htons(port);
		InetPtonA(iter->family, ip.c_str(), &addr.sin_addr);
		result = ::sendto(socket,buf.c_str(),lens,0 , (sockaddr*)&addr, sizeof(addr));
	}
	else if (iter->family == (int)family::ipv6)
	{
		sockaddr_in6 addr;
		addr.sin6_family = iter->family;
		addr.sin6_port = htons(port);
		addr.sin6_scope_id = 0;
		InetPtonA(iter->family, ip.c_str(), (PVOID)&addr.sin6_addr);
		result = ::sendto(socket, buf.c_str(), lens, 0, (sockaddr*)&addr, sizeof(addr));
	}
	else {
		return -2;
	}


	if (result == SOCKET_ERROR)
		return -3;


	return result;
}

std::tuple<std::string, int, struct SocketClass::IpType>
SocketClass::recvfrom(SOCKET socket, int lens)
{
	std::tuple<std::string, int, struct SocketClass::IpType> ret;
	auto iter = std::find_if(m_sockets.begin(), m_sockets.end(), [socket](struct SocketType& one) ->bool {
		if (one.sock == socket)
			return true;
		return false;
		});

	if (iter == m_sockets.end())
	{
		std::get<1>(ret) = -1;
		return ret;
	}

	struct SocketClass::IpType ipStruct;
	char buf[4096];
	int result = SOCKET_ERROR;
	while (true)
	{
		result = SOCKET_ERROR;
		ZeroMemory(buf, 4096);

		if (iter->family == (int)family::ipv4)
		{
			sockaddr_in addr;
			memset(&addr, 0, sizeof(addr));
			int len = sizeof(sockaddr_in);

			result = ::recvfrom(socket, buf, lens, 0, (sockaddr*)&addr, &len);
			InetNtopA(iter->family, (PVOID)&addr.sin_addr, ipStruct.ip, 254);
			ipStruct.port = ntohs(addr.sin_port);
		}
		else if (iter->family == (int)family::ipv6)
		{
			sockaddr_in6 addr;
			memset(&addr, 0, sizeof(addr));
			int len = sizeof(sockaddr_in6);

			result = ::recvfrom(socket, buf, lens, 0, (sockaddr*)&addr, &len);
			InetNtopA(iter->family, (PVOID)&addr.sin6_addr, ipStruct.ip, 254);
			ipStruct.port = ntohs(addr.sin6_port);
		}
		else {
			std::get<1>(ret) = -2;
			return ret;
		}

		if (result == SOCKET_ERROR)
		{
			std::get<1>(ret) = -3;
			return ret;
		}
		else {
			lens -= result;
			std::get<0>(ret).append(buf);
			break;
		}
	}

	std::get<2>(ret) = ipStruct;
	return ret;
}

bool SocketClass::close(SOCKET socket)
{
	auto iter = std::find_if(m_sockets.begin(), m_sockets.end(), [socket](struct SocketType& one) ->bool {
		if (one.sock == socket)
			return true;
		return false;
		});

	if (iter == m_sockets.end())
		return false;

	int result = ::closesocket(socket);
	if(result == SOCKET_ERROR)
	{
		return false;
	}

	m_sockets.erase(iter);
	return true;

}
