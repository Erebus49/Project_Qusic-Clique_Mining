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

    char *filename;
    int seed;
    int time_limit;
    int AC;

    int var_num;
    int set_num;
    int **org_var_set;
    int *org_var_set_num;
    int **org_set_var;
    int *org_set_var_num;
    int *org_cost;

    vector<basesolver *> workers;

    int nThreads = 10;

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