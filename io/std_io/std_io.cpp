#include "std_io.h"
#include "main/printAuto.h"
#include "QuickLib/quicklib.h"

#include "Shlwapi.h"

#pragma comment(lib,"Shlwapi.lib")

#define Fname(var) void __system__io__##var##__ (void* param,void* ret)
#define EXPORTDLL(var) extern "C" _declspec(dllexport) Fname(var)
#define RESULT(var) auto_c*var = (auto_c*)ret; *var = auto_c()
#define PARAMS(var) std::vector<auto_c>* var = (std::vector<auto_c>*)param
#define PTR(var) *var


namespace ScriptC {
	namespace Obj {
		using namespace AutoMem::Obj;
		EXPORTDLL(fopen) {
			RESULT(rets);
			PARAMS(params);

			auto_c filePath, OpenMode;
			getParamsBack(params, &OpenMode);
			getParamsBack(params, &filePath);

			if (filePath.getType() != LetObject::ObjT::string ||
				OpenMode.getType() != LetObject::ObjT::string) {
				throw("Vm : function fopen need “string,string”");
			}

			std::string path, mode;
			filePath >> path;
			OpenMode >> mode;

			FILE* ptr = nullptr;
			errno_t code = ::fopen_s(&ptr, path.c_str(), mode.c_str());
			if (code == 0) {
				numberT id = getNewFileId();
				setFilePtrToId(id, ptr);
				PTR(rets) << id;
			}
			else {
				PTR(rets) << false;
			}

			return;
		}

		EXPORTDLL(fclose) {
			RESULT(rets);
			PARAMS(params);

			auto_c fileId;
			getParamsBack(params, &fileId);

			if (fileId.getType() != LetObject::ObjT::number) {
				throw("Vm : function fclose need “string”");
			}

			numberT id;
			fileId >> id;

			auto FilePack = getFilePtrFromId(id);
			FILE* ptr = FilePack.second;
			if (ptr == nullptr) {
				PTR(rets) << false;
				return;
			}

			int code = ::fclose(ptr);
			if (code == 0) {
				PTR(rets) << true;
				clearFileId(id);
			}
			else {
				PTR(rets) << false;
			}



		}

		EXPORTDLL(fread) {
			RESULT(rets);
			PARAMS(params);

			auto_c fileId, ReadL;
			getParamsBack(params, &ReadL);
			getParamsBack(params, &fileId);

			if (fileId.getType() != LetObject::ObjT::number ||
				ReadL.getType() != LetObject::ObjT::number) {
				throw("Vm : function fread need “number,number”");
			}

			numberT id;numberT lens;
			fileId >> id;
			ReadL  >> lens;

			auto FilePack = getFilePtrFromId(id);
			FILE* ptr = FilePack.second;
			if (ptr == nullptr) {
				PTR(rets) << false;
				return;
			}

			char* mem = getReadMemery();
			ZeroMemory(mem, 4096);
			std::string txt;

			if (lens <= -2) {
				// 全部
				auto nowPos = ::ftell(ptr);
				::fseek(ptr, 0, SEEK_END);
				auto endPos = ::ftell(ptr);
				::fseek(ptr, nowPos, SEEK_SET);
				lens = static_cast<numberT>(endPos) - static_cast<numberT>(nowPos);
			}
			else if(lens < 0){
				// 行
				bool success = false;
				while(fgets(mem, 4096, ptr) != NULL){
					success = true;
					size_t memLens = strnlen_s(mem, 4096);
					mem[memLens] = '\0';
					txt.append(mem, memLens);
					if (txt[txt.length() - 1] == '\n' || txt[txt.length() - 1] == '\r') {
						break;
					}
				}

				if (!success)
					PTR(rets) << false;
				else
					PTR(rets) << txt;

				return;
			}

			long long lensC = 0;

			while (lens > 0) {
				auto lensR = ::fread(mem, 1, lens >= 4096 ? 4096 : lens, ptr);
				mem[4096] = '\0';
				lensC += lensR;
				lens -= static_cast<numberT>(lensR);
				txt.append(mem,lensR);
				if (lensR == 0)
					break;
			}

			PTR(rets) << txt;
		}

		EXPORTDLL(fwrite) {
			RESULT(rets);
			PARAMS(params);

			auto_c fileId, TxtStr, WriteL;
			getParamsBack(params, &WriteL);
			getParamsBack(params, &TxtStr);
			getParamsBack(params, &fileId);

			if (fileId.getType() != LetObject::ObjT::number ||
				(TxtStr.getType() != LetObject::ObjT::string && TxtStr.getType() != LetObject::ObjT::number)||
				WriteL.getType() != LetObject::ObjT::number) {
				throw("Vm : function fwrite need “number,string,number”");
			}

			numberT id; std::string txt; numberT lens;
			fileId >> id;
			if (TxtStr.getType() == LetObject::ObjT::number) {
				numberT num;
				TxtStr >> num;
				txt = kstring::stringFrom<numberT>(num);
			}
			else {
				TxtStr >> txt;
			}
			WriteL >> lens;

			auto FilePack = getFilePtrFromId(id);
			FILE* ptr = FilePack.second;
			if (ptr == nullptr) {
				PTR(rets) << false;
				return;
			}
		
			lens = lens < 0 ? txt.length() : lens;
			lens = ::fwrite(txt.c_str(), 1, lens, ptr);
			PTR(rets) << lens;
		}

