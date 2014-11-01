#ifndef _RANDOM_GEN_HPP_
#define _RANDOM_GEN_HPP_

/**
 * Contains utility functions for random number generation.
 * Uses the std::rand() function in the background.
 * TODO Use Mersenne twister algorithm from C++11
 */
namespace rnd {

/**
 * Initializes the seed
 */
void rand_init();

/**
 * Returns a continuous uniform random variable in
 * the interval [a,b], which is [0,1] by default
 */
double uniform();
double uniform(double a, double b);

/**
 * Returns a discrete uniform random variable in the
 * interval {a,...,b-1}, or {0,1,...,N-1} by default
 */
int uniformDiscrete(int N);
int uniformDiscrete(int a, int b);

/**
 * Returns a normal random variable. Default: standard normal
 */
double normal();
double normal(double mean, double stdev);

/**
 * Returns a chi-squared distributed random variable
 */
double chi_squared();

/**
 * Returns a Poisson random variable with the specified rate
 */
int poisson(double rate);

/**
 * Returns a Bernoulli random variable with parameter p
 */
bool bernoulli(double p);
/**
 * Returns a binomial random variable with parameters n and p
 */
int binomial(int n, double p);


} // namespace rnd

#endif // _RANDOM_GEN_HPP_
