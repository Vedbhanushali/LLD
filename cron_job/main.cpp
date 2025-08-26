#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <chrono>
#include <thread> // For std::this_thread::sleep_for
#include <functional> // For std::greater
#include <limits> // For std::numeric_limits
#include<windows.h>


// Represents a single task to be executed.
// This struct remains a simple data container.
struct Job {
    std::string command;
    std::chrono::system_clock::time_point execution_time;

    // Custom comparison for the priority queue to make it a "min-heap".
    // The job with the soonest execution time will have the highest priority.
    bool operator > (const Job& other) const {
        return execution_time > other.execution_time;
    }
};

// The Scheduler class encapsulates all the core logic for managing and running jobs.
class Scheduler {
    private:
    // A priority queue is the perfect data structure here.
    // It keeps the jobs sorted by execution time automatically.
    std::priority_queue<Job, std::vector<Job>, std::greater<Job>> m_jobs;
    
    // Executes a given job and prints its status.
    void execute_job(const Job& job) {
        std::cout << "\n[Executing] " << job.command << std::endl;
        
        // Use system() to execute the command.
        int return_code = system(job.command.c_str());

        if (return_code == 0) {
            std::cout << "[Finished] Command executed successfully." << std::endl;
        } else {
            std::cout << "[Finished] Command FAILED with exit code: " << return_code << std::endl;
        }
    }

public:
    // Adds a new job to the scheduling queue.
    void add_job(const std::string& command, long long epoch_time) {
        // Convert epoch time to a C++ time_point and add to the queue.
        m_jobs.push({command, std::chrono::system_clock::from_time_t(epoch_time)});
        std::cout << "Job added." << std::endl;
    }

    // Starts the main scheduler loop.
    void run() {
        std::cout << "\n--- Scheduler started. Press Ctrl+C to exit. ---" << std::endl;

        while (true) {
            // If there are no jobs left, the scheduler's work is done.
            if (m_jobs.empty()) {
                std::cout << "No more jobs to run. Exiting." << std::endl;
                break;
            }

            // Look at the next job without removing it from the queue.
            const Job& next_job = m_jobs.top();
            auto now = std::chrono::system_clock::now();

            // Check if it's time to execute the job.
            if (now >= next_job.execution_time) {
                execute_job(next_job);
                // The job is done, so remove it from the queue.
                m_jobs.pop();
            } else {
                // If it's not time, sleep for a short duration to prevent busy-waiting.
                // std::this_thread::sleep_for(std::chrono::seconds(1));
                Sleep(1000);
            }
        }
    }
};

// The main function is now responsible for user interaction and orchestrating the app.
int main() {
    Scheduler scheduler;

    std::cout << "--- Simple C++ Cron System ---" << std::endl;
    std::cout << "Enter commands and epoch times." << std::endl;
    std::cout << "Type 'run' when you are finished adding jobs to start the scheduler." << std::endl;
    
    std::string command;
    long long epoch_time;

    // --- Part 1: Get all jobs from the user ---
    while (true) {
        std::cout << "\n> Command (or 'run'): ";
        std::getline(std::cin, command);

        if (command == "run") {
            break;
        }

        std::cout << "> Epoch Time: ";
        std::cin >> epoch_time;

        if (std::cin.fail()) {
            std::cout << "Invalid epoch time. Please try again." << std::endl;
            std::cin.clear();
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.ignore();
            continue;
        }
        std::cin.ignore();
        // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        scheduler.add_job(command, epoch_time);
    }

    scheduler.run();

    return 0;
}
