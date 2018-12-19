#include <iostream>
#include <thread>

using namespace std;

int main()
{
    thread t1([](){
                cout << "Hello" << endl;
              });
    t1.join();
    return 0;
}
