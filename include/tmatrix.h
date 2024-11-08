// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
    size_t sz;
    T* pMem;
public:
    TDynamicVector(size_t size = 1) : sz(size)
    {
        if (sz <= 0 || sz > MAX_VECTOR_SIZE)
            throw out_of_range("Vector size is wrong");
        pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
    }
    TDynamicVector(T* arr, size_t s) : sz(s)
    {
        //assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
        pMem = new T[sz];
        std::copy(arr, arr + sz, pMem);
    }
    TDynamicVector(const TDynamicVector& v)
    {
        pMem = new T[v.sz];
        sz = v.sz;
        for (int i = 0; i < v.sz; ++i) {
            pMem[i] = v.pMem[i];
        }
    }
    TDynamicVector(TDynamicVector&& v) noexcept
    {
        this->pMem = v.pMem;
        v.pMem = nullptr;
        this->sz = v.sz;
        v.sz = 0;
    }
    ~TDynamicVector()
    {
        delete[] pMem;
    }

    TDynamicVector&& move(TDynamicVector&& v) {
        return static_cast<TDynamicVector&&>(v);
    }

    TDynamicVector& operator=(const TDynamicVector& v)
    {
        if ((*this) == v) return *this;
        delete[] pMem;
        pMem = new T[v.sz];
        this->sz = v.sz;
        for (int i = 0; i < v.sz; ++i) {
            pMem[i] = v.pMem[i];
        }
        return *this;
    }
    TDynamicVector& operator=(TDynamicVector&& v) noexcept
    {
        if ((*this) == v) return *this;
        this->pMem = v.pMem;
        v.pMem = nullptr;
        sz = v.sz;
        v.sz = 0;
        return *this;
    }

    size_t size() const noexcept { return sz; }

    // индексация
    T& operator[](size_t ind)
    {
        if (ind < 0 || ind > this->size()) throw "bad index";
        return pMem[ind];
    }
    const T& operator[](size_t ind) const
    {
        if (ind < 0 || ind > this->size()) throw "bad index";
        return pMem[ind];

    }
    // индексация с контролем
    T& at(size_t ind)
    {

    }
    const T& at(size_t ind) const
    {
    }

    // сравнение
    bool operator==(const TDynamicVector& v) const noexcept
    {
        bool chek = 1;
        if (this->size() != v.size()) return 0;
        for (int i = 0; i < this->size(); ++i) {
            if ((pMem[i]) != v.pMem[i]) chek = 0;
        }
        return chek;
    }
    bool operator!=(const TDynamicVector& v) const noexcept
    {
        return !(*this == v);
    }

    // скалярные операции
    TDynamicVector operator+(T val)
    {
        TDynamicVector res(*this);
        for (int i = 0; i < this->size(); ++i) {
            res.pMem[i] = pMem[i] + val;
        };
        return res;

    }
    TDynamicVector operator-(double val)
    {
        TDynamicVector res(*this);
        for (int i = 0; i < this->size(); ++i) {
            res.pMem[i] = pMem[i] - val;
        };
        return res;
    }
    TDynamicVector operator*(double val)
    {
        TDynamicVector res(*this);
        for (int i = 0; i < this->size(); ++i) {
            res.pMem[i] = pMem[i] * val;
        };
        return res;
    }

    // векторные операции
    TDynamicVector operator+(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "bad values";
        TDynamicVector res(*this);
        for (int i = 0; i < this->size(); ++i) {
            res.pMem[i] = pMem[i] + v.pMem[i];
        }
        return res;
    }
    TDynamicVector operator-(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "bad values";
        TDynamicVector res(*this);
        for (int i = 0; i < this->size(); ++i) {
            res.pMem[i] = pMem[i] - v.pMem[i];
        }
        return res;

    }

    // delete noexcept(noexcept(T()))
    T operator*(const TDynamicVector& v)
    {
        if (sz != v.sz) throw "bad values";
        T res = 0;
        for (int i = 0; i < this->size(); ++i) {
            res = res + (pMem[i] * v.pMem[i]);
        }
        return res;

    }

    friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
    {
        std::swap(lhs.sz, rhs.sz);
        std::swap(lhs.pMem, rhs.pMem);
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicVector& v)
    {
        for (size_t i = 0; i < v.sise(); i++)
            istr >> v.pMem[i]; // требуется оператор>> для типа T
        return istr;
    }
    friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
    {
        for (size_t i = 0; i < v.size(); i++)
            ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
        return ostr;
    }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : public TDynamicVector<TDynamicVector<T>>
{
    using TDynamicVector<TDynamicVector<T>>::pMem;
    using TDynamicVector<TDynamicVector<T>>::sz;
public:
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s) {
        if (s < 0 || s > MAX_MATRIX_SIZE) throw "all is bad";
        for (size_t i = 0; i < s; ++i) {
            pMem[i] = TDynamicVector<T>(sz);
        }
    }


    using TDynamicVector<TDynamicVector<T>>::operator[];



    // сравнение
    bool operator==(const TDynamicMatrix& m) const noexcept
    {

        bool chek = 1;
        for (int i = 0; i < this->size(); ++i) {
            if ((*this)[i] != m[i]) {
                chek = 0;
                break;
            }
            else chek = 1;

        }
        return chek;
    }

    // матрично-скалярные операции
    TDynamicVector<T> operator*(const T& val)
    {
        TDynamicMatrix<T> res(this->size());
        for (int i = 0; i < this->size(); i++) {
            res[i] = (*this)[i] * val;

        }
        return res;
    }

    // матрично-векторные операции
    TDynamicVector<T> operator*(const TDynamicVector<T>& v)
    {
        if (v.size() != this->size()) throw "bad value";
        TDynamicVector res(v.size());
        T val = 0;
        for (int i = 0; i < this->size(); ++i) {
            for (int j = i; j < this->size(); j++) {
                val += (*this)[i][j] * v[i];

            }
            res[i] = val;
            val = 0;

        }
        return res;

    }

    // матрично-матричные операции
    TDynamicMatrix operator+(const TDynamicMatrix& m)
    {
        if (this->size() != m.size()) throw "different sizes";
        TDynamicMatrix res(m.size());
        for (int i = 0; i < this->size(); ++i) {
            res[i] = (*this)[i] + m[i];
        }
        return res;
    }
    TDynamicMatrix operator-(const TDynamicMatrix& m)
    {
        if (this->size() != m.size()) throw "different sizes";
        TDynamicMatrix res(m.size());
        for (int i = 0; i < this->size(); ++i) {
            res[i] = (*this)[i] - m[i];
        }
        return res;
    }
    TDynamicMatrix operator*(const TDynamicMatrix& m)
    {
        TDynamicMatrix res(this->size());
        T val = 0;
        if (this->size() != m.size()) throw "different sizes";
        for (int i = 0; i < this->size(); ++i) {
            for (int j = 0; j < m[0].size(); ++j) {
                for (int k = 0; k < this->size(); ++k) {
                    val = (*this)[i][k] * m[k][j];
                    res[i][j] += val;

                }
            }
        }
        return res;
    }

    // ввод/вывод
    friend istream& operator>>(istream& istr, TDynamicMatrix& v)
    {
        for (int i = 0; i < v.size(); ++i) {
            istr >> v[i];
        }
        return istr;

    }
    friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
    {
        for (int i = 0; i < v.size(); ++i) {
            ostr << v[i] << ' ';

        }
        return ostr;
    }
};


#endif
