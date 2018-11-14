#ifndef _CTRACE_
#define _CTRACE_
#include <cstdio>
#include <fstream>
#include <cstring>
#include <MainStd.h>
namespace Namspace_Trace
{
#if defined(_WIN32)
#define FileName(x) strrchr(x,'\\')?strrchr(x,'\\')+1:x
#else
#define FileName(x) strrchr(x,'/')?strrchr(x,'/')+1:x
#endif

#define TraceLevel(LogLevel, format, ...)\
CTrace::Instance()->Trace(LogLevel, "[%s:%d]"##format, FileName(__FILE__), __LINE__, __VA_ARGS__)
#define TraceDebug(format, ...)\
CTrace::Instance()->Trace("[%s:%d]"##format, FileName(__FILE__), __LINE__, __VA_ARGS__)

enum LogLevel
{
	LOG_INFO,
	LOG_WARNING,
	LOG_DEBUG,
	LOG_ERROR,
	LOG_INVALID
};
class CTrace
{
private:
	CTrace();
public:
	~CTrace();
public:
	static CTrace* Instance();
	const bool Init(const std::string& strLogFile);
	void Trace(LogLevel enLevel, const char* format, ...);
	void Trace(const char* format, ...);
	static void Destroy();
private:
	void ToFile(const std::string& strLog);
	void SetLogLevel(LogLevel enLevel);
	void CloseLogFile();
	std::string GetCurrTime();
	const bool CheckLogLevl(LogLevel enLevel);
	const std::string GetLogLevelString(LogLevel Level);
private:
	static CTrace*	m_sInstance;
	std::fstream	m_file;
	std::string		m_strfilePath;
	bool			m_bInit;
	LogLevel		m_enCurrLogLevl;
};

} //Namspace_Trace_CFH

#endif // !_CTRACE_

