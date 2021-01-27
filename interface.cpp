#include "ascend.h"
#include <cstdlib>
#include "test.h"
#include "index.h"
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include "sparse_matrix.h"
#include "histogram.h"

using namespace std;

string FirstNames[10] { "Liam", "Noah", "Oliver", "William", "Elijah", "James", "Benjamin", "Lucas", "Mason", "Ethan" };
string MiddleNames[10] {"Joseph", "Christopher", "Donald", "Paul", "Thomas", "Rayan", "David", "Jeffrey", "Justin", "Jack"};
string LastNames[10] {"Lee", "Thompson", "Harris", "White", "Sanchez", "Walker", "Allen", "Green", "Carter", "Wright"};
//

string randomFN()
{
    int i = rand() % 10;
    return FirstNames[i];
}

string randomMN()
{
    int i = rand() % 10;
    return MiddleNames[i];
}

string randomLN()
{
    int i = rand() % 10;
    return LastNames[i];
}

int randomBY()
{
    return 1920 + (rand() % 100);
}

Person EnterPerson()
{
    string fn = "";
    string mn = "";
    string ln = "";
    int by = 0;
    cout << "FIRST NAME: ";
    cin >> fn;
    cout << "MIDDLE NAME: ";
    cin >> mn;
    cout << "LAST NAME: ";
    cin >> ln;
    cout << "BIRTH YEAR: ";
    cin >> by;
    return Person(fn, mn, ln, by);
}


void interface_index()
{
    IndexDictionary<string> *ind_dict=nullptr;
    IndexDictionary<int> *ind_dict_INT=nullptr;
    ArraySequence<Person> *seq = new ArraySequence<Person>();
    int choose = 0;
    int howManyPersons = 0;
    Person newPerson;
    string (Person::*getParam)() = NULL;
    int (Person::*getParamINT)() = NULL;
    int index_INT = 0;
    string index = "";

    while(true)
    {
        cout << "1.Add random persons" << endl;
        cout << "2.Add custom person" << endl;
        cout << "3.Index data" << endl;
        cout << "4.Quit" << endl;
        cin >> choose;
        cout << endl;

        switch (choose)
        {
            case 1:
                cout << "How many persons to generate" << endl;
                cin >> howManyPersons;
                for (int i = 0; i < howManyPersons; i++)
                {
                    newPerson = Person(randomFN(), randomMN(), randomLN(), randomBY());
                    seq->Append(newPerson);
                    cout << newPerson << endl;
                }
                cout << endl;
                break;
            case 2:
                seq->Append(EnterPerson());
                break;
            case 3:
                cout << "Choose index data parametr" << endl;
                cout << "1: INDEX = FIRST NAME" << endl;
                cout << "2: INDEX = MIDDLE NAME" << endl;
                cout << "3: INDEX = LAST NAME" << endl;
                cout << "4: INDEX = BIRTH YEAR" << endl;
                cout << "5: INDEX = FULL NAME" << endl;
                cout << "6: INDEX = FIO" << endl;
                cin >> choose;
                cout << endl;
                switch(choose)
                {
                    case 1:
                        getParam = &Person::GetFirstName;
                        break;
                    case 2:
                        getParam = &Person::GetMiddleName;
                        break;
                    case 3:
                        getParam = &Person::GetLastName;
                        break;
                    case 4:
                        getParamINT = &Person::GetBirthYear;
                        break;
                    case 5:
                        getParam = &Person::GetFullName;
                        break;
                    case 6:
                        getParam = &Person::GetFIO;
                        break;
                    default:
                        getParam = &Person::GetFirstName;
                        break;
                }

                if(getParam != NULL)
                    ind_dict = new IndexDictionary<string>(*seq, getParam);
                else 
                    ind_dict_INT = new IndexDictionary<int>(*seq, getParamINT);
                cout << "Indexed data:" << endl;
                if(getParam != NULL)
                    ind_dict->print();
                else 
                    ind_dict_INT->print();

                if(getParam != NULL)
                    cout << "An amount of indexed persons: " << ind_dict->GetCount() << endl;
                else 
                    cout << "An amount of indexed persons: " << ind_dict_INT->GetCount() << endl;
            default:
                delete seq;
                delete ind_dict;
                return;
        }
    }
}

