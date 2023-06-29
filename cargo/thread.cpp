#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include"thread.h"
#include"process.cpp"
#include <UnitreeCameraSDK.hpp>
#include <unistd.h>

UnitreeCamera cam("stereo_camera_config.yaml"); 
int rows=1856;
int cols=800;
cv::Size frameSize(rows,cols); 
int fps = 30;
bool producer(Factory<TaskData> &factory,std::chrono::_V2::steady_clock::time_point time_start){
    if(!cam.isOpened()){
        exit(EXIT_FAILURE);
        cout<<"camera open failed"<<endl;
    }
    cam.setRawFrameSize(frameSize); 
    cam.setRawFrameRate(fps);       
    cam.startCapture(); 
    cam.startStereoCompute(); 
    TaskData src;
    std::chrono::microseconds t;
    auto time_cap = std::chrono::steady_clock::now();
    while (cam.isOpened())
    {
        if(!cam.getRawFrame(src.img,t)){
            usleep(1000);
            cout<<"get img failed"<<endl;
            continue;
        }else src.timestamp = (int)(std::chrono::duration<double,std::milli>(time_cap - time_start).count());
    }
    
}

bool consumer(Factory<TaskData> &task_factory,Factory<VisionData> &transmit_factory)
{
    while (1)
    {
        TaskData dst;
        VisionData data;
        task_factory.consume(dst);
        Mat image=dst.img;
        unsigned char** array = new unsigned char*[rows];
        for (int i = 0; i < rows; ++i)
        {
            array[i] = image.ptr<unsigned char>(i);
        }
        run(array);
        delete[] array;
    }
    
}
