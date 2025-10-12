#pragma once
#include<stdexcept>
#include<vector>

namespace Engine2D 
{
    template<typename T>
    struct MinMax
    {
        T min;
        T max;
    };

    template<typename T>
    T clamp(T val, T min, T max);
    
    template<typename T>
    T min(T val1, T val2);

    template<typename T>
    T min(std::vector<T> values);
    
    template<typename T>
    T max(T val1, T val2);

    template<typename T>
    T max(std::vector<T> values);

    template<typename T>
    MinMax<T> getMinMax(std::vector<T> values);

    template <typename T>
    T clamp(T val, T min, T max)
    {
        if(min > max) throw new std::runtime_error("min is lager then max");
        if(val > max) return max;
        if(val < min) return min;
    }

    template <typename T>
    T min(T val1, T val2)
    {
        if(val1 < val2) return val1;
        return val2;
    }

    template <typename T>
    T min(std::vector<T> values)
    {
        T _min = values[0];

        for(size_t i = 1; i < values.size(); ++i)
        {
            _min = _min > values[i] ? values[i] : _min;
        }
        return _min;
    }

    template <typename T>
    T max(T val1, T val2)
    {
        if(val1 > val2) return val1;
        return val2;
    }

    template <typename T>
    T max(std::vector<T> values)
    {
        T _max = values[0];

        for(size_t i = 1; i < values.size(); ++i)
        {
            _max = _max < values[i] ? values[i] : _max;
        }
        return _max;
    }

    template <typename T>
    MinMax<T> getMinMax(std::vector<T> values)
    {
        MinMax<T> minmax;
        minmax.min = values[0];
        minmax.max = values[0];

        for(size_t i = 1; i < values.size(); ++i)
        {
            minmax.min = minmax.min > values[i] ? values[i] : minmax.min;
            minmax.max = minmax.max < values[i] ? values[i] : minmax.max;
        }
        return minmax;
    }
};