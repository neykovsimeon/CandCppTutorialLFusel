#pragma once
#include "FunctionPreCacher.hpp"

#include <iostream>
#include <stdexcept>

namespace SimpleCppApp
{
	class PreCacherContainer
	{
		public:
			PreCacherContainer() = default;													// Default constructor

			PreCacherContainer(const PreCacherContainer&) = default;						// Default copy constructor
			~PreCacherContainer() = default;												// Default destructor
			PreCacherContainer& operator=(const PreCacherContainer&) = default;				// Default "copy" assign operator overload
			PreCacherContainer(PreCacherContainer&&) noexcept = default;					// Default "move" constructor - The Big five concept
			PreCacherContainer& operator=(PreCacherContainer&&) noexcept = default;			// Default "move" assign operator overload - The Big five concept

			void PrintResult(std::ostream& os = std::cout) const
		{
			os << "Container at " << this << std::endl;
			for (int i = 0; i < m_usage; i++)
			{
				os << "FunctionPreCacher #" << (i + 1) << std::endl;
				os << m_preCachers[i];	// m_preCachers[i].PrintResult(os);
			}
		}
			void Append(const FunctionPreCacher& pc)
		{
			if (m_usage >= 8)
				throw std::overflow_error("PreCacherContainer overflown!");
			m_preCachers[m_usage++] = pc; // m_usage would be frist taken with its old value, then assignment, then m_usage increment
		}
			void Append(FunctionPreCacher&& pc)
		{
			if (m_usage >= 8)
				throw std::overflow_error("PreCacherContainer overflown!");
			m_preCachers[m_usage++] = std::move(pc); // m_usage would be first taken with its old value, then assignment, then m_usage increment
		}
			const FunctionPreCacher& At(int index) const
		{
			if (index >= 8 || index < 0)
				throw std::range_error("PreCaherContainer index out of range!");
			return m_preCachers[index];
		}
			FunctionPreCacher& At(int index)
		{
			if (index >= 8 || index < 0)
				throw std::range_error("PreCaherContainer index out of range!");
			return m_preCachers[index];
		}
			int Size() const noexcept
		{
			return m_usage;
		}

			PreCacherContainer& operator<<(const FunctionPreCacher& pc)
		{
			Append(pc);
			return *this;
		}
			PreCacherContainer& operator<<(FunctionPreCacher&& pc)
		{
			Append(std::move(pc));
			return *this;
		}
			const FunctionPreCacher& operator[](int index) const
		{
			return At(index);
		}
			FunctionPreCacher& operator[](int index)
		{
			return At(index);
		}

		private:
			FunctionPreCacher m_preCachers[8];
			int m_usage = 0;
	};
}

inline  std::ostream& operator<<(std::ostream& os, const SimpleCppApp::PreCacherContainer& pc)
{
	pc.PrintResult(os);
	return os;
}


