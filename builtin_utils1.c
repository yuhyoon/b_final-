/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 20:31:38 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/23 10:32:11 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	update_envp_array(t_minish *sh, char *cmd)
{
	int		new_count;
	int		i;
	char	**new_envp;

	new_count = sh->envp_count + 1;
	new_envp = (char **)malloc(sizeof(char *) * (new_count + 1)); //main에서 받은 envps 저장
	if (!new_envp)
		return ;
	i = -1;
	while (++i < (sh->envp_count))
	{
		new_envp[i] = ft_strdup(sh->envp[i]);
		if (!new_envp[i])
		{
			while (--i >= 0)
				free(new_envp[i]);
			free(new_envp);
			exit(EXIT_FAILURE);
		}
	}
	new_envp[sh->envp_count] = ft_strdup(cmd);
	new_envp[sh->envp_count + 1] = NULL; // NULL로 종료
	free_double_char(sh->envp);
	sh->envp = new_envp;
}

//시스템 envp 변수 -> node로 할당
// void	f_init_t_envp(char **envp, t_envp **n_envps)
void	f_init_env(char **envp, t_envp **n_envps)
{
	// int		count;
	int		i;
	t_envp	*tmp;

	tmp = new_node(envp, 0);
	*n_envps = tmp;
	i = 0;
    while (envp[++i])
	{
		tmp->next = new_node(envp, i);
		tmp = tmp->next;
	}
	tmp->next = NULL;
}

//노드 추가
//t_envp	*new_t_envp(char **envp, int idx)
t_envp	*new_node(char **envp, int idx)
{
	t_envp	*first;
	char	**split_envp;
    int     count;

    count = f_count_char(envp);
	first = (t_envp *)malloc(sizeof(t_envp));
	if (!first)
		return (NULL);
    split_envp = ft_split(envp[idx], '=');
    first->key = ft_strdup(split_envp[0]);
    if (split_envp[1] == NULL || split_envp[1][0] == '\0')
        first->value = ft_strdup("\0");
    else
        first->value = ft_strdup(split_envp[1]);
    first->count = count;
    first->next = NULL;
	free_double_char(split_envp);
	return (first);
}

//노드 삭제
void	delete_t_envp(t_envp **head, char *key)
{
	t_envp	*current;
	t_envp	*prev;

	if (!head || !*head)
		return ;
	current = *head;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(current->key)) == 0)
		{
			if (prev == NULL)
				*head = current->next;
			else
				prev->next = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

//노드 수정 (value 값만 수정)
int	update_t_envp(t_envp *node, char *key, char *value)
{
	while (node != NULL) 
	{
        if (strcmp(node->key, key) == 0) 
		{
            free(node->value);
            node->value = ft_strdup(value);
            return (1);
        }
        node = node->next;
    }
    return (0);
}

// //노드 key 조회
// char	*find_get_t_envp(t_envp *node, char *key)
// {
// 	while (node != NULL) 
// 	{
//         if (ft_strncmp(node->key, key, ft_strlen(node->key)) == 0) 
//             return (node->value);
//         node = node->next;
//     }
//     return (NULL);
// }

// f_getenv 수정 (이거 env.c 옮겨놓기)
char    *f_getenv(char **custom_envp, char *name)
{
    size_t	name_len;
    int		i;
    
    i = 0;
    if (!name || !custom_envp || ft_strlen(name) == 0)
        return (NULL);
    name_len = ft_strlen(name);
    while (custom_envp[i])
    {
        if (ft_strncmp(custom_envp[i], name, name_len) == 0 && \
		custom_envp[i][name_len] == '=')
            return (&custom_envp[i][name_len + 1]);
        i++;
    }
    return (NULL);
}

//main에서 2개만 받는다고 했을 때, 이게 맞지...
void	update_or_add_envp_node(t_envp **head, char *set)
{
	char	*key;
	char	*value;
	char	**sets;
	int		len;

	len = ft_strlen(set);
	sets = ft_split(set, '=');
	key = ft_strdup(sets[0]);
	value = NULL;
	if (sets[1] == NULL)
	{
		if (set[(len - 1)] == '=')
			value = ft_strdup("\0");
	}
	else
	{
		value = ft_strdup(sets[1]);
		if (!value)
			return ;
	}
	if (update_envp_node(head, key, value) == 1)
		add_envp_node(head, key, value);
	free(key);
	free(value);
	free_double_char(sets);
}

int	update_envp_node(t_envp **head, char *key, char *value)
{
	t_envp	*current;

	current = *head;
	while (current)
	{
		if ((ft_strlen(key) == ft_strlen(current->key)) && ft_strncmp(current->key, key, ft_strlen(current->key)) == 0)
		{
			if (value != NULL)
			{
				free(current->value);
				current->value = ft_strdup(value);
				if (!current->value)
					return (-1);
			}
			return (0);
		}
		current = current->next;
	}
	return (1);
}
