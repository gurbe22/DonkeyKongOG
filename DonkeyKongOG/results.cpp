#include "results.h"
#include <limits>
#include <fstream>
using namespace std;

Results Results::loadResults(const std::string& filename) {
	std::ifstream results_file(filename);
	Results results;
	if (!results_file) {
		throw std::runtime_error("Failed to open results file: " + filename);
	}
	size_t size;
	results_file >> size;
	while (!results_file.eof() && size-- != 0) {
		size_t iteration;
		int result;
		results_file >> iteration >> result;
		results.addResult(iteration, static_cast<ResultValue>(result));
	}
	return results;
}

void Results::saveResults(const std::string& filename) const {
	std::ofstream results_file(filename);
	results_file << results.size();
	for (const auto& result : results) {
		results_file << '\n' << result.first << ' ' << result.second;
	}
	results_file.close();
}

size_t Results::getNextDisqualificationIteration() const {
	if (!results.empty() && results.front().second == disqualified) {
		return results.front().first;
	}
	else return std::numeric_limits<size_t>::max(); // a big number we will never reach
}
