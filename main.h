#ifndef MAIN_H
# define MAIN_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <dirent.h>
# include <errno.h>
# include "libft/libft.h"
# include <limits.h>

typedef struct	s_minish
{
	char			*src;
	char			*mask;
	t_list			*ready;
	pid_t			*child_pids;
	int				cmd_count;
	int				prev_for_pipe;
	char			**envp;
	int				envp_count;
	struct s_envp	*n_envs;
	struct s_envp	*n_export;
	char			*pwd;
	int				built_code;
	int				save_in;
	int				save_out;
}				t_minish;

typedef struct	s_struct
{
	void			*ptr;
	struct s_struct	*next;
}				t_struct;

typedef enum	s_token
{
	NONE,
	TEXT,
	IN_RD,
	OUT_RD,
	DOLLAR,
	PIPE
}				t_token;

typedef struct	s_redrct
{
	char	*obj;
	int		fd;
	int		parts;
	int		access;
	char	type;
}				t_redrct;

typedef struct	s_char_state
{
	int		quote;
	int		quote_seq;
	char	*current;
}				t_char_state;

typedef struct	s_ready
{
	t_list		*text;
	t_list		*rdrct;
	int			rdrct_num;
	char		**cmd;
	t_redrct	*rdrct_in;
	t_redrct	*rdrct_out;
	int			num;
	int			input;
	int			output;
}t_ready;

typedef enum	s_child_state
{
	STATE_CHECK_RDRCT = 1,
	STATE_EXEC_BUILTIN,
	STATE_CHECK_CMD = 127,
	STATE_CHECK_PIPE,
	STATE_EXEC_CMD,
	STATE_COMPLETE
}				t_child_state;

typedef struct s_child_process
{
	int				num;
	t_child_state	state;
	int				*pp;
	char			**cmd;
	char			*exe_path;
	int				input_fd;
	int				output_fd;
	int				bulitin_code;
}t_child_process;
typedef struct	s_stack
{
	int				size;
	struct s_list	*top;
}				t_stack;

typedef struct s_envp
{
	char			*key;
	char			*value;
	int				count;
	struct s_envp	*next;
}				t_envp;

//a_static.h
int				*f_exitcode(void);
void			*ft_malloc(size_t size);
void			ft_free_all(void);

pid_t			create_process(t_ready *rdy, t_minish *sh);
void			parent_proccess(t_minish *sh, t_ready *rdy, pid_t pid, int *pp);

// signal
void			set_signal(void *handler);
void			set_signal_fork(void);
void			before_readline(int signal);
void			after_cat_grep_c(int signal);

//signal_heredoc
void			sig_handler_heredoc(int signo);
void			set_signal_heredoc(void);
void			set_signal_fork_heredoc(void);
void			update_envp_array(t_minish *sh, char *cmd);
void			set_signal_cat_grep(void *handler);

//builtins
int				init_envp(t_minish *sh, char **envp);

int				f_exit(t_minish *sh, t_ready *rdy);
int				f_env(t_minish *sh);

int				f_cd_home(t_minish *sh);
int				f_cd_go_back(t_minish *sh);
int				cd_err_msg(char *location, int exitstatus, int situation);
int				update_envps(t_minish *sh, char *newpwd, char *oldpwd);
int				f_update_pwds(t_minish *sh, char *current_pwd);
void			update_or_add_envps(t_minish *sh, char *cmd);

// # include "parse.h"
// # include "parse_utils.h"

int				ft_strlen_delim(char *s, char delim);
void			init_char_state(t_char_state *state, char *s);
int				is_whitespace(char c);
int				is_quote(char c);
int				ft_ismeta(char *input);
char			*syntax_result2(t_minish *sh, int result, char *mask);

//analysis.h
//syntax
int				syntax_analysis(const char *m, int *len);
int				valid_meta(int token, char *mask);

//quote	
int				valid_quote(char *s, int quote);
int				store_quote_seq(t_char_state *char_state, int len);
int				putchar_quote_state_zero(char *current, int fd);
int				read_store_fd(int fd, int quote_fd);
int				set_char_state(char *s, t_char_state *char_state);

//redirect	
t_redrct		*init_rdrct(void);
int				create_rdrct(char *src, char *mask, t_list **head, int *sig_c);

//dollar	
void			create_text_list(t_ready *rdy, char *src, char *mask, t_minish *sh);
int				get_variable(char *mask, char *src, t_list **head, t_minish *sh);
int				get_plain_text(char *s1, char *s2, char *src, t_list **head);
char			*valid_env(char *tmp, t_minish *sh);
int				count_text(char *mask);

//heredoc	
void			handle_heredoc_child(int write_fd, char *delimeter);
void			handle_heredoc_parent(t_redrct *rdrct, int read_fd, int write_fd, int *sig_c);
void			create_heredoc_pipe(int *read_fd, int *write_fd);
void			f_heredoc(t_redrct *rdrct, int *sig_c);

//heredoc utils
void			restore_terminal(void);
void			close_fd(int fd);


int				update_envps(t_minish *sh, char *newpwd, char *oldpwd);
int				f_update_pwds(t_minish *sh, char *current_pwd);
void			f_putstr_fd_error_msg(char *builtin, char *msg, char *location, int fd);
int				f_check_params(char *param1, int length);
int				f_cd_process_params(t_minish *sh, char **commands);

