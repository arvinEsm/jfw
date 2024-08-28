
#include <iostream>
#include <cstdio>   // Required for remove() function
#include <cstring>  // Required for strrchr() function
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    // Message to display
    std::cout << "This is your message and u can see that just one time ." << std::endl;

    // Get the path to the current executable
    char path[1024];
    if (readlink("/proc/self/exe", path, sizeof(path) - 1) == -1) {
        std::cerr << "Error: unable to get the executable path" << std::endl;
        return 1;
    }

    // Create a temporary file
    char tempPath[1024];
    strcpy(tempPath, path);
    strcat(tempPath, ".tmp");

    // Fork a new process
    pid_t pid = fork();
    if (pid == -1) {
        std::cerr << "Error: unable to fork a new process" << std::endl;
        return 1;
    }

    // Child process: delete the original executable file
    if (pid == 0) {
        // Wait for the parent process to finish
        sleep(1);

        // Delete the original executable file
        if (remove(path) != 0) {
            std::cerr << "Error: unable to delete the executable" << std::endl;
            return 1;
        }

        // Exit the child process
        return 0;
    }

    // Parent process: continue executing
    std::cout << "Program will now self-destruct..." << std::endl;

    // Wait for the child process to finish
    waitpid(pid, NULL, 0);

    return 0;
}

