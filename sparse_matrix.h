#pragma once
#include "dictionary.h"
#include "matrix.h"
#include "ascend.h"
#include <string>


template<class T1, class T2>
class Pair
{
private:
    T1 elem1;
    T2 elem2;
public:
    Pair() = default;
    
    Pair(T1 elem1, T2 elem2)
    {
        this->elem1 = elem1;
        this->elem2 = elem2;
    }
    
    ~Pair() = default;
    
    T1 GetFirst() const
    {
        return this->elem1;
    }
    
    T2 GetSecond() const
    {
        return this->elem2;
    }
    
    void SetFirst(T1 elem1)
    {
        this->elem1 = elem1;
    }
    
    void SetSecond(T2 elem2)
    {
        this->elem2 = elem2;
    }
    
    bool operator<(const Pair another)
    {
        if (this->elem1 != another.elem1)
            return this->elem1 < another.elem1;
        else return this->elem2 < another.elem2;
    }
    
    bool operator>(const Pair another)
    {
        if (this->elem1 != another.elem1)
            return this->elem1 > another.elem1;
        else return this->elem2 > another.elem2;
    }
    
    bool operator<=(const Pair another)
    {
        if (this->elem1 == another.elem1)
            return this->elem2 <= another.elem2;
        else return this->elem1 <= another.elem1;
    }
    
    bool operator>=(const Pair another)
    {
        if (this->elem1 == another.elem1)
            return this->elem2 >= another.elem2;
        return this->elem1 >= another.elem1;
    }
    
    bool operator!=(const Pair another)
    {
        if (this->elem1 != another.elem1)
            return this->elem2 != another.elem2;
        else return false;
    }
    
    bool operator==(const Pair another)
    {
        if (this->elem1 == another.elem1)
            return this->elem2 == another.elem2;
        else return false;
    }
};

template <class T1, class T2>
std::ostream& operator<< (std::ostream &out, const Pair<T1, T2> pair)
{
    return out << "(" << pair.GetFirst() << "; " << pair.GetSecond() << ")";
}

template <class T>
class SparseMatrix
{
private:
    Dictionary<Pair<int, int>, T> *dict;
    int rows = 0;
    int columns = 0;
public:
    SparseMatrix(int rows, int columns)
    {
        this->rows = rows;
        this->columns = columns;
        this->dict = new Dictionary<Pair<int, int>, T>(Pair<int,int>(0,0), (T)0, asc);
    }
    
    ~SparseMatrix() = default;
    
    void Set(int x, int y, T value)
    {
        this->Set(Pair<int, int>(x,y), value);
    }
    
    void Set(Pair<int, int> pair, T value)
    {
        if (pair.GetFirst() >= this->rows or pair.GetSecond() >= this->columns)
            throw std::out_of_range("OUT OF RANGE");
        if (value != (T)0)
            this->dict->Add(pair, value);
        else this->SetToZero(pair);
    }
    
    void SetToZero(int x, int y)
    {
        this->SetToZero(Pair<int, int>(x,y));
    }
    
    void SetToZero(Pair<int, int> pair)
    {
        if (pair.GetFirst() >= this->rows or pair.GetSecond() >= this->columns)
            throw std::out_of_range("OUT OF RANGE");
        if (this->IsNotZero(pair)) this->dict->Remove(pair);
    }
    
    bool IsNotZero(int x, int y)
    {
        return this->IsNotZero(Pair<int,int>(x,y));
    }
    
    bool IsNotZero(Pair<int, int> pair)
    {
        return this->dict->ContainsKey(pair);
    }
    
    T Get(int x, int y)
    {
        return this->Get(Pair<int,int>(x,y));
    }
    
    T Get (Pair<int,int> pair)
    {
        if (pair.GetFirst() >= this->rows or pair.GetSecond() >= this->columns)
            throw std::out_of_range("OUT OF RANGE");
        if (this->IsNotZero(pair))
            return this->dict->Get(pair);
        else 
            return (T)0;
    }
    
    int GetAmountOfNonZero()
    {
        return dict->GetCount();
    }
    
    int GetRows()
    {
        return this->rows;
    }
    
    int GetColumns()
    {
        return this->columns;
    }

    Dictionary<Pair<int, int>, T> GetDict()
    {
        return this->dict;
    }
    
    void SetRows(int a)
    {
        this->rows = a;
    }
    
    void SetColumns(int a)
    {
        this->columns = a;
    }

    void print()
    {
        this->dict->print();
    }
    
    void printAsMatrix()
    {
        for (int i = 0; i < this->rows; i++)
        {
            for (int j = 0; j < this->columns; j++)
            {
                cout << this->Get(i,j) << " ";
            }
            cout << endl;
        }
    }
};
