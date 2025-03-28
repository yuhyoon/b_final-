/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeyeom <hyeyeom@42student.gyeongsan.kr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 15:05:44 by hyeyeom           #+#    #+#             */
/*   Updated: 2025/03/17 14:55:22 by hyeyeom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	exit_err_msg(char *copy_str, int code)
{
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
	if (copy_str)
	{
		ft_putstr_fd(copy_str, STDOUT_FILENO);
		ft_putstr_fd(": ", STDOUT_FILENO);
	}
	if (code == 1)
		ft_putstr_fd("too many arguments\n", STDOUT_FILENO);
	else if (code == 2)
		ft_putstr_fd("numeric argument required\n", STDOUT_FILENO);
	exit(code);
}


int check_exit_cmd(char *second_cmd)
{
    int     code;
    char    *tmp;

    code = 0;
    tmp = second_cmd;
    while (*tmp)
    {
        if (ft_isalnum(*tmp) != 4)
            break;
        (*tmp)++;
    }
    if (*tmp != '\0')
        code = -1;
    else
    {
        code = ft_atoi(second_cmd);
        printf("[%s] %d\n", second_cmd, code);
    }
    return (code);
}

void    f_exit_only(int exitcode)
{
    *f_exitcode() = 0;
    ft_putstr_fd("exit\n", STDERR_FILENO);
    exit(0);
}

void    f_exit_with_msg(int size, char *second_cmd)
{
    int code;
   
    code = check_exit_cmd(second_cmd);

    if (size == 2)
    {
        if (code > 0)
            f_exit_only(code);
        else if (code == -1)
            exit_err_msg(second_cmd, STDERR_FILENO);
    }
    else if (size > 2)
    {
    //  second_cmd 가 유효하지 않은데 (e.g. 214748364a7) too many 면 numeric 우선
    //  second_cmd 가 유효한데 (e.g. 2147483647) too many 면 too many
        if (code == -1)
            exit_err_msg(second_cmd, 2);
        else
            exit_err_msg(NULL, 1);
    }
}

//free_minish 입력 시 void로 변경
int f_exit(t_minish *sh, t_ready* rdy)
{
    // t_list  *commands;
    // commands = (((t_ready *)(sh->ready->content))->text);
    char    **cmds;
    int     size;
    
    *f_exitcode() = 0;
    cmds = ((t_ready *)sh->ready->content)->cmd;
    printf("cmd : %s\n", cmds[0]);
    printf("cmd : %s\n", cmds[1]);
    size = f_count_char(cmds);
    if (size == 1)
        f_exit_only(0);
    else if (size > 1)
        f_exit_with_msg(size, cmds[1]);
    exit(0); //free_minish
}


// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   builtin_exit.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: yuhyoon <yuhyoon@student.42.fr>            +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/03/09 15:05:44 by hyeyeom           #+#    #+#             */
// /*   Updated: 2025/03/26 15:23:24 by yuhyoon          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "main.h"

// long long	ft_atol(char *str)
// {
// 	long long	res;
// 	int			sign;

// 	res = 0;
// 	sign = 1;
// 	if (*str == '\t' || *str == '\n' || *str == '\v' || *str == '\f'
// 		|| *str == '\r' || *str == ' ')
// 		str++;
// 	if (*str == '+' || *str == '-')
// 	{
// 		if (*str == '-')
// 			sign *= -1;
// 		str++;
// 	}
// 	while ('0' <= *str && *str <= '9')
// 	{
// 		res = res * 10 + *str - '0';
// 		str++;
// 	}
// 	return (sign * res);
// }

// long long	check_input_range(char *arvs)
// {
// 	int			z_cnt;
// 	int			length;
// 	long long	arv_atol;

// 	z_cnt = 0;
// 	if (arvs[0] == '-')
// 		z_cnt++;
// 	while (arvs[z_cnt] == '0')
// 		z_cnt++;
// 	length = ft_strlen(arvs);
// 	if (length == z_cnt)
// 		return (0); //모든 수가 0일때
// 	arv_atol = ft_atol(arvs);
//     printf("%lld\n", arv_atol);
// 	// if (ft_strlen(arvs + z_cnt) > 10)
//     //     return (0); // 에러
// 	return (1);
// }

// void	exit_err_msg(char *copy_str, int code)
// {
//     ft_putstr_fd("exit\n", STDOUT_FILENO);
// 	ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
// 	if (copy_str)
// 	{
// 		ft_putstr_fd(copy_str, STDOUT_FILENO);
// 		ft_putstr_fd(": ", STDOUT_FILENO);
// 	}
// 	if (code == 1)
// 		ft_putstr_fd("too many arguments\n", STDOUT_FILENO);
// 	else if (code == 2)
// 		ft_putstr_fd("numeric argument required\n", STDOUT_FILENO);
// 	exit(code);
// }

// long long check_exit_cmd(char *second_cmd)
// {
//     long long   code;
//     char        *tmp;

//     code = check_input_range(second_cmd);
//     tmp = second_cmd;
//     if (second_cmd[0] == '-')
//         return (4);
//     while (*tmp)
//     {
//         if (ft_isalnum(*tmp) != 4)
//             break ;
//         tmp++;
//     }
//     if (*tmp != '\0')
//         code = 2;
//     return (code);
// }

// void    f_exit_only(int exitcode)
// {
//     ft_putstr_fd("exit\n", STDERR_FILENO);
//     exit(*f_exitcode());
// }

// void    f_exit_with_msg(int size, char *second_cmd)
// {
//     int code;
   
//     code = check_exit_cmd(second_cmd);
//     if (size == 2)
//     {
//         if (code == -1)
//             exit_err_msg(second_cmd, STDERR_FILENO);
//         else
//             f_exit_only(code);
//     }
//     else if (size > 2)
//     {
//         if (code == -1)
//             exit_err_msg(second_cmd, 2);
//         else
//             exit_err_msg(NULL, 1);
//     }
// }

// // int f_exit(t_minish *sh) 
// int f_exit(t_minish *sh, t_ready *rdy)
// {
//     char    **cmds;
//     int     size;
    
//     // cmds = ((t_ready *)sh->ready->content)->cmd;
//     cmds = rdy->cmd;
//     size = f_count_char(cmds);
//     *f_exitcode() = 0;
//     if (size == 1)
//         f_exit_only(*f_exitcode());
//     else if (size > 1)
//         f_exit_with_msg(size, cmds[1]);
//     return (0);
// }
