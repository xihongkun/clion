//
// Created by xih on 2017/10/23.
//

#ifndef MYFIRSTCLIONPROJECT_THREADPOOL_H
#define MYFIRSTCLIONPROJECT_THREADPOOL_H

#include <iostream>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <thread>
#include <vector>
#include <list>

using namespace std;
typedef std::function<void(void)> Task;

class ThreadPool {
private:
    bool isRunning;
    int numThreads;
    mutex mut;
    std::condition_variable cond;
    vector<shared_ptr<thread>> threads;
    list<Task> tasks;
    void work();


public:
    explicit ThreadPool(int num);
    ~ThreadPool();
    void append(const Task &task);
    void start();
    void stop();
};

#endif //MYFIRSTCLIONPROJECT_THREADPOOL_H
