#include "INIpp.hpp"

#include <iostream>

class MyFancySettingsProvider
{
	public:
		MyFancySettingsProvider(std::ostream& os):
			m_os(os)
		{ }

		void KichOff(const std::filesystem::path& configFile = "./my_config.ini")
		{
			INIpp::SAXParser parser(
				std::bind(&MyFancySettingsProvider::OnKeyVauePair, this, 
				std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

			parser.AddFile(configFile);
		}

	private:
		void OnKeyVauePair(const std::string& section, const std::string& key, const std::string& value)
		{
			m_os << section << " -> " << key << " = " << value << ";" << std::endl;
		}

	private:
		std::ostream& m_os;
};

int main()
{
	MyFancySettingsProvider sp(std::cout);
	sp.KichOff();
	std::cout << "\nHello World! INI Cpp Parser..." << std::endl;

	return 0;
}

