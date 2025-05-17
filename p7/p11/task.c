#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD_LEN 256
#define MAX_CMDS 1000

typedef struct {
    char cmd[MAX_CMD_LEN];
    int count;
} Command;

int find_command(Command cmds[], int size, const char *cmd) {
    for (int i = 0; i < size; i++) {
        if (strcmp(cmds[i].cmd, cmd) == 0)
            return i;
    }
    return -1;
}

int is_simple_command(const char *cmd) {
    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] == '/' || cmd[i] == '\\')
            return 0; 
    }
    return 1;
}

int main() {
    char path[512];
    snprintf(path, sizeof(path), "%s/.bash_history", getenv("HOME"));
    
    FILE *fp = fopen(path, "r");
    if (!fp) {
        perror("Не вдалося відкрити .bash_history");
        return 1;
    }
    
    Command cmds[MAX_CMDS];
    int cmds_count = 0;

    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        char *cmd = strtok(line, " \t\n");
        if (!cmd) continue;

        if (!is_simple_command(cmd)) continue;

        int idx = find_command(cmds, cmds_count, cmd);
        if (idx == -1) {
            if (cmds_count < MAX_CMDS) {
                strncpy(cmds[cmds_count].cmd, cmd, MAX_CMD_LEN - 1);
                cmds[cmds_count].cmd[MAX_CMD_LEN - 1] = '\0';
                cmds[cmds_count].count = 1;
                cmds_count++;
            }
        } else {
            cmds[idx].count++;
        }
    }

    fclose(fp);

    int min_count = -1;
    for (int i = 0; i < cmds_count; i++) {
        if (min_count == -1 || cmds[i].count < min_count) {
            min_count = cmds[i].count;
        }
    }

    printf("Найменш використовувані команди (%d разів):\n", min_count);
    for (int i = 0; i < cmds_count; i++) {
        if (cmds[i].count == min_count) {
            printf("%s\n", cmds[i].cmd);
        }
    }

    return 0;
}
