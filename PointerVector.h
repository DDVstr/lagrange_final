#ifndef POINT_VECTOR_H
#define POINT_VECTOR_H

#include "Vector.h"


/**
 * \details ����� ��������� ������� ������ ��� ������, ������������� ������������ ������, �.�. �������� ��������� �� ������� ����������
 */
template <typename T>
class PointerVector :
	public Vector<T>
{
public:
	PointerVector(int32_t length);
	PointerVector(const PointerVector& object);
	PointerVector& operator=(const PointerVector& object);

	int32_t Push(const T& object);
    inline const T& Get(uint32_t index);
	~PointerVector() = default;

	int32_t Index;
};
//======================================================================================================================
/**
 * \brief ����������� ������ �� ����������
 * \param length ����� �������
 */
template <typename T>
PointerVector<T>::PointerVector(int32_t length) :
    Vector<T>(length),
    Index(0)
{
}

//----------------------------------------------------------------------------------------------------------------------
/**
 * \brief ����������� �����������
 * \param object 
 */
template <typename T>
PointerVector<T>::PointerVector(const PointerVector& object) :
    Vector<T>(object)
{
	Index = object.Index;
}

//----------------------------------------------------------------------------------------------------------------------
/**
 * \brief �������� ������������ ��� ����������
 * \param object ������ �����������
 * \return ������ ������������
 */
template <typename T>
PointerVector<T>& PointerVector<T>::operator=(const PointerVector& object)
{
	if (this != &object)
	{
		Index = object.Index;
		Vector<T>::operator=(object);
	}
	return *this;
}

//----------------------------------------------------------------------------------------------------------------------
/**
 * \brief ���������� ������� � ������
 * \param object ������
 * \return 0
 */
template <typename T>
int32_t PointerVector<T>::Push(const T& object)
{
	Vector<T>::data[Index] = object;
	Index = (Index + 1) % Vector<T>::Length;
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------
/**
 * \brief ��������� �������� �� ������� �������
 * \param index ������ ��������
 * \return ��������
 */
template <typename T>
inline const T& PointerVector<T>::Get(uint32_t index)
{	
	return Vector<T>::data[(Index + index) % Vector<T>::Length];
}

#endif /* POINT_VECTOR_H */
