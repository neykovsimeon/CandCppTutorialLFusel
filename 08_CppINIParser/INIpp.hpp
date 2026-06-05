#pragma once

#include <string>
#include <format>
#include <cctype>
#include <vector>
#include <sstream>
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

				// Convertion between string and other types (int for example)
				// Pay attention not to use Get() to return string using stringstream, because the space breaks the stream
				template<typename T>
				T Get(const T& defaultValue = T())
				{
					T temp = defaultValue;
					std::stringstream ss;
					ss << m_value;
					ss >> temp;
					return temp;
				}
				// A solution to use Get() with strings, but not using stringstream
				template<>
				std::string Get(const std::string& defaultValue)
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
					for (auto& pair : m_KeyValuePairs)
					{
						keys.push_back(pair.first);
					}
					return keys;
				}

				// Old Append implementation
				//void Append(const Key& key, KeyValuePair&& /* &&-> move semantic */ value)
				//{
				//	m_KeyValuePairs.emplace(key, std::move(value));
				//}
				void Append(KeyValuePair&& /* &&-> move semantic */ value)
				{
					m_KeyValuePairs.emplace(value.KeyName(), std::move(value));
				}

			private:
				// Will have multiple KeyValue pairs: Section -1-(key)-n-> KeyValuePairs
				std::string m_sectionName;
				std::unordered_map<Key, KeyValuePair> m_KeyValuePairs;
		};

		class Document
		{
			public:
				using Key = std::string;

				inline Section& operator[](const Key& sectionName)
				{
					// In case section doesn't exist we want to create it "on the fly"
					// TODO review: What happens if in the INI file more [section] with the same name exist?
					// Is the "next" supposed to overwrite the previous? Or can they be merged? What's the INI spec?
					// 1. Try to find: If exists - return it. Needed when a section has multiple keys
					auto it = m_sections.find(sectionName);
					if (it != m_sections.end())
					{
						return it->second;
					}
					// 2. It doesn't exists: Create new section to start with.
					else
					{
						auto& section = m_sections[sectionName];	// Here we create new (empty) section with the asked name
						section = std::move(Section(sectionName));	// Here we move the section's data
						return section;
					}
				}
				inline const Section& operator[](const Key& sectionName) const
				{
					// While this is const version -> we just return. It should exist!
					return m_sections.find(sectionName)->second;
				}

				std::vector<Key> Sections() const
				{
					std::vector<Key> sections;
					// Variant 1:
					//for (auto it = m_sections.begin(); it != m_sections.end(); ++it)
					//{
					//	sections.push_back(it->first);
					//}
					// Variant 2:
					for (auto& section : m_sections)
					{
						sections.push_back(section.first);
					}

					return sections;
				}

			private:
				// Will have multiple sections: Document -1-(name) -n->Sections
				std::unordered_map<Key, Section> m_sections;
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

			inline DOM::Document& Get()
			{
				return m_document;
			}

		private:
			DOM::Document m_document;
	};


}




