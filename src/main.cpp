#include <iostream>
#include "Sequence.h"
#include "DistanceLevenshtein.h"
#include "Instance.h"
#include "Solution.h"
#include "Algorithme.h"
using namespace std;

int main()
{
    string ADN1 = "+a-b+c-d+e-f+g-h+i";
    string ADN2 = "-g+f+e-d+g-f__-f+e";
    string ADN3 = "__________________";
    string ADN4 = "";
    string ADN5 = "";
    string ADN6 = "";

    Sequence sequence1 = Sequence(ADN1);
    Sequence sequence2 = Sequence(ADN2);
    Sequence sequence3 = Sequence(ADN3);
    Sequence sequence4 = Sequence(ADN4);
    Sequence sequence5 = Sequence(ADN5);
    Sequence sequence6 = Sequence(ADN6);


    cout << "Hello, World!" << endl;
    return 0;
}