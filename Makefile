NAME 			= minishell

CC 				= cc
CFLAGS 			= -g #-Wall -Wextra -Werror 
READLINEFLG 	= -lreadline
LIBFTA			= ./libft/libft.a
OBJS			= $(SRCS:.c=.o)

#signal1.c
SRCS 			= main.c \
				signals.c \
				signals_heredoc.c \
				stack.c \
				delete.c \
				error.c \
				free.c \
				a_static.c \
				analysis_heredoc.c \
				analysis_heredoc_utils.c \
				analysis_redirect.c \
				analysis_quote.c \
				analysis_syntax.c \
				analysis_dollar.c \
				execute.c \
				execution_cmd.c \
				execution_redirect.c \
				execution_io.c \
				child_process.c \
				execution_builtin.c \
				execution_utils.c \
				parse_step-0_blank.c \
				parse_step-1_utils.c \
				parse_step-1_mask.c \
				parse_step-2_handle_tokens.c \
				parse_step-1,2_utils2.c \
				init_envp.c \
				builtin_cd.c \
				builtin_cd_utils.c \
				builtin_echo.c \
				builtin_export.c \
				builtin_export_utils1.c \
				builtin_export_utils2.c \
				builtin_pwd.c \
				builtin_unset.c \
				builtin_utils.c \
				builtin_utils1.c \
				builtin_utils2.c \
				builtin_utils3.c \
				bulitin_env.c \
				builtin_exit.c \
				builtin_exit_utils.c \
				

all: 			$(LIBFTA) $(NAME)

%.o: %.c
				$(CC) $(CFLAGS) -c $< -o $@

$(NAME)			: $(OBJS) $(LIBFTA)
				make bonus -C libft
				$(CC) $(CFLAGS) $(OBJS) $(LIBFTA) $(READLINEFLG) -o $(NAME)

$(LIBFTA) : 
				make -C libft
				cp libft/libft.a .

clean:
				rm -f $(OBJS)
				make clean -C libft

fclean: 
				rm -f $(OBJS)
				rm -f $(NAME)
				rm -f libft.a
				rm -f .cache_exists		
				make fclean -C libft

VALGRIND_LOG = valgrind_log.txt

run: 			$(NAME)
				valgrind --leak-check=full \
				--show-leak-kinds=all \
				--suppressions=suppression_readline.supp \
				--show-reachable=yes \
				--track-fds=yes ./$(NAME) 

re: 			fclean all

.PHONY:			all clean fclean re .cache_exists
