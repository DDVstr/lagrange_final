#ifndef VECTOR_H
#define VECTOR_H
#include <cstdint>

template <typename T>
class Vector
{
public:
    explicit Vector(uint32_t length);
    ~Vector();
    Vector(const Vector &object);
    Vector &operator=(const Vector &object);
    inline T &operator[](uint32_t index);
    T *operator*();


    T *data;
    int32_t Length;

};
//=================================================================================================
/**
 * \brief �����������
 * \param length ����� �������
 */
template <typename T>
Vector<T>::Vector(uint32_t length) : Length(length)
{
    data = new T[Length];
}

//-------------------------------------------------------------------------------------------------
/**
 * \brief ����������
 */
template <typename T>
Vector<T>::~Vector()
{
    delete[] data;
}

//-------------------------------------------------------------------------------------------------
/**
 * \brief ����������� �����������
 * \param object ������
 */
template <typename T>
Vector<T>::Vector(const Vector& object)
{
    Length = object.Length;
    data = new T[Length];
    for (int32_t i = 0; i < Length; i++)
    {
        data[i] = object.data[i];
    }
}

//-------------------------------------------------------------------------------------------------
/**
 * \brief �������� ������������
 * \param object ������ �����������
 * \return ������������� �������
 */
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& object)  // NOLINT(bugprone-unhandled-self-assignment)
{
    if (this == &object)
        return *this;

    if (Length != object.Length)
    {
        this->~Vector();
        Length = object.Length;
        data = new T[Length];
    }

    for (int32_t i = 0; i < Length; i++)
    {
        data[i] = object.data[i];
    }
    return *this;
}

//-------------------------------------------------------------------------------------------------
/**
 * \brief ��� ������� ��������� �� �������
 * \param index ������ ��������
 * \return ������� ������
 */
template <typename T>
inline T& Vector<T>::operator[](uint32_t index)
{
    return data[index];
}

//-------------------------------------------------------------------------------------------------
/**
 * \brief ���������� ��������� �� ����� � �������.
 * \return ��������� �� ����� � �������
 * \details ����� ������� �����, ���� ������ ������ �� � ����� � ���, ��� ����� ������, �� � �����
 *          � ������������ ����
 */
template <typename T>
T* Vector<T>::operator*()
{
    return data;
}


#endif /* VECTOR_H */ 

