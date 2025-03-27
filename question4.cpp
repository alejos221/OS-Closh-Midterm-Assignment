#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main() {
    int rc = fork();

    if (rc < 0) {
        cerr << "Fork failed" << endl;
        exit(1);
    } else if (rc == 0) {
        close(STDOUT_FILENO);
        printf("Child process\n");
    } else {
        wait(NULL);
        printf("Parent process\n");
    }
}