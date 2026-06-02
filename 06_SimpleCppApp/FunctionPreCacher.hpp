#pragma once

#include <iostream>
#include <stdexcept>
#include <cstdint>
#include <cstring>

namespace SimpleCppApp
{
	template<typename T>
	class FunctionPreCacher
	{
		public:
			FunctionPreCacher() = default;
			FunctionPreCacher(const FunctionPreCacher& another)
			{
				x = another.x;
				count = another.count;
				function = another.function;
				if (another.values)
				{
					values = new T[another.count];
					if (values)
					{
						//std::cout << "Allocate values with <<COPY>> from " << another.values << " to " << this->values << std::endl;
						for (uint32_t i = 0; i < another.count; i++)
						{
							values[i] = another.values[i];
						}
						//std::memcpy(values, another.values, sizeof(T) * another.count);
					}
					else
					{
						throw std::runtime_error("FunctionPreCacher copy: not sufficient new values allocated");
					}
				}
			}
			FunctionPreCacher(FunctionPreCacher&& another) noexcept						// double && used as a "move" semantic
			{
				x = another.x;
				count = another.count;
				function = another.function;
				values = another.values;

				another.values = nullptr;
			}
			FunctionPreCacher(int32_t x, uint32_t count, T(*function)(int32_t))
			{
				Setup(x, count, function);
			}
			~FunctionPreCacher()
			{
				Release();
			}

			FunctionPreCacher& operator=(const FunctionPreCacher& another)
			{
				if (this != &another) // prevent self-assignment
				{
					this->~FunctionPreCacher();
					this->FunctionPreCacher::FunctionPreCacher(another);
				}
				return *this;
			}
			FunctionPreCacher& operator=(FunctionPreCacher&& another) noexcept
			{
				if (this != &another) // prevent self-assignment
				{
					this->~FunctionPreCacher();
					this->FunctionPreCacher::FunctionPreCacher(std::move(another));
				}
				return *this;
			}

			void Setup(int32_t x, uint32_t count, T(*function)(int32_t))
			{
				Release();
				this->x = x;
				this->count = count;
				this->function = function;
			}
			FunctionPreCacher& Compute()
			{
				if (function && count > 0)
				{
					Release();
					values = new T[count];
					if (values)
					{
						//std::cout << "Allocate values and Compute().." << this->values << std::endl;
						for (int32_t i = 1; i <= count; i++)
						{
							values[i - 1] = function(i * x);
						}
					}
					else
					{
						throw std::runtime_error("FunctionPreCacher: not sufficient new values allocated");
					}
				}

				return *this;
			}
			void Release()
			{
				if (values)
				{
					//std::cout << "Delete values with Release().." << this->values << std::endl;
					delete[] values; // delete[] specifies we delete certain amount (count) of data -> delete an array
					values = nullptr;
				}
			}
			void PrintResult(std::ostream& os = std::cout) const
			{
				if (values)
				{
					for (int32_t i = 1; i <= count; i++)
					{
						os << "f(" << i * x << ") = " << values[i - 1] << std::endl;
					}
					os << std::endl;
				}
			}
			T At(int32_t index) const //int32_t At(int32_t index) const, simo
			{
				if (index >= count)
					throw std::range_error("FunctionPreChacher index out of range!");
				return values[index];
			}
			uint32_t Size() const noexcept
			{
				return count;
			}
			FunctionPreCacher& operator()()
			{
				return Compute();
			}
			FunctionPreCacher& operator()(int32_t x, uint32_t count, T(*function)(int32_t))
			{
				Setup(x, count, function);
				return Compute();
			}
			const T& operator[](uint32_t index) const				// overload the array operator "[]"
			{
				return At(index);
			}
			operator bool()
			{
				return values != nullptr;
			}

		private:
			T* values = nullptr;
			int32_t x = 0;
			int32_t count = 0;
			T(*function)(int32_t x) = nullptr;
	};
}

// Tesll the complile to use inline copy/paste insertion of the function instead of creating an object
// which is then tried to be linked
template<typename T>
inline  std::ostream& operator<<(std::ostream& os, const SimpleCppApp::FunctionPreCacher<T>& pc)
{
	pc.PrintResult(os);
	return os;
}


