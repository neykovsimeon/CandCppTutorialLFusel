#include "INIpp.hpp"

void INIpp::Parser::AddFile(const std::filesystem::path& path)
{
	// Open the file
	std::ifstream fileIn(path, std::ios::binary | std::ios::in);
	if (!fileIn.is_open())
	{
		throw Exception(std::format("Can't open file \"{}\" ", path.string()));
	}

	// Find how big the file is
	fileIn.seekg(0, std::ios::end);
	size_t fileSize = fileIn.tellg();					// Takes the file size
	fileIn.seekg(0, std::ios::beg);						// Rewind the file, means return back to its beginning (beg)

	// Read the file and store in one string variable
	std::string fileData(fileSize, ' ');				// Resize the file buffer for fileData				
	//fileIn.read(&fileData[0], fileSize);				// Actual file read and store in app's resized variable fileData
	fileIn.read(fileData.data(), fileSize);				// Actual file read and store in app's resized variable fileData
	
	// Provide to the string processing function as one string
	AddString(fileData);
}
//**********************************************************************************************************************
void INIpp::Parser::AddString(const std::string_view& str)
{
	StateMachineReset();
	for (char c : str)
	{
		ProcessChar(c);
	}
}
//**********************************************************************************************************************
void INIpp::Parser::StateMachineReset()
{
	m_currentSectionName = "";
	m_currentKeyName = "";
	m_currentKeyValue = "";

	m_state = State::ReadyForData;
}
//**********************************************************************************************************************
void INIpp::Parser::ProcessChar(char c)
{
	// Catch control keys/chars
	if (std::iscntrl(c))
	{
		switch (c)
		{
			case '\t':
				[[fallthrough]];
			case '\n':
				break;
			default:
				return;
		}
	}

	// Normal char parsing
	switch (m_state)
	{
		case State::ReadyForData:
			switch (c)
			{
				case ';':
					[[fallthrough]];
				case '#':
					m_state = State::Comment; // Accept both ';' and '#' as a Comment line designator
					break;
				case '[':
					m_currentSectionName.clear();
					m_state = State::SectionName;
					break;
				case ' ':
					[[fallthrough]];
				case '\t':
					[[fallthrough]];
				case '\n':
					break;
				default:
					m_currentKeyName.clear();
					m_currentKeyName += c;	// This is just taking the first char(c) from the key's name
					m_state = State::KeyNameStarted;
					break;
			}
			break;
		case State::Comment:
			if (c == '\n')
			{
				m_state = State::ReadyForData;
			}		
			break;
		case State::SectionName:
			switch (c)
			{
				case ']':
					m_state = State::ReadyForData;
					break;
				// New line and tabulator are not allowed in Section name. Exception handling to be implemented
				case '\n':
					[[fallthrough]];
				case '\t':	
					throw Exception("New line and Tabulator are not allowed in section's name!\n");
					break;	// TODO do we need break; when we throw an exception?
				default:
					m_currentSectionName += c;
					break;
			}
			break;
		case State::KeyNameStarted:
			switch (c)
			{
			case '\t':	// Will accept tabulator as valid end of the key's name designator, same as the space (' ')
				[[fallthrough]];
			case ' ':
				m_state = State::KeyNameFinished;
				break;
			case '\n':
				throw Exception("New line is not allowed in the key's name!\n");
				break;	// TODO do we need break; when we throw an exception?
			default:
				m_currentKeyName += c;
				break;
			}
			break;
		case State::KeyNameFinished:
			switch (c)
			{
				case ' ':
					[[fallthrough]];
				case '\t':
					break;
				case '\n':
					throw Exception("New line is not allowed in the key value!\n");
					break;	// TODO do we need break; when we throw an exception?
				case '=':
					m_state = State::ReadyForKeyValue; // this is the part of data directly after '=' sign
					break;
				default:
					throw Exception("Key names are not allowed to have spaces in them!\n");
					break;	// TODO do we need break; when we throw an exception?
			}
			break;
		case State::ReadyForKeyValue:	// this is the part of data directly after '=' sign
			// Ignore spaces and tabs untill valid char comes for key's value
			switch (c)
			{
				case ' ':
					[[fallthrough]];
				case '\t':
					break;
				case '\n':
					throw Exception("New line directly after '=' is not a valid key value!\n");
					break;
				default:
					// Clear the value buffer, then add first char (c), 
					// then set the valid State for the continuous read of the key's value string
					m_currentKeyValue.clear(); 
					m_currentKeyValue += c;
					m_state = State::KeyValueStarted;
					break;
			}
			break;
		case State::KeyValueStarted:
			if (c == '\n')
			{
				RemoveTrailingWhitespace(m_currentKeyValue);
				ParseKeyValuePair(m_currentSectionName, m_currentKeyName, m_currentKeyValue);
				m_state = State::ReadyForData;
			}
			else
			{
				m_currentKeyValue += c;
			}
			break;

		default:
			break;
	}
}
//**********************************************************************************************************************
void INIpp::Parser::RemoveTrailingWhitespace(std::string& str) // AI - generated !!!
{
	// 1. Drop the explicit C-style null terminator if it exists at the end
	if (!str.empty() && str.back() == '\0') {
		str.pop_back();
	}

	// 2. Find the last actual character that isn't whitespace
	size_t end = str.find_last_not_of(" \t");

	if (end == std::string::npos) {
		str.clear();
	}
	else {
		str.erase(end + 1); // 3. Wipe out all trailing whitespace instantly
	}
}
//**********************************************************************************************************************
void INIpp::SAXParser::ParseKeyValuePair(const std::string& section, const std::string& key, const std::string& value)
{
	if (m_callback)
	{
		m_callback(section, key, value);
	}
}
//**********************************************************************************************************************
void INIpp::DOMParser::ParseKeyValuePair(const std::string& section, const std::string& key, const std::string& value)
{
	m_document[section].Append(DOM::KeyValuePair(key, value));
}


