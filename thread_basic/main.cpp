#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex mtx;
int counter;

void execute(int threadId) {
    for(int i=0;i<5;i++){
        //current thread incrementing counter every 1 sec
        mtx.lock();
        counter++;
        cout<<threadId<<" incremented "<<counter<<endl;
        mtx.unlock();
        this_thread::sleep_for(chrono::milliseconds(1000));
    }
}
int main() {
    vector<thread> threads;
    counter = 0;
    for(int i=0;i<5;i++){
        //creating 5 threads
        threads.emplace_back(thread(execute,i));
    }

    for(auto &t : threads) {
        if(t.joinable()){
            t.join();
        }
    }
    return 0;
}