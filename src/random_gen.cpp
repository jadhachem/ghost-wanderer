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
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <map>
#include <random>
#include <chrono>

namespace rnd {

void rand_init() {
	std::srand( std::time( NULL ) );
}

double uniform() {
	return (std::rand()+0.0) / RAND_MAX;
}

namespace {
	std::pair<double,double> box_muller() {
		double u = uniform();
		double v = uniform();

		double r  = std::sqrt( -2 * std::log(u) );
		double th = 2 * M_PI * v;
		double z1 = r * cos(th);
		double z2 = r * sin(th);

		return std::make_pair(z1,z2);
	}
}

int uniformDiscrete(int N) {
	return static_cast<int>( uniform()*N );
}
int uniformDiscrete(int a, int b) {
	return ( a + uniformDiscrete(b-a) );
}

double normal() {
	static bool generated = false;
	static double next = 0.0;
	
	if(generated)
		return next;
	else {
		std::pair<double,double> bm = box_muller();
		next = bm.second;
		return bm.first;
	}
}

double normal(double mean, double stdev) {
	return ( mean + normal() * stdev );
}

double chi_squared() {
	std::pair<double,double> bm = box_muller();
	return bm.first*bm.first+bm.second*bm.second;
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

