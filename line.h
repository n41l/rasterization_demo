//
// Created by Kun Huang on 2022/6/26.
//

#ifndef RASTERIZATION_DEMO_LINE_H
#define RASTERIZATION_DEMO_LINE_H

#include "math.h"

class Line {
public:
    Line(Vec2<int> const &start, Vec2<int> const &end): m_start(start), m_end(end) {};

    float slop() {
        return (float)(m_end.y() - m_start.y()) / (float)(m_end.x() - m_start.x());
    }

    template <size_t rows, size_t cols>
    void draw(Color (&image)[rows][cols]) {
        float s = slop();

        if (s > 0 && s <= 1) {
            int y = m_start.y();
            float d = dValue(m_start.x() + 1, y + 0.5);
            for (int x = m_start.x(); x <= m_end.x(); ++x) {
                image[x][y] = Color(1, 0, 0);
                if (d < 0) {
                    y = y + 1;
                    d = d + (m_end.x() - m_start.x()) + (m_start.y() - m_end.y());
                } else {
                    d = d + (m_start.y() - m_end.y());
                }
            }
        } else if (s > 1 && s <= std::numeric_limits<float>::max()) {
            int x = m_start.x();
            float d = dValue(m_start.x() + 0.5, m_start.y() + 1);
            for (int y = m_start.y(); y <= m_end.y(); ++y) {
                image[x][y] = Color(1, 0, 0);
                if (d > 0) {
                    x = x + 1;
                    d = d + (m_end.x() - m_start.x()) + (m_start.y() - m_end.y());
                } else {
                    d = d + (m_end.x() - m_start.x());
                }
            }
        } else if (s > -1 && s <= 0) {
            int y = m_start.y();
            float d = dValue(m_start.x() + 1, y - 0.5);
            for (int x = m_start.x(); x <= m_end.x(); ++x) {
                image[x][y] = Color(1, 0, 0);
                if (d > 0) {
                    y = y - 1;
                    d = d - (m_end.x() - m_start.x()) + (m_start.y() - m_end.y());
                } else {
                    d = d + (m_start.y() - m_end.y());
                }
            }
        } else {
            int x = m_start.x();
            float d = dValue(m_start.x() - 0.5, m_start.y() + 1);
            for (int y = m_start.y(); y <= m_end.y(); ++y) {
                image[x][y] = Color(1, 0, 0);
                if (d < 0) {
                    x = x - 1;
                    d = d + (m_end.x() - m_start.x()) - (m_start.y() - m_end.y());
                } else {
                    d = d + (m_end.x() - m_start.x());
                }
            }
        }
    }

private:
    float dValue(float x, float y) {
        return (float)(m_start.y() - m_end.y()) * x + (float)(m_end.x() - m_start.x()) * y + m_start.x() * m_end.y() - m_end.x() * m_start.y();
    }

private:
    Vec2<int> m_start;
    Vec2<int> m_end;
};

#endif //RASTERIZATION_DEMO_LINE_H
