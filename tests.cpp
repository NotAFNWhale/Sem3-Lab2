
#include "sortFunctions.h"
#include <iostream>
#include "dictionary.h"
#include "index.h"
#include "matrix.h"
#include "sparse_matrix.h"
#include "histogram.h"

using namespace std;

void testDynamicArray(){
	int initArr1[] = {1,2,3,4,5};
	int initArr2[] = {0,2,3,4,5,6};
	int initArr3[] = {0,2,3,4};

	DynamicArray<int> arr1(initArr1, 5);

	assert(arr1 == DynamicArray<int>(arr1));
	assert(arr1 == DynamicArray<int>(arr1, 5));
	assert(DynamicArray<int>() == DynamicArray<int>((int*)0, 0));
	assert(arr1.get(0) == 1);
	assert(arr1.get(3) == 4);
	assert(arr1.get(4) == 5);
	assert(arr1.getSize() == 5);

	arr1.resize(6);
	arr1.set(0, 0);
	arr1.set(6, 5);
		assert(arr1 == DynamicArray<int>(initArr2, 6));
	arr1.resize(4);
		assert(arr1 == DynamicArray<int>(initArr3, 4));
}

void testLinkedList(){
	int initArr1[] = {1,2,3,5};
	int initArr2[] = {-1,0,1,2,3,4,5,6,7};
	int initArr3[] = {-1};
	int initArr35[] = {-2,0,1,2,3,4,5,0,8};
	int initArr4[] = {0,1,2,3,5,0};
	int initArr5[] = {0,1,2,3,5,0,-1};
	int initArr6[] = {0,1,2,3,5,0,1,2,3,5};

	LinkedList<int> list1(initArr1, 4);	

	assert(list1 == LinkedList<int>(list1));
	assert(LinkedList<int>() == LinkedList<int>((int*)0, 0));
	assert(list1.get(0) == 1);
	assert(list1.getFirst() == 1);
	assert(list1.get(2) == 3);
	assert(list1.get(3) == 5);
	assert(list1.getLast() == 5);
	assert(list1.getSize() == 4);

	list1.prepend(0);
	list1.append(6);
	list1.insertAt(-1,0);
	list1.insertAt(7,7);
	list1.insertAt(4,5);
		assert(list1 == LinkedList<int>(initArr2,9));

	LinkedList<int> *list2 = list1.getSublist(0,0);
	LinkedList<int> *list3 = list1.getSublist(0,1);
	LinkedList<int> *list4 = list1.getSublist(0,9);
		assert(*list2 == LinkedList<int>());
		assert(*list3 == LinkedList<int>(initArr3,1));
		assert(*list4 == list1);

	list1.set(-2,0);
	list1.set(8,8);
	list1.set(0,7);
		assert(list1 == LinkedList<int>(initArr35,9));

	list1.removeAt(0);
	list1.removeAt(7);
	list1.removeAt(4);
		assert(list1 == LinkedList<int>(initArr4,6));

	LinkedList<int> *list5 = list1.concat(LinkedList<int>());
	LinkedList<int> *list6 = list1.concat(LinkedList<int>(initArr3, 1));
	LinkedList<int> *list7 = list1.concat(LinkedList<int>(initArr1, 4));
		assert(*list5 == list1);
		assert(*list6 == LinkedList<int>(initArr5,7));
		assert(*list7 == LinkedList<int>(initArr6,10));

	delete list2;
	delete list3;
	delete list4;
	delete list5;
	delete list6;
	delete list7;
}

