
#include "DataStructures/Histogram.h"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <vector>
#include <iomanip>
#ifndef LABA3_EXE_TEST_HISTOGRAM_H
#define LABA3_EXE_TEST_HISTOGRAM_H



struct Person {
    int age;
    double height;
    std::string name;

    Person(int a, double h, const std::string& n) : age(a), height(h), name(n){}
};

// Функция для вывода времени выполнения и количества элементов в файл
void printPerformanceToFile(long long duration, int dataSize, const std::string& filename) {
    std::ofstream file(filename, std::ios::app); // Открываем файл в режиме добавления
    if (file.is_open()) {
        file << duration << "\t" << dataSize << "\n";
        file.close();
        std::cout << "Performance data written to " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}



// Функция для запуска тестов с разными размерами данных
void runHistogramTests(const std::vector<int>& dataSizes, const std::string& filenamePrefix) {
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> age_dist(0, 100);
    std::uniform_real_distribution<> height_dist(1.0, 2.0);
    std::uniform_int_distribution<> name_dist(0, 25);

    const std::string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int dataSize : dataSizes) {
        std::vector<Person> people;
        for (int i = 0; i < dataSize; ++i) {
            int age = age_dist(gen);
            double height = height_dist(gen);
            std::string name(1, alphabet[name_dist(gen)]);
            people.emplace_back(age, height, name);
        }

        // Тестирование гистограммы по возрасту (равномерное разбиение)
        std::vector<int> ageBuckets = {0, 20, 40, 60, 80, 100};

        Histogram<Person, int> ageHistogram(ageBuckets, [](const Person& p){ return p.age; });


        auto start = std::chrono::high_resolution_clock::now();
        for(const auto& person : people){
            ageHistogram.add(person);
        }
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::string ageFilename = filenamePrefix + "_age_performance.txt";
        printPerformanceToFile(duration.count(), dataSize, ageFilename);

        std::cout << "Histogram age test for " << dataSize << " elements: " << duration.count() << " ms\n";

        //тест гистограммы по росту(неравномерное разбиение)
        std::vector<std::pair<double, double>> heightBuckets = {{1.0, 1.5}, {1.5, 1.8}, {1.8, 2.0}};
        Histogram<Person, double> heightHistogram(heightBuckets, [](const Person& p){ return p.height; });
        start = std::chrono::high_resolution_clock::now();
        for(const auto& person : people){
            heightHistogram.add(person);
        }
        end = std::chrono::high_resolution_clock::now();
        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::string heightFilename = filenamePrefix + "_height_performance.txt";

        printPerformanceToFile(duration.count(), dataSize, heightFilename);

        std::cout << "Histogram height test for " << dataSize << " elements: " << duration.count() << " ms\n";
    }
}

void test_histogram() {
    std::cout << "Starting Histogram tests...\n";
    std::vector<int> dataSizes = {10000, 50000, 100000};
    runHistogramTests(dataSizes, "histogram_test_results");

    std::cout << "All Histogram tests completed.\n";
}


#endif //LABA3_EXE_TEST_HISTOGRAM_H
