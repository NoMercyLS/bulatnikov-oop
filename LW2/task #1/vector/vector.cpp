#include "vector.h"

int main()
{
    vector<float> numbers = GetVector(cin);
    PrintVector(numbers);
    MultMaxDivMin(numbers);
    SortVector(numbers);
    PrintVector(numbers);
}