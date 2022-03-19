#include <stdio.h>
#include <math.h>
#include "Modelo.cpp"  

void calculo_calor(int intervals);

double temperatura_inicial(int j, double Tr,double Tl, int N){
    return (Tl-Tr)/(j*N);
}


void recursion_proceso(int i, Modelo solution,double Tl,double Tr, int x_intervals,double C){
    #pragma omp parallel shared(solution, Tl, Tr, x_intervals, C)
    #pragma omp single nowait
    {
        for (int j = 1; j < x_intervals - 1; j++){
            #pragma omp task
                
                if(j-1==0){solution.set(j - 1, i, Tl);} if(j+1==x_intervals-1){solution.set(j + 1, i, Tr);}
                double T_ji;   
                double T_J1i;  
                double T_j1i;  
                if(i!=0){T_ji = solution.get(j,i);T_J1i =  solution.get(j+1,i);T_j1i = solution.get(j-1,i);}
                  else {T_ji = T0(j, Tl, Tr, x_intervals);T_J1i = T0(j+1, Tl, Tr, x_intervals);T_j1i = T0(j-1, Tl, Tr, x_intervals);solution.set(j , i, T0(j, Tl, Tr, x_intervals));}

                double new_value = T_ji + C*(T_j1i - 2*T_ji + T_J1i);
                solution.set(j , i+1, new_value);
        }
        if(stopCondition(i)){
            recursion_proceso(i+1, solution, Tl, Tr, x_intervals, C);
        }
    }
}

bool verificacion(double i){
    return (i<100000);
}
void calculo_calor(int intervals, double Tl, double Tr, double C, int x_intervals, int t_intervals) {
    Modelo solution = Modelo();
    solution.columns = t_intervals;
    solution.rows = x_intervals;
    solution.matrix = new double[x_intervals * t_intervals];

    recursion_proceso(0, solution, Tl, Tr, x_intervals, C);
}

// ----------------------------

void calculo_calor_sec(int intervals);

double T0(int j, double Tr,double Tl, int N){
    return (Tl-Tr)/(j*N);
}

bool stopCondition(double i){
    return (i>100000);
}

void calculo_calor_sec(int intervals, double Tl, double Tr, double C, int x_intervals, int t_intervals) {
    Modelo solution = Modelo();
    solution.columns = t_intervals;
    solution.rows = x_intervals;
    solution.matrix = new double[x_intervals * t_intervals];

    int i = 0;

    bool done = false;

    while (!done){
        for (int j = 1; j < x_intervals - 1; j++){
            double T_ji;   //T(j,i)
            double T_J1i;  //T(j+1,i)
            double T_j1i;  //T(j-1,i)
            
            if(j-1==0){
                solution.set(j - 1, i, Tl);
            } if(j+1==x_intervals-1){
                solution.set(j + 1, i, Tr);
            }

            if(i!=0){
                T_ji = solution.get(j,i);
                T_J1i =  solution.get(j+1,i);
                T_j1i = solution.get(j-1,i);
            } else {
                T_ji = T0(j, Tl, Tr, x_intervals);
                T_J1i = T0(j+1, Tl, Tr, x_intervals);
                T_j1i = T0(j-1, Tl, Tr, x_intervals);
                solution.set(j , i, T0(j, Tl, Tr, x_intervals));
            }

            double new_value = T_ji + C*(T_j1i - 2*T_ji + T_J1i);
            //printf("i: %d\n", i);//, j:%d, value:%f\n", i, j, new_value);
            if(i!=0 && j-1!=0 && j+1!=x_intervals-1){
                if(stopCondition(i)){
                    done = true;
                }
            }
            solution.set(j , i+1, new_value);
        }
        i++;
    }  
}

