#include "printAuto.h"
#include <unordered_map>
#include <iomanip>
#include <random>

namespace Cervice {
	namespace Obj {

		namespace {
			class _FileGc {
			private:
				_FileGc() {}
				~_FileGc() {
					for (auto& i : m_file_id_vec) {
						::fclose(i.second);
					}
				}
				
				static _FileGc* m_instance;

				class Gc {
				public:
					~Gc() {
						if (m_instance) {
							delete m_instance;
						}
					};
				};
			public:
				static _FileGc* getGc() {
					static _FileGc::Gc gc;

					if (!m_instance) {
						m_instance = new _FileGc;
					}

					return m_instance;
				}
			public:
				static std::string m_error_str;
				static std::unordered_map<numberT, FILE*> m_file_id_vec;
				static char* m_file_memery_cache;
			};
			_FileGc* _FileGc::m_instance = nullptr;
			std::unordered_map<numberT, FILE*> _FileGc::m_file_id_vec;
			char* _FileGc::m_file_memery_cache = new char[4096]{ 0 };
			std::string _FileGc::m_error_str;
		}

		char* getReadMemery()
		{
			auto gc = _FileGc::getGc();
			return gc->m_file_memery_cache;
		}

		std::string getErrorStr()
		{
			auto gc = _FileGc::getGc();
			std::string ret = std::move(gc->m_error_str);
			return ret;
		}
		
		void setErrorStr(std::string str)
		{
			auto gc = _FileGc::getGc();
			gc->m_error_str = std::move(str);
		}

		void getParamsBack(std::vector<auto_c>* vec, auto_c* value) {
			*value = vec->back();
			vec->pop_back();
		}

		numberT getNewFileId()
		{
			auto gc = _FileGc::getGc();
			std::mt19937 mt_rand(std::random_device{}());
			unsigned int id = 0;
			do {
				id = mt_rand();
			} while (!(id > 0 && gc->m_file_id_vec.find(id) == gc->m_file_id_vec.end()));

			return static_cast<numberT>(id);
		}

		std::pair<numberT, FILE*> getFilePtrFromId(numberT id)
		{
			std::pair<numberT, FILE*>ret;
			auto gc = _FileGc::getGc();
			ret.first = id;
			auto finder = gc->m_file_id_vec.find(id);
			if (finder == gc->m_file_id_vec.end()) {
				ret.second = nullptr;
			}
			else {
				ret = *finder;
			}

			return ret;
		}

		void setFilePtrToId(numberT id, FILE* ptr)
		{
			std::pair<numberT, FILE*>ret;
			auto gc = _FileGc::getGc();
			gc->m_file_id_vec[id] = ptr;
		}

		void clearFileId(numberT id)
		{
			std::pair<numberT, FILE*>ret;
			auto gc = _FileGc::getGc();
			auto finder = gc->m_file_id_vec.find(id);
			if (finder != gc->m_file_id_vec.end()) {
				gc->m_file_id_vec.erase(finder);
			}

			return;
		}

		void printAuto_c(auto_c& value)
		{
			if (value.getType() == LetObject::ObjT::array) {
				auto indexV = value.getIndexs();
				for (auto& in : indexV) {
					if (in.getType() == LetObject::ObjT::number) {
						auto_c i;
						i = value[LetObject::cast<numberT>(in)];
						if (i.getType() == LetObject::ObjT::array) {
							printAuto_c(i);
						}
						else if (i.getType() == LetObject::ObjT::number) {
							std::cout << std::setiosflags(std::ios_base::fixed) << LetObject::cast<numberT>(i);
						}
						else if (i.getType() == LetObject::ObjT::boolean) {
							std::cout << std::boolalpha << LetObject::cast<bool>(i);
						}
						else {
							std::cout << LetObject::cast<std::string>(i);
						}
					}
					else {
						auto_c i;
						i = value[LetObject::cast<std::string>(in)];
						if (i.getType() == LetObject::ObjT::array) {
							printAuto_c(i);
						}
						else if (i.getType() == LetObject::ObjT::boolean) {
							std::cout << std::boolalpha << " " << LetObject::cast<bool>(i);
						}
						else if (i.getType() == LetObject::ObjT::number) {
							std::cout << std::setiosflags(std::ios_base::fixed) << LetObject::cast<numberT>(i);
						}
						else {
							std::cout << LetObject::cast<std::string>(i);
						}
					}
				}
			}
			else if (value.getType() == LetObject::ObjT::number) {
				std::cout << std::setiosflags(std::ios_base::fixed) << LetObject::cast<long double>(value);
			}
			else if (value.getType() == LetObject::ObjT::string) {
				std::cout << LetObject::cast<std::string>(value);
			}
			else if (value.getType() == LetObject::ObjT::boolean) {
				std::cout << std::boolalpha << LetObject::cast<bool>(value);
			}

		}

	}
}
