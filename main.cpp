#include <random>
#include <iostream>
#include <cstdint>
#include <utility>
#include <tuple>

const auto accumulate = [](size_t n, auto distribution) {
	double sum;
	for(auto i = 0; i != n; ++i) {
		sum += distribution();
	}
	return std::make_tuple(sum/n);
};

bool within(double low, double value, double high) {
	return low < value && value < high;
}

bool near(double target, double value, double abserror = 1.0e-1) {
	return within(target - abserror, value, target + abserror);
}

bool testDefaultEngine() {
	std::random_device r;
	std::default_random_engine engine(r());
	std::uniform_real_distribution<double> uniform;
	
	const auto result = accumulate(100000, [=] () mutable { return uniform(engine);});
	if (!near(0.5, std::get<0>(result))) {
		std::cerr << "mean value expected to be near 0.5: " << std::get<0>(result) << std::endl;
		return false;
	} else return true;
}

int main(int argc, char**args) {
	return testDefaultEngine()
		? 0
		: -1;
}
