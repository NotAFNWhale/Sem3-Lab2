#pragma once

#include "binary_tree.h"

#define NO_ELEMENT "NO ELEMENT WITH GIVEN KEY"

template<class TKey, class TElement>
class PairKE
{
private:
    TKey key;
    TElement element;
public:
    PairKE() = default;

    PairKE(TKey key, TElement element)
    {
        this->key = key;
        this->element = element;
    }

    ~PairKE() = default;
    
    TElement GetElem() const
    {
        return this->element;
    }
    
    TKey GetKey() const
    {
        return this->key;
    }
    
    void SetKey(TKey key)
    {
        this->key = key;
    }
    
    void SetElem(TElement elem)
    {
        this->element = elem;
    }
    
    bool operator<(const PairKE another)
    {
        return this->key < another.key;
    }
    
    bool operator>(const PairKE another)
    {
        return this->key > another.key;
    }
    
    bool operator<=(const PairKE another)
    {
        return this->key <= another.key;
    }
    
    bool operator>=(const PairKE another)
    {
        return this->key >= another.key;
    }
    
    bool operator!=(const PairKE another)
    {
        return this->key != another.key;
    }
    
    bool operator==(const PairKE another)
    {
        return this->key == another.key;
    }
};

template <class TKey, class TElement>
std::ostream& operator<< (std::ostream &out, const PairKE<TKey, TElement> pair)
{
    return out << "<" << pair.GetKey() << ", " << pair.GetElem() << ">";
}

template <class TKey, class TElement>
class Dictionary
{
protected:

    BinaryTree<PairKE<TKey,  TElement>>* dict;

public:
    Dictionary(const TKey key, const TElement elem, bool (*cmp)(PairKE<TKey, TElement>, PairKE<TKey, TElement>))
    {
        PairKE<TKey, TElement> spair = PairKE<TKey, TElement>(key, elem);
        this->dict = new BinaryTree<PairKE<TKey, TElement>>(spair, cmp);
    }
    
    ~Dictionary() = default;
    
    int GetCount()
    {
        return this->dict->GetSize();
    }
    
    TElement Get(TKey key)
    {
        PairKE<TKey, TElement> spair = PairKE<TKey, TElement>();
        spair.SetKey(key);
        if(this->dict->Exist(spair))
            return this->dict->GetElem(dict->Search(spair)).GetElem();
        throw std::out_of_range(NO_ELEMENT);
    }

    bool ContainsKey(TKey key)
    {
        PairKE<TKey, TElement> spair = PairKE<TKey, TElement>();
        spair.SetKey(key);
        return this->dict->Exist(spair);
    }
    
    void Add(TKey key, TElement element)
    {
        PairKE<TKey, TElement> spair = PairKE<TKey, TElement>(key, element);
        if(this->dict->Exist(spair))
        {
            return;
        }
        this->dict->Add(spair);
    }
    
    void Remove(TKey key)
    {
        PairKE<TKey, TElement> spair = PairKE<TKey, TElement>();
        spair.SetKey(key);
        if(this->dict->Exist(spair))
        {
            this->dict->Erase(spair);
            return;
        }
        throw std::out_of_range(NO_ELEMENT);
    }
    
    void print()
    {
        this->dict->printAll();
    }
    
    void ChangeElem(TKey key, TElement elem)
    {
        PairKE<TKey, TElement> pair = PairKE<TKey, TElement>(key, elem);
        this->dict->SetElem(this->dict->Search(pair), pair);
    }
};