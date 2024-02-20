#include <iostream>
#include <thread>
#include <chrono>

void task1()
{
  std::cout << "Thread 1 started\n";
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "Thread 1 ended\n";
}

void task2()
{
  std::cout << "Thread 2 started\n";
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << "Thread 2 ended\n";
}

void task3()
{
  std::cout << "Thread 3 started\n";
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::cout << "Thread 3 ended\n";

   int* ptr = nullptr;
    *ptr = 42;  // Attempting to dereference a null pointer
    std::cout << *ptr << std::endl;  // This line may cause a segmentation fault
  while (1)
  {
    static int count{0};
    std::cout << count++ << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

int main()
{

  std::cout << "Main thread started\n";
  std::thread t1(task1);
  std::thread t2(task2);
  std::thread t3(task3);

  // Wait for all threads to finish
  t1.join();
  t2.join();
  t3.join();

  std::cout << "Main thread ended\n";
  return 0;
}
