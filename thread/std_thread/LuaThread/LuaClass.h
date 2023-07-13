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
	* 运行lua
	*************/ 
	void run();		

	/************
	* 设置全局变量
	* param 参数值
	* name 全局变量名
	*************/
	bool varSet(auto_c param,const char * name);		

	/************
	* 获取全局变量
	* name 全局变量名
	*************/
	auto_c varGet(const char* name);	

	/************
	* 设置lua文件
	* file : 文件路径
	*************/
	void file(const char* file);

private:
	std::string m_file;			// lua 文件名
	lua_State* m_lua;		// lua 虚拟机
};

#endif

