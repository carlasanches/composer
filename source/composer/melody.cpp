//
// Created by Alan Freitas on 12/14/20.
//

#include "melody.h"

namespace composer {

    std::default_random_engine melody::generator_ = std::default_random_engine(std::chrono::system_clock::now().time_since_epoch().count());

    melody::melody(const size_t &problem_size, const size_t &individual_size)
    : melody_(problem_size)
    {
        for (size_t i = 0; i < problem_size; ++i) {
            this->melody_[i] = create_individual(individual_size);
        }
    }

    void melody::display() {

        std::cout << "Melody" << std::endl;

        for (const std::vector<int> &measure : this->melody_) {
            for (const int &note : measure) {
                std::cout << note << " ";
            }
            std::cout << std::endl;
        }
    }

    std::vector<int> melody::create_individual(const size_t &individual_size) {
        std::vector<int> measure(individual_size);

        std::generate(measure.begin(), measure.end(), []() {
            std::uniform_int_distribution<int> d(0, 127);
            return d(generator_);
        });

        return measure;
    }

    std::vector<int> melody::crossover(std::vector<int> &parent) {
        std::uniform_int_distribution<int> d(0,1);
        std::vector<int> child = create_individual(parent.size());

        for (size_t i = 0; i < parent.size(); ++i) {
            if (d(generator_)) {
                child[i] = parent[i];
            }
        }

        return child;
    }

    void melody::simple_mutation(std::vector<int> &individual, double mutation_strength) {

        std::uniform_real_distribution<double> d(0.0, 1.0);

        for (int &item : individual) {
            if (d(generator_) < mutation_strength) {
                item = item + 1;
            }
        }
    }

    void melody::reverse_measure(std::vector<int> &individual, double mutation_strength) {

        std::uniform_real_distribution<double> d(0.0, 1.0);

        if (d(generator_) < mutation_strength) {
            std::reverse(individual.begin(), individual.end());
        }
    }

    void melody::exchange_pulses(std::vector<int> &individual, double mutation_strength) {

        std::uniform_real_distribution<double> d(0.0, 1.0);
        if (d(generator_) < mutation_strength) {
            std::uniform_int_distribution<int> value_distribution(0, static_cast<int>(individual.size()-1));
            int first_pulse = value_distribution(generator_);
            int second_pulse = value_distribution(generator_);
            std::swap(individual[first_pulse], individual[second_pulse]);
        }
    }

    void melody::reverse_pulses(std::vector<int> &individual, double mutation_strength) {

        std::uniform_real_distribution<double> d(0.0, 1.0);
        if (d(generator_) < mutation_strength) {

            std::uniform_int_distribution<int> first_value_distribution(0, static_cast<int>(individual.size()));
            int first_pulse = first_value_distribution(generator_);

            std::uniform_int_distribution<int> second_value_distribution(first_pulse, static_cast<int>(individual.size()));
            int second_pulse = second_value_distribution(generator_);

            std::reverse(individual.begin() + first_pulse, individual.begin() + second_pulse);
        }
    }

    double melody::normalize(int &value, double max, double min, double max_value, double min_value) {
        return (max - min) * (value - min_value)/(max_value - min_value);
    }

    double melody::evaluate_pitch_distribution(std::vector<int> &individual) {

        int mode = 0;
        int max_count = 0;
        double mode_value = 0;

        for (const int &value : individual) {
            int count = std::count(individual.begin(), individual.end(), value);
            if (count > max_count) {
                max_count = count;
                mode = value;
            }
        }

        mode_value = normalize(mode, 1., -1., 0., 108.);

        return mode_value;
    }

    std::tuple<double, double> melody::evaluate(std::vector<int> &individual) {
        double valence = 0;
        double arousal = 0;

        valence = valence;
        arousal = arousal + evaluate_pitch_distribution(individual);

        return {valence, arousal};
    }

    std::vector<std::vector<int>> melody::get_melody() {
        return this->melody_;
    }

    void melody::add_individual(std::vector<int> individual) {
        melody_.push_back(individual);
    }

    void melody::clear() {
        melody_.clear();
    }
}
