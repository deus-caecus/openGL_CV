#include "pixelTool.h"

static bool isInside(Point p, EdgeType edge, Point clipMin, Point clipMax) {
    switch (edge) {
    case EdgeType::Left:
        return p.x >= clipMin.x;
    case EdgeType::Right:
        return p.x <= clipMax.x;
    case EdgeType::Bottom:
        return p.y >= clipMin.y;
    case EdgeType::Top:
        return p.y <= clipMax.y;
    }
    return false; // Should never reach here
}

static Point intersection(Point p1, Point p2, EdgeType edge, Point clipMin, Point clipMax) {
    Point result;
    switch (edge) {
    case EdgeType::Left:
        result.y = p1.y + (p2.y - p1.y) * (clipMin.x - p1.x) / (p2.x - p1.x);
        result.x = clipMin.x;
        break;
    case EdgeType::Right:
        result.y = p1.y + (p2.y - p1.y) * (clipMax.x - p1.x) / (p2.x - p1.x);
        result.x = clipMax.x;
        break;
    case EdgeType::Bottom:
        result.x = p1.x + (p2.x - p1.x) * (clipMin.y - p1.y) / (p2.y - p1.y);
        result.y = clipMin.y;
        break;
    case EdgeType::Top:
        result.x = p1.x + (p2.x - p1.x) * (clipMax.y - p1.y) / (p2.y - p1.y);
        result.y = clipMax.y;
        break;
    }
    return result;
}

std::vector<Point> sutherlandHodgman(std::vector<Point> polygon, Point clipMin, Point clipMax) 
{
    std::vector<EdgeType> edges = { EdgeType::Left, EdgeType::Right, EdgeType::Bottom, EdgeType::Top };
    std::vector<Point> output = polygon;

    for (auto edge : edges) {
        std::vector<Point> input = output;
        output.clear();
        size_t n = input.size();

        for (size_t i = 0; i < n; ++i) {
            Point p1 = input[i];
            Point p2 = input[(i + 1) % n];

            bool inside1 = isInside(p1, edge, clipMin, clipMax);
            bool inside2 = isInside(p2, edge, clipMin, clipMax);

            if (inside1 && inside2) {
                output.push_back(p2);
            }
            else if (inside1 && !inside2) {
                output.push_back(intersection(p1, p2, edge, clipMin, clipMax));
            }
            else if (!inside1 && inside2) {
                output.push_back(intersection(p1, p2, edge, clipMin, clipMax));
                output.push_back(p2);
            }
        }
    }
    return output;
}

int sutherlandHodgmanMain() {
    std::vector<Point> polygon = { Point(50, 150), Point(200, 50), Point(350, 150), Point(200, 250) };
    Point clipMin(100, 100);
    Point clipMax(300, 300);

    std::vector<Point> clippedPolygon = sutherlandHodgman(polygon, clipMin, clipMax);

    std::cout << "Clipped Polygon Vertices:" << std::endl;
    for (const auto& point : polygon)
    {
        std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
    }

    std::cout << "clipMin:" << clipMin.x << "," << clipMin.y << std::endl;
    std::cout << "clipMax:" << clipMax.x << "," << clipMax.y << std::endl;

    for (const auto& point : clippedPolygon)
    {
        std::cout << "(" << point.x << ", " << point.y << ")" << std::endl;
    }

    return 0;
}