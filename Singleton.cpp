//
// Created by xih on 2017/10/19.
//
#include <iostream>

/*
#include <pthread.h>

using namespace std;

// 线程不安全版本
class Singleton {
private:
    static Singleton *p;
    //构造函数. 把复制构造函数和=操作符也设为私有,防止被复制
    Singleton();
    Singleton(const Singleton&);
    Singleton &operator=(const Singleton&);

public:
    static Singleton *instance();
};

Singleton* Singleton::p = nullptr;
Singleton* Singleton::instance() {
    if (p == nullptr)
        p = new Singleton();
    return p;
}


// 线程安全版本1
class Singleton1 {
private:
    static Singleton1 *p;
    static pthread_mutex_t mutex;

    Singleton1() {
        pthread_mutex_init(&mutex);
    };

    Singleton1(const Singleton1&);
    Singleton1 &operator=(const Singleton1&);

public:
    static Singleton1* instance();
};

Singleton1* Singleton1::p = nullptr;
pthread_mutex_t Singleton1::mutex;

Singleton1* Singleton1::instance() {
    if (p == nullptr) {
        pthread_mutex_lock(&mutex);
        if (p == nullptr) {
            p = new Singleton1();
        }
        pthread_mutex_unlock(&mutex);
    }
    return p;
}
*/