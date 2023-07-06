// #include"process.cpp"
// #include"process.h"
#include"thread.cpp"
#include"thread.h"
int main(){
    auto time_start = std::chrono::steady_clock::now();
    Factory<TaskData> task_factory(3);
    Factory<VisionData> data_transmit_factory(5);
    std::thread task_producer(&producer, ref(task_factory), ref(time_start));
    std::thread task_consumer(&consumer, ref(task_factory),ref(data_transmit_factory));
    task_producer.join();
    task_consumer.join();
    return 0;
}