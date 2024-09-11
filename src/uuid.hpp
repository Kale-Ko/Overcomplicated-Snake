#ifndef SNAKE_UUIDH
#define SNAKE_UUIDH

#include <random>

namespace Snake
{
    struct UUID
    {
        unsigned long upper;
        unsigned long lower;
    };

    static std::random_device randomDevice;
    static std::default_random_engine randomEngine = std::default_random_engine(randomDevice());

    static std::uniform_int_distribution<unsigned int> intDistribution(0U, 4294967295U);
    static std::uniform_int_distribution<unsigned long> longDistribution(0UL, 18446744073709551615UL);

    static std::uniform_real_distribution<float> floatDistribution(0.0, 1.0);
    static std::uniform_real_distribution<double> doubleDistribution(0.0, 1.0);

    static inline unsigned int randomInt()
    {
        return intDistribution(randomEngine);
    }

    static inline unsigned long randomLong()
    {
        return longDistribution(randomEngine);
    }

    static inline double randomFloat()
    {
        return floatDistribution(randomEngine);
    }

    static inline double randomDouble()
    {
        return doubleDistribution(randomEngine);
    }

    static inline UUID* randomUuid()
    {
        unsigned long upper = randomLong();
        unsigned long lower = randomLong();

        return new UUID{ .upper = upper, .lower = lower };
    }

    static inline void deleteUuid(UUID* uuid)
    {
        delete uuid;
    }
};
#endif