int				f_cd_root(void);
int				f_cd_goto(char *location);
int				f_cd_home(t_minish *sh);
int				f_cd_go_back(t_minish *sh);
int				f_cd(t_minish *sh, t_ready *rdy);

void			f_print_echo(char **param_list, int option_off);
int				f_check_n_option(char *is_option);
int				check_n_option(char **cmds, int size);
void			process_echo(char **cmds, int size);
unsigned int	f_echo(t_minish *sh, t_ready *rdy);

long long		ft_atol(char *str);
long long		ft_atol_length(char *str);
int				check_input_length(char *arvs);

void			f_exit_only(int exitcode, t_minish *sh);
void			f_exit_args(int size, char *second_cmd, t_minish *sh);
int				check_number_or_not(char *second_cmd);
void			exit_err_msg(char *copy_str, int code, t_minish *sh);


void			bubble_sort_envp(char **envp, int count);
void			f_sort_and_store_envp(char **envp, t_envp **sorted_envp);
void			export_err_msg(char *cmds);
void			print_export(t_envp *lst);
void			update_or_add_envps(t_minish *sh, char *cmd);


//before_norm
void	export_update_or_add(char **cmds, char *original_cmd, t_minish *sh);
int	process_envp_update(char **cmd, int index, char *original_cmd, int is_name, t_minish *sh);
int	is_valid_value2(char **cmd, size_t *index_stack, char *original_cmd, int is_name, t_minish *sh);
int	is_valid_name(char *name);

// int				is_valid_name(char *name);
// size_t			find_cmd_in_original(char *original_cmd, char *cmd, size_t index_stack);
// int				handle_name_case(char **cmd, char *original_cmd, int tmp_i, t_minish *sh);
// int				process_envp_update(char **cmd, char *original_cmd, int is_name, t_minish *sh);
// void			export_update_or_add(char **cmds, char *original_cmd, t_minish *sh);
// int				f_export(t_minish *sh);
int	f_export(t_minish *sh, t_ready *rdy);


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

int				child_process(t_ready *rdy, int *pp, t_minish *sh);
void			*valid_redirect(t_child_process *child, t_ready *rdy, t_minish *sh);
void			init_child_process(t_child_process *child, int *pp, t_ready *rdy, t_minish *sh);
int				execute_bulitin(t_child_process *child, t_minish *sh, t_ready *rdy);

void			err_such(int exit, char *obj);
void			err_permission(int exit, char *obj);
void			err_exec(int exit, char *cmd_name);
void			err_syntax(int syntax_result);

//execute
int				execute(t_minish *sh);
void			wait_childs(t_minish *sh);
int				execute_single_builtin(int bulitin_code, t_minish *sh);
int				execute_single_is_builtin(t_list *lst, t_minish *sh);

//utils
char			**create_str_2(t_list **head);
void			free_splited(char **abs);

//redire		ct
int				find_rdrct(t_ready *rdy);
int				prmssn_rdrct(t_redrct *rdrct);
int				redirect(t_ready *rdy);
void			set_io(t_ready *rdy, t_stack *in, t_stack *out);
void			sort_io(t_stack *in, t_stack *out, t_ready *rdy);
void			redirect_input_b(t_ready *rdy, int *io);
void			redirect_output_b(t_ready *rdy, int *io);

//pipe		
void			set_pipe(t_child_process *child, t_minish *sh);
void			redirect_input(t_child_process *child, t_ready *rdy);
void			redirect_output(t_child_process *child, t_ready *rdy);
void			close_pp(t_child_process *child, t_minish *sh);

//cmd		
char			*get_exepath(t_ready *rdy, t_minish *sh);
char			*find_exepath(char *name, t_minish *sh);
void			*access_exepath(t_child_process *child, t_ready *rdy);
void			execute_cmd(t_child_process *child, t_minish *sh);

//builtin
int				is_builtin(char *cmd_name);

void			dengling(void *content, int size_type);
void			free_minish(t_minish *minish);
void			free_str_array(char **arr);
void			free_all_envps(t_minish *sh);

//parse 		step 0
char			*check_blank(char *mask);

//parse 		step 1
char			*generate_mask(t_minish *sh);
int				write_replace_spaces(char *s, int replace_fd);
int				handle_putchar(t_char_state *char_state, int fd);
int				set_char_state(char *s, t_char_state *char_state);
char			*read_maskfd(int mask_fd, int *len);

//parse 		step 2
void			*parsing(t_minish *sh, int len);
int				handle_pipe(t_minish *sh, t_ready *current_rdy, t_list	**rdrct, int save);
t_list			*init_parsing_structure(t_list **rdy_head);
void			*create_rdy(void);


void			set_signal_fork(void);
void			before_readline(int signal);
void			set_signal(void *handler);
void			set_signal_cat_grep(void *handler);
void			set_signal_heredoc(void);
void			set_signal_fork_heredoc(void);

void			init_stack(t_stack *stack, void *top, int size);
int				is_emthy(t_stack *stack);
void			push(t_stack *stack, void *data);
int				pop(t_stack *stack);
void			*pop2(t_stack *stack);

void			del_text(void *txt);
void			del_redrct(void *rd);
void			del_ready(void *ready);
void			del_stack(void *st);

#endif
