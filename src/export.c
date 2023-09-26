#include "../include/minishell.h"

t_envepval *set_newvariable(char *args)
{
    char          *key;
    char          *val;
    t_envepval    *variable;

    if (!args)
        return (NULL);
    val = ft_strchr(args, '=');
    key = ft_substr(args, 0, (ft_strlen(args) - ft_strlen(val)));
    val++;
    variable = create_env_node(key, val);
    return (variable);
}

int ft_export(t_env *env, char **args)
{
    t_envepval	*new_variable;
    int i;

    i = 1;
    if (!args[i])
        print_my_env(env->env);
    if (ft_strchr(args[i], '=') != NULL)
    {
        new_variable = set_newvariable(args[i]);
        if (new_variable != NULL)
        {
            envlst_add(&env->env, new_variable);
            //here update the env with the variable;
            //print_my_env(env->env);
            //new_variable->next = NULL;
        }
    }
    return (0);
}    

// int ft_export(t_env *env, char **args)
// {
//     int i = 1;

//     // Se non ci sono argomenti specificati, stampa l'ambiente corrente
//     if (!args[i]) {
//         print_my_env(env->env);
//         return 0;
//     }

//     // Itera attraverso gli argomenti e aggiungi le variabili all'ambiente
//     while (args[i]) {
//         // Verifica se l'argomento contiene un segno uguale (=)
//         char *equal_sign = ft_strchr(args[i], '=');
//         if (equal_sign != NULL) {
//             // Estrai la chiave e il valore dalla stringa
//             char *key = ft_substr(args[i], 0, equal_sign - args[i] + 1);
//             char *val = ft_strdup(equal_sign + 1); // +1 per saltare il segno uguale

//             // Crea un nuovo nodo t_envepval con la chiave e il valore
//             t_envepval *new_variable = create_env_node(key, val);

//             // Stampa la chiave e il valore per debug
//             printf("Key: %s, Value: %s\n", new_variable->key, new_variable->val);

//             // Aggiungi il nuovo nodo all'ambiente
//             envlst_add(&(env->env), new_variable);
//         }

//         i++;
//     }

//     return 0;
// }



// int main()
// {
//     char    variabile[50] = "Ciao_Sono_Francesco Ciao_sono_Antonio";
//     char    *variabile_new_env;
//     variabile_new_env = set_newvariable(variabile);
//     printf("%s\n", variabile_new_env);
// }