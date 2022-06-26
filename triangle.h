//
// Created by Kun Huang on 2022/6/26.
//

#ifndef RASTERIZATION_DEMO_TRIANGLE_H
#define RASTERIZATION_DEMO_TRIANGLE_H

#include "math.h"

class Triangle {
public:
    Triangle(Vec2_f a, Vec2_f b, Vec2_f c) : m_a(a), m_b(b), m_c(c) {};

    template <size_t rows, size_t cols>
    void draw(Color (&image)[rows][cols]) {
        float A = fbc(m_a.x(), m_a.y());
        float B = fca(m_b.x(), m_b.y());
        float C = fab(m_c.x(), m_c.y());

        for (int y = (int)minY(); y <= (int)maxY(); ++y) {
            for (int x = (int)minX(); x <= (int)maxX(); ++x) {
                float a = fbc(x, y) / A;
                float b = fca(x, y) / B;
                // precision is not enough
                // float c = 1.0f - a - b;
                float c = fab(x, y) / C;

                if (a >= 0 && b >= 0 && c >=0) {
                    if ((a > 0 || A * fbc(-1, -1) > 0) &&
                        (b > 0 || B * fca(-1, -1) > 0) &&
                        (c > 0 || C * fab(-1, -1) > 0)
                    ) {
                        image[x][y] = Color (1, 0, 0);
                    }
                }
            }
        }
    }

    float minX() {
        float res = std::min(m_a.x(), m_b.x());
        res = std::min(res, m_c.x());
        return res;
    }

    float maxX() {
        float res = std::max(m_a.x(), m_b.x());
        res = std::max(res, m_c.x());
        return res;
    }

    float minY() {
        float res = std::min(m_a.y(), m_b.y());
        res = std::min(res, m_c.y());
        return res;
    }

    float maxY() {
        float res = std::max(m_a.y(), m_b.y());
        res = std::max(res, m_c.y());
        return res;
    }

private:
    float fab(float x, float y) {
        return (m_a.y() - m_b.y()) * x + (m_b.x() - m_a.x()) * y + m_a.x() * m_b.y() - m_a.y() * m_b.x();
    }

    float fbc(float x, float y) {
        return (m_b.y() - m_c.y()) * x + (m_c.x() - m_b.x()) * y + m_b.x() * m_c.y() - m_b.y() * m_c.x();
    }

    float fca(float x, float y) {
        return (m_c.y() - m_a.y()) * x + (m_a.x() - m_c.x()) * y + m_c.x() * m_a.y() - m_a.x() * m_c.y();
    }

private:
    Vec2_f m_a;
    Vec2_f m_b;
    Vec2_f m_c;
};

#endif //RASTERIZATION_DEMO_TRIANGLE_H
