#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>
#include <list>
#include <forward_list>
#include <set>
#include <map>
#include <chrono>

using namespace std;

//firstTask
template <class T>
using valueType = typename std::remove_reference<decltype(*std::begin(std::declval<typename std::add_lvalue_reference<T>::type>()))>::type;

template<class Container>
void insert_sorted(Container& data, const valueType<Container>& value) {
    Container _insert{ value };
    auto insertPlace = find_if(begin(data), end(data), [value](const auto& element) { return value < element; });
    auto insertIterator = inserter(data, insertPlace);
    move(begin(_insert), end(_insert), insertIterator);
};

template<typename T>
void insert_sorted(forward_list<T>& data, const valueType<forward_list<T>>& value) {
    forward_list<T> _insert{ value };
    auto insertPlace = distance(data.before_begin(), find_if(begin(data), end(data), [value](const auto& element) { return value < element; }));
    data.insert_after(next(data.before_begin(), insertPlace - 1), value);
};

template<typename Container>
void printContainer(const Container& data) {
    cout << "Container: ";
    for_each(data.begin(), data.end(), [](const auto& row) { cout << row << " "; });
    cout << endl;
};

void firstTask() {
    forward_list<int> data{4, 9, 0};
    printContainer(data);
    insert_sorted(data, 2);
    printContainer(data);
    insert_sorted(data, 1);
    printContainer(data);
    insert_sorted(data, 6);
    printContainer(data);

    vector<double> data2{ 4, 9, 0 };
    printContainer(data2);
    insert_sorted(data2, 2);
    printContainer(data2);
    insert_sorted(data2, 1);
    printContainer(data2);
    insert_sorted(data2, 6);
    printContainer(data2);
}
//firstTask
//secondTask
void secondTask() {
    const double lower_bound = 0;
    const double upper_bound = 10000;
    const int amount = 100;
    uniform_real_distribution<double> unif(lower_bound, upper_bound);
    default_random_engine re(chrono::system_clock::now().time_since_epoch().count());
    vector<double> dirty(amount);
    generate(dirty.begin(), dirty.end(), [unif, &re]() { return unif(re); });
    printContainer(dirty);
    vector<int> clean;
    transform(dirty.begin(), dirty.end(), back_inserter(clean), [](double element) { return static_cast<int>(floor(element)); });
    printContainer(clean);
    double signalError = 0;
    for_each(dirty.begin(), dirty.end(), [&signalError](double element) { 
        signalError += pow((element - floor(element)), 2);
    });
    cout << "Signal error: " << signalError << endl;
    
};
//secondTask
int main()
{
    firstTask();
    secondTask();
}