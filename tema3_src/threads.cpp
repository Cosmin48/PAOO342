#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <memory>

// Fire de execuție și semafor
std::mutex coutMutex;
std::condition_variable cv;
bool ready = false;

void workerThread(int id) {
    std::unique_lock<std::mutex> lock(coutMutex);
    std::cout << "Thread " << id << " is waiting." << std::endl;

    // Așteaptă semnalul
    cv.wait(lock, [] { return ready; });

    std::cout << "Thread " << id << " is working." << std::endl;
}

// Mutex-uri/semafoare RAII
class SharedResource {
private:
    std::mutex mutex_;

public:
    void accessResource(int threadId) {
        std::lock_guard<std::mutex> lock(mutex_);
        std::cout << "Thread " << threadId << " is accessing the shared resource." << std::endl;
    }
};

// Pointeri RAII (smart pointers)
void smartPointerExample() {
    std::shared_ptr<int> smartIntPointer = std::make_shared<int>(42);
    std::cout << "Smart Pointer Value: " << *smartIntPointer << std::endl;
}

int main() {
    const int numThreads = 3;

    // Fire de execuție și semafor
    std::thread threads[numThreads];
    for (int i = 0; i < numThreads; ++i) {
        threads[i] = std::thread(workerThread, i + 1);
    }

    // Semafor: notifică toate firele că pot începe să lucreze
    {
        std::lock_guard<std::mutex> lock(coutMutex);
        std::cout << "Main thread signals workers to start." << std::endl;
    }
    ready = true;
    cv.notify_all();

    // Așteaptă ca toate firele să se termine
    for (int i = 0; i < numThreads; ++i) {
        threads[i].join();
    }

    // Mutex-uri/semafoare RAII
    SharedResource sharedResource;
    sharedResource.accessResource(0);

    // Pointeri RAII (smart pointers)
    smartPointerExample();

    return 0;
}
