#include "std_direct.h"
#include "QuickLib/quicklib.h"

#define Fname(var) void __system__direct__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllexport) Fname(var)
#define RESULT(var) auto_c*var = (auto_c*)ret; *var = auto_c()
#define PARAMS(var) std::vector<auto_c>* var = (std::vector<auto_c>*)param
#define PTR(var) (*var)

#include <algorithm>
#include <optional>
#include <variant>
#include <filesystem>
#include <shlobj.h>
#pragma comment(lib, "shell32.lib") 

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

		// chdir		�ı䵱ǰ����Ŀ¼		���ַ��� -> �ɹ�true�����򷵻ش�����
		EXPORTDLL(chdir)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			int code = ::_wchdir(kconvert::GbkToUtf8(path).c_str());
			if (code == 0)
				PTR(rets) << true;
			else
				PTR(rets) << -::abs(code);
			return;
		}

		// getcwd		���ص�ǰ����Ŀ¼		��void -> �ɹ��ַ��������򷵻�null
		EXPORTDLL(getcwd)
		{
			PARAMS(params);
			RESULT(rets);

			wchar_t* oldCWD = ::_wgetcwd(NULL, 0);
			if (oldCWD != NULL)
				PTR(rets) << kconvert::Utf8ToGbk(oldCWD);
			return;
		}

		// listdir		����ָ�����ļ��а������ļ����ļ��е����ֵ��б�		���ַ��� -> �ɹ����飬���򷵻ش�����
		EXPORTDLL(listdir)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;
			try
			{
				auto dirList = std::filesystem::directory_iterator::directory_iterator(path);
				size_t index = 0;
				for (const auto& file : dirList)
				{
					std::string strfile;
					strfile = file.path().filename().string();
					PTR(rets)[index] << strfile;
					index++;
				}
			}
			catch (std::filesystem::filesystem_error const& ex)
			{
				PTR(rets) << -::abs(ex.code().value());
				return;
			}
			return;
		}

		// chmod  ����Ŀ¼���ļ�Ȩ��	: �ַ��� | ���� -> �ɹ�����true�����򷵻ش�����
		EXPORTDLL(chmod)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);
			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::number)
			{
				return;
			}

			std::string path;
			numberT mode;

			value1 >> path;
			value2 >> mode;

			namespace fs = std::filesystem;
	
			try
			{
				fs::perms perms = fs::perms((unsigned int)mode);
				fs::permissions(path, perms, fs::perm_options::replace);
			}
			catch (std::filesystem::filesystem_error const& ex)
			{
				PTR(rets) << -::abs(ex.code().value());;
				return;
			}
			

			PTR(rets) << true;
			return;
		}

		// makedirs		�ݹ鴴��Ŀ¼��		���ַ��� -> �ɹ�true�����򷵻ش�����
		EXPORTDLL(makedirs)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;
			if (*path.rbegin() == '\\' || *path.rbegin() == '/')
				path = path.substr(0, path.size() - 1);

			namespace fs = std::filesystem;
			std::error_code ec;
			bool code = fs::create_directories(path, ec);
			if (code == true)
			{
				PTR(rets) << true;
				return;
			}
			else
			{
				PTR(rets) << -::abs(ec.value());;
			}

			return;
		}

		// mkdir		����Ŀ¼��		���ַ��� -> �ɹ�true�����򷵻ش�����
		EXPORTDLL(mkdir)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;
			if (*path.rbegin() == '\\' || *path.rbegin() == '/')
				path = path.substr(0, path.size() - 1);

			namespace fs = std::filesystem;
			std::error_code ec;
			bool code = fs::create_directory(path, ec);
			if (code == true)
			{
				PTR(rets) << true;
				return;
			}
			else
			{
				PTR(rets) << -::abs(ec.value());;
			}

			return;
		}

		// removedirs		�ݹ�ɾ��Ŀ¼��		���ַ��� -> �ɹ�����true�����򷵻ش�����
		EXPORTDLL(removedirs)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			namespace fs = std::filesystem;

			std::string path;
			value1 >> path;
			if (*path.rbegin() == '\\' || *path.rbegin() == '/')
				path = path.substr(0, path.size() - 1);
			path = kstring::StringReplace(path, "/", "\\");

			fs::path path_cls;
			fs::path path_tar;
			fs::path path_rot;

			try
			{
				path_cls = fs::path{ path };
				path_tar = fs::canonical(path_cls);
				path_rot = fs::canonical(path_cls.begin()->filename().string());
				if(path_rot.empty())
					path_rot = fs::canonical(path_cls.root_directory());
			}
			catch (const std::filesystem::filesystem_error& ex)
			{
				PTR(rets) << -::abs(ex.code().value());
				return;
			}
			


			while (true)
			{
				std::error_code ec;
				bool code = fs::remove(path_tar, ec);
				if (code == true)
				{
					path_tar = path_tar.parent_path();
					if (path_tar == path_rot)
						break;
				}
				else
				{
					PTR(rets) << -::abs(ec.value());
					return;
				}
			}

			PTR(rets) << true;
			return;
		}

		// rmdir		ɾ��Ŀ¼��		���ַ��� -> �ɹ�true�����򷵻ش�����
		EXPORTDLL(rmdir)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				PTR(rets) << -404;
				return;
			}

			std::string path;
			value1 >> path;
			if (*path.rbegin() == '\\' || *path.rbegin() == '/')
				path = path.substr(0, path.size() - 1);

			namespace fs = std::filesystem;
			std::error_code ec;
			bool code = fs::remove(path, ec);
			if (code == true)
			{
				PTR(rets) << true;
				return;
			}
			else
			{
				PTR(rets) << -::abs(ec.value());
			}

			return;
		}

		// rename		������Ŀ¼����		���ַ��� | �ַ��� -> �ɹ�true�����򷵻ش�����
		EXPORTDLL(rename)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);
			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string src;
			std::string des;

			value1 >> src;
			value2 >> des;

			namespace fs = std::filesystem;

			try
			{
				fs::rename(src, des);
			}
			catch (std::filesystem::filesystem_error const& ex)
			{
				PTR(rets) << -::abs(ex.code().value());
				return;
			}


			PTR(rets) << true;
			return;
		}


		// stat 		 ���������ڸ�����·����ִ��һ��ϵͳ stat �ĵ���		���ַ��� -> �ɹ����飬���򷵻ش�����
		EXPORTDLL(stat)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			namespace fs = std::filesystem;

			try
			{
				bool not_exists = !fs::exists(path);
				bool not_file = fs::is_directory(path);
				if (not_exists)
				{
					PTR(rets) << -404;
					return;
				}
				if (not_file)
				{
					PTR(rets) << -400;
					return;
				}

			}
			catch(const fs::filesystem_error & ex)
			{
				PTR(rets) << -::abs(ex.code().value());
				return;
			}

			struct ::_stat64i32 st;
			int code = ::_wstat(kconvert::GbkToUtf8(path).c_str(), &st);

			if (code == 0)
			{
				PTR(rets)["dev"] << (numberT)st.st_dev;
				PTR(rets)["ino"] << (numberT)st.st_ino;
				PTR(rets)["mode"] << (numberT)st.st_mode;
				PTR(rets)["uid"] << (numberT)st.st_uid;
				PTR(rets)["gid"] << (numberT)st.st_gid;
				PTR(rets)["rdev"] << (numberT)st.st_rdev;
				PTR(rets)["size"] << (numberT)st.st_size;
				PTR(rets)["atime"] << (numberT)st.st_atime;
				PTR(rets)["mtime"] << (numberT)st.st_mtime;
				PTR(rets)["ctime"] << (numberT)st.st_ctime;
			}
			else
				PTR(rets) << -::abs(code);
			return;
		}

		// abspath 		 ���ؾ���·��	���ַ��� -> �ɹ��ַ��������򷵻ش�����
		EXPORTDLL(abspath)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			namespace fs = std::filesystem;
			try
			{
				fs::path abs_path = fs::canonical(path);
				PTR(rets) << abs_path.string();
			}
			catch (std::filesystem::filesystem_error const& ex)
			{
				PTR(rets) << -::abs(ex.code().value());
				return;
			}

			return;
		}



		// relative 	�������·��	���ַ��� -> �ɹ��ַ��������򷵻ش�����
		EXPORTDLL(relative)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			namespace fs = std::filesystem;
			try
			{
				fs::path abs_path = fs::canonical(path).relative_path();
				PTR(rets) << abs_path.string();
			}
			catch (std::filesystem::filesystem_error const& ex)
			{
				PTR(rets) << -::abs(ex.code().value());
				return;
			}

			return;
		}

		// basename 		 �����ļ���	���ַ��� -> �ɹ��ַ��������򷵻ش�����
		EXPORTDLL(basename)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			namespace fs = std::filesystem;
			try
			{
				fs::path path_cls{ path };
				PTR(rets) << path_cls.filename().string();
			}
			catch (std::filesystem::filesystem_error const& ex)
			{
				PTR(rets) << -::abs(ex.code().value());
				return;
			}

			return;
		}

		// commonprefix 		 ���ض��·���У����й��е����·��	������ -> �ɹ��ַ��������򷵻�null
		EXPORTDLL(commonprefix)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::array)
			{
				return;
			}

			namespace fs = std::filesystem;

			fs::path share_path;
			auto getShare = [&](fs::path one, fs::path two) -> fs::path {
				if (one.compare(two) < 0)
					one.swap(two);

				fs::path ret;

				int index = 0;

				fs::path::iterator one_it = one.begin();
				fs::path::iterator two_it = two.begin();

				while (one_it != one.end() && two_it != two.end())
				{
					if (*one_it == *two_it)
					{
						ret += (*one_it);
						ret += "\\";
						one_it++;
						two_it++;
						continue;
					}
					break;
				}
				return ret;
			};

			std::vector<std::string> path_vec;
			
			for (auto& i : *value1.getNumArrayPtr())
			{
				if (i.second.getType() != LetObject::ObjT::string)
				{
					PTR(rets) << auto_c();
					return;
				}
				path_vec.push_back(LetObject::cast<std::string>(i.second));
			}

			for (auto& i : *value1.getStrArrayPtr())
			{
				if (i.second.getType() != LetObject::ObjT::string)
				{
					PTR(rets) << auto_c();
					return;
				}
				path_vec.push_back(LetObject::cast<std::string>(i.second));
			}

			if (path_vec.empty())
				return;

			share_path = *path_vec.begin();
			std::sort(path_vec.begin(), path_vec.end());
			for (auto& i : path_vec)
			{
				share_path = getShare(share_path, fs::path{ i });
				if (share_path.empty())
					break;
			}


			PTR(rets) << share_path.string();
			return;
		}

		// dirname 		 �����ļ�·��	���ַ��� -> �ɹ��ַ��������򷵻ش�����
		EXPORTDLL(dirname)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			namespace fs = std::filesystem;
			try
			{
				fs::path path_cls{ path };
				PTR(rets) << path_cls.remove_filename().string();
			}
			catch (std::filesystem::filesystem_error const& ex)
			{
				PTR(rets) << -::abs(ex.code().value());
				return;
			}

			return;
		}

		// exists 		 ·���Ƿ����	���ַ��� -> �ɹ�true�����򷵻�false
		EXPORTDLL(exists)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			namespace fs = std::filesystem;
			PTR(rets) << false;

			try
			{
				fs::path path_cls{ path };
				PTR(rets) << fs::exists(path_cls);
			}
			catch (std::filesystem::filesystem_error const& ex)
			{
				PTR(rets) << -::abs(ex.code().value());
				return;
			}

			return;
		}

		// expand 		���ݻ���������ֵ�滻%�ַ���%ֵ	���ַ��� -> �ɹ��ַ��������򷵻ش�����
		EXPORTDLL(expand)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			auto vector = kstring::StringFindIndex(path, "%",-1);
			if (vector.size() % 2 != 0)
			{
				PTR(rets) << -1;
				return;
			}
			
			std::string ret_str;
			while (!vector.empty())
			{
				size_t first = vector.back();
				vector.pop_back();
				size_t second = vector.back();
				vector.pop_back();

				
				std::string one = path.substr(first+1, path.length());
				std::string vars = path.substr(second+1, first - second-1);
				std::wstring vars_w = kconvert::GbkToUtf8(vars);
				path = path.substr(0, second);

				wchar_t buffer[MAX_PATH];
				DWORD code = GetEnvironmentVariable(vars_w.c_str(), buffer, MAX_PATH);

				if (code != 0 && buffer != NULL)
				{
					ret_str = one + ret_str;
					ret_str = kconvert::Utf8ToGbk(buffer) + ret_str;
				}
				else
				{
					PTR(rets) << -2;
					return;
				}
			}

			ret_str = path + ret_str;

			PTR(rets) << ret_str;
			return;
		}

		// getatime 		�����������ʱ��	���ַ��� -> �ɹ����֣����򷵻ش�����
		EXPORTDLL(getatime)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			struct ::_stat64i32 st;
			int code = ::_wstat(kconvert::GbkToUtf8(path).c_str(), &st);

			if (code == 0)
			{
				PTR(rets) << (numberT)st.st_atime;
			}
			else
				PTR(rets) << -::abs(code);
			return;
		}

		// getmtime 		��������ļ��޸�ʱ��	���ַ��� -> �ɹ����֣����򷵻ش�����
		EXPORTDLL(getmtime)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			struct ::_stat64i32 st;
			int code = ::_wstat(kconvert::GbkToUtf8(path).c_str(), &st);

			if (code == 0)
			{
				PTR(rets) << (numberT)st.st_mtime;
			}
			else
				PTR(rets) << -::abs(code);
			return;
		}

		// getctime 		�����ļ�����ʱ��	���ַ��� -> �ɹ����֣����򷵻ش�����
		EXPORTDLL(getctime)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			struct ::_stat64i32 st;
			int code = ::_wstat(kconvert::GbkToUtf8(path).c_str(), &st);

			if (code == 0)
			{
				PTR(rets) << (numberT)st.st_ctime;
			}
			else
				PTR(rets) << -::abs(code);
			return;
		}

		// getsize 		�����ļ���С	���ַ��� -> �ɹ����֣����򷵻ش�����
		EXPORTDLL(getsize)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			struct ::_stat64i32 st;
			int code = ::_wstat(kconvert::GbkToUtf8(path).c_str(), &st);

			if (code == 0)
			{
				PTR(rets) << (numberT)st.st_size;
			}
			else
				PTR(rets) << -::abs(code);
			return;
		}

		// isabs 			�ж��Ƿ�Ϊ����·��	���ַ��� -> �ɹ�true�����򷵻�false
		EXPORTDLL(isabs)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			namespace fs = std::filesystem;
			PTR(rets) << false;

			try
			{
				fs::path path_cls{ path };
				PTR(rets) << path_cls.is_absolute();
			}
			catch (std::filesystem::filesystem_error const& ex)
			{
				PTR(rets) << -::abs(ex.code().value());
				return;
			}

			return;
		}

		// isfile 			�ж�·���Ƿ�Ϊ�ļ�	���ַ��� -> �ɹ�true�����򷵻�false
		EXPORTDLL(isfile)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			namespace fs = std::filesystem;
			PTR(rets) << false;

			try
			{
				auto file_status = fs::status(path);
				if (fs::exists(file_status) && !fs::is_directory(path)) {
					PTR(rets) << true;
					return;
				}
			}
			catch (std::filesystem::filesystem_error const& ex)
			{
				PTR(rets) << -::abs(ex.code().value());
				return;
			}

			return;
		}

		// isdir 			�ж�·���Ƿ�ΪĿ¼	���ַ��� -> �ɹ�true�����򷵻�false
		EXPORTDLL(isdir)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			namespace fs = std::filesystem;
			PTR(rets) << false;

			try
			{
				auto file_status = fs::status(path);
				if (fs::exists(file_status) && fs::is_directory(path)) {
					PTR(rets) << true;
					return;
				}
			}
			catch (std::filesystem::filesystem_error const& ex)
			{
				PTR(rets) << -::abs(ex.code().value());
				return;
			}

			return;
		}

		// normcase 		��·���ַ����Ĵ�д����б��ת��	���ַ��� -> �ɹ��ַ��������򷵻ش�����
		EXPORTDLL(normcase)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			namespace fs = std::filesystem;
			PTR(rets) << false;

			try
			{
				path = kstring::StringToLower(path);
				fs::path path_ret{ path };
				path_ret.make_preferred();
				PTR(rets) << path_ret.string();
			}
			catch (std::filesystem::filesystem_error const& ex)
			{
				PTR(rets) << -::abs(ex.code().value());
				return;
			}

			return;
		}

		// normpath 		�淶·���ַ�����ʽ	���ַ��� -> �ɹ��ַ��������򷵻ش�����
		EXPORTDLL(normpath)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			namespace fs = std::filesystem;
			PTR(rets) << false;

			try
			{
				fs::path path_ret{ path };
				path_ret = path_ret.lexically_normal();
				PTR(rets) << path_ret.string();
			}
			catch (std::filesystem::filesystem_error const& ex)
			{
				PTR(rets) << -::abs(ex.code().value());
				return;
			}

			return;
		}


		// pathinfo 		��������Ϣ	���ַ��� -> �ɹ����飬���򷵻ش�����
		EXPORTDLL(info)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1;
			Funcs::getParams<LetObject>(params, &value1);
			if (value1.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path;
			value1 >> path;

			namespace fs = std::filesystem;
			PTR(rets) << false;

			try
			{
				fs::path path_ret{ path };
				PTR(rets)["abs"] << fs::absolute(path_ret).string();
				PTR(rets)["relative"] << fs::relative(path_ret).string();
				PTR(rets)["filename"] << path_ret.filename().string();
				PTR(rets)["stem"] << path_ret.stem().string();
				PTR(rets)["ext"] << path_ret.extension().string();
				PTR(rets)["parent"] << path_ret.parent_path().string();
				PTR(rets)["drive"] << path_ret.root_name().string();
				PTR(rets)["dirname"] << path_ret.remove_filename().string();
			}
			catch (std::filesystem::filesystem_error const& ex)
			{
				PTR(rets) << -::abs(ex.code().value());
				return;
			}

			return;
		}

		// samefile 		�ж�Ŀ¼���ļ��Ƿ���ͬ ���ַ���|�ַ��� -> �ɹ����֣����򷵻ش�����
		EXPORTDLL(samefile)
		{
			PARAMS(params);
			RESULT(rets);

			auto_c value1, value2;
			Funcs::getParams<LetObject>(params, &value2, &value1);
			if (value1.getType() != LetObject::ObjT::string ||
				value2.getType() != LetObject::ObjT::string)
			{
				return;
			}

			std::string path1,path2;

			value1 >> path1;
			value2 >> path2;

			namespace fs = std::filesystem;

			try
			{
				fs::path path1_cls{ path1 };
				fs::path path2_cls{ path2 };

				PTR(rets) << path1_cls.compare(path2_cls);
			}
			catch (std::filesystem::filesystem_error const& ex)
			{
				PTR(rets) << -::abs(ex.code().value());
				return;
			}

			return;
		}
	}
}