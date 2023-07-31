#pragma once
#ifndef _CERVER_STD_PRINTAUTO_
#define _CERVER_STD_PRINTAUTO_

#include <vector>

#include "../Public/AutoObject/LetManager.h"
#include "../Public/AutoObject/LetObject.h"


namespace ScriptC {
	namespace Obj {
		using namespace AutoMem::Obj;

		void printAuto_c(auto_c& value);
		void getParamsBack(std::vector<auto_c> * vec , auto_c* value);

		numberT getNewFileId();
		std::pair<numberT, FILE*> getFilePtrFromId(numberT id);
		void setFilePtrToId(numberT id, FILE* ptr);
		void clearFileId(numberT id);

		void setErrorStr(std::string str);
		std::string getErrorStr();

		char* getReadMemery();
	}
}


#endif