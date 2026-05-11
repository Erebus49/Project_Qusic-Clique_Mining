#ifndef PRS_H
#define PRS_H

#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>
#include "utils/vec.h"
#include "solvers/wscp.h"
using namespace std;

class basesolver;

class PRS
{
    public:

    char *filename = nullptr;
    int seed = 0;
    int time_limit = 0;
    int AC = 0;

    int var_num = 0;
    int set_num = 0;
    int **org_var_set = nullptr;
    int *org_var_set_num = nullptr;
    int **org_set_var = nullptr;
    int *org_set_var_num = nullptr;
    int *org_cost = nullptr;

    vector<basesolver *> workers;

    int nThreads = 10;

    ~PRS();

    void arg_parse(int argc, char **argv);
    // void diversity_workers();
    void run();
    void solve();
    // void terminate_workers();
    void read_instance();
    WSCP *build_instance();
    void init_workers();
};
#endif