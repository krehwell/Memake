#include "Vector2d.h"
#include <cmath>

Vector2::Vector2( float x_in,float y_in )
	:
	x( x_in ),
	y( y_in )
{
}

Vector2 Vector2::operator+( const Vector2& rhs ) const
{
	return Vector2( x + rhs.x,y + rhs.y );
}

Vector2& Vector2::operator+=( const Vector2& rhs )
{
	return *this = *this + rhs;
}

Vector2 Vector2::operator*( float rhs ) const
{
	return Vector2( x * rhs,y * rhs );
}

Vector2& Vector2::operator*=( float rhs )
{
	return *this = *this * rhs;
}

Vector2 Vector2::operator-( const Vector2& rhs ) const
{
	return Vector2( x - rhs.x,y - rhs.y );
}

Vector2& Vector2::operator-=( const Vector2& rhs )
{
	return *this = *this - rhs;
}

float Vector2::GetLength() const
{
	return std::sqrt( GetLengthSq() );
}

float Vector2::GetLengthSq() const
{
	return x * x + y * y;
}

Vector2& Vector2::Normalize()
{
	return *this = GetNormalized();
}

Vector2 Vector2::GetNormalized() const
{
	const float len = GetLength();
	if( len != 0.0f )
	{
		return *this * (1.0f / len);
	}
	return *this;
}

