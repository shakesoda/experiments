/* Logger - Simply logs activity as the owner wishes */
#ifndef _NEPGEAR_LOG_H_
#define _NEPGEAR_LOG_H_

#include <cstdarg>
#include <cstdio>
#include <physfs.h>
#include <string>

// Extra warnings, hm
#define PRINTF(m,n) __attribute__((format(__printf__,m,n)))

namespace Nepgear
{


enum LogLevel
{
	LOG_TRACE	= 0x01,
	LOG_DEBUG	= 0x02,
	LOG_WARN	= 0x04,
	LOG_ERROR	= 0x08
};

enum ConsoleColor
{
	FG_BLACK	= 30,
	FG_RED		= 31,
	FG_GREEN	= 32,
	FG_BROWN	= 33,
	FG_BLUE		= 34,
	FG_MAGENTA	= 35,
	FG_CYAN		= 36,
	FG_WHITE	= 37,
	FG_YELLOW	= 38,
	FG_INVALID	= 255
};

class Logger
{
public:
	// Constructor and destructor
	Logger(const char *sPath = NULL);
	virtual ~Logger();

	// Log functions
	void trace(const char *fmt, ...) PRINTF(2,3);
	void debug(const char *fmt, ...) PRINTF(2,3);
	void warn(const char *fmt, ...) PRINTF(2,3);
	void error(const char *fmt, ...) PRINTF(2,3);

	void trace(const std::string s) { trace("%s", s.c_str()); }
	void debug(const std::string s) { debug("%s", s.c_str()); }
	void warn(const std::string s)  { warn("%s", s.c_str());  }
	void error(const std::string s) { error("%s", s.c_str()); }

	void print_header();

	void use_colors(bool flag) { m_use_colors = flag; }
	void show_traces(bool flag) { m_show_traces = flag; }

private:
	// This one does all the real work
	void internal(std::string str, std::string message,
		ConsoleColor color, bool show = true);
	
	// The file for this log
	PHYSFS_File *m_File;
	bool m_use_colors, m_show_traces;
};

}

#undef PRINTF

#endif
