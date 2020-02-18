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

// Функция замены всех включений подстроки во входной строке
string Replacer(string& inputString, const string& searchString, const string& replaceString)
{
	string outputString = "";
	size_t startPos;
	while (inputString.find(searchString) != string::npos)
	{
		startPos = inputString.find(searchString);
		outputString += inputString.substr(0, startPos);
		inputString.erase(0, startPos + searchString.size());
		outputString += replaceString;
	}
	outputString += inputString;
	return outputString;
}

//	Функция замены всех включений подстроки в тексте из потока ввода и последующая запись полученного текста в поток вывода
bool ReplaceString(istream& input, ostream& output, const string& searchString, const string& replaceString)
{
	string someString;
	string outputString;
	while (getline(input, someString))
	{
		outputString = Replacer(someString, searchString, replaceString);

		if (!input.eof())
		{
			if (!(output << outputString << '\n'))
			{
				return false;
			}
		}
		else
		{
			if (!(output << outputString))
			{
				return false;
			}
		}
	}
	return true;
};

//	Функция копирования с заменой из потока ввода в поток вывода
bool CopyWithReplace(const string& inputFileName, const string& outputFileName, const string& searchString, const string& replaceString)
{
	//	Инициализация входного потока
	ifstream inputFile;
	inputFile.open(inputFileName);
	if (!inputFile.is_open())
	{
		cout << "Failed to open " << inputFileName << " for reading\n";
		return false;
	}

	//	Инициализация выходного потока
	ofstream outputFile;
	outputFile.open(outputFileName);
	if (!outputFile.is_open())
	{
		cout << "Failed to open " << outputFileName << " for writing\n";
		return false;
	}

	//	Замена искомых подстрок в строках файла входного потока с последующим выводом в выходной поток
	if (!ReplaceString(inputFile, outputFile, searchString, replaceString))
	{
		return false;
	}

	//	Проверка состояния входного потока
	if (inputFile.bad())
	{
		cout << "Failed to read data from input file\n";
		return false;
	}

	//	Проверка состояния выходного потока
	if (!outputFile.flush())
	{
		cout << "Failed to write data to output file\n";
		return false;
	}

	return true;
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
	if (!CopyWithReplace(args->inputFileName, args->outputFileName, args->searchString, args->replaceString))
	{
		return 1;
	}

	return 0;
}