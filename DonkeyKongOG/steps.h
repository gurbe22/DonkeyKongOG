#ifndef STEPS_H
#define STEPS_H

#include <list>
#include <string>

class Steps
{
    long randomSeed = 0;  // Random seed used for generating steps
    std::list<std::pair<size_t, char>> steps;  // List of steps, each with iteration and step character
public:
    // Static method to load steps from a file and return them as a Steps object
    static Steps loadSteps(const std::string& filename);

    // Method to save the steps to a file
    void saveSteps(const std::string& filename) const;

    // Getter for the random seed
    long getRandomSeed() const {
        return randomSeed;
    }

    // Setter for the random seed
    void setRandomSeed(long seed) {
        randomSeed = seed;
    }

    // Add a step to the steps list
    void addStep(size_t iteration, char step) {
        steps.push_back({ iteration, step });
    }

    // Check if the next step is on a specific iteration
    bool isNextStepOnIteration(size_t iteration) const {
        return !steps.empty() && steps.front().first == iteration;
    }

    // Pop and return the first step from the list
    char popStep() {
        if (steps.empty()) {
            return '\0';  // Return a neutral value when no steps are available
        }
        char step = steps.front().second;  // Get the step character
        steps.pop_front();  // Remove the step from the list
        return step;
    }
};

#endif
