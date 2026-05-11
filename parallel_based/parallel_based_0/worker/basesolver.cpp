#include "basesolver.h"
#include "solvers/wscp.h"

void basesolver::solve()
{
    solver->start_timing();  // 在 init 前调用 start_timing
    solver->init();
    solver->local_search();
    best_time = solver->best_time; 
    best_cost = solver->best_cost;
    best_step = solver->best_step;
}

void basesolver::parse_from_instance()
{
    solver = new WSCP();
    /*solver->set_num = prs->set_num;
    solver->var_num = prs->var_num;
    solver->cost = new int[prs->set_num + 10];
    solver->org_cost = new int[prs->set_num + 10];
    solver->var_set = new int *[prs->var_num + 10];
    solver->var_set_num = new int[prs->var_num + 10];
    solver->set_var = new int *[prs->set_num + 10];
    solver->set_var_num = new int[prs->set_num + 10];
    solver->avg_cost = new int[prs->var_num + 10];
    solver->gap = 0;
    for (int i = 0; i < prs->set_num; ++i)
    {
        solver->cost[i] = prs->org_cost[i];
        solver->org_cost[i] = prs->org_cost[i];
        solver->gap = std::max(solver->cost[i], solver->gap);
        //cout << "i " << i << " cost " << solver->cost[i] << endl;
    }
    memset(solver->set_var_num, 0, prs->set_num * sizeof(int));
    for (int i = 0; i < prs->var_num; ++i)
    {
        solver->var_set_num[i] = prs->org_var_set_num[i];
        solver->avg_cost[i] = 0;
        solver->var_set[i] = new int[solver->var_set_num[i] + 1];
        for (int j = 0; j < solver->var_set_num[i]; ++j)
        {
            solver->var_set[i][j] = prs->org_var_set[i][j];
            solver->avg_cost[i] += solver->cost[solver->var_set[i][j]];
            ++solver->set_var_num[solver->var_set[i][j]];
        }
        solver->avg_cost[i] /= solver->var_set_num[i];
        //cout << "i " << i << " var_set_num " << solver->var_set_num[i] << " avg_cost " << solver->avg_cost[i] << endl;
    }

    for (int i = 0; i < prs->set_num; ++i)
    {
        solver->set_var[i] = new int[solver->set_var_num[i] + 1];
        //cout << "i " << i << " set_var_num " << solver->set_var_num[i] << endl;
        solver->set_var_num[i] = 0; // reset for build set_var
    }
    // build set_var
    for (int i = 0; i < prs->var_num; ++i)
    {
        for (int j = 0; j < solver->var_set_num[i]; ++j)
        {
            int cur_set = solver->var_set[i][j];
            //cout << " i " << i << " set " << cur_set << " prs->set_num + 10 " <<prs->set_num + 10 << " solver->set_var_num[cur_set] " << solver->set_var_num[cur_set] << " solver->set_var_num[i] " << solver->set_var_num[i]+1 << endl;
            solver->set_var[cur_set][solver->set_var_num[cur_set]++] = i;
            
        }
    }
    printf("parse_from_instance: var_num %d, set_num %d\n", prs->var_num, prs->set_num);
    */
    solver = prs->build_instance();
    if (!solver) {
        fprintf(stderr, "parse_from_instance: failed to build solver\n");
        return;
    }
    solver->seed = prs->seed + thread_id;  // 根据线程号设置不同的 seed
    solver->reduce_instance();
    solver->set_param();
}

