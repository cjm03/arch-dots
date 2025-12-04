#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>

pid_t pid = -1;

void copeSIGINT(int sig) {
    printf("\n 'exit' to quit\n");
    fflush(stdout);
}

typedef enum {
    OP_NONE, OP_SEMICOLON, OP_AND
} OperatorType;

typedef struct {
    char* cmd;
    OperatorType op;
} CommandSegment;

char* trimwhitespace(char* str) {
    while (isspace(*str)) str++;
    if (*str == 0) return str;
    char* end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--;
    *(end + 1) = '\0';
    return str;
}

int harnessCommandLine(char* input, CommandSegment segments[], int max_segments) {
    int count = 0;
    char* start = input;
    char* p = input;
    while (*p && count < max_segments) {
        if (*p == ';') {
            *p = '\0';
            segments[count].cmd = trimwhitespace(start);
            segments[count].op = OP_SEMICOLON;
            count++;
            p++;
            start = p;
        } else if (*p == '&' && *(p + 1) == '&') {
            *p = '\0';
            segments[count].cmd = trimwhitespace(start);
            segments[count].op = OP_AND;
            count++;
            p += 2;
            start = p;
        } else {
            p++;
        }
    }
    if (count < max_segments && *start) {
        segments[count].cmd = trimwhitespace(start);
        segments[count].op = OP_NONE;
        count++;
    }
    return count;
}

