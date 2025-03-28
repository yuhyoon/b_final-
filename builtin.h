#ifndef BUILTIN_H
# define BUILTIN_H

# include "main.h"

//환경변수 관리용 구조체
typedef struct s_envp
{
	char			*key;
	char			*value;
	int				count;
	struct s_envp	*next;
}				t_envp;

int		f_count_char(char **envp);
void	free_double_char(char **double_char);

t_envp	*new_node(char **envp, int idx);
void	f_init_env(char **envp, t_envp **n_envps);

void	bubble_sort_envp(char **envp, int count);
// void	f_sort_and_store_envp(char *envp, t_envp **sorted_envp);
void	f_sort_and_store_envp(char **envp, t_envp **sorted_envp);

// void	free_n_envps(t_envp **envp);
void	free_node_t_envp(t_envp **envp); //전이름 : free_n_envps
int		add_envp_node(t_envp **head, char *key, char *value);

int		update_t_envp(t_envp *node, char *key, char *value);
// char	*find_get_t_envp(t_envp *node, char *key);
int		update_envp_node(t_envp **head, char *key, char *value);
// void	update_or_add_envp_node(t_envp **head, char *key, char *value);
void	update_or_add_envp_node(t_envp **head, char *set);
void	delete_t_envp(t_envp **head, char *key); // void	delete_envp_node(t_envp **head, char *key);

void	print_export(t_envp *lst);
void	export_err_msg(char *cmds);
char	*get_name_in_value(char *value, int *i);
int		is_valid_name(char *name);


//bulitin export utils
// t_envp *merge_sorted_lists(t_envp *a, t_envp *b);
// void split_list(t_envp *source, t_envp **front, t_envp **back);
// void merge_sort(t_envp **head_ref);

char    *f_getenv(char **custom_envp, char *name);
// void print_export_sorted(t_envp *lst);
// void bubble_sort(t_envp **array, int size);
// int list_size(t_envp *lst);

int f_cd_root(void);
int f_cd_goto(char *location);
void f_putstr_fd_error_msg( char *builtin,  char *msg,  char *location, int fd);
int f_check_params(char *param1, int length);


#endif