void testArraySequence(){
	int initArr1[] = {1,2,3,5};
	int initArr2[] = {-1,0,1,2,3,4,5,6,7};
	int initArr3[] = {-1};
	int initArr35[] = {-2,0,1,2,3,4,5,0,8};
	int initArr4[] = {0,1,2,3,5,6};
	int initArr5[] = {-2,0,1,2,3,4,5,0,8,-1};
	int initArr6[] = {-2,0,1,2,3,4,5,0,8,1,2,3,5};

	ArraySequence<int> seq1(initArr1, 4);	

	assert(seq1 == ArraySequence<int>(seq1));
	assert(ArraySequence<int>() == ArraySequence<int>((int*)0, 0));
	assert(seq1.get(0) == 1);
	assert(seq1.getFirst() == 1);
	assert(seq1.get(2) == 3);
	assert(seq1.get(3) == 5);
	assert(seq1.getLast() == 5);
	assert(seq1.getSize() == 4);

	seq1.prepend(0);
	seq1.append(6);
	seq1.insertAt(-1,0);
	seq1.insertAt(7,7);
	seq1.insertAt(4,5);
		assert(seq1 == ArraySequence<int>(initArr2,9));
		
	ArraySequence<int> *seq2 = seq1.getSubsequence(0,0);
	ArraySequence<int> *seq3 = seq1.getSubsequence(0,1);
	ArraySequence<int> *seq4 = seq1.getSubsequence(0,9);
		assert(*seq2 == ArraySequence<int>());
		assert(*seq3 == ArraySequence<int>(initArr3,1));
		assert(*seq4 == seq1);

	seq1.set(-2,0);
	seq1.set(8,8);
	seq1.set(0,7);
		assert(seq1 == ArraySequence<int>(initArr35,9));

	ArraySequence<int> *seq5 = seq1.concat(ArraySequence<int>());
	ArraySequence<int> *seq6 = seq1.concat(ArraySequence<int>(initArr3, 1));
	ArraySequence<int> *seq7 = seq1.concat(ArraySequence<int>(initArr1, 4));
		assert(*seq5 == seq1);
		assert(*seq6 == ArraySequence<int>(initArr5,10));
		assert(*seq7 == ArraySequence<int>(initArr6,13));

	delete seq2;
	delete seq3;
	delete seq4;
	delete seq5;
	delete seq6;
	delete seq7;
}

void testListSequence(){
	int initArr1[] = {1,2,3,5};
	int initArr2[] = {-1,0,1,2,3,4,5,6,7};
	int initArr3[] = {-1};
	int initArr35[] = {-2,0,1,2,3,4,5,0,8};
	int initArr4[] = {0,1,2,3,5,6};
	int initArr5[] = {-2,0,1,2,3,4,5,0,8,-1};
	int initArr6[] = {-2,0,1,2,3,4,5,0,8,1,2,3,5};

	ListSequence<int> seq1(initArr1, 4);	

	assert(seq1 == ListSequence<int>(seq1));
	assert(ListSequence<int>() == ListSequence<int>((int*)0, 0));
	assert(seq1.get(0) == 1);
	assert(seq1.getFirst() == 1);
	assert(seq1.get(2) == 3);
	assert(seq1.get(3) == 5);
	assert(seq1.getLast() == 5);
	assert(seq1.getSize() == 4);

	seq1.prepend(0);
	seq1.append(6);
	seq1.insertAt(-1,0);
	seq1.insertAt(7,7);
	seq1.insertAt(4,5);
		assert(seq1 == ListSequence<int>(initArr2,9));
		
	ListSequence<int> *seq2 = seq1.getSubsequence(0,0);
	ListSequence<int> *seq3 = seq1.getSubsequence(0,1);
	ListSequence<int> *seq4 = seq1.getSubsequence(0,9);
		assert(*seq2 == ListSequence<int>());
		assert(*seq3 == ListSequence<int>(initArr3,1));
		assert(*seq4 == seq1);

	seq1.set(-2,0);
	seq1.set(8,8);
	seq1.set(0,7);
		assert(seq1 == ListSequence<int>(initArr35,9));

	ListSequence<int> *seq5 = seq1.concat(ListSequence<int>());
	ListSequence<int> *seq6 = seq1.concat(ListSequence<int>(initArr3, 1));
	ListSequence<int> *seq7 = seq1.concat(ListSequence<int>(initArr1, 4));
		assert(*seq5 == seq1);
		assert(*seq6 == ListSequence<int>(initArr5,10));
		assert(*seq7 == ListSequence<int>(initArr6,13));

	delete seq2;
	delete seq3;
	delete seq4;
	delete seq5;
	delete seq6;
	delete seq7;

}

