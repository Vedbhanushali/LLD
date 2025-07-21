#include<iostream>
#include<chrono>
#include<vector>
#include<queue>
#include<windows.h>

using namespace std;

class Job {
    private:
    string command;
    std::chrono::system_clock::time_point epoch_time;
    public:
    Job(string command,long long time) {
        this->command = command;
        this->epoch_time = std::chrono::system_clock::from_time_t(time);
    }
    std::chrono::system_clock::time_point getJobTime() const {
        return epoch_time;
    }
    string getCommand() const {
        return command;
    }
    bool operator > (const Job& job) const {
        this->epoch_time > job.epoch_time;
    }
};

class Scheduler {
    private:
    priority_queue<Job,vector<Job>,greater<Job>> jobQueue;
    void executeJob(const Job &job) {
        int return_code = system(job.getCommand().c_str());
        if(return_code == 0) {
            cout<<"Executed successful"<<endl;
        } else {
            //can add return logic
        }
    }
    public:
    void addJobs(string command,long long epoch_time){
        jobQueue.push(Job(command,epoch_time));
        cout<<"Job added"<<endl;
    }
    void run() {
        while(true) {
            if(jobQueue.empty()) break;

            const Job &currentJob = jobQueue.top();
            auto currentTime = chrono::system_clock::now();
            if(currentJob.getJobTime() <= currentTime) {
                executeJob(currentJob); //can added threading here
                jobQueue.pop();
            } else {
                Sleep(1000);
            }
        }
    }
};

int main() {
    Scheduler s;

    string command;
    long long epoch_time;

    while(true) {
        cout<<"run or command";
        getline(cin,command);
        if(command == "run") break;
        cout<<"epoch time ";
        cin>>epoch_time;
        if(cin.fail()){
            cin.clear();
            cin.ignore();
            continue;
        }
        cin.ignore();
        s.addJobs(command,epoch_time);
    }

    //running / scheduling jobs
    s.run();
}

