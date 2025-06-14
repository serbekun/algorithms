#include <iostream>
#include <random>

using namespace std;

class rng {
public:
    rng() : gen(rd()) {}

    double GetRandomDoubleWithDiapason(double min, double max) {
        std::uniform_real_distribution<double> dist(min, max);
        return dist(gen);
    }

private:
    std::random_device rd;
    std::mt19937 gen;
};

void SetRandomNum(rng& random_giv, double *array, size_t array_size, double min, double max)
{

    for (int i = 0; i < array_size; i++)
    {
        array[i] = random_giv.GetRandomDoubleWithDiapason(min, max);
    }

}


int main() {

    // init obj
    rng random_giver;

    // init value
    double min = 0;
    double max = 0;

    const size_t array_size = 10000;
    
    double *array_1 = new double[array_size];
    double *array_2 = new double[array_size];

    SetRandomNum(random_giver, array_1, array_size, min, max);

    // delete dinamicks array
    delete[] array_1;
    delete[] array_2;

}