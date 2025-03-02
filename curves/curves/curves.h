#pragma once
#ifdef CURVES_EXPORTS
#define CURVES_API __declspec(dllexport)
#else
#define CURVES_API __declspec(dllimport)
#endif
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <memory>
#include <time.h>
#include <vector>
#include <omp.h>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <string>
/**
 * @brief The Point3D struct Структура для хранения координат точки в трехмерном пространстве.
 */
struct CURVES_API Point3D {                                               // Структура для хранения координат точки в трехмерном пространстве.
    double x=0;                                                           // Координат X точки в трехмерном пространстве.
    double y=0;                                                           // Координат Y точки в трехмерном пространстве.
    double z=0;                                                           // Координат Z точки в трехмерном пространстве.
};
/**
 * @brief The Vector3D struct Структура для хранения координат вектора в трехмерном пространстве.
 */
struct CURVES_API Vector3D {                                              // Структура для хранения координат вектора в трехмерном пространстве.
    double x = 0;                                                         // Координата X начала вектора.
    double y = 0;                                                         // Координата Y начала вектора.
    double z = 0;                                                         // Координата Z начала вектора.
};
//---------------------------------------------------------------------------------------------------------------------------------------
namespace curve {
    /**
     * @brief The Curve class Абстрактный базовый класс кривой.
     */
    class CURVES_API Curve
    {
    public:
        enum class CurveType {                                            // Перечисление возможных типов фигуры.
            NONE,
            ELLIPS,
            CIRCLE,
            HELIXE
        };
        Curve();                                                          // Конструктор по умолчанию.
        Curve(CurveType Identifier);                                      // Конструктор от параметра.
        void setCentrX(double X);                                         // Метод установки координаты X цента фигуры.
        void setCentrY(double Y);                                         // Метод установки координаты Y цента фигуры.
        double getCentrX();                                               // Метод получения координаты X цента фигуры.
        double getCentrY();                                               // Метод получения координаты Y цента фигуры.
        CurveType getIdentifier();                                        // Метод получения типа фигуры.
        virtual Point3D getPoint3D(double t) = 0;                         // Виртуальный метод, возвращает точку на касания.
        virtual Vector3D getVector3D(double t) = 0;                       // Виртуальный метод, возвращает вектор производной.
        virtual void print(std::ostream& out, double t) = 0;              // Виртуальный метод, выполняет печать фигуры в поток.
    protected:
        double centreX;                                                   // Координата X центра фигуры.
        double centreY;                                                   // Координата Y центра фигуры.
        CurveType identifier;                                             // Переменная для хранения типа фигуры.
    };
    /**
    * @brief The Ellipse class   Производный класс эллипс.
    */
    class CURVES_API Ellipse : public Curve
    {
    public:
        Ellipse(double CentreX, double CentreY, double RX, double RY);    // Конструктор фигуры эллипса от параметра.
        void setRX(double RX);                                            // Метод установки радиуса эллипса по оси OX.
        void setRY(double RY);                                            // Метод установки радиуса эллипса по оси OY.
        double getRX();                                                   // Метод получения радиуса эллипса по оси OX.
        double getRY();                                                   // Метод получения радиуса эллипса по оси OY.
        Point3D getPoint3D(double t);                                     // Метод возвращает точку на касания.
        Vector3D getVector3D(double t);                                   // Метод, возвращает вектор производной.
        void print(std::ostream& out, double t);                          // Метод, выполняет печать фигуры в поток.
    private:
        double rX;                                                        // Радиус эллипса по оси OX.
        double rY;                                                        // Радиус эллипса по оси OY.
    };
    /**
    * @brief The Ellipse class   Производный класс окружность.
    */
    class CURVES_API Circle : public Curve
    {
    public:
        Circle(double CentreX, double CentreY, double R);                 // Конструктор фигуры окружности от параметра.
        void setR(double R);                                              // Метод установки радиуса окружности.
        double getR();                                                    // Метод получения адреса окружности.
        virtual Point3D getPoint3D(double t);                             // Метод получения координат точки касания.
        Vector3D getVector3D(double t);                                   // Метод получения вектора производной.
        bool operator > (const Circle& E1);                               // Перегруженный оператор >.
        bool operator < (const Circle& E1);                               // Перегруженный оператор <.
        bool operator == (const Circle& E1);                              // Перегруженный оператор ==.
        void print(std::ostream& out, double t);                          // Метод печати фигуры в поток.
    private:
        double r;                                                         // Радиус окружности.
    };
    /**
    * @brief The Ellipse class   Производный класс спираль.
    */
    class CURVES_API Helixe : public Curve
    {
    public:
        Helixe(double CentreX, double CentreY, double R, double Step);    // Конструктор фигуры спирали от параметра.
        void setR(double R);                                              // Метод установки радиуса спирали.
        double getR();                                                    // Метод получения радиуса спирали.
        void setStep(double Step);                                        // Метод установки шага спирали.
        double getStep();                                                 // Метод получения шага спирали.
        virtual Point3D getPoint3D(double t);                             // Метод получения координат точки касания.
        Vector3D getVector3D(double t);                                   // Метод получения координат вектора производной.
        void print(std::ostream& out, double t);                          // Метод печати фигуры спирали.
    private:
        double r;                                                         // Радиус спирали.
        double step;                                                      // Шаг спирали.
    };
}
/**
 * @brief randomCurveVector Функция заполнения контейнера случайными кривыми.
 * @param [out] V Ссылка на контейнер для заполнения.
 * @param n Количество сгенерированных кривых.
 */
CURVES_API void randomCurveVector(std::vector<std::shared_ptr<curve::Curve>> & V, int n);
/**
 * @brief foundCircleCurve Функция поиска и копирование указателей на окружностей из первого контейнера во второй. 
 * @param [in] V1 Ссылка на контейнер исходных кривых.
 * @param [out] V2 Ссылка на контейнер окружностей для заполнения.
 */
CURVES_API void foundCircleCurve( std::vector<std::shared_ptr<curve::Curve>> const& V1, std::vector<std::shared_ptr<curve::Circle>> & V2);
/**
 * @brief sortCircleByIncreasingRadius Функция сортировки контейнера окружностей.
 * @param [out] V Ссылка на контейнер окружностей.
 */
CURVES_API void sortCircleByIncreasingRadius(std::vector<std::shared_ptr<curve::Circle>> & V);
/**
 * @brief sumRadius Функция вычисления суммы радиусов окружностей в контейнере.
 * @param [in] V Ссылка на контейнер окружностей.
 */
CURVES_API double sumRadius(std::vector<std::shared_ptr<curve::Circle>> const& V);
/**
 * @brief output3DDateToFile Функция вывода в файл контейнера, содержащего различные кривые.
 * @param [in] V Ссылка на контейнер различных кривых.
 * @param angleRad Параметр t в радианах.
 * @param fileName Имя выходного файла.
 */
CURVES_API void output3DDateToFile(std::vector<std::shared_ptr<curve::Curve>> const& V, double angleRad, std::string fileName);
/**
 * @brief output3DDateToFile Функция вывода в файл контейнера, содержащего окружности.
 * @param [in] V Ссылка на контейнер окружностей.
 * @param angleRad Параметр t в радианах.
 * @param fileName Имя выходного файла.
 */
CURVES_API void output3DDateToFile( std::vector<std::shared_ptr<curve::Circle>> const& V, double angleRad, std::string fileName);
