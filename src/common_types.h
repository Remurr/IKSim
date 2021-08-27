#pragma once
#include "log.h"
#include <new>

struct Vec2
{
    Vec2() : x(0), y(0) {}
    Vec2(float x, float y) : x(x), y(y) { }
    float LenSq() const { return x * x + y * y; }    

    Vec2 operator+(Vec2 p) { return p += *this; }
    Vec2 operator+=(const Vec2& p) { x += p.x; y += p.y; return *this; }
    Vec2 operator-(Vec2 p) { return p -= *this; }
    Vec2 operator-=(const Vec2& p) { x -= p.x; y -= p.y; return *this; }

    float x;
    float y;
};

template <typename I, int S, int N>
class InplaceInterfaceHolder
{
public:
    InplaceInterfaceHolder()
        : mNumElements(0)
        , mData()
    {}

    I operator[](int idx) { ASRT(idx >= 0 && idx < mNumElements); return (I)mData[idx].bytes; }

    int Len() const { return mNumElements; }
    
    template <typename T>
    T* Add() 
    { 
        ASRT(mNumElements < N); 
        ASRT(sizeof(T) <= S);
        T* el = new (mData[mNumElements].bytes)T();
        ++mNumElements; 
        return el; 
    }
    void Remove(int idx) 
    {
        ASRT(idx < mNumElements);
        if (idx < mNumElements - 1)
        {
            mData[idx] = mData[mNumElements - 1];
        }
        --mNumElements;
    }

protected:
    int mNumElements;
    struct {
        unsigned char bytes[S];
    } mData[N];
};


