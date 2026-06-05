#pragma once

#include <string>
#include <format>
#include <cctype>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <functional>
#include <string_view>
#include <filesystem>
//#include <map>	// TODO: Review: Contains the items in the order they have been inserted
#include <unordered_map>

namespace INIpp
{
	namespace DOM // Document Object's Model
	{
		class KeyValuePair
		{
			public:
				// Constructors
				KeyValuePair() = default;
				KeyValuePair(const std::string_view& key, const std::string_view& value):
					m_key(key), m_value(value)
				{ }

				inline const std::string& KeyName() const noexcept
				{
					return m_key;
				}
				inline const std::string& KeyValue() const noexcept
				{
					return m_value;
				}

			private:
			// strings
				std::string m_key;
				std::string m_value;
		};

		class Section
		{
			public:
				using Key = std::string;
				
				Section() = default;
				Section(const std::string_view& name):
					m_sectionName(name)
				{ }

				inline const std::string& SectionName() const noexcept
				{
					return m_sectionName;
				}
				inline KeyValuePair& operator[](const Key& key)
				{
					return m_KeyValuePairs.find(key)->second;
				}
				inline const KeyValuePair& operator[](const Key& key) const
				{
					return m_KeyValuePairs.find(key)->second;
				}

				std::vector<Key> Keys() const
				{
					std::vector<Key> keys;
					for (auto it = m_KeyValuePairs.begin(); it != m_KeyValuePairs.end(); ++it)
					{
						keys.push_back(it->first);
					}
					return keys;
				}

				void Append(const Key& key, KeyValuePair&& /* &&-> move semantic */ value)
				{
					m_KeyValuePairs.emplace(key, std::move(value));
				}

			private:
				// Will have multiple KeyValue pairs: Section -1-(key)-n-> KeyValuePairs
				std::string m_sectionName;
				std::unordered_map<Key, KeyValuePair> m_KeyValuePairs;
		};

		class Document
		{
			
			private:
				// Will have multiple sections: Document -1-(name) -n->Sections
		};
	}


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




