//
// Created by Kun Huang on 2022/6/26.
//

#ifndef RASTERIZATION_DEMO_MATH_H
#define RASTERIZATION_DEMO_MATH_H

template <typename T>
class Vec2 {
public:
    T x() const { return m_v[0]; }
    T y() const { return m_v[1]; }

    Vec2() {};

    Vec2(T x, T y) {
        m_v[0] = x;
        m_v[1] = y;
    };

    Vec2 operator + (Vec2 const &other) {
        return Vec2(x() + other.x(), y() + other.y());
    }

    Vec2 operator - (Vec2 const &other) {
        return Vec2(x() - other.x(), y() - other.y());
    }

    Vec2 operator * (float scaling) {
        return Vec2(x() * scaling, y() * scaling);
    }

    T dot(Vec2 const &other) {
        return x() * other.x() + y() * other.y();
    }

    T cross(Vec2 const &other) {
        return x() * other.y() - y() * other.x();
    }

private:
    T m_v[2];
};

using Vec2_f = Vec2<float>;

template <typename T>
class Vec3 {
public:
    T x() const { return m_v[0]; }
    T y() const { return m_v[1]; }
    T z() const { return m_v[2]; }

    Vec3() {};

    Vec3(T x, T y, T z) {
        m_v[0] = x;
        m_v[1] = y;
        m_v[2] = z;
    };

    Vec3 operator + (Vec3 const &other) {
        return Vec3(x() + other.x(), y() + other.y(), z() + other.z());
    }

    Vec3 operator - (Vec3 const &other) {
        return Vec3(x() - other.x(), y() - other.y(), z() - other.z());
    }

    Vec3 operator * (float scaling) {
        return Vec3(x() * scaling, y() * scaling, z() * scaling);
    }

    T dot(Vec3 const &other) {
        return x() * other.x() + y() * other.y() + z() * other.z();
    }

    Vec3 cross(Vec3 const &other) {
        return Vec3(
                y() * other.z() - z() * other.y(),
                z() * other.x() - x() * other.z(),
                x() * other.y() - y() * other.x()
                );
    }

private:
    T m_v[3];
};

using Color = Vec3<float>;

#endif //RASTERIZATION_DEMO_MATH_H
