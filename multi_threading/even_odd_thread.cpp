

/*******************************************************
 * Copyright (C) 2010-2011 Ch V Kishore <apps.kisstronics@gmail.com>
 * 
 * This file is part of CPP Samples.
 * 
 * CPP Samples can be copied and/or distributed without the express
 * permission
 * 
 *******************************************************/
#include <iostream>
#include <string>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vector>

// variables 
std::mutex thread_mutex;
std::condition_variable cv;

int max_counter = 20;
std::vector<int> data_list;
int current_index=0;


// functions
void odd();
void even();
void debug(std::string msg);


int main(int argc, char ** )
{
    std::thread evenThread(even);
    std::thread oddThread(odd);

    evenThread.join();
    oddThread.join();

    debug("Completed");
    // for(auto &it:data_list){
    //     debug(std::to_string(it));
    // }
    return 0;
}

void push_to_data_list(std::string type)
{
    debug(type+ " :: " + std::to_string(current_index) );
    data_list.push_back(current_index);
    current_index++;
    cv.notify_one();
}


void even(){
   do
    {
        std::unique_lock<std::mutex> lock(thread_mutex);
        while(current_index %2 !=0){
            cv.wait(lock);
        }
        push_to_data_list("even");
    }while(current_index < max_counter);
}

void odd(){
    do
    {
        std::unique_lock<std::mutex> lock(thread_mutex);
        while(current_index %2 !=1){
            cv.wait(lock);
        }
        push_to_data_list("odd");
    }while(current_index < max_counter);
}

void debug(std::string msg){
    std::cout << msg << std::endl;
}