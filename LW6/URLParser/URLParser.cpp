#include "source.h"
#include "CHttpUrl.h"

int main()
{
	string urlString;
	while (!cin.eof() && !cin.fail())
	{
		cout << "Enter URL: ";
		getline(cin, urlString);
		try
		{
			CHttpUrl url(urlString);
			cout << GetInfo(url);
		}
		catch (exception const& e)
		{
			cout << e.what();
		}
		cout << endl;
	}
	return 0;
}
