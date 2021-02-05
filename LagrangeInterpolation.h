#ifndef LAGRANGE_INTERPOLATION_H
#define LAGRANGE_INTERPOLATION_H
#include <cstdint>

#include "PointerVector.h"

/**
 * \brief �������������� ������������ �� ������ ����������� ��������
 * \details ������ ������������ ��� ����������� ������� ��������
 */
class LagrangeInterpolation
{
public:

    typedef enum Status
    {
        INITED,
        DEINITED,
        NOT_INIT,
        NOT_DEINIT,
        VALID_VALUE,
        INVALID_VALUE
    } tStatus;

    LagrangeInterpolation();
    ~LagrangeInterpolation();

    tStatus Init(const uint32_t &numberOfPoints);
    tStatus DeInit();
    tStatus SetDeltaX(double dx);
    tStatus Interpolate(const double &newPointY, double *value);
    inline double GetUsingDx() const;
    inline int32_t GetUsingNumberOfPoints() const;

private:
    int32_t NumberOfPoints;
    PointerVector<double> *DelayLine;
    double *Coefficients;
    int32_t CounterOfDelay;
    double Dx;
    const int32_t MINIMAL_NUMBER_OF_POINTS;
    const int32_t DEFAULT_VALUE_NUMBER_OF_POINTS;
};

//======================================================================================================================
/**
 * \brief ������� ��� ������� ������������ �������� dx
 * \return dx
 */
inline double LagrangeInterpolation::GetUsingDx() const 
{
    return Dx;
}

//----------------------------------------------------------------------------------------------------------------------
/**
 * \brief ������� ������� ����� ������������ ����� ��� �������
 * \return ����� ������������ �����
 */
inline int32_t LagrangeInterpolation::GetUsingNumberOfPoints() const
{
    return NumberOfPoints;
}

#endif

