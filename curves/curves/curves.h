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
struct CURVES_API Point3D {                                             // Структура для хранения координат точки в трехмерном пространстве.
    double x = 0;                                                       // Координат X точки в трехмерном пространстве.
    double y = 0;                                                       // Координат Y точки в трехмерном пространстве.
    double z = 0;                                                       // Координат Z точки в трехмерном пространстве.
};
/**
 * @brief The Vector3D struct Структура для хранения координат вектора в трехмерном пространстве.
 */
struct CURVES_API Vector3D {                                            // Структура для хранения координат вектора в трехмерном пространстве.
    double x = 0;                                                       // Координата X вектора.
    double y = 0;                                                       // Координата Y вектора.
    double z = 0;                                                       // Координата Z вектора.
};
//---------------------------------------------------------------------------------------------------------------------------------------
namespace curve {
    /**
     * @brief header Заголовок таблицы вывода фигур.
     */
    const std::wstring header = L"  -------------------------------------------------------------------------------------------------------------------------------------------------------\n"
                                 " |  Кривая     |     Точка центра     |  Радиус X  |  Радиус Y  |   Радиус   |    Шаг     |           3D Точка           |     3D Вектор производной     |\n"
                                 "  -------------+----------------------+------------+------------+------------+------------+------------------------------+-------------------------------\n";
    /**
     * @brief endTab Окончание таблицы.
     */
    const std::wstring endTab = L"  -------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    /**
     * @brief The Curve class Абстрактный базовый класс кривой.
     */
    class CURVES_API Curve
    {
    public:
        Curve(double CenterX, double CenterY);                          // Конструктор от параметров.
        void setCentreX(double X);                                      // Метод установки координаты X цента фигуры.
        void setCentreY(double Y);                                      // Метод установки координаты Y цента фигуры.
        double getCentreX() const;                                      // Метод получения координаты X цента фигуры.
        double getCentreY() const;                                      // Метод получения координаты Y цента фигуры.
        virtual Point3D getPoint3D(double t) const = 0;                 // Виртуальный метод, возвращает точку кривой в зависимости от параметра t.
        virtual Vector3D getVector3D(double t) const = 0;               // Виртуальный метод, возвращает вектор первой производной.
        virtual void print(double t) const = 0;                         // Виртуальный метод, выполняет печать фигуры в консоль.
        virtual ~Curve();                                               // Виртуальный деструктор базового класса.
    protected:
        double centreX;                                                 // Координата X центра фигуры.
        double centreY;                                                 // Координата Y центра фигуры.
    };
    /**
    * @brief The Ellipse class   Производный класс эллипс.
    */
    class CURVES_API Ellipse : public Curve
    {
    public:
        Ellipse(double CentreX, double CentreY, double RX, double RY);  // Конструктор фигуры эллипса от параметров.
        void setRX(double RX);                                          // Метод установки радиуса эллипса по оси OX.
        void setRY(double RY);                                          // Метод установки радиуса эллипса по оси OY.
        double getRX() const;                                           // Метод получения радиуса эллипса по оси OX.
        double getRY() const;                                           // Метод получения радиуса эллипса по оси OY.
        virtual Point3D getPoint3D(double t) const override;            // Метод возвращает точку на эллипсе в зависимостиот параметра t.
        virtual Vector3D getVector3D(double t) const override;          // Метод, возвращает вектор первой производной.
        virtual void print(double t) const override;                    // Метод, выполняет печать фигуры в консоль.
        virtual ~Ellipse() override;                                    // Виртуальный деструктор производного класса.
    private:
        double rX;                                                      // Радиус эллипса по оси OX.
        double rY;                                                      // Радиус эллипса по оси OY.
    };
    /**
    * @brief The Ellipse class   Производный класс окружность.
    */
    class CURVES_API Circle : public Curve
    {
    public:
        Circle(double CentreX, double CentreY, double R);               // Конструктор фигуры окружности от параметра.
        void setR(double R);                                            // Метод установки радиуса окружности.
        double getR() const;                                            // Метод получения радиуса окружности.
        virtual Point3D getPoint3D(double t) const override;            // Метод получения координат точки окружности в зависимости от параметра t.
        virtual Vector3D getVector3D(double t) const override;          // Метод получения вектора первой производной.
        virtual void print(double t) const override;                    // Метод, выполняет печать фигуры в консоль.
        virtual ~Circle() override;                                     // Виртуальный деструктор производного класса.
    private:
        double r;                                                       // Радиус окружности.
    };
    /**
    * @brief The Ellipse class   Производный класс спираль.
    */
    class CURVES_API Helixe : public Curve
    {
    public:
        Helixe(double CentreX, double CentreY, double R, double Step);  // Конструктор фигуры спирали от параметра.
        void setR(double R);                                            // Метод установки радиуса спирали.
        double getR() const;                                            // Метод получения радиуса спирали.
        void setStep(double Step);                                      // Метод установки шага спирали.
        double getStep() const;                                         // Метод получения шага спирали.
        virtual Point3D getPoint3D(double t) const override;            // Метод получения координат точки спирали в зависимости от параметра t.
        virtual Vector3D getVector3D(double t) const override;          // Метод получения координат вектора производной.
        virtual void print(double t) const override;                    // Метод, выполняет печать фигуры в консоль.
        virtual ~Helixe() override;                                     // Виртуальный деструктор производного класса.
    private:
        double r;                                                       // Радиус спирали.
        double step;                                                    // Шаг спирали.
    };
}
/**
 * @brief randomCurveVector Функция заполнения контейнера случайными кривыми.
 * @param [out] Vout Ссылка на контейнер для заполнения.
 * @param n Количество сгенерированных кривых.
 */
CURVES_API void randomCurveVector(std::vector<std::shared_ptr<curve::Curve>> & Vout, int n);
/**
 * @brief findCircle Функция поиска и копирование указателей на окружностеи из первого контейнера во второй. 
 * @param [in] Vin Ссылка на контейнер исходных кривых.
 * @param [out] Vout Ссылка на контейнер окружностей для заполнения.
 */
CURVES_API void findCircle( std::vector<std::shared_ptr<curve::Curve>> const& Vin, std::vector<std::shared_ptr<curve::Circle>> & Vout);
/**
 * @brief sortCircleByIncreasingRadius Функция сортировки контейнера окружностей.
 * @param [out] Vout Ссылка на контейнер окружностей.
 */
CURVES_API void sortCircleByIncreasingRadius(std::vector<std::shared_ptr<curve::Circle>> & Vout);
/**
 * @brief sumRadius Функция вычисления суммы радиусов окружностей в контейнере.
 * @param [in] Vin Ссылка на контейнер окружностей.
 */
CURVES_API double sumRadius(std::vector<std::shared_ptr<curve::Circle>> const& Vin);
/**
 * @brief toString Функция перобразования числа в строку.
 * @param num Число с плавающей точкой.
 * @return Строковое представление числа.
 */
CURVES_API std::wstring toString(double num);