#ifndef _MATH_H
#define _MATH_H
#include <SFML/Graphics.hpp>

using vector2 = sf::Vector2f;
using vector2i = sf::Vector2i;
using vector2u = sf::Vector2u;

static vector2 vector2_origin(0.0f, 0.0f);

template <class _T>
constexpr inline float LengthSqr(const sf::Vector2<_T>& vec)
{
	return (vec.x * vec.x + vec.y * vec.y);
}

template <class _T>
constexpr inline float Length(const sf::Vector2<_T>& vec)
{
	return std::sqrtf(LengthSqr(vec));
}

template <class _T>
constexpr inline float DotProduct(const sf::Vector2<_T>& a, const sf::Vector2<_T>& b)
{
	return (a.x * b.x + a.y * b.y);
}

#endif // !_MATH_H
