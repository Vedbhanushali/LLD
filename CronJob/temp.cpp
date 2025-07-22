#include<iostream>
#include<chrono>
#include<vector>
#include<queue>
#include<windows.h>
#include<thread>

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
        return this->epoch_time > job.epoch_time;
    }
};

class Scheduler {
    private:
    priority_queue<Job,vector<Job>,greater<Job>> jobQueue;
    vector<thread> jobThreads;

    static void runCommand(Job job) {
        int return_code = system(job.getCommand().c_str());
        if (return_code == 0) {
            cout << "Executed successfully: " << job.getCommand() << endl;
        } else {
            cout << "Execution failed: " << job.getCommand() << endl;
        }
    }
    void executeJob(const Job& job) {
        jobThreads.emplace_back(runCommand, job);
    }
    public:
    void addJobs(string command,long long epoch_time){
        jobQueue.push(Job(command,epoch_time));
        cout<<"Job added"<<endl;
    }
    void run() {
        cout<<"Scheduler running"<<endl;
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
        // Wait for all job threads to finish
        for (auto& t : jobThreads) {
            if (t.joinable()) {
                t.join();
            }
        }
    }
};

int main() {
    Scheduler s;

    string command;
    long long epoch_time;

    while(true) {
        cout<<"run or command ";
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

