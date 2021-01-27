
#include "ascend.h"
#include <iostream>
#include "dictionary.h"
#include "index.h"
#include "matrix.h"
#include "sparse_matrix.h"
#include "histogram.h"

using namespace std;

void testDynamicArray() {
    int initArr1[] = { 1,2,3,4,5 };
    int initArr2[] = { 0,2,3,4,5,6 };
    int initArr3[] = { 0,2,3,4 };

    DynamicArray<int> arr1(initArr1, 5);

    assert(arr1 == DynamicArray<int>(arr1));
    assert(arr1 == DynamicArray<int>(arr1, 5));
    assert(DynamicArray<int>() == DynamicArray<int>((int*)0, 0));
    assert(arr1.Get(0) == 1);
    assert(arr1.Get(3) == 4);
    assert(arr1.Get(4) == 5);
    assert(arr1.GetSize() == 5);

    arr1.resize(6);
    arr1.Set(0, 0);
    arr1.Set(6, 5);
    assert(arr1 == DynamicArray<int>(initArr2, 6));
    arr1.resize(4);
    assert(arr1 == DynamicArray<int>(initArr3, 4));
}

void testLinkedList() {
    int initArr1[] = { 1,2,3,5 };
    int initArr2[] = { -1,0,1,2,3,4,5,6,7 };
    int initArr3[] = { -1 };
    int initArr35[] = { -2,0,1,2,3,4,5,0,8 };
    int initArr4[] = { 0,1,2,3,5,0 };
    int initArr5[] = { 0,1,2,3,5,0,-1 };
    int initArr6[] = { 0,1,2,3,5,0,1,2,3,5 };

    LinkedList<int> list1(initArr1, 4);

    assert(list1 == LinkedList<int>(list1));
    assert(LinkedList<int>() == LinkedList<int>((int*)0, 0));
    assert(list1.Get(0) == 1);
    assert(list1.GetFirst() == 1);
    assert(list1.Get(2) == 3);
    assert(list1.Get(3) == 5);
    assert(list1.GetLast() == 5);
    assert(list1.GetSize() == 4);

    list1.Prepend(0);
    list1.Append(6);
    list1.insertAt(-1, 0);
    list1.insertAt(7, 7);
    list1.insertAt(4, 5);
    assert(list1 == LinkedList<int>(initArr2, 9));

    LinkedList<int>* list2 = list1.GetSublist(0, 0);
    LinkedList<int>* list3 = list1.GetSublist(0, 1);
    LinkedList<int>* list4 = list1.GetSublist(0, 9);
    assert(*list2 == LinkedList<int>());
    assert(*list3 == LinkedList<int>(initArr3, 1));
    assert(*list4 == list1);

    list1.Set(-2, 0);
    list1.Set(8, 8);
    list1.Set(0, 7);
    assert(list1 == LinkedList<int>(initArr35, 9));

    delete list2;
    delete list3;
    delete list4;
}

void testArraySequence() {
    int initArr1[] = { 1,2,3,5 };
    int initArr2[] = { -1,0,1,2,3,4,5,6,7 };
    int initArr3[] = { -1 };
    int initArr35[] = { -2,0,1,2,3,4,5,0,8 };
    int initArr4[] = { 0,1,2,3,5,6 };
    int initArr5[] = { -2,0,1,2,3,4,5,0,8,-1 };
    int initArr6[] = { -2,0,1,2,3,4,5,0,8,1,2,3,5 };

    ArraySequence<int> seq1(initArr1, 4);

    assert(seq1 == ArraySequence<int>(seq1));
    assert(ArraySequence<int>() == ArraySequence<int>((int*)0, 0));
    assert(seq1.Get(0) == 1);
    assert(seq1.GetFirst() == 1);
    assert(seq1.Get(2) == 3);
    assert(seq1.Get(3) == 5);
    assert(seq1.GetLast() == 5);
    assert(seq1.GetSize() == 4);

    seq1.Prepend(0);
    seq1.Append(6);
    seq1.insertAt(-1, 0);
    seq1.insertAt(7, 7);
    seq1.insertAt(4, 5);
    assert(seq1 == ArraySequence<int>(initArr2, 9));

    ArraySequence<int>* seq2 = seq1.GetSubsequence(0, 0);
    ArraySequence<int>* seq3 = seq1.GetSubsequence(0, 1);
    ArraySequence<int>* seq4 = seq1.GetSubsequence(0, 9);
    assert(*seq2 == ArraySequence<int>());
    assert(*seq3 == ArraySequence<int>(initArr3, 1));
    assert(*seq4 == seq1);

    seq1.Set(-2, 0);
    seq1.Set(8, 8);
    seq1.Set(0, 7);
    assert(seq1 == ArraySequence<int>(initArr35, 9));

    ArraySequence<int>* seq5 = seq1.concat(ArraySequence<int>());
    ArraySequence<int>* seq6 = seq1.concat(ArraySequence<int>(initArr3, 1));
    ArraySequence<int>* seq7 = seq1.concat(ArraySequence<int>(initArr1, 4));
    assert(*seq5 == seq1);
    assert(*seq6 == ArraySequence<int>(initArr5, 10));
    assert(*seq7 == ArraySequence<int>(initArr6, 13));

    delete seq2;
    delete seq3;
    delete seq4;
    delete seq5;
    delete seq6;
    delete seq7;
}

