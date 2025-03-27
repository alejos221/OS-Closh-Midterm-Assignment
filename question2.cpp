#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <fstream>

using namespace std;

int main() {
    fstream fs;
    fs.open("text.txt", fstream::in | fstream::out | fstream::app);
    int rc = fork();

    if (rc < 0) {
        cerr << "Fork failed" << endl;
        exit(1);
    } else if (rc == 0) {
        fs << "Child process" << endl;
    } else {
        fs << "Parent process" << endl;
    }
}