void testSortFunctions()
{
    ArraySequence<int> *arr0 = new ArraySequence<int>(0);

    bubbleSort(arr0, desc);
    assert(arr0->getSize() == 0);
    mergeSort(arr0, desc);
    assert(arr0->getSize() == 0);
    quickSort(arr0, desc);
    assert(arr0->getSize() == 0);
    delete arr0;


    ArraySequence<int> *arr1 = new ArraySequence<int>(1);
    arr1->set(3, 0);

    bubbleSort(arr0, desc);
    assert(arr1->getSize() == 1);
    assert(arr1->getFirst() == 3);
    mergeSort(arr0, desc);
    assert(arr1->getSize() == 1);
    assert(arr1->getFirst() == 3);
    quickSort(arr0, desc);
    assert(arr1->getSize() == 1);
    assert(arr1->getFirst() == 3);
    delete arr1;


    ArraySequence<int> *arr2 = new ArraySequence<int>(5);
    arr2->set(6, 0);
    arr2->set(3, 1);
    arr2->set(5, 2);
    arr2->set(7, 3);
    arr2->set(4, 4);

    bubbleSort(arr2, desc);
    assert(arr2->getSize() == 5);
    assert(arr2->get(0) == 7);
    assert(arr2->get(1) == 6);
    assert(arr2->get(2) == 5);
    assert(arr2->get(3) == 4);
    assert(arr2->get(4) == 3);

    bubbleSort(arr2, asc);
    assert(arr2->getSize() == 5);
    assert(arr2->get(0) == 3);
    assert(arr2->get(1) == 4);
    assert(arr2->get(2) == 5);
    assert(arr2->get(3) == 6);
    assert(arr2->get(4) == 7);
    delete arr2;

    arr2 = new ArraySequence<int>(5);
    arr2->set(1, 0);
    arr2->set(1, 1);
    arr2->set(1, 2);
    arr2->set(1, 3);
    arr2->set(1, 4);
    bubbleSort(arr2, asc);
    assert(arr2->getSize() == 5);
    assert(arr2->get(0) == 1);
    assert(arr2->get(1) == 1);
    assert(arr2->get(2) == 1);
    assert(arr2->get(3) == 1);
    assert(arr2->get(4) == 1);
    delete arr2;


    arr2 = new ArraySequence<int>(5);
    arr2->set(6, 0);
    arr2->set(3, 1);
    arr2->set(5, 2);
    arr2->set(7, 3);
    arr2->set(4, 4);
    mergeSort(arr2, asc);
    assert(arr2->getSize() == 5);
    assert(arr2->get(0) == 3);
    assert(arr2->get(1) == 4);
    assert(arr2->get(2) == 5);
    assert(arr2->get(3) == 6);
    assert(arr2->get(4) == 7);
    delete arr2;

    arr2 = new ArraySequence<int>(5);
    arr2->set(1, 0);
    arr2->set(1, 1);
    arr2->set(1, 2);
    arr2->set(1, 3);
    arr2->set(1, 4);
    mergeSort(arr2, asc);
    assert(arr2->getSize() == 5);
    assert(arr2->get(0) == 1);
    assert(arr2->get(1) == 1);
    assert(arr2->get(2) == 1);
    assert(arr2->get(3) == 1);
    assert(arr2->get(4) == 1);
    delete arr2;

    arr2 = new ArraySequence<int>(5);
    arr2->set(6, 0);
    arr2->set(3, 1);
    arr2->set(5, 2);
    arr2->set(7, 3);
    arr2->set(4, 4);
    quickSort(arr2, asc);
    assert(arr2->getSize() == 5);
    assert(arr2->get(0) == 3);
    assert(arr2->get(1) == 4);
    assert(arr2->get(2) == 5);
    assert(arr2->get(3) == 6);
    assert(arr2->get(4) == 7);
    delete arr2;

    arr2 = new ArraySequence<int>(5);
    arr2->set(1, 0);
    arr2->set(1, 1);
    arr2->set(1, 2);
    arr2->set(1, 3);
    arr2->set(1, 4);
    quickSort(arr2, asc);
    assert(arr2->getSize() == 5);
    assert(arr2->get(0) == 1);
    assert(arr2->get(1) == 1);
    assert(arr2->get(2) == 1);
    assert(arr2->get(3) == 1);
    assert(arr2->get(4) == 1);
    delete arr2;
}

void testDictionary()
{
    bool (*cmp)(PairKE<int, int>, PairKE<int, int>) = asc;
    Dictionary<int, int> *dict = new Dictionary<int, int>(101, 170, cmp);
    assert(dict->containsKey(101));
    assert(dict->get(101) == 170);
    assert(dict->getCount() == 1);

    dict->add(102, 101);
    dict->add(170, 101);
    dict->add(1, 1);
    assert(!dict->containsKey(2));
    assert(dict->getCount() == 4);
    assert(dict->get(102) == 101);
    assert(dict->get(1) == 1);

    dict->changeElem(1, 2);
    assert(!dict->containsKey(2));
    assert(dict->containsKey(1));
    assert(dict->getCount() == 4);
    assert(dict->get(1) == 2);

    dict->remove(1);
    assert(!dict->containsKey(1));
    assert(dict->getCount() == 3);

    delete &cmp;
    delete dict;
}

