#include "MiniDictionary.h"

int main()
{
	ConsoleInit();
	map <string, string> dictionary;
	ReadDictionary(dictionary);
	RunTranslator(dictionary);
}