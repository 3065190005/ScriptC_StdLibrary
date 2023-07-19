#pragma once
#ifndef __SELECT_CLASS__FOR__SCRIPTC__
#define __SELECT_CLASS__FOR__SCRIPTC__

#include <WinSock2.h>
#include <Windows.h>

#include <list>
#include <tuple>

class SelectClass
{
public:
	enum tagUnit_state {
		unkonw = 0,
		is_set = 1,
		no_set = 2
	};

	struct tagUnit_type {
		SOCKET socket{ 0 };
		fd_set* fd{ nullptr };
		tagUnit_state state{ tagUnit_state::no_set };
	};

	struct tagElement_type {
		fd_set fd{FD_ZERO(&fd)};
		int count{ 0 };
	};

	using unit_list = std::list<tagUnit_type>;
	using fd_set_list = std::list<fd_set>;
	using select_ret = std::tuple<unit_list, unit_list, unit_list,int>;

public:
	tagUnit_type initUnit(SOCKET socket);

	bool Join(tagUnit_type& sock);
	bool Leave(tagUnit_type& sock);
	select_ret Select(std::list<tagUnit_type> sockets, struct timeval tv);

private:
	std::list<tagElement_type> m_element;
};


using Unit = SelectClass::tagUnit_type;
using UnitState = SelectClass::tagUnit_state;


#endif

