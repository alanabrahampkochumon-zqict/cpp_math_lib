#pragma once

namespace math
{
    class Vector3D
    {
    public:
        Vector3D();
        Vector3D(float v1, float v2, float v3);

    private:
        float v1, v2, v3;
    };
}

#include "Vector3D.tpp"