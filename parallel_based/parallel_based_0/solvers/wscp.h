#pragma once

#include <iostream>
#include <vector>
#include <set>
#include <chrono>


using namespace std;

#define mypop(stack) stack[--stack##_fill_pointer]
#define mypush(item, stack) stack[stack##_fill_pointer++] = item

class WSCP
{
  public:
    //set(variable, soft clause) information
    long long *score;
    long long *pscore;
    long long *time_stamp;
    int *cost;
    int *org_cost;
    bool *cc;
    int *fix;
    set<int> tabu_list;
    int *zero_stack;
    int zero_stack_fill_pointer;
    int *index_in_zero_stack;
	int *var_sort; 
    //variable(hard clause)
    long long *weight;
    int *cover_count;
    int *avg_cost; 
    int *cover_set;
    int *cover_set2;
    int *uncover_stack;
    int *index_in_uncover_stack;
    int *unlocked_stack;
    int uncover_stack_fill_pointer;
    int unlocked_stack_fill_pointer;
    //solution information
    int *cur_solu;
    long long cur_cost;
    int reduce_cost;
    int *best_solu;
    long long best_cost;
    double best_time;
    int *set_solu;
    int *index_in_set_solu;
    int set_count;
    int gap;

    //date structure
    int cutoff_time;
    unsigned int seed;
    int bms_t;
    long long step;
    long long max_step;
    long long best_step;
    long long tries;
    long long max_tries;
	bool flag_tabu;
    int var_num;
    int set_num;

    int *var_delete;
    int *set_delete;
    int **var_set;
    int *var_set_num;
    int *org_var_set_num;
    int **set_var;
    int *set_var_num;
    int *org_set_var_num;

    int *goodset_stack;
    int goodset_stack_fill_pointer;

    std::chrono::steady_clock::time_point start_time;

    WSCP();
    WSCP(int time_limit);
    void all_memory();
    void free_memory();

    void build_instance(char *file_name);
    void reduce_instance();
    void init();
    void local_search();
    void local_search1();
    void add_set(int s);
    void remove_set(int s);
    void flip(int flip_set);
    void cover(int selected_var);
    void uncover(int selected_var);
    int break_ties_score_subscore(int set1, int set2, int op);
    void compute_score(int compute_set, long long & set_score, int & set_weight);
    int compare(int set1, int set2, int flag);
    int compare1(int s1, int c1, int s2, int c2);
    int compare2(int s1, int c1, int s2, int c2, int p1, int p2);
    int compareV2(int s1, int c1, int s2, int c2, int p1, int p2, int weight1, int weight2);
    int compareV3(int s1, int c1, int s2, int c2, int p1, int p2, int weight1, int weight2);
    int (WSCP::*compareVersion)(int s1, int c1, int s2, int c2, int p1, int p2, int weight1, int weight2);
    bool cmp(int x,int y);
    double weight1 = 4;
    double weight2 = 1;
    double novelty_p = 0.5;
    double explore_p = 0.5;
    int tabu_length = 5;
    int select_set(int is_tabu);
    int select_set_1();
    int select_set_new(int is_tabu);
    int select_set_Novelty();
    int select_set_Novelty_no_tabu(int var1);
    int local_greedy_addition();
    int remove_best_score();
    int select_set_from_zero_stack();
    int select_set_from_zero_stack_new();
    void set_param();
    void update_weight();
    void check_solu();
    void check_cur_solu();
    int count_2cc(int var);
    vector<int> index_in_unlocked_stack;
    bool flag1,flag2,flag3,flag4,flag5,flag6; 

    inline double get_runtime() const
    {
        auto now = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = now - start_time;
        return diff.count();           // 秒
    }

    inline void start_timing()
    {
        start_time = std::chrono::steady_clock::now();
    }
};



