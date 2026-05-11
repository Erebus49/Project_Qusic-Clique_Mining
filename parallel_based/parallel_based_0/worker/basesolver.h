#include <chrono>

#include "PRS.h"

struct WSCP;

class basesolver
{
public:

    WSCP *solver;
    PRS *prs;

    long long best_cost;
    double best_time;
    long long best_step;
    int thread_id;
    std::chrono::steady_clock::time_point thread_start;

    basesolver(PRS *p) : prs(p), solver(nullptr), best_cost(0), best_time(0.0), best_step(0), thread_id(0) {}

    // void diversity();
    void parse_from_instance();
    
    void solve();

    // void terminate();
    // void shuffle_init();
    // void print_solution();


   
};