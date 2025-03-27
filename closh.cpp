#include <iostream>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <limits>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

int main() {
    string userInput = "";
    char *myargs[2]; // array of c strings for program name and NULL
    
    cout << "Welcome to Closh! Type exit to quit the shell." << endl;
    do {
        cout << "closh> ";
        cin >> userInput;
        
        if(userInput.find("./") == 0) {     // if the first two characters are "./"
            // Check if the file exists
            ifstream file(userInput.c_str());
            if (!file) {
                cerr << "Error: File " << userInput.substr(userInput.find("./") + 2) << " does not exist." << endl;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');    // Clears the input buffer up to the '/n'
                continue; // skips to the end of the if statement, which loops again from closh>
            }
            file.close();

            char programName[userInput.length()];   // c string of size of userInput
            strcpy(programName, userInput.c_str()); // copy userInput to programName

            myargs[0] = strdup(programName); // program name (ie. "./programName.exe")
            myargs[1] = NULL; // marks end of array

            int count = 0;  // count for number of processes to run
            string temp;    // variable to get parallel or sequential option; used to set isSequential
            bool isSequential = false;
            
            cout << "count> ";
            cin >> count;
            cin.ignore();
            count = min(count, 9);  // limit count to 9
            
            cout << "[p]arallel or [s]equential> ";
            cin >> temp;
            cin.ignore();
            if(temp == "s") {isSequential = true;};
            
            // starts the processes
            for(int i = 0; i < count; i++) {
                int rc = fork(); // returns child process id to parent AND 0 to child
                if (rc < 0) { // Failed fork
                    cout << "Fork failed!";
                    exit(1);
                } else if(rc == 0) { // Child process
                    //cout << "i am children #" << getpid() << endl;
                    if (execvp(myargs[0], myargs) == -1) {  // EXEC
                        cerr << "Error: failed to execute " << programName << endl;
                        exit(1);
                    }
                    
                } else { // Parent process
                    //cout << "i am parent #" << getpid() << ")" << endl;
                    if (isSequential) {wait(NULL);} // if sequential, wait for child to finish EVERY LOOP
                }
            }

            if (!isSequential) {   // if parallel, create all processes and wait for all AT THE END
                for (int i = 0; i < count; i++) {
                    wait(NULL);
                }
            }
        }
        else {
            if (userInput != "exit" && userInput != "") {   
                cout << "Invalid command: " << userInput << endl;
            }
        }
    } while(userInput != "exit");
    return 0;
}