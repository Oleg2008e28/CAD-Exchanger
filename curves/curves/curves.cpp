#include "pch.h"
#include "curves.h"
#include <sstream>
using namespace curve;
//Базовый класс Curve
Curve::Curve(double CentreX, double CentreY) {
    centreX = CentreX;
    centreY = CentreY;
}
void Curve::setCentreX(double X) {
    centreX = X;
}
void Curve::setCentreY(double Y) {
    centreY = Y;
}
double Curve::getCentreX() const {
    return centreX;
}
double Curve::getCentreY() const {
    return centreY;
}
Curve::~Curve() {}
//Производный класс Ellipse
Ellipse::Ellipse(double CentreX, double CentreY, double RX, double RY) : Curve(CentreX, CentreY) {
    rX = RX;
    rY = RY;
};
void Ellipse::setRX(double RX) {
    rX = RX;
}
void Ellipse::setRY(double RY) {
    rY = RY;
}
double Ellipse::getRX() const {
    return rX;
}
double Ellipse::getRY() const {
    return rY;
}
Point3D Ellipse::getPoint3D(double t) const {
    return { rX * cos(t) + centreX, rY * sin(t) + centreY, 0 };
}
Vector3D Ellipse::getVector3D(double t) const {
    return { -1 * rX * sin(t), rY * cos(t), 0 };
}
void Ellipse::print(double t) const {
    std::wstring ws(120, ' ');
    ws.insert(0, L" | Эллипс");
    ws.insert(15, L"|  ( " + toString(centreX) + L" : " + toString(centreY) + L" )");
    ws.insert(38, L"|  " + toString(rX));
    ws.insert(51, L"|  " + toString(rY));
    ws.insert(64, L"|");
    ws.insert(77, L"|");
    Point3D p = getPoint3D(t);
    ws.insert(90, L"|  ( " + toString(p.x) + L" : " + toString(p.y) + L" : " + toString(p.z) + L" )");
    Vector3D v = getVector3D(t);
    ws.insert(121, L"|  ( " + toString(v.x) + L" : " + toString(v.y) + L" : " + toString(v.z) + L" )");
    ws.insert(153, L"|");
    ws.erase(154);
    std::wcout << ws << std::endl;
}
Ellipse::~Ellipse() {}
//Производный класс Circle
Circle::Circle(double CentreX, double CentreY, double R) : Curve(CentreX, CentreY) {
    r = R;
    centreX = CentreX;
    centreY = CentreY;
};
void Circle::setR(double R) {
    r = R;
}
double Circle::getR() const {
    return r;
}
Point3D Circle::getPoint3D(double t) const {
    double x = r * cos(t) + centreX;
    double y = r * sin(t) + centreY;
    return { x,y,0 };
}
Vector3D Circle::getVector3D(double t) const {
    double x = -sin(t) * r;
    double y = cos(t) * r;
    return { x,y,0 };
}
void Circle::print(double t) const {
    std::wstring ws(120, ' ');
    ws.insert(0, L" | Окружность");
    ws.insert(15, L"|  ( " + toString(centreX) + L" : " + toString(centreY) + L" )");
    ws.insert(38, L"|");
    ws.insert(51, L"|");
    ws.insert(64, L"|  " + toString(r));
    ws.insert(77, L"|");
    Point3D p = getPoint3D(t);
    ws.insert(90, L"|  ( " + toString(p.x) + L" : " + toString(p.y) + L" : " + toString(p.z) + L" )");
    Vector3D v = getVector3D(t);
    ws.insert(121, L"|  ( " + toString(v.x) + L" : " + toString(v.y) + L" : " + toString(v.z) + L" )");
    ws.insert(153, L"|");
    ws.erase(154);
    std::wcout << ws << std::endl;
}
Circle::~Circle() {}
//Производный класс Helixe
Helixe::Helixe(double CentreX, double CentreY, double R, double Step) : Curve(CentreX, CentreY) {
    r = R;
    step = Step;
    centreX = CentreX;
    centreY = CentreY;
};
void Helixe::setR(double R) {
    r = R;
}
double Helixe::getR() const {
    return r;
}
void Helixe::setStep(double Step) {
    step = Step;
}
double Helixe::getStep() const {
    return step;
}
Point3D Helixe::getPoint3D(double t) const {
    double x = r * cos(t) + centreX;
    double y = r * sin(t) + centreY;
    double z = (step * t) / (2 * M_PI);
    return { x,y,z };
}
Vector3D Helixe::getVector3D(double t) const {
    double x = -sin(t) * r;
    double y = cos(t) * r;
    double z = step / (2 * M_PI);
    return { x,y,z };
}
void Helixe::print(double t) const {
    std::wstring ws(120, ' ');
    ws.insert(0, L" | Спираль");
    ws.insert(15, L"|  ( " + toString(centreX) + L" : " + toString(centreY) + L" )");
    ws.insert(38, L"|");
    ws.insert(51, L"|");
    ws.insert(64, L"|  " + toString(r));
    ws.insert(77, L"|  " + toString(step));
    Point3D p = getPoint3D(t);
    ws.insert(90, L"|  ( " + toString(p.x) + L" : " + toString(p.y) + L" : " + toString(p.z) + L" )");
    Vector3D v = getVector3D(t);
    ws.insert(121, L"|  ( " + toString(v.x) + L" : " + toString(v.y) + L" : " + toString(v.z) + L" )");
    ws.insert(153, L"|");
    ws.erase(154);
    std::wcout << ws << std::endl;

}
Helixe::~Helixe() {}
//Дополнительные функции
void randomCurveVector(std::vector<std::shared_ptr<curve::Curve>> & V, int n) {
    V.clear();
    V.reserve(n);
    for (auto i = 0; i < n; i++) {
        int y = rand() % 3 + 1;
        if (y == 1) {
            double CX, CY, RX, RY;
            CX = double(rand()) / 1000;
            CY = double(rand()) / 1000;
            RX = double(rand()) / 1000;
            RY = double(rand()) / 1000;
            V.push_back(std::make_shared<curve::Ellipse>(CX, CY, RX, RY));
        }
        else if (y == 2) {
            double CX, CY, R;
            CX = double(rand()) / 1000;
            CY = double(rand()) / 1000;
            R = double(rand()) / 1000;
            V.push_back(std::make_shared<curve::Circle>(CX, CY, R));
        }
        else {
            double CX, CY, R, H;
            CX = double(rand()) / 1000;
            CY = double(rand()) / 1000;
            R = double(rand()) / 1000;
            H = double(rand()) / 1000;
            V.push_back(std::make_shared<curve::Helixe>(CX, CY, R, H));
        }
    }
}
void findCircle( std::vector<std::shared_ptr<curve::Curve>> const& Vin, std::vector<std::shared_ptr<curve::Circle>>& Vout) {
    Vout.clear();
    for (auto a : Vin) {
        std::shared_ptr<Circle> ptr = std::dynamic_pointer_cast<curve::Circle>(a);
        if (ptr) {
            Vout.push_back(ptr);
        }
    }
}
void sortCircleByIncreasingRadius(std::vector<std::shared_ptr<curve::Circle>>& V) {
    std::sort(V.begin(), V.end(), [] 
    (const std::shared_ptr<curve::Circle>& ptrC1, const std::shared_ptr<curve::Circle>& ptrC2) {
        return (ptrC1->getR() < ptrC2->getR());
    });                                                                                             //Сортировка в порядке возрастания радиусов.
}
double sumRadius(std::vector<std::shared_ptr<curve::Circle>> const& V) {
    double sum = 0;
#pragma omp parallel
    {
        //std::wcout << omp_get_num_threads() << std::endl;    //Посмотреть количество потоков
        double local_sum = 0;
#pragma omp for
        for (auto i = 0; i < V.size(); i++) {
            local_sum += V[i]->getR();
        }
#pragma omp atomic
        sum += local_sum;
    }
    return sum;
}
std::wstring toString(double num) {
    std::wstringstream wss;
    std::wstring ws;
    wss.precision(4);
    wss << num;
    wss >> ws;
    return ws;
}