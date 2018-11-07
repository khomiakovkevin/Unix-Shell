#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>

// Used to get the sublist
void helper_for_operate(char * output[], char * input[], int k, int n) {
    for (int i = 0; i < (n - k); i++) {
        output[i] = input[k + i];
    }

    output[n - k] = NULL;

    exit(0);
}

// Used to complete the commands
void complete(int argc, char * args[], char * chd, int cf, int f) {

    char * ex = "exit";
    char * cd = "cd";
    char * arr = args[0];

    int fd[2];
    int cpid;
    int st;

    if (argc < 1) {
        return;
    }

    if (strcmp(arr, ex) == 0) {
        exit(0);
    }

    if (argc > 1 && strcmp(arr, cd) == 0) {
        char * d = args[1];
        chdir(d);
        return;
    }

    if (cpid = fork()) {
        if (f == 1) {
            return;
        }

        waitpid(cpid, & st, 0);

    } else {
        switch (cf) {
        case 20:
            fd[0] = open(chd, O_RDONLY);

            dup2(fd[0], STDIN_FILENO);

            close(fd[0]);

            break;

        case 10:

            fd[0] = open(chd, O_WRONLY | O_CREAT, 0666);

            dup2(fd[0], STDOUT_FILENO);

            close(fd[0]);

            break;
        }

        execvp(arr, args);

        exit(1);
    }
}

// Used to deal with the operators
void operate(char * c) {

    char * line = " \n";
    char * tok = strtok(c, line);
    char * arr[80];
    char * es = "";

    arr[0] = tok;


    int n = 0;
    int fd;
    int f = 0;

    while (tok != NULL) {
        tok = strtok(NULL, line);
        arr[++n] = tok;
    }

    for (int i = 1; i < n; i++) {

        if (strcmp(arr[i], ">") == 0 && i + 1 < n) {

            char * c[i + 1];

            helper_for_operate(c, arr, 0, i);
            complete(i, c, arr[i + 1], 10, f);

        } else if (strcmp(arr[i], "<") == 0 && i + 1 < n) {

            char * c[i + 1];

            helper_for_operate(c, arr, 0, i);
            complete(i, c, arr[i + 1], 20, f);

        } else if (strcmp(arr[i], "&") == 0) {
            f = 1;

        } else if (((strcmp(arr[i], "&&") == 0) && (strcmp(arr[0], "false") != 0))) {

                int ab = n - (i + 1);

                char * bb[i + 1];
                char * cab[ab + 1];

                helper_for_operate(bb, arr, 0, i);
		complete(i, bb, es, 0, f);

                helper_for_operate(cab, arr, i + 1, n);
                complete(ab, cab, es, 0, f);

        } else if ((strcmp(arr[i], "||") == 0) && (strcmp(arr[0], "false") == 0)) {
                int ab = n - (i + 1);

                char * cab[ab + 1];

                helper_for_operate(cab, arr, i + 1, n);
                complete(ab, cab, es, 0, f);

        } else if ((strcmp(arr[i], "||") == 0) && (strcmp(arr[0], "false") != 0)){
                char * bb[i + 1];

                helper_for_operate(bb, arr, 0, i);
                complete(i, bb, es, 0, f);
        }
	
    }
        complete(n, arr, es, 0, f);

}

// Used to manipulate with semicolons
void helper_for_main(char * arr) {
    char * str = ";\n";
    char * tok = strtok(arr, str);
    char * args[80];

    int n = 0;

    args[n++] = tok;

    while (tok != NULL) {
        tok = strtok(NULL, str);
        args[n++] = tok;
    }

    for (int i = 0; i < n; i++) {
        operate(args[i]);
    }
}

// Main Function
int main(int argc, char * argv[]) {
    FILE * file;

    char arr[256];
    char * str = "nush$ ";

    if (argc == 1) {
        printf("%s", str);
        fflush(stdout);
        file = stdin;

    } else if (argc > 1) {
        file = fopen(argv[1], "r");
    }

    while (fgets(arr, 256, file) != NULL) {
        helper_for_main(arr);

        if (argc == 1) {
            printf("%s", str);
        }
    }

    return 0;
}
