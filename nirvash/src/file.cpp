#include "file.h"
#include <assert.h>

using namespace std;
using namespace Nepgear;

File::File(string filename)
{
	m_handle.open(filename.c_str(), std::fstream::in);

	assert(m_handle.is_open());

	m_content = this->read();
}

File::~File()
{
	if (m_handle.is_open())
		m_handle.close();
}

string File::read()
{
	using namespace std;
	string str((istreambuf_iterator<char>(m_handle)), istreambuf_iterator<char>());
	return str;
}

string File::get_section(string section)
{
	size_t start = m_content.find("-- "+section);
	size_t end = string::npos;

	// No matches
	if (start == string::npos)
		return "";

	// Separator isn't on a newline - invalid.
	if (start != 0 && m_content.at(start-1) != '\n')
		return "";

	// We've got a match. Remove the current line.
	start = m_content.find("\n", start)+1;

	// Stop at the next section, if it exists.
	end = m_content.find("\n--", start);

	return m_content.substr(start, end - start);
}