int thinking(char* command) {
    char cmdcpy[100];
    strncpy(cmdcpy, command, sizeof(cmdcpy));
    cmdcpy[sizeof(cmdcpy) - 1] = '\0';

    if (strchr(cmdcpy, '|') != NULL) {
        #define MAX_C 10
        char* cmds[MAX_C];
        int ncmds = 0;
        char* pipetok = strtok(cmdcpy, "|");
        while (pipetok != NULL && ncmds < MAX_C) {
            cmds[ncmds++] = trimwhitespace(pipetok);
            pipetok = strtok(NULL, "|");
        }

        int totalpipes = ncmds - 1;
        int pipefd[2 * totalpipes];
        for (int i = 0; i < totalpipes; i++) {
            if (pipe(pipefd + i * 2) < 0) {
                perror("pipe");
                exit(EXIT_FAILURE);
            }
        }

        for (int i = 0; i < ncmds; i++) {
            pid_t pidpipe = fork();
            if (pidpipe < 0) {
                perror("fork");
                exit(EXIT_FAILURE);
            }
            if (pidpipe == 0) {
                if (i != 0) {
                    if (dup2(pipefd[(i - 1) * 2], STDIN_FILENO) < 0) {
                        perror("dup2 stdin");
                        exit(EXIT_FAILURE);
                    }
                }

                if (i != ncmds - 1) {
                    if (dup2(pipefd[i * 2 + 1], STDOUT_FILENO) < 0) {
                        perror("dup2 stdout");
                        exit(EXIT_FAILURE);
                    }
                }

                for (int j = 0; j < 2 * totalpipes; j++) {
                    close(pipefd[j]);
                }

                char* redirIN = NULL;
                char* redirOUT = NULL;
                int appendmode = 0;
                char* segment = cmds[i];
                char* appendpos = strstr(segment, ">>");
                if (appendpos) {
                    *appendpos = '\0';
                    redirOUT = appendpos + 2;
                    appendmode = 1;
                } else {
                    char* outpos = strchr(segment, '>');
                    if (outpos) {
                        *outpos = '\0';
                        redirOUT = outpos + 1;
                    }
                }
                char* inpos = strchr(segment, '<');
                if (inpos) {
                    *inpos = '\0';
                    redirIN = inpos + 1;
                }
                if (redirOUT) redirOUT = strtok(redirOUT, " \t");
                if (redirIN) redirIN = strtok(redirIN, " \t");

                if (redirIN) {
                    int fdin = open(redirIN, O_RDONLY);
                    if (fdin < 0) {
                        perror("open input");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fdin, STDIN_FILENO);
                    close(fdin);
                }
                if (redirOUT) {
                    int fdout;
                    if (appendmode) fdout = open(redirOUT, O_WRONLY | O_CREAT | O_APPEND, 0644);
                    else fdout = open(redirOUT, O_WRONLY | O_CREAT | O_TRUNC, 0644);

                    if (fdout < 0) {
                        perror("open output");
                        exit(EXIT_FAILURE);
                    }
                    dup2(fdout, STDOUT_FILENO);
                    close(fdout);
                }
                char* args[20];
                int argsidx = 0;
                char* parts = strtok(segment, " \t");
                while (parts != NULL && argsidx < 19) {
                    args[argsidx++] = parts;
                    parts = strtok(NULL, " \t");
                }
                args[argsidx] = NULL;
                if (args[0] == NULL) exit(EXIT_SUCCESS);
                if (execvp(args[0], args) < 0) {
                    perror("execvp");
                    exit(EXIT_FAILURE);
                }
            }
        }
        for (int i = 0; i < 2 * totalpipes; i++) {
            close(pipefd[i]);
        }
        for (int i = 0; i < ncmds; i++) {
            wait(NULL);
        }
        return 0;
    }

    char *redir_in = NULL;
    char *redir_out = NULL;
    int append_mode = 0;
    char *temp_cmd = cmdcpy;
    char *append_pos = strstr(temp_cmd, ">>");
    if (append_pos) {
        *append_pos = '\0';
        redir_out = append_pos + 2;
        append_mode = 1;
    } else {
        char *out_pos = strchr(temp_cmd, '>');
        if (out_pos) {
            *out_pos = '\0';
            redir_out = out_pos + 1;
        }
    }
    char *in_pos = strchr(temp_cmd, '<');
    if (in_pos) {
        *in_pos = '\0';
        redir_in = in_pos + 1;
    }
    if (redir_out) redir_out = strtok(redir_out, " \t");
    if (redir_in) redir_in = strtok(redir_in, " \t");
    
    char *input[10]; 
    int i = 0;
    char *parts = strtok(temp_cmd, " ");
    while (parts != NULL && i < 9) {
        input[i++] = parts;
        parts = strtok(NULL, " ");
    }
    input[i] = NULL;

    if (input[0] && strcmp(input[0], "cd") == 0) {
        char cwd[1024];
        if (input[1] == NULL) {
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                char *last_slash = strrchr(cwd, '/');
                if (last_slash && last_slash != cwd)
                    *last_slash = '\0';
                else
                    strcpy(cwd, "/");
                if (chdir(cwd) != 0) {
                    perror("cd");
                    return 1;
                }
            } else {
                perror("getcwd");
                return 1;
            }
        } else {
            if (chdir(input[1]) != 0) {
                perror("cd");
                return 1;
            }
        }
        return 0;
    }

    pid = fork();
    if (pid < 0) {
        perror("Fork Failed");
        return 1;
    }
    if (pid == 0) {
        if (redir_out) {
            int fd;
            if (append_mode)
                fd = open(redir_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
            else
                fd = open(redir_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0) {
                perror("open output");
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        if (redir_in) {
            int fd = open(redir_in, O_RDONLY);
            if (fd < 0) {
                perror("open input");
                exit(1);
            }
            dup2(fd, STDIN_FILENO);
            close(fd);
        }
        
        if (strcmp(input[0], "pwd") == 0) {
            execl("/bin/pwd", "pwd", NULL);
            perror("execl failed");
            exit(1);
        } else if (strcmp(input[0], "uname") == 0) {
            execl("/bin/uname", "uname", NULL);
            perror("uname failed");
            exit(1);
        } else if (strcmp(input[0], "whoami") == 0) {
            execl("/bin/whoami", "whoami", NULL);
            perror("whoami failed");
            exit(1);
            
        } else {
            execvp(input[0], input);
            perror("execvp");
            exit(1);
        }
    } else {
        int status;
        waitpid(pid, &status, 0);
        pid = -1;
        if (WIFEXITED(status))
            return WEXITSTATUS(status);
        else
            return 1;

    }

}

int main(int argc, char* argv[]) {
    int flag = 0;
    char str[100];
    signal(SIGINT, copeSIGINT);
    const char* history = "history.txt";

    while (1) {
        char loc[1024];
        if (getcwd(loc, sizeof(loc)) != NULL) {
            printf("%s sh> ", loc);
        }
        if (fgets(str, sizeof(str), stdin) == NULL) {
            break;
        }
        str[strcspn(str, "\n")] = 0;
        if (strcmp(str, "^C") == 0) {
            break;
        }
        if (strcmp(str, "exit") == 0) {
            printf("Exiting...\n");
            break;
        }
        FILE* fp = fopen(history, "a");
        if (fp == NULL) {
            perror("history file open");
        } else {
            fprintf(fp, "%s\n", str);
            fclose(fp);
        }
        if (strcmp(str, "history") == 0) {
            FILE* fp = fopen(history, "r");
            if (fp == NULL) {
                printf("No history\n");
                continue;
            }
            char line[1000];
            int linenum = 1;
            while (fgets(line, sizeof(line), fp) != NULL) {
                line[strcspn(line, "\n")] = 0;
                printf("%4d  %s\n", linenum++, line);
            }
            fclose(fp);
            continue;
        }
        #define MAX_SEGMENTS 20
        CommandSegment segments[MAX_SEGMENTS];
        int segCount = harnessCommandLine(str, segments, MAX_SEGMENTS);
        int overall = 0;
        for (int i = 0; i < segCount; i++) {
            overall = thinking(segments[i].cmd);
            if (segments[i].op == OP_AND && overall != 0) {
                break;
            }
        }
    }
    return 0;
}
