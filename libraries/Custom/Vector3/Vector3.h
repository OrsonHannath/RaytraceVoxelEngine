//
// Created by User on 3/07/2023.
//

#ifndef ADVANCEDVOXELENGINE_VECTOR3_H
#define ADVANCEDVOXELENGINE_VECTOR3_H

#include <string>
#include <sstream>

template <typename T>
class Vector3 {
private:
    T x = 0;
    T y = 0;
    T z = 0;
public:
    Vector3() = default;
    Vector3(T x_, T y_, T z_){x = x_; y = y_; z = z_;};

    void SetX(T value){x = value;};
    void SetY(T value){y = value;};
    void SetZ(T value){z = value;};
    void SetXYZ(T x_, T y_, T z_){x = x_; y = y_; z = z_;};

    T GetX(){return x;};
    T GetY(){return y;};
    T GetZ(){return z;};

    std::string ToString(){
        return "x: " + tostring(this->GetX()) + ", " + "y: " + tostring(this->GetY()) + ", " + "z: " + tostring(this->GetZ());
    };

    void Minus(Vector3<T> vec){
        this->SetXYZ(this->GetX() - vec.GetX(), this->GetY() - vec.GetY(), this->GetZ() - vec.GetZ());
    };

    void Plus(Vector3<T> vec){
        this->SetXYZ(this->GetX() + vec.GetX(), this->GetY() + vec.GetY(), this->GetZ() + vec.GetZ());
    };

    void Multiply(Vector3<T> vec){
        this->SetXYZ(this->GetX() * vec.GetX(), this->GetY() * vec.GetY(), this->GetZ() * vec.GetZ());
    };

    Vector3 operator * (const Vector3<T>& vec){

        return Vector3<T>(this->GetX() * vec.GetX(), this->GetY() * vec.GetY(), this->GetZ() * vec.GetZ());
    };

    Vector3 operator + (const Vector3<T>& vec){

        return Vector3<T>(this->GetX() + vec.GetX(), this->GetY() + vec.GetY(), this->GetZ() + vec.GetZ());
    };

    Vector3 operator - (const Vector3<T>& vec){

        return Vector3<T>(this->GetX() - vec.GetX(), this->GetY() - vec.GetY(), this->GetZ() - vec.GetZ());
    };

    std::string tostring(const T& t) {
        std::ostringstream os;
        os << t;
        return os.str();
    }
};


#endif //ADVANCEDVOXELENGINE_VECTOR3_H
