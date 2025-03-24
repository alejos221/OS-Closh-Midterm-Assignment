#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() {
    // Write C++ code here
    string userInput = "";
    
    cout << "Welcome to Closh! Type exit to quit the shell." << endl;
    do {
        wait(NULL);
        cout << "closh> ";
        cin >> userInput;
        
        if(userInput.find("./") != -1) {
            string programName = userInput.substr(userInput.find("./") + 2);
            char *myargs[2] = {strdup(programName), NULL};

            int count = 0;
            bool isSequential = false;
            
            cout << "count> ";
            cin >> count;
            count = min(count, 9);
            
            cout << "[p]arallel or [s]equential> ";
            string temp;
            cin >> temp;
            if(temp == "s") {isSequential = true;};
            
            for(int i = 0; i < count; i++) {
                int rc = fork(); // returns child process id to parent AND 0 to child
                if (rc < 0) { // Failed fork
                    cout << "Fork failed!";
                    exit(1);
                }
                else if(rc == 0) // Child process
                {
                    cout << "hello bitches (pid:" << (int)getpid() << ")" << endl;
                    // EXEC
                    return 0;
                }
                else { // Parent process
                    cout << "i am parent (pid:" << (int)getpid() << ")" << endl;
                    if (isSequential) {wait(NULL);}
                }
            }
        }
        else {
            if (userInput != "exit") {
                cout << "Invalid command.";
            }
        }
    } while(userInput != "exit");

    return 0;
}