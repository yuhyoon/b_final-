#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>
#include <dirent.h>
#include <errno.h>
#include "libft/libft.h"
#include "builtin.h"
#include "delete.h"

int *f_exitcode(void);
typedef struct s_minish
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
	int				exitcode;
}t_minish;

typedef struct s_ready t_ready; 

pid_t	create_process(t_ready *rdy, t_minish *sh);



// signal
void	set_signal(void *handler);
void	set_signal_fork(void);
void	before_readline(int signal);
void	after_cat_grep_c(int signal);

//signal_heredoc
void	sig_handler_heredoc(int signo);
void 	set_signal_heredoc(void);
void 	set_signal_fork_heredoc(void);
void	update_envp_array(t_minish *sh, char *cmd);
void	set_signal_cat_grep(void *handler);
int		process_envp_update(char **cmd, char *original_cmd, int is_name, t_minish *sh);

//builtins
int		init_envp(t_minish *sh, char **envp);
int		f_cd(t_minish *sh);
unsigned int	f_echo(t_minish *sh, t_ready *rdy);
// int		f_echo(t_minish *sh);

// int		f_pwd(void);
int			f_pwd(t_ready *rdy);
int			f_exit(t_minish *sh, t_ready *rdy);

int			f_env(t_minish *sh);
int			f_export(t_minish *sh);
int			f_unset(t_minish *sh);

// int		ff_pwd(t_ready *rdy);

int			f_cd_home(t_minish *sh);
int			f_cd_go_back(t_minish *sh);
int			update_envps(t_minish *sh, char *newpwd, char *oldpwd);
int			f_update_pwds(t_minish *sh, char *current_pwd);
void		update_or_add_envps(t_minish *sh, char *cmd);


int			*f_exitcode(void);

#endif