void testListSequence() {
    int initArr1[] = { 1,2,3,5 };
    int initArr2[] = { -1,0,1,2,3,4,5,6,7 };
    int initArr3[] = { -1 };
    int initArr35[] = { -2,0,1,2,3,4,5,0,8 };
    int initArr4[] = { 0,1,2,3,5,6 };
    int initArr5[] = { -2,0,1,2,3,4,5,0,8,-1 };
    int initArr6[] = { -2,0,1,2,3,4,5,0,8,1,2,3,5 };

    ListSequence<int> seq1(initArr1, 4);

    assert(seq1 == ListSequence<int>(seq1));
    assert(ListSequence<int>() == ListSequence<int>((int*)0, 0));
    assert(seq1.Get(0) == 1);
    assert(seq1.GetFirst() == 1);
    assert(seq1.Get(2) == 3);
    assert(seq1.Get(3) == 5);
    assert(seq1.GetLast() == 5);
    assert(seq1.GetSize() == 4);

    seq1.Prepend(0);
    seq1.Append(6);
    seq1.insertAt(-1, 0);
    seq1.insertAt(7, 7);
    seq1.insertAt(4, 5);
    assert(seq1 == ListSequence<int>(initArr2, 9));

    ListSequence<int>* seq2 = seq1.GetSubsequence(0, 0);
    ListSequence<int>* seq3 = seq1.GetSubsequence(0, 1);
    ListSequence<int>* seq4 = seq1.GetSubsequence(0, 9);
    assert(*seq2 == ListSequence<int>());
    assert(*seq3 == ListSequence<int>(initArr3, 1));
    assert(*seq4 == seq1);

    seq1.Set(-2, 0);
    seq1.Set(8, 8);
    seq1.Set(0, 7);
    assert(seq1 == ListSequence<int>(initArr35, 9));

    ListSequence<int>* seq5 = seq1.concat(ListSequence<int>());
    ListSequence<int>* seq6 = seq1.concat(ListSequence<int>(initArr3, 1));
    ListSequence<int>* seq7 = seq1.concat(ListSequence<int>(initArr1, 4));
    assert(*seq5 == seq1);
    assert(*seq6 == ListSequence<int>(initArr5, 10));
    assert(*seq7 == ListSequence<int>(initArr6, 13));

    delete seq2;
    delete seq3;
    delete seq4;
    delete seq5;
    delete seq6;
    delete seq7;

}

void testDictionary()
{
    bool (*cmp)(PairKE<int, int>, PairKE<int, int>) = asc;
    Dictionary<int, int>* dict = new Dictionary<int, int>(101, 170, cmp);
    assert(dict->ContainsKey(101));
    assert(dict->Get(101) == 170);
    assert(dict->GetCount() == 1);

    dict->Add(102, 101);
    dict->Add(170, 101);
    dict->Add(1, 1);
    assert(!dict->ContainsKey(2));
    assert(dict->GetCount() == 4);
    assert(dict->Get(102) == 101);
    assert(dict->Get(1) == 1);

    dict->ChangeElem(1, 2);
    assert(!dict->ContainsKey(2));
    assert(dict->ContainsKey(1));
    assert(dict->GetCount() == 4);
    assert(dict->Get(1) == 2);

    dict->Remove(1);
    assert(!dict->ContainsKey(1));
    assert(dict->GetCount() == 3);

    delete& cmp;
    delete dict;
}

