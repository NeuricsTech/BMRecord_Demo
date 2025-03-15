#include "Core.h"

#include <memory>
#include <string>
#include <vector>

namespace BMRecord_Lib
{
	class ErrorManager {
	public:
		struct ErrorInfo {
			int code;
			char message[100];
			char file[100];
			int line;
			char function[100];
			char timestamp[100];
		};

		_BMR_API_ static ErrorManager& getInstance();
		_BMR_API_ static void enableErrorManager(bool enable);

		_BMR_API_ bool hasError() const noexcept;
		_BMR_API_ ErrorInfo ErrorManager::getLastError();
		_BMR_API_ void clearErrors() noexcept;

		_BMR_API_ bool hasInfo() const noexcept;
		_BMR_API_ ErrorInfo ErrorManager::getLastInfo();
		_BMR_API_ ErrorInfo ErrorManager::getFirstInfo();
		_BMR_API_ void clearInfos() noexcept;

		ErrorManager(const ErrorManager&) = delete;
		ErrorManager& operator=(const ErrorManager&) = delete;

		void addError(int code, const std::string& msg, const char* file, int line, const char* func);
		void addInfo(int code, const std::string& msg, const char* file, int line, const char* func);

	private:
		ErrorManager();
		~ErrorManager();

		static bool log;
		struct Impl;
		std::shared_ptr<Impl> pimpl;
	};
}

#ifdef BMR_DEBUG
#define LOG_ERROR(code, msg) \
    addError(code, msg, __FILE__, __LINE__, __FUNCTION__)
#define LOG_INFO(msg) \
    addInfo(0, msg, __FILE__, __LINE__, __FUNCTION__)
#else
#define LOG_ERROR(code, msg) \
	addError(code, msg, "[FILE]", 0, "[FUNCTION]")
#define LOG_INFO(msg) \
    addInfo(0, msg, "[FILE]", 0, "[FUNCTION]")
#endif