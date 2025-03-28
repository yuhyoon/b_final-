#ifndef BUILTIN_H
# define BUILTIN_H

# include "main.h"
typedef struct s_minish t_minish;
typedef struct s_ready t_ready; 
typedef struct s_envp
{
	char			*key;
	char			*value;
	int				count;
	struct s_envp	*next;
}				t_envp;

int				update_envps(t_minish *sh, char *newpwd, char *oldpwd);
int				f_update_pwds(t_minish *sh, char *current_pwd);
void			f_putstr_fd_error_msg(char *builtin, char *msg, char *location, int fd);
int				f_check_params(char *param1, int length);
int				f_cd_process_params(t_minish *sh, t_list *commands);

int				f_cd_root(void);
int				f_cd_goto(char *location);
int				f_cd_home(t_minish *sh);
int				f_cd_go_back(t_minish *sh);
int				f_cd(t_minish *sh);

void			f_print_echo(char **param_list, int option_off);
int				f_check_n_option(char *is_option);
int				check_n_option(char **cmds, int size);
void			process_echo(char **cmds, int size);
unsigned int	f_echo(t_minish *sh, t_ready *rdy);

long long		ft_atol(char *str);
long long		check_input_range(char *arvs);

void			exit_err_msg(char *copy_str, int code);
long long		check_exit_cmd(char *second_cmd);
void			f_exit_only(int exitcode);
void			f_exit_with_msg(int size, char *second_cmd);

void			bubble_sort_envp(char **envp, int count);
void			f_sort_and_store_envp(char **envp, t_envp **sorted_envp);
void			export_err_msg(char *cmds);
void			print_export(t_envp *lst);
void			update_or_add_envps(t_minish *sh, char *cmd);

int				is_valid_name(char *name);
size_t			find_cmd_in_original(char *original_cmd, char *cmd, size_t index_stack);
int				handle_name_case(char **cmd, char *original_cmd, int tmp_i, t_minish *sh);
int				process_envp_update(char **cmd, char *original_cmd, int is_name, t_minish *sh);
void			export_update_or_add(char **cmds, char *original_cmd, t_minish *sh);
int				f_export(t_minish *sh);

int				f_pwd(t_ready *rdy);

void			delete_double_char(t_minish *sh, char *cmd);
int				f_unset(t_minish *sh);

void			free_node_t_envp(t_envp **envp);
int				f_count_char(char **envp);
void			free_double_char(char **double_char);

void			update_envp_array(t_minish *sh, char *cmd);
void			f_init_env(char **envp, t_envp **n_envps);
t_envp			*new_node(char **envp, int idx);
void			delete_t_envp(t_envp **head, char *key);
int				update_t_envp(t_envp *node, char *key, char *value);

t_envp			*create_new_node(char *key, char *value);
int				find_insert_position(t_envp *head, char *key, t_envp **prev, t_envp **current);
int				insert_node(t_envp **head, t_envp *new_node, t_envp *prev, t_envp *current);
int				add_envp_node(t_envp **head, char *key, char *value);

char			*f_getenv(char **custom_envp, char *name);
void			update_or_add_envp_node(t_envp **head, char *set);
int				update_envp_node(t_envp **head, char *key, char *value);


#endif