void testIndexDictionary()
{
    string(Person:: * GetParam)() = &Person::GetFirstName;
    ArraySequence<Person>* seq = new ArraySequence<Person>();
    seq->Append(Person("Vadim", "Ivanov", "Ivanovich", 2001));
    seq->Append(Person("Ivan", "Ivanov", "Petrovich", 2002));
    seq->Append(Person("Andrey", "Petrov", "Ivanovich", 2003));

    IndexDictionary<string>* ind_dict = new IndexDictionary<string>(*seq, GetParam);
    assert(ind_dict->Get("Ivan").GetBirthYear() == 2002);
    assert(ind_dict->GetCount() == 3);
    assert(ind_dict->Contains("Vadim"));

    delete ind_dict;
    delete seq;
}

void testSparseMatrix()
{
    SparseMatrix<int>* matrix = new SparseMatrix<int>(3, 4);
    matrix->SetRows(9);
    matrix->SetColumns(5);
    matrix->Set(3, 4, 5);
    matrix->SetToZero(1, 3);

    matrix->Set(2, 1, 9);
    matrix->Set(0, 0, 0);

    assert(matrix->Get(1, 1) == 0);
    assert(matrix->GetColumns() == 5);
    assert(matrix->GetRows() == 9);
    assert(matrix->GetAmountOfNonZero() == 2);
    matrix->SetToZero(2, 1);
    assert(matrix->GetAmountOfNonZero() == 1);
    assert(!matrix->IsNotZero(2, 1));
    assert(matrix->IsNotZero(3, 4));
    assert(matrix->Get(3, 4) == 5);

    delete matrix;
}

void testHistogram()
{
    ArraySequence<Person>* seq = new ArraySequence<Person>();
    seq->Append(Person("Vadim", "Ivanov", "Ivanovich", 2001));
    seq->Append(Person("Vadim", "Ivanov", "Ivanovich", 2004));
    seq->Append(Person("Vadim", "Ivanov", "Ivanovich", 2003));
    seq->Append(Person("Vadim", "Ivanov", "Ivanovich", 2014));
    seq->Append(Person("Vadim", "Ivanov", "Ivanovich", 2051));
    seq->Append(Person("Vadim", "Ivanov", "Ivanovich", 2099));
    seq->Append(Person("Vadim", "Ivanov", "Ivanovich", 2108));
    seq->Append(Person("Vadim", "Ivanov", "Ivanovich", 3008));
    seq->Append(Person("Vadim", "Ivanov", "Ivanovich", 2223));
    seq->Append(Person("Vadim", "Ivanov", "Ivanovich", 1678));
    seq->Append(Person("Vadim", "Ivanov", "Ivanovich", 1578));
    seq->Append(Person("Vadim", "Ivanov", "Ivanovich", 1890));
    seq->Append(Person("Vadim", "Ivanov", "Ivanovich", 1537));
    seq->Append(Person("Vadim", "Ivanov", "Ivanovich", 9999));


    int (Person:: * GetParam)() = &Person::GetBirthYear;
    Histogram* hist;

    hist = new Histogram(*seq, GetParam, 4);

    assert(hist->GetAmountOfSubSets() == 4);

    delete seq;
    delete hist;
}


void tests() {
    testDynamicArray();
    cout << "class DynamicArray is successfully tested" << endl;
    testLinkedList();
    cout << "class LinkedList is successfully tested" << endl;
    testArraySequence();
    cout << "class ArraySequence is successfully tested" << endl;
    testListSequence();
    cout << "class ListSequence is successfully tested" << endl;
    //testDictionary();
    cout << "class Dictionary is successfully tested" << endl;
    //testIndexDictionary();
    cout << "class IndexDictionary is successfully tested" << endl;
    //testSparseMatrix();
    cout << "class SparseMatrix is successfully tested" << endl;
    //testHistogram();
    cout << "class Histogram is successfully tested" << endl;
    system("pause");
}