//
// Created by Kun Huang on 2022/6/26.
//

#ifndef RASTERIZATION_DEMO_TRIANGLE_H
#define RASTERIZATION_DEMO_TRIANGLE_H

#include "math.h"

class Triangle {
public:
    Triangle(Vec2_f a, Vec2_f b, Vec2_f c, Color colors[3]) : m_a(a), m_b(b), m_c(c) {
        m_colors = colors;
    };

    template <size_t rows, size_t cols>
    void draw(Color (&image)[rows][cols]) {
        float A = fbc(m_a.x(), m_a.y());
        float B = fca(m_b.x(), m_b.y());
        float C = fab(m_c.x(), m_c.y());

        float aNBase = fbc(minX(), minY());
        float bNBase = fca(minX(), minY());
        float cNBase = fab(minX(), minY());

        float aN = aNBase;
        float bN = bNBase;
        float cN = cNBase;

        float fbcA = (m_b.y() - m_c.y());
        float fcaA = (m_c.y() - m_a.y());
        float fabA = (m_a.y() - m_b.y());

        float fbcB = (m_c.x() - m_b.x());
        float fcaB = (m_a.x() - m_c.x());
        float fabB = (m_b.x() - m_a.x());

        for (int y = (int)minY(); y <= (int)maxY(); ++y) {
            for (int x = (int)minX(); x <= (int)maxX(); ++x) {
//                float a = fbc(x, y) / A;
//                float b = fca(x, y) / B;
//                // precision is not enough
//                // float c = 1.0f - a - b;
//                float c = fab(x, y) / C;

                float a = aN / A;
                float b = bN / B;
                float c = cN / C;

                if (a >= 0 && b >= 0 && c >=0) {
                    if ((a > 0 || A * fbc(-1, -1) > 0) &&
                        (b > 0 || B * fca(-1, -1) > 0) &&
                        (c > 0 || C * fab(-1, -1) > 0)
                    ) {
                        image[x][y] = color_a() * a + color_b() * b + color_c() * c;
                    }
                }

                aN += fbcA;
                bN += fcaA;
                cN += fabA;
            }
            aN = aNBase + (y - minY()) * fbcB;
            bN = bNBase + (y - minY()) * fcaB;
            cN = cNBase + (y - minY()) * fabB;
        }
    }

    Color color_a() {
        return m_colors[0];
    }

    Color color_b() {
        return m_colors[1];
    }

    Color color_c() {
        return m_colors[2];
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
    Color *m_colors;
};

#endif //RASTERIZATION_DEMO_TRIANGLE_H
