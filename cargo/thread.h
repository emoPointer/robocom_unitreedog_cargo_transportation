#include<iostream>
#include<opencv2/opencv.hpp>
#include<Eigen/Core>
using namespace std;
using namespace cv;

struct TaskData
{
    Mat img;
    int timestamp;//单位：ms
};

struct VisionData
{
    int dis_inx;
};

struct arm_msg
{
    int conditiion;
    int timestamp;
};

template <typename T>
class Factory
{
private:
    std::deque<T> buffer;
    int buffer_size;
    mutex lock;

public:
    /**
     * @brief 工厂类初始化
     * @param size 队列长度
    **/
    Factory(int size)
    {
        buffer_size = size;
    };
    bool produce(T &product);
    bool consume(T &product);
};

template <typename T>
bool Factory<T>::produce(T &product)
{

    lock.lock();
    if (buffer.size() < buffer_size)
        buffer.push_back(product);
    else
    {
        buffer.pop_front();
        buffer.push_back(product);
    
    }
    lock.unlock();

    return true;
}

template <typename T>
bool Factory<T>::consume(T &product)
{
    while (1)
    {
        lock.lock();
        if (!buffer.empty())
            break;
        lock.unlock();
        usleep(1e3);
    }
    product = buffer.front();
    buffer.pop_front();
    lock.unlock();

    return true;
}