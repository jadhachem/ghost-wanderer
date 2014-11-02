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

#include "random_gen.hpp"
#include <random>
#include <chrono>

namespace rnd {

namespace {
	std::mt19937 mt;
}

void rand_init() {
	mt.seed( std::chrono::high_resolution_clock::now()
						.time_since_epoch().count()
			);
}

double uniform() {
	static std::uniform_real_distribution<double> unif(0.0,1.0);
	return unif(mt);
}

int uniformDiscrete(int N) {
	return static_cast<int>( uniform()*N );
}
int uniformDiscrete(int a, int b) {
	return ( a + uniformDiscrete(b-a) );
}

double normal() {
	static std::normal_distribution<double> norm(0.0,1.0);
	return norm(mt);
}

double normal(double mean, double stdev) {
	return ( mean + normal() * stdev );
}

double chi_squared() {
	double x = normal();
	return x*x;
}

int poisson(double rate) {
	double L = std::exp(-rate);
	int k = 0;
	double p = 1.0;
	do {
		k++;
		p *= uniform();
	} while(p>L);
	return k-1;
}

bool bernoulli(double p) {
	return (uniform()<p);
}

int binomial(int n, double p) {
	int k = 0;
	for(int i=0; i<n; i++)
		k += bernoulli(p)?1:0;
	return k;
}

} // namespace rnd

