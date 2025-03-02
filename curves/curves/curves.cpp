#include "pch.h"
#include "curves.h"
using namespace curve;
//Базовый класс Curve
Curve::Curve() {
    centreX = 0;
    centreY = 0;
    identifier = CurveType::NONE;
}
Curve::Curve(CurveType Identifier) {
    centreX = 0;
    centreY = 0;
    identifier = Identifier;
}
void Curve::setCentrX(double X) {
    centreX = X;
}
void Curve::setCentrY(double Y) {
    centreY = Y;
}
double Curve::getCentrX() {
    return centreX;
}
double Curve::getCentrY() {
    return centreY;
}
Curve::CurveType Curve::getIdentifier() {
    return identifier;
}
//Производный класс Ellipse
Ellipse::Ellipse(double CentreX, double CentreY, double RX, double RY) : Curve(Curve::CurveType::ELLIPS) {
    rX = RX;
    rY = RY;
    setCentrX(CentreX);
    setCentrY(CentreY);
};
void Ellipse::setRX(double RX) {
    rX = RX;
}
void Ellipse::setRY(double RY) {
    rY = RY;
}
double Ellipse::getRX() {
    return rX;
}
double Ellipse::getRY() {
    return rY;
}
Point3D Ellipse::getPoint3D(double t) {
    if (cos(t) == 0) {
        if (sin(t) > 0) return { 0 + centreX, rY + centreY, 0 };
        else if (sin(t) < 0) return { 0 + centreX, -rY + centreY, 0 };
        else return { 0 + centreX, 0 + centreY, 0 };
    }
    else {
        double A = atan((rX * sin(t)) / (rY * cos(t)));
        return { rX * cos(A) + centreX, rY * sin(A) + centreY, 0 };
    }
}
Vector3D Ellipse::getVector3D(double t) {
    if (cos(t) == 0) {
        return{ -rX,0,0 };
    }
    else {
        double A = atan((rX * sin(t)) / (rY * cos(t)));
        return { rX * -sin(A), rY * cos(A), 0 };
    }
}
void Ellipse::print(std::ostream& out, double t) {
    Vector3D v = this->getVector3D(t);
    Point3D p = this->getPoint3D(t);
    std::string s;
    out.setf(std::ios_base::left);
    out.width(10);
    out << "Ellipse:";
    s = "center ( " + std::to_string(this->centreX) + " : " + std::to_string(this->centreY) + " )";
    out.width(45);
    out << s;
    s = "Radius by X = " + std::to_string(this->getRX());
    out.width(30);
    out << s;
    s = "Radius by Y = " + std::to_string(this->getRY());
    out.width(30);
    out << s;
    s = "3D point ( " + std::to_string(p.x) + " : " + std::to_string(p.y) + " : " + std::to_string(p.z) + " )";
    out.width(60);
    out << s;
    s = "3D vector ( " + std::to_string(v.x) + " : " + std::to_string(v.y) + " : " + std::to_string(v.z) + " )";
    out.width(60);
    out << s << std::endl;
}
//Производный класс Circle
Circle::Circle(double CentreX, double CentreY, double R) : Curve(Curve::CurveType::CIRCLE) {
    r = R;
    setCentrX(CentreX);
    setCentrY(CentreY);
};
void Circle::setR(double R) {
    r = R;
}
double Circle::getR() {
    return r;
}
Point3D Circle::getPoint3D(double t) {
    double x = r * cos(t) + centreX;
    double y = r * sin(t) + centreY;
    return { x,y,0 };
}
Vector3D Circle::getVector3D(double t) {
    double x = -sin(t) * r;
    double y = cos(t) * r;
    return { x,y,0 };
}
bool Circle::operator > (const Circle& E1) {
    return this->r > E1.r;
}
bool Circle::operator < (const Circle& E1) {
    return this->r < E1.r;
}
bool Circle::operator == (const Circle& E1) {
    return this->r == E1.r;
}
void Circle::print(std::ostream& out, double t) {
    Vector3D v = this->getVector3D(t);
    Point3D p = this->getPoint3D(t);
    std::string s;
    out.setf(std::ios_base::left);
    out.width(10);
    out << "Circle:";
    s = "center ( " + std::to_string(this->centreX) + " : " + std::to_string(this->centreY) + " )";
    out.width(45);
    out << s;
    s = "Radius = " + std::to_string(this->getR());
    out.width(60);
    out << s;
    s = "3D point ( " + std::to_string(p.x) + " : " + std::to_string(p.y) + " : " + std::to_string(p.z) + " )";
    out.width(60);
    out << s;
    s = "3D vector ( " + std::to_string(v.x) + " : " + std::to_string(v.y) + " : " + std::to_string(v.z) + " )";
    out.width(60);
    out << s << std::endl;
}
//Производный класс Helixe
Helixe::Helixe(double CentreX, double CentreY, double R, double Step) : Curve(Curve::CurveType::HELIXE) {
    r = R;
    step = Step;
    setCentrX(CentreX);
    setCentrY(CentreY);
};
void Helixe::setR(double R) {
    r = R;
}
double Helixe::getR() {
    return r;
}
void Helixe::setStep(double Step) {
    step = Step;
}
double Helixe::getStep() {
    return step;
}
Point3D Helixe::getPoint3D(double t) {
    double x = r * cos(t) + centreX;
    double y = r * sin(t) + centreY;
    double z = (step * t) / (2 * M_PI);
    return { x,y,z };
}
Vector3D Helixe::getVector3D(double t) {
    double x = -sin(t) * r;
    double y = cos(t) * r;
    double z = step / (2 * M_PI);
    return { x,y,z };
}
void Helixe::print(std::ostream& out, double t) {
    Vector3D v = this->getVector3D(t);
    Point3D p = this->getPoint3D(t);
    std::string s;
    out.setf(std::ios_base::left);
    out.width(10);
    out << "Helixe:";
    s = "center ( " + std::to_string(this->centreX) + " : " + std::to_string(this->centreY) + " )";
    out.width(45);
    out << s;
    s = "Radius = " + std::to_string(this->getR());
    out.width(30);
    out << s;
    s = "Step = " + std::to_string(this->getStep());
    out.width(30);
    out << s;
    s = "3D point ( " + std::to_string(p.x) + " : " + std::to_string(p.y) + " : " + std::to_string(p.z) + " )";
    out.width(60);
    out << s;
    s = "3D vector ( " + std::to_string(v.x) + " : " + std::to_string(v.y) + " : " + std::to_string(v.z) + " )";
    out.width(60);
    out << s << std::endl;
}
//Дополнительные функции
void randomCurveVector(std::vector<std::shared_ptr<curve::Curve>> & V, int n) {
    srand(time(NULL));
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
            V.push_back(std::make_shared<curve::Ellipse>(10, 15, 15, 20));
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
void foundCircleCurve( std::vector<std::shared_ptr<curve::Curve>> const& V1, std::vector<std::shared_ptr<curve::Circle>>& V2) {
    int counterCircle = 0;
    for (auto i = 0; i < V1.size(); i++) {
        if (V1[i]->getIdentifier() == curve::Curve::CurveType::CIRCLE) counterCircle++;
    }
    V2.clear();
    V2.reserve(counterCircle);
    for (auto i = 0; i < V1.size(); i++) {
        if (V1[i]->getIdentifier() == curve::Curve::CurveType::CIRCLE) {
            V2.push_back(std::dynamic_pointer_cast<curve::Circle>(V1[i]));
        }
    }
}
bool comp(std::shared_ptr<curve::Circle> V1, std::shared_ptr<curve::Circle> V2) {
    return *V1 < *V2;
}
void sortCircleByIncreasingRadius(std::vector<std::shared_ptr<curve::Circle>>& V) {
    std::sort(V.begin(), V.end(), comp);                //Сортировка в порядке возрастания радиусов.
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
void output3DDateToFile(std::vector<std::shared_ptr<curve::Curve>> const& V, double angleRad, std::string fileName) {
    std::ofstream outFile;
    outFile.open(fileName);
    if (!outFile) {
        std::wcerr << L"Не удалось открыть файл ";
        exit(1);
    }
    for (auto a : V) {
        a->print(outFile, angleRad);
    }
    outFile.close();
}
void output3DDateToFile(std::vector<std::shared_ptr<curve::Circle>> const& V, double angleRad, std::string fileName) {
    std::ofstream outFile;
    outFile.open(fileName);
    if (!outFile) {
        std::wcerr << L"Не удалось открыть файл ";
        exit(1);
    }
    for (auto a : V) {
        a->print(outFile, angleRad);
    }
    outFile << "\n-------------------------------------------------------------------------"
        "---------------------------------------------------------------------------"
        "---------------------------------------------------------------------------"
        << std::endl;
    outFile << "\nSum of the radii of the circles = " << sumRadius(V);
    outFile.close();
}
