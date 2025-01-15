#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 100
#define MAX_LENGTH 100

int read_tac_from_file(const char *filename, char tac[MAX_LINES][MAX_LENGTH])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 0;
    }

    int i = 0;
    while (fgets(tac[i], MAX_LENGTH, file) != NULL && i < MAX_LINES)
    {
        tac[i][strcspn(tac[i], "\n")] = '\0';
        i++;
    }

    fclose(file);
    return i;
}

int dead_code_elimination(char tac[MAX_LINES][MAX_LENGTH], int len, char optimized[MAX_LINES][MAX_LENGTH])
{
    int optimized_len = 0;
    int used_variables[MAX_LINES] = {0};

    for (int i = 0; i < len; i++)
    {
        if (strstr(tac[i], "i") || strstr(tac[i], "j") || strstr(tac[i], "arr"))
        {
            used_variables[i] = 1;
        }
    }

    for (int i = 0; i < len; i++)
    {
        if (used_variables[i])
        {
            strcpy(optimized[optimized_len++], tac[i]);
        }
    }
    return optimized_len;
}

int common_subexpression_elimination(char tac[MAX_LINES][MAX_LENGTH], int len, char optimized[MAX_LINES][MAX_LENGTH])
{
    int optimized_len = 0;
    char last_expr[MAX_LINES][MAX_LENGTH];

    for (int i = 0; i < len; i++)
    {
        int expr_found = 0;

        for (int j = 0; j < optimized_len; j++)
        {
            if (strcmp(tac[i], last_expr[j]) == 0)
            {
                expr_found = 1;
                break;
            }
        }

        if (!expr_found)
        {
            strcpy(optimized[optimized_len], tac[i]);
            strcpy(last_expr[optimized_len], tac[i]);
            optimized_len++;
        }
    }
    return optimized_len;
}

int loop_optimization(char tac[MAX_LINES][MAX_LENGTH], int len, char optimized[MAX_LINES][MAX_LENGTH])
{
    int optimized_len = 0;
    int preserve_labels[MAX_LINES] = {0};
    char loop_labels[MAX_LINES][MAX_LENGTH];
    int loop_label_count = 0;

    for (int i = 0; i < len; i++)
    {
        if (strstr(tac[i], "goto") != NULL)
        {
            char *label_start = strchr(tac[i], ' ') + 1;
            if (label_start != NULL)
            {
                label_start[strcspn(label_start, "\n")] = '\0';
                for (int j = 0; j < len; j++)
                {
                    if (strncmp(tac[j], label_start, strlen(label_start)) == 0 && tac[j][strlen(label_start)] == ':')
                    {
                        preserve_labels[j] = 1;
                        break;
                    }
                }
            }
        }

        if (strchr(tac[i], ':') != NULL)
        {
            strcpy(loop_labels[loop_label_count++], tac[i]);
        }
    }

    for (int i = 0; i < len; i++)
    {
        if (preserve_labels[i] || strchr(tac[i], ':') != NULL)
        {
            strcpy(optimized[optimized_len++], tac[i]);
            continue;
        }

        strcpy(optimized[optimized_len++], tac[i]);
    }

    for (int i = 0; i < loop_label_count; i++)
    {
        strcpy(optimized[optimized_len++], loop_labels[i]);
    }

    return optimized_len;
}

void write_optimized_code_to_file(const char *filename, char optimized[MAX_LINES][MAX_LENGTH], int len)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        perror("Error opening output file");
        return;
    }

    for (int i = 0; i < len; i++)
    {
        fprintf(file, "%s\n", optimized[i]);
    }

    fclose(file);
}

int main()
{
    char tac[MAX_LINES][MAX_LENGTH];
    char optimized[MAX_LINES][MAX_LENGTH];

    int len = read_tac_from_file("input_tac.txt", tac);

    if (len == 0)
    {
        return 1;
    }
    int optimized_len = dead_code_elimination(tac, len, optimized);
    optimized_len = common_subexpression_elimination(optimized, optimized_len, tac);
    optimized_len = loop_optimization(optimized, optimized_len, optimized);
    write_optimized_code_to_file("optimized_tac.txt", optimized, optimized_len);
    printf("Optimized TAC code has been written to 'optimized_tac.txt'.\n");

    return 0;
}