		EXPORTDLL(ftell) {
			RESULT(rets);
			PARAMS(params);

			auto_c fileId;
			getParamsBack(params, &fileId);

			if (fileId.getType() != LetObject::ObjT::number) {
				throw("Vm : function ftell need “number”");
			}

			numberT id;
			fileId >> id;

			auto FilePack = getFilePtrFromId(id);
			if (FilePack.second == nullptr) {
				PTR(rets) << false;
				return;
			}

			int lens = ::ftell(FilePack.second);
			if(lens == -1L)
				PTR(rets) << false;
			else
				PTR(rets) << lens;

			return;
		}

		EXPORTDLL(fseek) {
			RESULT(rets);
			PARAMS(params);

			auto_c fileId,position,offset;
			getParamsBack(params, &offset);
			getParamsBack(params, &position);
			getParamsBack(params, &fileId);

			if (fileId.getType() != LetObject::ObjT::number || 
				position.getType() != LetObject::ObjT::number ||
				offset.getType() != LetObject::ObjT::number) {
				throw("Vm : function fseek need “number,number,number”");
			}

			numberT id, pos, off;
			fileId >> id;
			position >> pos;
			offset >> off;

			auto FilePack = getFilePtrFromId(id);
			if (FilePack.second == nullptr || 
				!(static_cast<int>(pos) >= 0 && static_cast<int>(pos) <= 2)) {
				PTR(rets) << false;
				return;
			}
			FILE* ptr = FilePack.second;

			int offi = static_cast<int>(off);
			int posi = static_cast<int>(pos);

			// 文件Id 偏移 位置
			int code = ::fseek(ptr, offi, posi);
			ptr = nullptr;
			if (code == 0)
				PTR(rets) << true;
			else
				PTR(rets) << false;

			return;
		}

		EXPORTDLL(errset) {
			RESULT(rets);
			PARAMS(params);

			std::string pathstr;
			auto_c filepath;
			getParamsBack(params, &filepath);

			if (filepath.getType() != LetObject::ObjT::string) {
				throw("Vm : function errset need “string”");
			}

			filepath >> pathstr;
			setErrorStr(pathstr);
		}

		EXPORTDLL(errget) {
			RESULT(rets);

			std::string pathstr;
			std::string err = getErrorStr();
			if (err.empty())
				PTR(rets) << false;
			else
				PTR(rets) << err;
			
			return;
		}

		EXPORTDLL(tmpfile) {
			RESULT(rets);
			PARAMS(params);

			FILE* ptr = nullptr;
			errno_t code = ::tmpfile_s(&ptr);
			if (code == 0) {
				numberT id = getNewFileId();
				setFilePtrToId(id, ptr);
				PTR(rets) << id;
				return;
			}
			else {
				PTR(rets) << false;
			}

			return;
		}

		EXPORTDLL(frename) {
			RESULT(rets);
			PARAMS(params);

			auto_c oneName , twoName;
			std::string sourceFile, renameFile;
			getParamsBack(params, &oneName);
			getParamsBack(params, &twoName);

			if (oneName.getType() != LetObject::ObjT::string || twoName.getType() != LetObject::ObjT::string) {
				throw("Vm : function frename need “string,string”");
			}

			twoName >> sourceFile;
			oneName >> renameFile;

			int code = ::rename(sourceFile.c_str(), renameFile.c_str());
			if (code == 0)
				PTR(rets) << true;
			else
				PTR(rets) << false;

			return;
		}

		EXPORTDLL(fremove) 
		{
			RESULT(rets);
			PARAMS(params);

			std::string pathstr;
			auto_c filepath;
			getParamsBack(params, &filepath);

			if (filepath.getType() != LetObject::ObjT::string) {
				throw("Vm : function fremove need “string”");
			}

			filepath >> pathstr;
			int removeRet = ::remove(pathstr.c_str());
			if (removeRet == 0) {
				PTR(rets) << true;
				return;
			}

			PTR(rets) << false;
			return;
		}

		EXPORTDLL(fcreate) 
		{
			RESULT(rets);
			PARAMS(params);

			std::string pathstr;
			auto_c filepath;
			getParamsBack(params, &filepath);

			if (filepath.getType() != LetObject::ObjT::string) {
				throw("Vm : function fcreate need string");
			}

			filepath >> pathstr;
			bool isExist = PathFileExistsA(pathstr.c_str());
			if (isExist) {
				PTR(rets) << false;
				return;
			}

			FILE* ptr = nullptr;
			errno_t err = fopen_s(&ptr,pathstr.c_str(), "a");
			if (err != 0) {
				PTR(rets) << false;
				return;
			}

			fclose(ptr);

			PTR(rets) << true;
			return;
		}

		EXPORTDLL(fexist)
		{
			RESULT(rets);
			PARAMS(params);

			std::string pathstr;
			auto_c filepath;
			getParamsBack(params, &filepath);

			if (filepath.getType() != LetObject::ObjT::string) {
				throw("Vm : function fexist need “string”");
			}

			filepath >> pathstr;

			bool isExist = PathFileExistsA(pathstr.c_str());
			PTR(rets) << isExist;
		}

		EXPORTDLL(print)
		{
			std::vector<auto_c>* params = (std::vector<auto_c>*)param;
			auto_c* rets = (auto_c*)ret;
			for (auto& i : *params) {
				printAuto_c(i);
			}

			*rets = auto_c(false,false);
		}

		EXPORTDLL(input)
		{
			auto_c* rets = (auto_c*)ret;
			
			std::string str;
			std::cin >> str;

			*rets = auto_c(false, false);
			(*rets) << str;
		}


	}
}