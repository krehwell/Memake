#include "Vector2d.h"
#include <cmath>

Vector2::Vector2(float x_in, float y_in)
	: x(x_in),
	  y(y_in)
{
}

Vector2 Vector2::operator+(const Vector2 &rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 &Vector2::operator+=(const Vector2 &rhs)
{
	return *this = *this + rhs;
}

Vector2 Vector2::operator*(float rhs) const
{
	return Vector2(x * rhs, y * rhs);
}

Vector2 &Vector2::operator*=(float rhs)
{
	return *this = *this * rhs;
}

Vector2 Vector2::operator-(const Vector2 &rhs) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 &Vector2::operator-=(const Vector2 &rhs)
{
	return *this = *this - rhs;
}

float Vector2::getLength() const
{
	return std::sqrt(getLengthSq());
}

float Vector2::getLengthSq() const
{
	return x * x + y * y;
}

Vector2 &Vector2::normalize()
{
	return *this = getNormalized();
}

Vector2 Vector2::getNormalized() const
{
	const float len = getLength();
	if (len != 0.0f)
	{
		return *this * (1.0f / len);
	}
	return *this;
}
