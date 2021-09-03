#include "Core/Math/Matrix4.hpp"
using namespace Scramble;

Matrix4::Matrix4()
{
    this->data = new float[16];

    memset(this->data, 0, 16 * sizeof(float));
}
Matrix4::Matrix4(Vector4 r0, Vector4 r1, Vector4 r2, Vector4 r3)
{
    this->data = new float[16];

    (*this)(0,0) = r0.x; (*this)(0,1) = r0.y; (*this)(0,2) = r0.z; (*this)(0,3) = r0.w;
    (*this)(1,0) = r1.x; (*this)(1,1) = r1.y; (*this)(1,2) = r1.z; (*this)(1,3) = r1.w;
    (*this)(2,0) = r2.x; (*this)(2,1) = r2.y; (*this)(2,2) = r2.z; (*this)(2,3) = r2.w;
    (*this)(3,0) = r3.x; (*this)(3,1) = r3.y; (*this)(3,2) = r3.z; (*this)(3,3) = r3.w;
}
Matrix4::Matrix4(const Matrix4& m)
{
    this->data = new float[16];
    
    memcpy(this->data, m.data, 16 * sizeof(float));
}
Matrix4::Matrix4(Matrix4&& m)
{
    this->data = m.data;
    m.data = nullptr;
}

Matrix4::~Matrix4()
{
    delete[] this->data;
}

Matrix4 Matrix4::operator =(Matrix4 m)
{
    memcpy(this->data, m.data, 16 * sizeof(float));
    
    return *this;
}
float& Matrix4::operator ()(int row, int column)
{
    return this->data[(4 * row) + column];
}

Matrix4 Matrix4::operator *(Matrix4 m)
{
    return Matrix4
    (
        Vector4(
            (*this)(0,0) * m(0,0) + (*this)(0,1) * m(1,0) + (*this)(0,2) * m(2,0) + (*this)(0,3) * m(3,0),
            (*this)(0,0) * m(0,1) + (*this)(0,1) * m(1,1) + (*this)(0,2) * m(2,1) + (*this)(0,3) * m(3,1),
            (*this)(0,0) * m(0,2) + (*this)(0,1) * m(1,2) + (*this)(0,2) * m(2,2) + (*this)(0,3) * m(3,2),
            (*this)(0,0) * m(0,3) + (*this)(0,1) * m(1,3) + (*this)(0,2) * m(2,3) + (*this)(0,3) * m(3,3)
        ),
        Vector4(
            (*this)(1,0) * m(0,0) + (*this)(1,1) * m(1,0) + (*this)(1,2) * m(2,0) + (*this)(1,3) * m(3,0),
            (*this)(1,0) * m(0,1) + (*this)(1,1) * m(1,1) + (*this)(1,2) * m(2,1) + (*this)(1,3) * m(3,1),
            (*this)(1,0) * m(0,2) + (*this)(1,1) * m(1,2) + (*this)(1,2) * m(2,2) + (*this)(1,3) * m(3,2),
            (*this)(1,0) * m(0,3) + (*this)(1,1) * m(1,3) + (*this)(1,2) * m(2,3) + (*this)(1,3) * m(3,3)
        ),
        Vector4(
            (*this)(2,0) * m(0,0) + (*this)(2,1) * m(1,0) + (*this)(2,2) * m(2,0) + (*this)(2,3) * m(3,0),
            (*this)(2,0) * m(0,1) + (*this)(2,1) * m(1,1) + (*this)(2,2) * m(2,1) + (*this)(2,3) * m(3,1),
            (*this)(2,0) * m(0,2) + (*this)(2,1) * m(1,2) + (*this)(2,2) * m(2,2) + (*this)(2,3) * m(3,2),
            (*this)(2,0) * m(0,3) + (*this)(2,1) * m(1,3) + (*this)(2,2) * m(2,3) + (*this)(2,3) * m(3,3)
        ),
        Vector4(
            (*this)(3,0) * m(0,0) + (*this)(3,1) * m(1,0) + (*this)(3,2) * m(2,0) + (*this)(3,3) * m(3,0),
            (*this)(3,0) * m(0,1) + (*this)(3,1) * m(1,1) + (*this)(3,2) * m(2,1) + (*this)(3,3) * m(3,1),
            (*this)(3,0) * m(0,2) + (*this)(3,1) * m(1,2) + (*this)(3,2) * m(2,2) + (*this)(3,3) * m(3,2),
            (*this)(3,0) * m(0,3) + (*this)(3,1) * m(1,3) + (*this)(3,2) * m(2,3) + (*this)(3,3) * m(3,3)
        )
    );
}
Vector4 Matrix4::operator *(Vector4 v)
{
    return Vector4
    (
        (*this)(0,0) * v.x + (*this)(0,1) * v.y + (*this)(0,2) * v.z + (*this)(0,3) * v.w,
        (*this)(1,0) * v.x + (*this)(1,1) * v.y + (*this)(1,2) * v.z + (*this)(1,3) * v.w,
        (*this)(2,0) * v.x + (*this)(2,1) * v.y + (*this)(2,2) * v.z + (*this)(2,3) * v.w,
        (*this)(3,0) * v.x + (*this)(3,1) * v.y + (*this)(3,2) * v.z + (*this)(3,3) * v.w
    );
}

