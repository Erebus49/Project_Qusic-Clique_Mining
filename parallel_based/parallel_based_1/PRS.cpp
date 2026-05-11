#include "PRS.h"
#include "worker/basesolver.h"
#include "solvers/wscp.h"   // for timing functions
#include <cstdlib>
#include <cstring>

using namespace std;

PRS::~PRS()
{
    for (size_t i = 0; i < workers.size(); ++i)
    {
        delete workers[i];
    }
    workers.clear();

    if (org_var_set != nullptr)
    {
        for (int i = 0; i < var_num; ++i)
            delete[] org_var_set[i];
    }
    if (org_set_var != nullptr)
    {
        for (int i = 0; i < set_num; ++i)
            delete[] org_set_var[i];
    }
    delete[] org_cost;
    delete[] org_var_set;
    delete[] org_var_set_num;
    delete[] org_set_var;
    delete[] org_set_var_num;
}


void *solve_worker(void *arg)
{
    
    basesolver *sq = (basesolver *)arg;
    
    sq->parse_from_instance();
    
    sq->solve();
    return NULL;
}

void PRS::init_workers()
{
    for (int i = 0; i < nThreads; i++)
    {
        basesolver *solver = new basesolver(this);
        solver->thread_id = i;
        workers.push_back(solver);
    }
}

void PRS::arg_parse(int argc, char **argv) {
    if (argc < 5)
    {
        fprintf(stderr, "Usage: %s <instance_file> <time_limit> <seed> <AC>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    filename = argv[1];
    time_limit = atoi(argv[2]);
    seed = atoi(argv[3]);
    AC = atoi(argv[4]);
    //cout << "filename " << filename << " time_limit " << time_limit << " seed " << seed << endl;
}

void PRS::read_instance()
{
    ifstream infile(filename);
    infile >> var_num >> set_num;
    org_cost = new int[set_num];
    org_var_set = new int *[var_num];
    org_var_set_num = new int[var_num];
    org_set_var = new int *[set_num];
    org_set_var_num = new int[set_num];
    //cout << "read_instance var_num " << var_num << " set_num " << set_num << endl;
     for (int i = 0; i < set_num; ++i)
    {
        infile >> org_cost[i];
	    if (AC) org_cost[i] = ((i + 1) % 200) + 1;
        
    }
    memset(org_set_var_num, 0, set_num * sizeof(int));
    for (int i = 0; i < var_num; ++i)
    {
        infile >> org_var_set_num[i];
        org_var_set[i] = new int[org_var_set_num[i] + 1]; 
        for (int j = 0; j < org_var_set_num[i]; ++j)
        {
            infile >> org_var_set[i][j];
            if (!AC) --org_var_set[i][j];
            ++org_set_var_num[org_var_set[i][j]];
        }
    }

    for (int i = 0; i < set_num; ++i)
    {
        org_set_var[i] = new int[org_set_var_num[i] + 1];
        org_set_var_num[i] = 0; //reset for build set_var
    }
    //build set_var
    for (int i = 0; i < var_num; ++i)
    {
        for (int j = 0; j < org_var_set_num[i]; ++j)
        {
            int cur_set = org_var_set[i][j];
            org_set_var[cur_set][org_set_var_num[cur_set]++] = i;
        }
    }
    for (int s = 0; s < set_num; ++s) {
        //cout << "set " << s << " cost " << org_cost[s] << " var_num " << org_set_var_num[s] << endl;
    }
}

WSCP *PRS::build_instance()
{
    // 如果想直接使用带参构造函数可以改为：
    // WSCP *wscp = new WSCP(time_limit);
    WSCP *wscp = new WSCP();
    // 通过输入的 time_limit 设置求解器的 cutoff_time
    wscp->cutoff_time = time_limit;
    //compareVersion = &WSCP::compareV3;
    //printf("bms_t %d\n", t);
    wscp->set_num = set_num;
    wscp->var_num = var_num;
    wscp->cost = new int[set_num+10];
    wscp->org_cost = new int[set_num+10];
    wscp->var_set = new int *[var_num+10];
    wscp->var_set_num = new int[var_num+10];
    wscp->set_var = new int *[set_num+10];
    wscp->set_var_num = new int[set_num+10];
    wscp->avg_cost = new int[var_num+10];
    wscp->gap = 0;
    // cout << "build_instance file " << filename << " time " << time_limit << " seed " << seed << " set_num " << set_num << endl;
    // cout << "build_instance var_num " << var_num << " set_num " << set_num << endl;
    for (int i = 0; i < set_num; ++i)
    {
        wscp->cost[i] = org_cost[i];
        //wscp->cost[i] = ((i + 1) % 200) + 1;
        wscp->org_cost[i] = org_cost[i];
        wscp->gap = std::max(wscp->cost[i],wscp->gap);
        //cout << "i " << i << " cost " << wscp->cost[i] << endl;
    }
    memset(wscp->set_var_num, 0, set_num * sizeof(int));
    for (int i = 0; i < var_num; ++i)
    {
        wscp->var_set_num[i] = org_var_set_num[i];
        wscp->avg_cost[i] = 0;
        wscp->var_set[i] = new int[wscp->var_set_num[i] + 1]; 
        for (int j = 0; j < wscp->var_set_num[i]; ++j)
        {
            wscp->var_set[i][j] = org_var_set[i][j];
            wscp->avg_cost[i] += wscp->cost[wscp->var_set[i][j]];
            ++wscp->set_var_num[wscp->var_set[i][j]];
        }
        wscp->avg_cost[i] /= wscp->var_set_num[i];
    }

    for (int i = 0; i < set_num; ++i)
    {
        wscp->set_var[i] = new int[wscp->set_var_num[i] + 1];
        wscp->set_var_num[i] = 0; //reset for build set_var
    }
    //build set_var
    for (int i = 0; i < var_num; ++i)
    {
        for (int j = 0; j < wscp->var_set_num[i]; ++j)
        {
            int cur_set = wscp->var_set[i][j];
            wscp->set_var[cur_set][wscp->set_var_num[cur_set]++] = i;
        }
    }

    return wscp;
}



void PRS::solve() {
   //printf("c -----------------solve start----------------------\n");
    vector<pthread_t> ptr(nThreads);
    for (int i = 0; i < nThreads; i++)
    {
        //cout << "create thread " << i << " nThreads " << nThreads << endl;
        pthread_create(&ptr[i], NULL, solve_worker, workers[i]);
    }

    //printf("c ending solve\n");

    for (int i = 0; i < nThreads; i++)
    {
        pthread_join(ptr[i], NULL);
    }
    //printf("c ending join\n");

}


void PRS::run()
{
    read_instance();
    init_workers();
    // diversity_workers();
    solve();
    for(int i = 0; i < nThreads; i++) {
        cout << "file: " << filename << " Thread " << i << " best cost: " << workers[i]->best_cost << ", time: " << workers[i]->best_time << " seconds, step: " << workers[i]->best_step << endl;
    }
}