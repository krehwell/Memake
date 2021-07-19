#pragma once

class Vector2
{
public:
    Vector2() = default;
    Vector2(float x_in, float y_in);
    Vector2 operator+(const Vector2 &rhs) const;
    Vector2 &operator+=(const Vector2 &rhs);
    Vector2 operator*(float rhs) const;
    Vector2 &operator*=(float rhs);
    Vector2 operator-(const Vector2 &rhs) const;
    Vector2 &operator-=(const Vector2 &rhs);
    float getLength() const;
    float getLengthSq() const;
    Vector2 &normalize();
    Vector2 getNormalized() const;

public:
    float x;
    float y;
};
