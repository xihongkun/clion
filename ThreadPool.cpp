//
// Created by xih on 2017/10/23.
//

#include "ThreadPool.h"

ThreadPool::ThreadPool(int num) : numThreads(num), isRunning(false), mut() {}

ThreadPool::~ThreadPool() {
    if (isRunning) stop();
}

void ThreadPool::start() {
    isRunning = true;
    threads.reserve(numThreads);
    for (int i = 0; i < numThreads; i++) {
        threads.push_back(make_shared<thread>(&ThreadPool::work, this));
    }
}

void ThreadPool::stop() {
    // 唤醒所有等待线程，线程池要销毁了
    unique_lock<mutex> locker(mut);
    isRunning = false;
    cond.notify_all();

    for (auto t : threads ) {
        if (t->joinable()) t->join();
    }

}


void ThreadPool::append(const Task &task) {
    if (isRunning) {
        unique_lock<mutex> locker(mut);
        tasks.push_back(task);
        cond.notify_one();
    }
}

void ThreadPool::work() {
    while (isRunning) {
        Task task;
        unique_lock<mutex> locker(mut);
        if (isRunning && tasks.empty()) {
            cond.wait(locker);
        }

        // 任务列表不为空
        if (!tasks.empty()) {
            task = tasks.front();
            tasks.pop_front();
        }

        if (task) task();
    }
}