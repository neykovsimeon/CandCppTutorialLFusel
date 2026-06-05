#pragma once

#include <string>
#include <format>
#include <cctype>
#include <fstream>
#include <stdexcept>
#include <functional>
#include <string_view>
#include <filesystem>


namespace INIpp
{
	class Exception : public std::runtime_error
	{
		public:
			using std::runtime_error::runtime_error;

	};
	
	class Parser
	{
		private:
			enum class State
			{
				ReadyForData,					// Internal state flushed and ready for any ini data
				Comment,						// Comment started
				SectionName,					// Section is being defined
				KeyNameStarted,					// Key Name Started
				KeyNameFinished,				// Key Name finished, wait for '=' to come
				ReadyForKeyValue,				// Equal sign '=' comes
				KeyValueStarted,				// Key value started
				InvalidState,					// t.b.d. how to use
			};

		public:
			void AddFile(const std::filesystem::path& path);
			void AddString(const std::string_view& str);
			void StateMachineReset();

			// Make it virtual, ask the app which will do the parsing to implement on its own (main.cpp in this example)
			virtual void ParseKeyValuePair(const std::string& section, const std::string& key, const std::string& value) = 0;

		private:
			void ProcessChar(char c);	// Actual State Machine to process the char c read from the file
			void RemoveTrailingWhitespace(std::string& str);


		private:
			State m_state = State::ReadyForData;
			std::string m_currentSectionName, m_currentKeyName, m_currentKeyValue;
	};

	class SAXParser : public Parser
	{
		public:
			using Callback = std::function<void(const std::string&, const std::string&, const std::string&)>;

			SAXParser() = default;
			SAXParser(Callback callback):
				m_callback(callback)
			{ }

			void ParseKeyValuePair(const std::string& section, const std::string& key, const std::string& value) override;

		private:
			Callback m_callback;
	};

	class DOMParser : public Parser
	{
	public:
		void ParseKeyValuePair(const std::string& section, const std::string& key, const std::string& value) override;

	private:

	};


}




