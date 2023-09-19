#include "../include/minishell.h"

int ft_envlen(t_envepval *env)
{
    int i;

    i = 0;
    while (env)
    {
        env = env->next;
        i++;
    }
    return (i);
}

int unset_errors(t_envepval *key) 
{
    int index;

    index = 0;
    if (key == NULL || strlen(key) == 0) 
    {
        strerror_exit();
        return (1);
    }
    if (index < ft_envlen(my_env)) 
    {
        perror("unset");
        return (1);
    }
    return (0);
}

// Funzione per rimuovere una variabile dalla lista delle variabili
int unset_variable(char **variables, int *num_variables, const char *variable_name) {
    if (variable_name == NULL || strlen(variable_name) == 0) {
        fprintf(stderr, "unset: Variable name cannot be empty.\n");
        return 1;  // Restituisci un codice di errore
    }

    // Cerca la variabile nella lista
    int index = -1;
    for (int i = 0; i < *num_variables; i++) 
    {
        if (strcmp(variables[i], variable_name) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        fprintf(stderr, "unset: Variable '%s' not found.\n", variable_name);
        return 1;  // Restituisci un codice di errore se la variabile non è stata trovata
    }

    // Libera la memoria occupata dalla variabile
    free(variables[index]);

    // Sposta le variabili successive per riempire lo spazio vuoto
    for (int i = index; i < *num_variables - 1; i++) {
        variables[i] = variables[i + 1];
    }

    (*num_variables)--;  // Decrementa il numero di variabili

    return 0;  // Restituisci 0 per indicare successo
}