void testIndexDictionary()
{
    string (Person::*getParam)() = Person::getFirstName;
    ArraySequence<Person> *seq = new ArraySequence<Person>();
    seq->append(Person("Vadim", "Ivanov", "Ivanovich", 2001));
    seq->append(Person("Ivan", "Ivanov", "Petrovich", 2002));
    seq->append(Person("Andrey", "Petrov", "Ivanovich", 2003));

    IndexDictionary<string> *ind_dict = new IndexDictionary<string>(*seq, getParam);
    assert(ind_dict->get("Ivan").getBirthYear() == 2002);
    assert(ind_dict->getCount() == 3);
    assert(ind_dict->contains("Vadim"));

    delete ind_dict;
    delete seq;
}

void testSparseMatrix()
{
    SparseMatrix<int> *matrix = new SparseMatrix<int>(3, 4);
    matrix->setRows(9);
    matrix->setColumns(5);
    matrix->set(3, 4, 5);
    matrix->setToZero(1, 3);

    matrix->set(2, 1, 9);
    matrix->set(0,0,0);

    assert(matrix->get(1,1) == 0);
    assert(matrix->getColumns() == 5);
    assert(matrix->getRows() == 9);
    assert(matrix->getAmountOfNonZero() == 2);
    matrix->setToZero(2, 1);
    assert(matrix->getAmountOfNonZero() == 1);
    assert(!matrix->isNotZero(2, 1));
    assert(matrix->isNotZero(3,4));
    assert(matrix->get(3,4) == 5);

    delete matrix;
}

void testHistogram()
{
    ArraySequence<Person> *seq = new ArraySequence<Person>();
    seq->append(Person("Vadim", "Ivanov", "Ivanovich", 2001));
    seq->append(Person("Vadim", "Ivanov", "Ivanovich", 2004));
    seq->append(Person("Vadim", "Ivanov", "Ivanovich", 2003));
    seq->append(Person("Vadim", "Ivanov", "Ivanovich", 2014));
    seq->append(Person("Vadim", "Ivanov", "Ivanovich", 2051));
    seq->append(Person("Vadim", "Ivanov", "Ivanovich", 2099));
    seq->append(Person("Vadim", "Ivanov", "Ivanovich", 2108));
    seq->append(Person("Vadim", "Ivanov", "Ivanovich", 3008));
    seq->append(Person("Vadim", "Ivanov", "Ivanovich", 2223));
    seq->append(Person("Vadim", "Ivanov", "Ivanovich", 1678));
    seq->append(Person("Vadim", "Ivanov", "Ivanovich", 1578));
    seq->append(Person("Vadim", "Ivanov", "Ivanovich", 1890));
    seq->append(Person("Vadim", "Ivanov", "Ivanovich", 1537));
    seq->append(Person("Vadim", "Ivanov", "Ivanovich", 9999));


    int (Person::*getParam)() = Person::getBirthYear;
    Histogram *hist;

    hist = new Histogram(*seq, getParam, 4);

    assert(hist->getAmountOfSubsets() == 4);

    delete seq;
    delete &getParam;
    delete hist;
}


int main(int argc, const char *argv[]){
	testDynamicArray();
	cout << "class DynamicArray is successfully tested" << endl;
	testLinkedList();
    cout << "class LinkedList is successfully tested" << endl;
	testArraySequence();
    cout << "class ArraySequence is successfully tested" << endl;
	testListSequence();
    cout << "class ListSequence is successfully tested" << endl;
	testSortFunctions();
    cout << "Sort functions for class Sequence are successfully tested" << endl;
    testDictionary();
    cout << "class Dictionary is successfully tested" << endl;
    testIndexDictionary();
    cout << "class IndexDictionary is successfully tested" << endl;
    testSparseMatrix();
    cout << "class SparseMatrix is successfully tested" << endl;
    testHistogram();
    cout << "class Histogram is successfully tested" << endl;
	system("pause");
	return 0;
}