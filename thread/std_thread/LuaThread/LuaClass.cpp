#include "LuaClass.h"

LuaClass::LuaClass():
	m_lua(nullptr)
{
	m_lua = luaL_newstate();
	luaL_openlibs(m_lua);
}

LuaClass::~LuaClass()
{
	lua_close(m_lua);
}

void LuaClass::run()
{
	if (m_file.empty())
		return;

	luaL_dofile(m_lua, m_file.c_str());
}

bool LuaClass::varSet(auto_c param, const char* name)
{
	bool ret = false;
	if (param.getType() == LetObject::ObjT::number) {
		lua_pushnumber(m_lua, LetObject::cast<lua_Number>(param));
		lua_setglobal(m_lua, name);
		ret = true;
	}
	if (param.getType() == LetObject::ObjT::string) {
		lua_pushstring(m_lua, LetObject::cast<std::string>(param).c_str());
		lua_setglobal(m_lua, name);
		ret = true;
	}
	if (param.getType() == LetObject::ObjT::boolean) {
		lua_pushboolean(m_lua, LetObject::cast<bool>(param));
		lua_setglobal(m_lua, name);
		ret = true;
	}

	return ret;
}

auto_c LuaClass::varGet(const char* name)
{
	auto_c ret;

	lua_getglobal(m_lua, name);
	if (lua_isboolean(m_lua, -1)) {
		ret << lua_toboolean(m_lua, -1);
	}
	if (lua_isnumber(m_lua, -1)) {
		ret << lua_tonumber(m_lua, -1);
	}
	if (lua_isstring(m_lua, -1)) {
		ret << lua_tostring(m_lua, -1);
	}

	return std::move(ret);
}

void LuaClass::file(const char* file)
{
	lua_close(m_lua);
	m_file = file;
	m_lua = luaL_newstate();
	luaL_openlibs(m_lua);
}
