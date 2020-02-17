#include <iostream>
#include <fstream>
#include <optional>
#include <string>

using namespace std;

//	Разработайте программу replace.exe,
//	выполняющую замену всех вхождений подстроки в текстовом файле на другую строку,
//	и записывающей результат в выходной файл(отличный от входного).

struct Args
{
	string inputFileName;
	string outputFileName;
	string searchString;
	string replaceString;
};

//	Функция получения данных из аргументов командной строки
optional<Args> GetArgs(int argc, char* argv[])
{
	if (argc != 5)
	{
		cout << "Invalid number of arguments\n";
		cout << "Usage: Replace.exe <input file> <output file> <search string> <replace string>\n";
		return nullopt;
	}
	Args args;
	args.inputFileName = argv[1];
	args.outputFileName = argv[2];
	args.searchString = argv[3];
	args.replaceString = argv[4];
	return args;
}

//	Функция замены искомой подстроки в исходной строке
int ReplaceString(istream& input, ostream& output, const string& searchString, const string& replaceString)
{
	string someString;
	string outputString;
	int startPos;
	while (getline(input, someString))
	{
		outputString = "";
		while (someString.find(searchString) != string::npos)
		{
			startPos = someString.find(searchString);
			outputString += someString.substr(0, startPos);
			someString.erase(0, startPos + searchString.size());
			outputString += replaceString;
		}
		outputString += someString;
		if (!input.eof())
		{
			if (!(output << outputString << '\n'))
			{
				return 1;
			}
		}
		else
		{
			if (!(output << outputString))
			{
				return 1;
			}
		}
	}
	return 0;
};

//	Функция копирования с заменой из потока ввода в поток вывода
int CopyWithReplace(const string& inputFileName, const string& outputFileName, const string& searchString, const string& replaceString)
{
	//	Инициализация входного потока
	ifstream inputFile;
	inputFile.open(inputFileName);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << inputFileName << " for reading\n";
		return 1;
	}

	//	Инициализация выходного потока
	ofstream outputFile;
	outputFile.open(outputFileName);
	if (!outputFile.is_open())
	{
		cout << "Failed to open " << outputFileName << " for writing\n";
		return 1;
	}

	//	Замена искомых подстрок в строках файла входного потока с последующим выводом в выходной поток
	if (ReplaceString(inputFile, outputFile, searchString, replaceString) != 0)
	{
		return 1;
	}

	//	Проверка состояния входного потока
	if (inputFile.bad())
	{
		cout << "Failed to read data from input file\n";
		return 1;
	}

	//	Проверка состояния выходного потока
	if (!outputFile.flush())
	{
		cout << "Failed to write data to output file\n";
		return 1;
	}

	return 0;
}

int main(int argc, char* argv[])
{
	//	Получение данных из аргументов командной строки
	auto args = GetArgs(argc, argv);
	if (args == nullopt)
	{
		return 1;
	}

	//	Проверка искомой строки на пустоту
	if (args->searchString.empty())
	{
		cout << "Sought string is empty, please type string" << '\n';
		return 1;
	}

	//	Копирование данных из input в output с заменой искомой строки на строку-заменитель
	if (CopyWithReplace(args->inputFileName, args->outputFileName, args->searchString, args->replaceString) == 1)
	{
		return 1;
	}

	return 0;
}