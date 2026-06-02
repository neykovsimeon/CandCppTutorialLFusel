#pragma once

#include "PreCacherContainer.hpp"

#include <iostream>
#include <cstdint>

namespace SimpleCppApp
{
	struct SimpleCppAppVector
	{
		float x = 0.f, y = 0.f;

		SimpleCppAppVector operator+(const SimpleCppAppVector& rhs) const
		{
			return SimpleCppAppVector{ (x + rhs.x), (y + rhs.y) };
		}
		SimpleCppAppVector operator-(const SimpleCppAppVector& rhs) const
		{
			return SimpleCppAppVector{ (x - rhs.x), (y - rhs.y) };
		}
		SimpleCppAppVector operator*(const SimpleCppAppVector& rhs) const
		{
			return SimpleCppAppVector{ (x * rhs.x), (y * rhs.y) };
		}
	};
	//inline int32_t f(int32_t x)
	//{
	//		return x * x + 5 * x + 5;
	//}
	inline SimpleCppAppVector f(int32_t x)
	{
		return SimpleCppAppVector{ (float)x,(float)x } * SimpleCppAppVector{1.0f, 2.0f};
	}
	int SaveMain();
}

inline std::ostream& operator<<(std::ostream& os, const SimpleCppApp::SimpleCppAppVector& vec)
{
	os << "(" << vec.x << ", " << vec.y << ")";
	return os;
}
