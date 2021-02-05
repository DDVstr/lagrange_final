#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <corecrt_math_defines.h>
#include "LagrangeInterpolation.h"

const double F1 = 10;
const double F2 = 20;
const double F3 = 30;
const double step = 1.0 / 500.0;

double func(int32_t counter, double dx)
{
    return  sin(2.0 * M_PI * F1 * (counter * step - dx * step)) +
            sin(2.0 * M_PI * F2 * (counter * step - dx * step)) +
            sin(2.0 * M_PI * F3 * (counter * step - dx * step));
}

int main(int argc, char* argv[], char *env[])
{
    system("chcp 65001");
    printf("Установлена кодировка UTF-8\n");
    printf("Начало выполнения программы.\n");
    const char *fileNameSrcY = "SrcY.bin";
    const char *fileNameSrcYTrue = "SrcYTrue.bin";
    const char *fileNameInterpY = "InterpY.bin";
    FILE *streamSrcY = fopen(fileNameSrcY, "wb");
    FILE *streamSrcYTrue = fopen(fileNameSrcYTrue, "wb");
    FILE *streamInterpY = fopen(fileNameInterpY, "wb");

    if (streamSrcY == nullptr)
    {
        printf("Ошибка открытия файла %s\n", fileNameSrcY);
        printf("Аварийный выход из программы\n");
        system("pause");
        exit(-1);
    }

    if (fileNameSrcYTrue == nullptr)
    {
        printf("Ошибка открытия файла %s\n", fileNameSrcYTrue);
        printf("Аварийный выход из программы\n");
        system("pause");
        exit(-1);
    }

    if (streamInterpY == nullptr)
    {
        printf("Ошибка открытия файла %s\n", fileNameInterpY);
        printf("Аварийный выход из программы\n");
        system("pause");
        exit(-1);
    }

    const int32_t Npoints = 15;
    const double dx = 0.25;
    int32_t counterPhase = 0.0;
    double meanDelta = 0.0;
    const int32_t NumberOfExperiments = 100;

    LagrangeInterpolation *interp = new LagrangeInterpolation();
    LagrangeInterpolation::tStatus status = interp->Init(Npoints);
    if (status != LagrangeInterpolation::INITED)
    {
        printf("Ошибка, не инциализировано.\n");
        system("pause");
    }
    status = interp->SetDeltaX(dx);
    if (status != LagrangeInterpolation::VALID_VALUE)
    {
        printf("Ошибка, смещение не установлено.\n");
        system("pause");
    }
    for (int32_t i = 0; i < NumberOfExperiments; i++)
    {
        /* здесь формируем для линии задержки сигналы */
        const double srcY = func(counterPhase, 0.0);
        fwrite(&srcY, sizeof(double), 1, streamSrcY);
        double interpY = 0.0;
        status = interp->Interpolate(srcY, &interpY);
        
        if (status == LagrangeInterpolation::INVALID_VALUE)
        {
            /* ожидаем окончания переходного процесса */
            counterPhase++;
            continue;
        }

        /* пересчитываем значение функции с учетом внесенной задержки для расчета относительной погрешности */
        const int32_t t = counterPhase - interp->GetUsingNumberOfPoints() / 2;
        const double srcYTrue = func(t, dx);

        const double delta = abs((interpY - srcYTrue) / srcYTrue);
        /*
         * Чем выше относительная погрешность delta, тем больше будет децибел [дБ]
         * расчет ведется по принципу delta_dB = 20*log10(delta), коэффициент 20 выбирается из принципа, что это отношение амплитуд
         * погрешность  100% =   0 дБ
         * погрешность   50% =  -6 дБ (почти 6 дБ)
         * погрешность   10% = -20 дБ
         * погрешность 0,01% = -60 дБ
         */
        if (i == interp->GetUsingNumberOfPoints() / 2)
        {
            printf("\nЛиния задержки наполнена до половины, здесь самая максимальная погрешность интерполяции.\n\n");
        }
        if (i == interp->GetUsingNumberOfPoints())
        {
            printf("\nЛиния задержки заполнена. Погрешность интерполяции снизилась до возможного предела.\n\n");
        }
        if (i >= interp->GetUsingNumberOfPoints())
        {
            meanDelta += delta;
        }
        printf("Шаг[%d]: Относительная погрешность = %4.2f дециБел\n", t, 20*log10(delta));

        fwrite(&srcYTrue, sizeof(double), 1, streamSrcYTrue);
        fwrite(&interpY, sizeof(double), 1, streamInterpY);
        counterPhase++;
    }

    printf("\nСредняя относительная погрешность в установившемся режиме = %4.2f дециБел\n\n", 
           20 * log10(meanDelta / (static_cast<double>(NumberOfExperiments) - static_cast<double>(interp->GetUsingNumberOfPoints()))));
    
    fclose(streamSrcY);
    fclose(streamSrcYTrue);
    fclose(streamInterpY);
    printf("Запись в файл завершена.\n");

    delete interp;
    printf("Память высвобождена.\n");
    printf("Программа завершена.\n");
    system("pause");
    return 0;
}
