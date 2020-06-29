#include "source.h"
#include "CHttpUrl.h"

int main()
{
	std::string urlString;
	while (!std::cin.eof() && !std::cin.fail())
	{
		std::cout << "Enter URL: ";
		std::getline(std::cin, urlString);
		try
		{
			CHttpUrl url(urlString);
			std::cout << GetInfo(url);
		}
		catch (std::exception const& e)
		{
			std::cout << e.what();
		}
		std::cout << std::endl;
	}
	return 0;
}
