#include <atomic>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#ifndef _DEFAULT_SOURCE
#define _DEFAULT_SOURCE
#endif

struct ThreadRandomState {
    random_data data;
    char state_buf[128];
    bool initialized;
    ThreadRandomState()
        : initialized(false)
    {
        std::memset(&data, 0, sizeof(data));
        std::memset(state_buf, 0, sizeof(state_buf));
    }
};

static thread_local ThreadRandomState tls_random_state;

static void tls_srandom(unsigned int seed)
{
    initstate_r(seed, tls_random_state.state_buf, sizeof(tls_random_state.state_buf), &tls_random_state.data);
    tls_random_state.initialized = true;
}

static long tls_random()
{
    if (!tls_random_state.initialized)
        tls_srandom(1);

    int32_t result = 0;
    random_r(&tls_random_state.data, &result);
    return static_cast<long>(result);
}

#define srandom tls_srandom
#define random tls_random
#include "wscp.h"

struct Task {
    std::string instance_file;
    int time_limit;
    int seed;
    int AC;
};

static bool parse_int(const std::string& text, int& value)
{
    if (text.empty())
        return false;

    char* end = NULL;
    long tmp = std::strtol(text.c_str(), &end, 10);
    if (*end != '\0')
        return false;

    value = static_cast<int>(tmp);
    return true;
}

static bool parse_task_line(const std::string& line, Task& task)
{
    std::istringstream iss(line);
    std::vector<std::string> tokens;
    std::string token;

    while (iss >> token) {
        if (token == ">" || token == ">>")
            break;
        tokens.push_back(token);
    }

    if (tokens.empty())
        return false;
    if (!tokens[0].empty() && tokens[0][0] == '#')
        return false;

    if (tokens[0] == "./FastSC" || tokens[0] == "FastSC") {
        if (tokens.size() < 5)
            return false;
        task.instance_file = tokens[1];
        if (!parse_int(tokens[2], task.time_limit))
            return false;
        if (!parse_int(tokens[3], task.seed))
            return false;
        if (!parse_int(tokens[4], task.AC))
            return false;
        return true;
    }

    if (tokens.size() < 4)
        return false;

    task.instance_file = tokens[0];
    if (!parse_int(tokens[1], task.time_limit))
        return false;
    if (!parse_int(tokens[2], task.seed))
        return false;
    if (!parse_int(tokens[3], task.AC))
        return false;

    return true;
}

static int run_serial_solver(const Task& task, std::string& result_line)
{
    std::ifstream infile(task.instance_file.c_str());
    if (!infile.is_open())
        return 1;

    int var_num = 0;
    int set_num = 0;
    if (!(infile >> var_num >> set_num))
        return 1;

    WSCP wscp_solver(task.time_limit);
    srandom(static_cast<unsigned int>(task.seed));

    int new_weight = 0;
    int tabu_len = 0;
    double novelty_p = 0.0;

    bool flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0, flag6 = 0;
    if (set_num >= 500 || var_num >= 500)
        flag1 = 1;
    if (var_num < set_num)
        flag2 = 1;
    if (set_num > 100000 || var_num > 100000)
        flag3 = 1;
    if (var_num > 2500 && var_num < 5000 && set_num > 920000 && set_num < 1100000)
        flag4 = 1;
    if ((var_num > 600 && var_num < 650 && set_num > 3450 && set_num < 3500)
        || (var_num > 2800 && var_num < 2850 && set_num > 13400 && set_num < 13500)
        || (var_num > 19100 && var_num < 19200 && set_num > 62500 && set_num < 62600)
        || (var_num > 74000 && var_num < 75000 && set_num > 166000 && set_num < 167000))
        flag5 = 1;
    if (var_num > 120000 && var_num < 810000 && set_num > 620000 && set_num < 3900000)
        flag6 = 1;

    if (flag3) {
        if (set_num < var_num) {
            new_weight = 5;
            tabu_len = 4;
            novelty_p = 0.1;
        } else {
            new_weight = 80;
            tabu_len = 5;
            if (var_num / set_num > 10)
                novelty_p = 0.05;
            else
                novelty_p = 0.5;
        }
    } else {
        if (set_num > var_num) {
            new_weight = 5;
            tabu_len = 4;
            novelty_p = 0.1;
        } else {
            new_weight = 80;
            tabu_len = 5;
            if (var_num / set_num > 10)
                novelty_p = 0.05;
            else
                novelty_p = 0.5;
        }
    }

    if (flag4) {
        new_weight = 3;
        tabu_len = 80;
        novelty_p = 0.21;
    }
    if (flag5) {
        new_weight = 15;
        tabu_len = 10;
        novelty_p = 0.21;
    }

    wscp_solver.flag1 = flag1;
    wscp_solver.flag2 = flag2;
    wscp_solver.flag3 = flag3;
    wscp_solver.flag4 = flag4;
    wscp_solver.flag5 = flag5;
    wscp_solver.flag6 = flag6;

    std::vector<char> file_buf(task.instance_file.begin(), task.instance_file.end());
    file_buf.push_back('\0');

    wscp_solver.build_instance(file_buf.data(), task.AC);
    wscp_solver.reduce_instance();
    wscp_solver.set_param(new_weight, tabu_len, novelty_p);

    start_timing();
    wscp_solver.init();
    wscp_solver.local_search();
    wscp_solver.check_solu();

    int cnt = 0;
    for (int i = 0; i < wscp_solver.set_num; ++i)
        if (wscp_solver.best_solu[i] == 1)
            cnt++;

    std::ostringstream oss;
    oss << task.instance_file << " " << wscp_solver.best_cost << " " << task.seed << " " << wscp_solver.best_time << " " << cnt;
    result_line = oss.str();

    wscp_solver.free_memory();
    return 0;
}

