#include "MiniDictionary.h"

void ConsoleInit()
{
	setlocale(LC_ALL, "ru");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

void SetColor(ConsoleColor text)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((Black << 4) | text));
}

void WaitNewMessage()
{
	SetColor(White);
	cout << ">";
	SetColor(Red);
}

string LowerCase(const string& message)
{
	string result = "";
	for (size_t i = 0; i < message.size(); i++)
		result += tolower(message[i]);
	return result;
}

string GetTranslate(map<string, string> ::iterator it)
{
	return it->second;
}

void SaveChanges(map<string, string> _dictionary)
{
	ofstream dictionaryFile;
	dictionaryFile.open("Dictionary.txt");
	for (auto item : _dictionary)
	{
		dictionaryFile << item.first << '\n' << item.second << '\n';
	}
	SetColor(LightCyan);
	cout << "»зменени€ сохранены. ƒо свидани€.\n";
}

void ReadDictionary(map<string, string>& _dictionary)
{
	ifstream dictionaryFile;
	dictionaryFile.open("Dictionary.txt");
	if (dictionaryFile.is_open())
	{
		string word, translate;
		while (!dictionaryFile.eof())
		{
			getline(dictionaryFile, word);
			if (word.size() != 0)
			{
				getline(dictionaryFile, translate);
				if (translate.size() != 0)
				{
					_dictionary.insert(make_pair(word, translate));
				}
			}
		}
	}
	else
	{
		dictionaryFile.close();
		ofstream createFile("Dictionary.txt");
		createFile.close();
	}
}

void SaveTranslation(map <string, string>& _dictionary, const string& word, const string& translation)
{
	SetColor(LightCyan);
	cout << "—лово У" << word << "Ф сохранено в словаре как У" << translation << "Ф.\n";
	_dictionary.insert(make_pair(LowerCase(word), translation));
}

void RunTranslator(map <string, string>& _dictionary)
{
	bool isChanged = false;
	string message;
	string buffer;
	map <string, string> ::iterator it;

	while (true)
	{
		WaitNewMessage();
		getline(cin, message);
		if (message != "...")
		{
			it = _dictionary.find(LowerCase(message));
			if (it != _dictionary.end())
			{
				SetColor(LightCyan);
				cout << GetTranslate(it) << '\n';
			}
			else
			{
				SetColor(LightCyan);
				cout << "Ќеизвестное слово У" << message << "Ф. ¬ведите перевод или пустую строку дл€ отказа.\n";
				WaitNewMessage();
				buffer = message;
				getline(cin, message);
				if (message.size() != 0 && message != "...")
				{
					isChanged = true;
					SaveTranslation(_dictionary, buffer, message);
				}
				else
				{
					SetColor(LightCyan);
					cout << "—лово У" << buffer << "Ф проигнорировано.\n";
				}
			}
		}
		else
		{
			if (isChanged)
			{
				SetColor(LightCyan);
				cout << "¬ словарь были внесены изменени€. ¬ведите Y или y дл€ сохранени€ перед выходом.\n";
				WaitNewMessage();
				getline(cin, message);
				if (LowerCase(message) == "y")
				{
					SaveChanges(_dictionary);
					break;
				}
				else
				{
					SetColor(LightCyan);
					cout << "»зменени€ не сохраненены. ƒо свидани€.\n";
					break;
				}
			}
			else
			{
				SetColor(LightCyan);
				cout << "ƒо свидани€!\n";
				break;
			}
		}
	}
}