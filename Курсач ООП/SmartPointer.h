#pragma once
namespace Pointer
{
	template<typename T>
	class SmartPointer
	{
	public:
		SmartPointer(T* ptr);
		~SmartPointer();
		T& operator*();
	private:
		T* ptr;
	};	

template<typename T>
inline SmartPointer<T>::SmartPointer(T* ptr)
{
	this->ptr = ptr;
}

template<typename T>
inline SmartPointer<T>::~SmartPointer()
{
	delete ptr;
}

template<typename T>
inline T& SmartPointer<T>::operator*()
{
	return *ptr;
}
}