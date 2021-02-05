#include "LagrangeInterpolation.h"

LagrangeInterpolation::LagrangeInterpolation() :
    MINIMAL_NUMBER_OF_POINTS(3),
    DEFAULT_VALUE_NUMBER_OF_POINTS(-1)
{
    NumberOfPoints = DEFAULT_VALUE_NUMBER_OF_POINTS;
    DelayLine = nullptr;
    Coefficients = nullptr;
    CounterOfDelay = 0;
    Dx = 0;
}

LagrangeInterpolation::~LagrangeInterpolation()
{
    if (NumberOfPoints != DEFAULT_VALUE_NUMBER_OF_POINTS)
    {
        DeInit();
    }
}

LagrangeInterpolation::tStatus LagrangeInterpolation::Init(const uint32_t &numberOfPoints)
{
    if (NumberOfPoints != DEFAULT_VALUE_NUMBER_OF_POINTS)
    {
        return Status::NOT_DEINIT;
    }
    if (static_cast<int32_t>(numberOfPoints) < MINIMAL_NUMBER_OF_POINTS)
    {
        return INVALID_VALUE;
    }

    if ((numberOfPoints & 0x1) == 0)
    {
        return INVALID_VALUE;
    }

    NumberOfPoints = numberOfPoints;

    DelayLine = new PointerVector<double>(NumberOfPoints);
    Coefficients = new double[NumberOfPoints];
    CounterOfDelay = NumberOfPoints / 2;

    for (int32_t i = 0; i < NumberOfPoints; i++)
    {
        DelayLine->data[i] = 0.0;
        Coefficients[i] = 0.0;
    }

    return Status::INITED;
}

LagrangeInterpolation::tStatus LagrangeInterpolation::DeInit()
{
    if (NumberOfPoints == DEFAULT_VALUE_NUMBER_OF_POINTS)
    {
        return Status::NOT_INIT;
    }

    delete DelayLine;
    DelayLine = nullptr;
    delete[] Coefficients;
    Coefficients = nullptr;

    CounterOfDelay = 0;
    NumberOfPoints = DEFAULT_VALUE_NUMBER_OF_POINTS;

    return Status::DEINITED;
}

LagrangeInterpolation::tStatus LagrangeInterpolation::SetDeltaX(double dx)
{
    if (NumberOfPoints == DEFAULT_VALUE_NUMBER_OF_POINTS)
    {
        return  Status::NOT_INIT;
    }

    if (dx > 1 && dx < -1.0)
    {
        return Status::INVALID_VALUE;
    }
    Dx = dx;
    dx = static_cast<double>(NumberOfPoints / 2) - dx;  // NOLINT(bugprone-integer-division)
    
    for (int32_t i = 0; i < NumberOfPoints; i++)
    {
        Coefficients[i] = 1;
        for (int32_t j = 0; j < NumberOfPoints; j++)
        {
            if (i == j)
                continue;

            Coefficients[i] *= (dx - static_cast<double>(j)) /
                (static_cast<double>(i) - static_cast<double>(j));
        }
    }

    return Status::VALID_VALUE;
}

LagrangeInterpolation::tStatus LagrangeInterpolation::Interpolate(const double &newPointY, double *value)
{
    if (NumberOfPoints == DEFAULT_VALUE_NUMBER_OF_POINTS)
    {
        return  Status::NOT_INIT;
    }
    /* обнуляем значение прежде чем будет заполнять */
    *value = 0.0;

    /* добавляем в линию задержки новое значение */
    DelayLine->Push(newPointY);
    /* Подсчитываем значение в заданной точке интерполяции */
    for (int32_t i = 0; i < NumberOfPoints; i++)
    {
        *value += DelayLine->Get(i) * Coefficients[i];
    }
    /* если есть переходной процесс */
    if (CounterOfDelay != 0)
    {
        /* сидим считаем сколько нужно ждать */
        CounterOfDelay--;
        /* сообщаем пользователю о том, что значение не рекомендовано к использованию */
        return Status::INVALID_VALUE;
    }

    /* переходной процесс окончен, сообщаем, что значение можно использовать для интерполяции */
    return Status::VALID_VALUE;
}


