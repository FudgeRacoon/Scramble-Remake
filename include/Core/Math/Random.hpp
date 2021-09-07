#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

#include "../Common/Types.hpp"

namespace Scramble
{
    class Random
    {
    private:
        std::default_random_engine generator;

    private:
        std::bernoulli_distribution probablityDistributor;
        std::uniform_int_distribution<int> integerDistributor;
        std::uniform_real_distribution<float> floatDistributor;

    private:
        F32 prob = 0.5;
        F32 min = 0.0, max = 100.0;

    public:
        Random(F64 seed);

    public:
        void Prob(F32 value);
        void Min(F32 value);
        void Max(F32 value);

    public:
        bool Value();

    public:
        I32 IntRange();
        F32 FloatRange();
    };
}

#endif