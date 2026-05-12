#include "wscp.h"

int main(int argc, char *argv[])
{
    int time_limit = atoi(argv[2]);
    int initial_K = argc > 5 ? atoi(argv[5]) : 5;
    int delta_K = argc > 6 ? atoi(argv[6]) : 5;
    long long no_improve_limit = argc > 7 ? atoll(argv[7]) : 5;
    WSCP wscp_solver(time_limit, initial_K, delta_K, no_improve_limit);
    int seed = atoi(argv[3]);
    //int seedd = atoi(argv[3]);
    srand(seed);
    int num = atoi(argv[4]);

    wscp_solver.build_instance(argv[1], num);
    wscp_solver.reduce_instance();

    start_timing();
    wscp_solver.init();
    wscp_solver.local_search();
    wscp_solver.check_solu();
    cout << argv[1] << " " << seed << " " << wscp_solver.best_cost << " " << wscp_solver.best_time << endl;
    //cout << wscp_solver.best_cost << " " << wscp_solver.best_time << endl;
    // cout << "v ";
    // for (int i = 0; i < wscp_solver.set_num; ++i)
    //     cout << wscp_solver.best_solu[i] << " ";
    // cout << endl;
    wscp_solver.free_memory();
}
