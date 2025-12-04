#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int cd(char* path) {
    return chdir(path);
}

int main(int argc, char* argv[])
{
    if (argc > 2) {
        fprintf(stderr, "error: call ./%s or ./%s <path>\n", argv[0], argv[0]);
        return 0;
    }
    char* cwd = NULL;
    cwd = getcwd(cwd, 64);
    printf("%s\n", cwd);

    if (argc == 1) {
        int ret = cd("~/");
        if (ret != 0) {
            fprintf(stderr, "error changind directory\n");
            free(cwd);
            return 0;
        }
        printf("%s -> %s\n", cwd, "$HOME");
    } else if (argc == 2) {
        if (strncmp(argv[1], "/", 1) == 0) {
            int ret = cd(argv[1]);
            if (ret != 0) {
                fprintf(stderr, "error changind directory\n");
                free(cwd);
                return 0;
            }
            printf("%s -> %s\n", cwd, argv[1]);
        } else {
            size_t cwdlen = strlen(cwd);
            size_t cdlen = strlen(argv[1]);
            char* try = malloc((cwdlen + cdlen + 2) * sizeof(char));
            if (!try) {
                fprintf(stderr, "malloc: failed to allocate\n");
                free(cwd);
                return 0;
            }
            strcpy(try, cwd);
            try[cwdlen] = '/';
            strcat(try, argv[1]);
            try[cwdlen + cdlen + 2] = '\0';
            printf("TRY: %s\n", try);

            int ret = cd(try);
            if (ret != 0) {
                fprintf(stderr, "error changind directory");
                free(try);
                free(cwd);
                return 0;
            }
            printf("%s -> %s\n", cwd, try);
            free(try);
        }
    }
    free(cwd);
    return 0;
}
