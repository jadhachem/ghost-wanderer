/**
 * Copyright (C) 2014 Jad Hachem <jad.hachem@gmail.com>
 * 
 * This file is part of Ghost Wanderer.
 * 
 * Ghost Wanderer is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Ghost Wanderer is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
