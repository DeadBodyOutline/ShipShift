#ifndef __STUFFMATH_H__
#define __STUFFMATH_H__

#include <SFML/System.hpp>

#define PI 3.14159265359f

float stuffSqrt(const float number);
float stuffDistance(const float x, const float y);
float stuffDistanceF(const float x1, const float y1, const float x2, const float y2);
int stuffCompareDistance(const float x1, const float y1, const float x2, const float y2);
sf::Vector2f truncate(sf::Vector2f vec, float max);
float d2r(float degrees);
float r2d(float rad);

#endif // __STUFFMATH_H__
