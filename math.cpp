#include "math.hpp"

float Engine2D::clamp(float val, float min, float max)
{
    if(min > max) throw std::runtime_error("min is lager then max");
    if(val > max) return max;
    if(val < min) return min;
}

float Engine2D::min(float val1, float val2)
{
    if(val1 < val2) return val1;
    return val2;
}
float Engine2D::max(float val1, float val2)
{
    if(val1 > val2) return val1;
    return val2;
}
