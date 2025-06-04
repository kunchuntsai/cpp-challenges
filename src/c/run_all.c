#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

#define MAX_PATH 1024
#define MAX_EXAMPLES 100

typedef struct {
    char name[MAX_PATH];
    char path[MAX_PATH];
} Example;

// Function to check if a file is executable and not a directory
int is_executable(const char *path) {
    struct stat st;
    if (stat(path, &st) == 0) {
        return (st.st_mode & S_IXUSR) != 0 && !S_ISDIR(st.st_mode);
    }
    return 0;
}

// Function to check if a directory is one of our practice directories
int is_practice_dir(const char *name) {
    const char *practice_dirs[] = {"memory", "strings", "arrays", "bits", "system", NULL};
    for (int i = 0; practice_dirs[i] != NULL; i++) {
        if (strcmp(name, practice_dirs[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// Function to collect all executable examples
int collect_examples(const char *build_dir, Example *examples, int max_examples) {
    DIR *dir;
    struct dirent *ent;
    int count = 0;
    char path[MAX_PATH];

    // Open the build directory
    if ((dir = opendir(build_dir)) == NULL) {
        perror("Error opening build directory");
        return -1;
    }

    // Read all entries in the directory
    while ((ent = readdir(dir)) != NULL && count < max_examples) {
        // Skip . and .. directories
        if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
            continue;
        }

        // Skip non-practice directories
        if (!is_practice_dir(ent->d_name)) {
            continue;
        }

        // Construct full path
        snprintf(path, sizeof(path), "%s/%s", build_dir, ent->d_name);

        // Check if it's a directory
        struct stat st;
        if (stat(path, &st) == 0 && S_ISDIR(st.st_mode)) {
            // Search for executables in the directory
            DIR *subdir;
            struct dirent *subent;
            if ((subdir = opendir(path)) != NULL) {
                while ((subent = readdir(subdir)) != NULL && count < max_examples) {
                    if (strcmp(subent->d_name, ".") == 0 || strcmp(subent->d_name, "..") == 0) {
                        continue;
                    }

                    char subpath[MAX_PATH];
                    snprintf(subpath, sizeof(subpath), "%s/%s", path, subent->d_name);

                    if (is_executable(subpath)) {
                        strncpy(examples[count].name, subent->d_name, sizeof(examples[count].name) - 1);
                        strncpy(examples[count].path, subpath, sizeof(examples[count].path) - 1);
                        count++;
                    }
                }
                closedir(subdir);
            }
        }
    }

    closedir(dir);
    return count;
}

// Function to run an example
void run_example(const char *path) {
    printf("\nRunning %s...\n", path);
    printf("----------------------------------------\n");
    
    // Fork and execute the program
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        execl(path, path, NULL);
        perror("Error executing program");
        exit(1);
    } else if (pid > 0) {
        // Parent process
        int status;
        waitpid(pid, &status, 0);
    } else {
        perror("Error forking process");
    }
    
    printf("----------------------------------------\n");
}

int main(int argc, char *argv[]) {
    const char *build_dir = "build";
    Example examples[MAX_EXAMPLES];
    int num_examples;

    // Collect all executable examples
    num_examples = collect_examples(build_dir, examples, MAX_EXAMPLES);
    if (num_examples < 0) {
        fprintf(stderr, "Error collecting examples\n");
        return 1;
    }

    if (num_examples == 0) {
        printf("No executable examples found in %s directory\n", build_dir);
        return 1;
    }

    printf("Found %d executable examples:\n", num_examples);
    for (int i = 0; i < num_examples; i++) {
        printf("%d. %s\n", i + 1, examples[i].name);
    }

    // If a specific example is requested
    if (argc > 1) {
        for (int i = 0; i < num_examples; i++) {
            if (strcmp(examples[i].name, argv[1]) == 0) {
                run_example(examples[i].path);
                return 0;
            }
        }
        printf("Example '%s' not found\n", argv[1]);
        return 1;
    }

    // Run all examples
    printf("\nRunning all examples...\n");
    for (int i = 0; i < num_examples; i++) {
        run_example(examples[i].path);
    }

    return 0;
} 