int main(int argc, char* argv[])
{
    std::string run_file = "run_p.txt";
    std::string output_file = "res_p.txt";

    int thread_count = static_cast<int>(std::thread::hardware_concurrency());
    if (thread_count <= 0)
        thread_count = 1;

    if (argc >= 2)
        run_file = argv[1];
    if (argc >= 3)
        output_file = argv[2];
    if (argc >= 4) {
        if (!parse_int(argv[3], thread_count) || thread_count <= 0) {
            std::cerr << "Invalid thread count: " << argv[3] << std::endl;
            return 1;
        }
    }

    std::ifstream in(run_file.c_str());
    if (!in.is_open()) {
        std::cerr << "Cannot open run file: " << run_file << std::endl;
        return 1;
    }

    std::vector<Task> tasks;
    std::string line;
    while (std::getline(in, line)) {
        Task task;
        if (parse_task_line(line, task))
            tasks.push_back(task);
    }

    if (tasks.empty()) {
        std::cerr << "No valid task found in " << run_file << std::endl;
        return 1;
    }

    std::ofstream out(output_file.c_str(), std::ios::out | std::ios::trunc);
    if (!out.is_open()) {
        std::cerr << "Cannot open output file: " << output_file << std::endl;
        return 1;
    }

    if (thread_count > static_cast<int>(tasks.size()))
        thread_count = static_cast<int>(tasks.size());

    std::atomic<int> next(0);
    std::atomic<int> failed(0);
    std::mutex output_mutex;
    std::mutex err_mutex;

    auto worker = [&]() {
        while (true) {
            int idx = next.fetch_add(1);
            if (idx >= static_cast<int>(tasks.size()))
                break;

            std::string result_line;
            int rc = run_serial_solver(tasks[idx], result_line);
            if (rc != 0) {
                failed.fetch_add(1);
                std::lock_guard<std::mutex> lock(err_mutex);
                std::cerr << "Task failed: " << tasks[idx].instance_file << " seed=" << tasks[idx].seed << std::endl;
                continue;
            }

            {
                std::lock_guard<std::mutex> lock(output_mutex);
                out << result_line << "\n";
            }
        }
    };

    std::vector<std::thread> pool;
    pool.reserve(thread_count);
    for (int i = 0; i < thread_count; ++i)
        pool.push_back(std::thread(worker));
    for (size_t i = 0; i < pool.size(); ++i)
        pool[i].join();

    out.flush();

    if (failed.load() > 0) {
        std::cerr << "Finished with failures: " << failed.load() << "/" << tasks.size() << std::endl;
        return 1;
    }

    std::cerr << "Finished " << tasks.size() << " tasks. Output: " << output_file << std::endl;
    return 0;
}
