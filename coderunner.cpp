#include <cstdio>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <pthread.h>
#include <thread>

using namespace std;

void coderunner() {
    int res_exec = system("cat input.txt | ./codefile > output.txt");
    exit(0);
}

void codekiller() {
    sleep(1);
    
    int res_kill = system("kill `pidof codefile`");
    system("echo Time Limit Exceeded > output.txt");

    exit(0);
}

int main(int argc, char **argv) {
    int res_compile = system("g++ codefile.cpp -o codefile 2> output.txt");
    if (res_compile)
        exit(0);
        
    thread code_runner(coderunner);
    thread code_killer(codekiller);

    code_runner.join();
    code_killer.join();

    return 0;
}