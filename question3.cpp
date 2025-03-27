#include <iostream>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

int main() {
    int rc = fork();

    if (rc < 0) {
        cerr << "Fork failed" << endl;
        exit(1);
    } else if (rc == 0) {
        cout << "Child process" << endl;
    } else {
        int a;
        cin >> a;
        cout << "Parent process" << endl;
    }
}