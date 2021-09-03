#include "Core/Math/Random.hpp"
using namespace Scramble;

Random::Random(U32 seed)
{
    this->generator = std::default_random_engine(seed);

    this->probablityDistributor = std::bernoulli_distribution(prob);
    this->integerDistributor = std::uniform_int_distribution<int>((int)min, (int)max);
    this->floatDistributor = std::uniform_real_distribution<float>(min, max);
}

void Random::Prob(F32 value)
{
    this->prob = value;
    
    this->probablityDistributor = std::bernoulli_distribution(prob);
}
void Random::Min(F32 value)
{
    this->min = value;

    this->integerDistributor = std::uniform_int_distribution<int>((int)min, (int)max);
    this->floatDistributor = std::uniform_real_distribution<float>(min, max);
}
void Random::Max(F32 value)
{
    this->max = value;
    
    this->integerDistributor = std::uniform_int_distribution<int>((int)min, (int)max);
    this->floatDistributor = std::uniform_real_distribution<float>(min, max);
}

bool Random::Value()
{
    return this->probablityDistributor(this->generator);
}

I32 Random::IntRange()
{
    return this->integerDistributor(this->generator);
}
F32 Random::FloatRange()
{
    return this->floatDistributor(this->generator);
}
