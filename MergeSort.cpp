// C++Testrun.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

void shift(string listname[], int start, int checker) {
    string temp = listname[checker];
    for (int index = checker; index > start;index--) {
        listname[index] = listname[index - 1];
    }
    listname[start] = temp;
}

void sortarray(string listname[], int start, int finish) {
    int index = start;
    int checker = index +1;
    while (index < finish) {
        while (checker <= finish) {
            if (listname[checker].length() < listname[index].length()) {
                shift(listname, index, checker);
            }
            checker+=1;
        }
        index+=1;
        checker = index + 1;
    }
}

void Divsort(string listname[], int start, int finish) {
    int Size = finish - start + 1;
    if (Size > 2) {
        //cut array in 2 halves
        Divsort(listname, start, start + (Size / 2) - 1);
        Divsort(listname, finish - (Size / 2), finish);
        //combine

    }
    //sort array
    sortarray(listname, start, finish);
}

void test(string listname[], int Size) {
    cout << listname[3].length() << "\n";
    listname[3] = "change";
}

int main()
{
    string listName[10] = { "Charlie", "Zoe", "Chest","olie", "Santa","chloer", "mamapoula","devilish", "Good", "anastasia" };
    Divsort(listName, 0,9);
    cout << listName[0] << "\n" << listName[1] << "\n" << listName[2] << "\n" << listName[3] << "\n" << listName[4] << "\n" << listName[5] << "\n" << listName[6] << "\n" << listName[7] << "\n" << listName[8] << "\n" << listName[9] << "\n";
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
