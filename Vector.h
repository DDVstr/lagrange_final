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
 * \brief Конструктор
 * \param length длина вектора
 */
template <typename T>
Vector<T>::Vector(uint32_t length) : Length(length)
{
    data = new T[Length];
}

//-------------------------------------------------------------------------------------------------
/**
 * \brief Деструктор
 */
template <typename T>
Vector<T>::~Vector()
{
    delete[] data;
}

//-------------------------------------------------------------------------------------------------
/**
 * \brief Конструктор копирования
 * \param object вектор
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
 * \brief Оператор присваивания
 * \param object объект копирования
 * \return скопированный элемент
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
 * \brief Для удобной навигации по вектору
 * \param index индекс элемента
 * \return элемент буфера
 */
template <typename T>
inline T& Vector<T>::operator[](uint32_t index)
{
    return data[index];
}

//-------------------------------------------------------------------------------------------------
/**
 * \brief Возвращает указатель на буфер с данными.
 * \return указатель на буфер с данными
 * \details Очень удобная штука, если другой объект не в курсе о том, что такое вектор, но в курсе
 *          о используемом типе
 */
template <typename T>
T* Vector<T>::operator*()
{
    return data;
}


#endif /* VECTOR_H */ 

