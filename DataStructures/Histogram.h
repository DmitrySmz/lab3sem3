

#include "HashTable.h"
#include <vector>
#include <functional>
#include <limits>
#include <fstream>
#include <chrono>
#include <type_traits>
#ifndef LABA3_EXE_HISTOGRAM_H
#define LABA3_EXE_HISTOGRAM_H


template<typename T, typename TKey>
class Histogram {
public:
    // Структура для хранения статистики
    struct Statistics {
        size_t count = 0;
        TKey min = std::numeric_limits<TKey>::max();
        TKey max = std::numeric_limits<TKey>::lowest();
        double sum = 0.0;

        void update(const TKey& value) {
            count++;
            min = std::min(min, value);
            max = std::max(max, value);
            sum += static_cast<double>(value);
        }

        double getAverage() const {
            if(count == 0) return 0;
            return sum / count;
        }

        void reset(){
            count = 0;
            min = std::numeric_limits<TKey>::max();
            max = std::numeric_limits<TKey>::lowest();
            sum = 0.0;
        }
    };

    // Тип, который будет хранить диапазон значений и статистику
    using BucketStats = std::pair<TKey, Statistics>;

    // Конструкторы
    Histogram(const std::vector<TKey>& buckets, std::function<TKey(const T&)> extractor); // Конструктор для равномерных диапазонов
    Histogram(const std::vector<std::pair<TKey, TKey>>& buckets, std::function<TKey(const T&)> extractor); // Конструктор для неравномерных диапазонов


    // Метод для добавления элементов
    void add(const T& value);

    // Метод для получения результатов гистограммы
    const HashTable<TKey, Statistics>& getHistogram() const; // Возвращаем ссылку


    // Метод для получения диапазонов
    std::vector<TKey> getBuckets() const;

    void reset();


private:
    HashTable<TKey, Statistics> histogramData;
    std::vector<TKey> buckets;
    std::vector<std::pair<TKey, TKey>> rangedBuckets;

    std::function<TKey(const T&)> valueExtractor;
    bool isRangedBuckets = false;


    TKey findBucket(const TKey& value) const;
};

template<typename T, typename TKey>
Histogram<T, TKey>::Histogram(const std::vector<TKey>& buckets, std::function<TKey(const T&)> extractor)
        : buckets(buckets), valueExtractor(extractor), isRangedBuckets(false) {

    for(const auto& bucket : buckets){
        histogramData.Add(bucket, Statistics());
    }
}


template<typename T, typename TKey>
Histogram<T, TKey>::Histogram(const std::vector<std::pair<TKey, TKey>>& buckets, std::function<TKey(const T&)> extractor)
        : rangedBuckets(buckets), valueExtractor(extractor), isRangedBuckets(true){

    for(const auto& bucket : buckets){
        histogramData.Add(bucket.first, Statistics());
    }
}

template<typename T, typename TKey>
void Histogram<T, TKey>::add(const T& value) {
    TKey extractedValue = valueExtractor(value);

    TKey bucket;
    if(!isRangedBuckets)
        bucket = findBucket(extractedValue);
    else {
        bucket = findBucket(extractedValue);
    }

    if (histogramData.ContainsKey(bucket)){
        Statistics stats = histogramData.Get(bucket);
        stats.update(extractedValue);
        histogramData.Update(bucket, stats);
    }
}

template<typename T, typename TKey>
void Histogram<T, TKey>::reset() {
    auto iterator = histogramData.GetIterator();
    while (iterator->MoveNext()) {
        TKey currentKey = iterator->GetCurrentKey();
        Statistics stats = histogramData.Get(currentKey);
        stats.reset();
        histogramData.Update(currentKey, stats);
    }
}

template<typename T, typename TKey>
const HashTable<TKey, typename Histogram<T, TKey>::Statistics>& Histogram<T, TKey>::getHistogram() const {
    return histogramData; // Возвращаем константную ссылку
}



template<typename T, typename TKey>
std::vector<TKey> Histogram<T, TKey>::getBuckets() const {
    return buckets;
}


template<typename T, typename TKey>
TKey Histogram<T, TKey>::findBucket(const TKey& value) const {

    if(isRangedBuckets){
        for(const auto& range : rangedBuckets){
            if (value >= range.first && value < range.second)
                return range.first;
        }
        return rangedBuckets.back().first;

    } else {
        for (size_t i = 0; i < buckets.size(); ++i) {
            if (i + 1 < buckets.size() && value >= buckets[i] && value < buckets[i + 1]) {
                return buckets[i];
            } else if(i + 1 == buckets.size() && value >= buckets[i])
                return buckets[i];
        }
        return buckets.back();
    }
}



#endif //LABA3_EXE_HISTOGRAM_H
