#ifndef _NEPGEAR_FILE_H_
#define _NEPGEAR_FILE_H_

#include <fstream>
#include <string>

namespace Nepgear
{

class File
{
public:
	File(std::string filename);
	virtual ~File();
	std::string read();
	std::string get_section(std::string section);

private:
	std::ifstream m_handle;
	std::string m_content;
};

}

#endif

