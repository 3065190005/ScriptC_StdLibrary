#pragma once
#ifndef __LUA_CLASS__
#define __LUA_CLASS__

#pragma comment(lib,"lua54.lib")

#include <string>

#include "LuaH/lua.hpp"
#include "..\Public\AutoObject\LetManager.h"
#include "..\Public\AutoObject\LetObject.h"

using namespace Cervice::Obj;

class LuaClass
{
public:
	LuaClass();
	~LuaClass();

public:
	/************
	* ����lua
	*************/ 
	void run();		

	/************
	* ����ȫ�ֱ���
	* param ����ֵ
	* name ȫ�ֱ�����
	*************/
	bool varSet(auto_c param,const char * name);		

	/************
	* ��ȡȫ�ֱ���
	* name ȫ�ֱ�����
	*************/
	auto_c varGet(const char* name);	

	/************
	* ����lua�ļ�
	* file : �ļ�·��
	*************/
	void file(const char* file);

private:
	std::string m_file;			// lua �ļ���
	lua_State* m_lua;		// lua �����
};

#endif

