#pragma once

#include <string>
#include "dictionary.h"
#include "sequence.h"
#include "ascend.h"
#include "person.h"

using namespace std;

template <class T>
class IndexDictionary
{
private:

    Dictionary<T, Person> *dict;
    T (Person::*getParam)();

public:
    IndexDictionary(ArraySequence<Person> seq, T (Person::*getParam)())
    {
        this->getParam = getParam;
        bool (*cmp)(PairKE<T, Person>, PairKE<T, Person>) = asc;
        dict = new Dictionary<T, Person>((seq.Get(0).*getParam)(), seq.Get(0), cmp);
        for(int i = 1; i < seq.GetSize(); i++)
            dict->Add((seq.Get(i).*getParam)(), seq.Get(i));
    }
    
    ~IndexDictionary() = default;
    
    Person Get(T index)
    {
        return this->dict->Get(index);
    }
    
    int GetCount()
    {
        return this->dict->GetCount();
    }
    

    bool Contains(T index)
    {
        return this->dict->ContainsKey(index);
    }

    void print()
    {
        this->dict->print();
    }
};