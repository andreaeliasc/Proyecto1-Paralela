
#include <chrono>
#include <iostream>
#include <iomanip>
#include "Equation.cpp"  
using namespace std::chrono;
  
int THREAD_COUNT_PARALLEL = 5000;
double Tl = 0.0;
double Tr = 60.0;

void parallel_function(int THREAD_COUNT, double Tl, double Tr, double C, int x_intervals, int t_intervals){
    calculo_calor(THREAD_COUNT, Tl, Tr, C , x_intervals, t_intervals);
}

void sec_function(int THREAD_COUNT, double Tl, double Tr, double C, int x_intervals, int t_intervals){
    calculo_calor_sec(THREAD_COUNT, Tl, Tr, C , x_intervals, t_intervals);
}


int main(int argc, char const *argv[])
{
    try {
        THREAD_COUNT_PARALLEL = strtol(argv[1], NULL, 10);
        Tl = strtol(argv[2], NULL, 10);
        Tr = strtol(argv[3], NULL, 10);
    } catch (const std::exception&) {
        std::cout << "Inputs erroneos" << std::endl;
    }

    double C=0.4;
    int x_intervals = THREAD_COUNT_PARALLEL;
    int t_intervals = int((pow(x_intervals, 2) * 6e-3)/C);

    std::cout << "C =  " << C << std::endl;
    std::cout << "Tenemos --> " << x_intervals << " intervalos en x" << std::endl;
    std::cout << "Tl: " << Tl << "°c" << std::endl;
    std::cout << "Tenemos --> " << t_intervals << " intervalos en t" << std::endl;
    std::cout << "Tr: " << Tr << "°c\n" << std::endl;


    std::cout<<"Ejecucion secuencial --> " << std::endl;
    auto initial_seq_time = high_resolution_clock::now();
    sec_function(THREAD_COUNT_PARALLEL, Tl, Tr, C , x_intervals, t_intervals);
    auto final_seq_time = high_resolution_clock::now();

    std::cout<<"Ejecucion paralela --> " << std::endl;
    auto initial_parallel_time = high_resolution_clock::now();
    parallel_function(THREAD_COUNT_PARALLEL, Tl, Tr, C , x_intervals, t_intervals);
    auto final_parallel_time = high_resolution_clock::now();

    auto seq_time = duration_cast<microseconds>(final_seq_time - initial_seq_time);
    auto parallel_time = duration_cast<microseconds>(final_parallel_time - initial_parallel_time);


    std::cout << "Tiempo Secuencial: " << seq_time.count() << "µs" << std::endl;
    std::cout << "Tiempo Paralelo: " << parallel_time.count() << " µs" << std::endl;
    long double speedup = seq_time.count() / parallel_time.count();
    long double eff = speedup / THREAD_COUNT_PARALLEL;
    std::cout << std::fixed << "Eficiencia: " << eff << std::endl;
    std::cout << std::fixed << "Speed up: " << speedup << std::endl;


    return 0;
}
