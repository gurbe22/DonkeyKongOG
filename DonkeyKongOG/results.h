#ifndef RESULTS_H
#define RESULTS_H

#include <list>
#include <string>

class Results
{
public:
    // Enum representing possible result values for a game iteration
    enum ResultValue { victory, wonLevel, disqualified, lose, noResult };

private:
    // List of results, each stored as a pair of iteration number and result value
    std::list<std::pair<size_t, ResultValue>> results;

public:
    // Static method to load results from a file
    static Results loadResults(const std::string& filename);

    // Method to save results to a file
    void saveResults(const std::string& filename) const;

    // Method to add a result to the results list
    void addResult(size_t iteration, ResultValue result) {
        results.push_back({ iteration, result });
    }

    // Method to pop the first result from the list and return it
    std::pair<size_t, ResultValue> popResult() {
        if (results.empty()) return { 0, Results::noResult };
        auto result = results.front();
        results.pop_front();
        return result;
    }

    // Method to check if the game was finished by a specific iteration
    bool isFinishedBy(size_t iteration) const {
        return results.empty() || results.back().first < iteration;
    }

    // Method to get the next iteration where a disqualification occurred
    size_t getNextDisqualificationIteration() const;
};

#endif
