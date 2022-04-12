#pragma once

template <class T>
class Singleton
{
public:
    static void CreateInst() 
    {
        if (s_Inst == nullptr)
        {
            s_Inst = new T();
        }
    }
    static T* Inst() { return s_Inst; }

private:
    static T* s_Inst = nullptr;
};

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

enum class BattleSide
{
    None,
    SideA,
    SideB,
};

enum class BattleResult
{
    None,
    Victory,
    Defeat,
    Draw,    
};
