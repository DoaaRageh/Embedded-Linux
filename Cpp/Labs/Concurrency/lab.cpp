#include <iostream>
#include <thread>

void beeb(int delay)
{
    while (true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(delay));
        std::cout << '\a' << std::endl;
    }
}

void stop()
{
    char input;
    while (true)
    {
        std::cout << "Press Enter to stop beeping" << std::endl;
        input = std::cin.get();
        if (input == '\n')
        {
            exit(0);
        }
    }
}

int main()
{
    std::thread t1(beeb, 3);
    std::thread t2(stop);
    t1.join();
    t2.join();
}