void interface_sparse_matrix()
{
    int choose = 0;
    int x = 0;
    int y = 0;
    int len = 0;
    SparseMatrix<int> *matrix = new SparseMatrix<int>(0,0);


    cout << "Input rows number" << endl;
    cin >> choose;
    matrix->SetRows(choose);
    cout << "Input columns number" << endl;
    cin >> choose;
    matrix->SetColumns(choose);
    cout << endl;
    cout << "1.Random matrix of a given size" << endl;
    cout << "2.Fill manually" << endl;
    cin >> choose;
    switch(choose)
    {
        case 1:
            cout << "Enter an amount of non-zero elements" << endl;
            cin >> len;
            cout << endl;
            if (len > matrix->GetRows() * matrix->GetColumns())
                len = matrix->GetRows() * matrix->GetColumns();
            for (int i = 0; i < len; i++)
            {
                do
                {
                    x = rand() % (matrix->GetRows());
                    y = rand() % (matrix->GetColumns());
                } while (matrix->IsNotZero(x,y));
                matrix->Set(x, y, 1 + (rand() % 9));
            }
            break;
        case 2:
            while(true)
            {
                cout << "Enter a row" << endl;
                cin >> x;
                cout << endl;
                cout << "Enter a column" << endl;
                cin >> y;
                cout << endl;
                cout << "Enter a value" << endl;
                cin >> choose;
                matrix->Set(x, y, choose);
                cout << "1.Add another element to the matrix" << endl;
                cout << "2.Finish matrix creating" << endl;
                cin >> choose;
                if (choose != 1) break;
            }
            break;
        default:
            delete matrix;
            return;
    }
    if(matrix->Get(0,0) == 0) matrix->SetToZero(0,0);
    cout << endl;
    cout << "Matrix (as dictionary):" << endl;
    matrix->print();
    cout << endl;
    return;
}

void interface_histogram()
{
    ArraySequence<Person> *seq = new ArraySequence<Person>();
    int choose = 0;
    int howManyPersons = 0;
    Person newPerson;
    int (Person::*getParam)() = NULL;
    Histogram *hist;

    while(true) {
        cout << "1.Add random persons" << endl;
        cout << "2.Add custom person" << endl;
        cout << "3.Build a histogram" << endl;
        cout << "4.Quit" << endl;
        cin >> choose;
        cout << endl;

        switch (choose) 
        {
            case 1:
                cout << "How many persons to generate" << endl;
                cin >> howManyPersons;
                for (int i = 0; i < howManyPersons; i++) {
                    newPerson = Person(randomFN(), randomMN(), randomLN(), randomBY());
                    seq->Append(newPerson);
                    cout << newPerson << endl;
                }
                cout << endl << howManyPersons << " persons have been generated" << endl << endl;
                break;
            case 2:
                seq->Append(EnterPerson());
                break;
            case 3:
                cout << "BIRTH YEAR is a parameter for the histogram" << endl;
                getParam = &Person::GetBirthYear;
                cout << "Enter an amount of subSets" << endl;
                cin >> choose;
                hist = new Histogram(*seq, getParam, choose);
                cout << "The histogram:" << endl;
                hist->print();
                break;
            default:
                return;
        }
    }
}

void interface()
{
    int choose = 0;

    while(true)
    {
        cout << "1.Data indexing" << endl;
        cout << "2.Sparse matrixes" << endl;
        cout << "3.Histogram" << endl;
        cout << "4.Tests" << endl;
        cout << "5.Quit" << endl;
        cin >> choose;
        
        switch (choose) {
            case 1:
                interface_index();
                break;
            case 2:
                interface_sparse_matrix();
                break;
            case 3:
                interface_histogram();
                break;
            case 4: 
                tests();
                break;
            default:
                return;
        }
    }
}

int main()
{
    srand(time(0));
    interface();
	return 0;
}