const float* Matrix4::GetRawData()
{
    return this->data;
}

Matrix4 Matrix4::Identity()
{
    return Matrix4(
        Vector4(1, 0, 0, 0),
        Vector4(0, 1, 0, 0),
        Vector4(0, 0, 1, 0),
        Vector4(0, 0, 0, 1)
    );
}
Matrix4 Matrix4::Inverse(Matrix4 m)
{
    Matrix4 mat = Identity();

    for(int column = 0; column < 4; column++) 
    { 
        if(m(column,column) == 0) 
        { 
            int big = column; 

            for(int row = 0; row < 4; row++)
                if(Math::Abs(m(row,column)) > Math::Abs(m(big,column))) 
                    big = row;
            
            if(big != column)
                for(int j = 0; j < 4; ++j)
                {
                    Utils::Swap<float>(&m(column,j), &m(big,j)); 
                    Utils::Swap<float>(&mat(column,j), &mat(big,j));
                } 
        }  
    
        for (int row = 0; row < 4; row++) 
        { 
            if(row != column) 
            { 
                float coeff = m(row,column) / m(column,column); 

                if (coeff != 0) 
                { 
                    for (int j = 0; j < 4; j++) 
                    { 
                        m(row,j) -= coeff * m(column,j); 
                        mat(row,j) -= coeff * mat(column,j); 
                    } 
                    
                    m(row,column) = 0; 
                } 
            } 
        }
    } 

    for(int row = 0; row < 4; row++) 
        for(int column = 0; column < 4; column++) 
            mat(row,column) /= m(row,row);

    return mat;
}

Matrix4 Matrix4::Transalte(Vector3 translate)
{
    Matrix4 m = Identity();

    m(0,3) = translate.x;
    m(1,3) = translate.y;
    m(2,3) = translate.z;

    return m;
}
Matrix4 Matrix4::Scale(Vector3 scale)
{
    Matrix4 m = Identity();

    m(0,0) = scale.x;
    m(1,1) = scale.y;
    m(2,2) = scale.z;

    return m;
}
Matrix4 Matrix4::Rotate(float angle, Vector3 axis)
{
    Matrix4 m = Identity();

    if(axis.x == 1.0f && axis.y == 0.0f && axis.z == 0.0f)
    {
        m(1,1) = cos(angle);
        m(1,2) = sin(angle);
        m(2,1) = -sin(angle);
        m(2,2) = cos(angle);
    }
    else if(axis.x == 0.0f && axis.y == 1.0f && axis.z == 0.0f)
    {
        m(0,0) = cos(angle);
        m(0,2) = -sin(angle);
        m(2,0) = sin(angle);
        m(2,2) = cos(angle);
    }
    else if(axis.x == 0.0f && axis.y == 0.0f, axis.z == -1.0f)
    {
        m(0,0) = cos(angle);
        m(0,1) = -sin(angle);
        m(1,0) = sin(angle);
        m(1,1) = cos(angle);
    }

    return m;
}
Matrix4 Matrix4::Transform(Vector3 translate, Vector3 scale, Vector3 rotation)
{
    Matrix4 m = Identity();

    m = m * Transalte(translate);
    m = m * Rotate(rotation.x, Vector3::Right);
    m = m * Rotate(rotation.y, Vector3::Up);
    m = m * Rotate(rotation.z, Vector3::Forward);
    m = m * Scale(scale);

    return m;
}

Matrix4 Matrix4::LookAt(Vector3 position, Vector3 target, Vector3 up)
{
    Vector3 z = Vector3::Normalize(target - position);
    Vector3 x = Vector3::Normalize(Vector3::Cross(z, up));
    Vector3 y = Vector3::Normalize(Vector3::Cross(x, z));

    z = Vector3::Negate(z);

    return Matrix4
    (
        Vector4(
            x.x, x.y, x.z, -Vector3::Dot(x, position)
        ),
        Vector4(
            y.x, y.y, y.z, -Vector3::Dot(y, position)
        ),
        Vector4(
            z.x, z.y, z.z, -Vector3::Dot(z, position)
        ),
        Vector4(
            0  , 0  , 0  , 1
        )
    );  
}
Matrix4 Matrix4::Orthographic(float left, float right, float bottom, float top, float near, float far)
{
    Matrix4 m = Identity();

    float xOut = 2 / (right - left);
    float yOut = 2 / (top - bottom);
    float zOut = 2 / (far - near);

    float tx = -(right + left) / (right - left);
    float ty = -(top + bottom) / (top - bottom);
    float tz = -(far + near) / (far - near);

    m(0,0) = xOut;
    m(1,1) = yOut;
    m(2,2) = zOut;
    m(0,3) = tx;
    m(1,3) = ty;
    m(2,3) = tz;

    return m;
}