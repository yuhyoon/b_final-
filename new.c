#include "main.h"

char **create_newsrc(t_ready *rdy, char *src, char *mask, t_minish *sh);
int e(t_minish *sh, t_ready *rdy);
char *get_variable_new(char *mask, char *src, t_minish *sh);
void f(char *submsk, char *subsrc, int fd, t_minish *sh);
int check_env_value(char *env_value, int fd, char *submsk, char *subsrc);
int pipex_get_size(char *s, int len);
char **pipex_splited(char *s_dup, int w, char **abs);

char **create_newsrc(t_ready *rdy, char *src, char *mask, t_minish *sh)
{
	int i;
	int size;
	int newsrc_len;
	char **cmd;

	i = 0;
	while (mask[i] != '\n' && mask[i] != PIPE)
		i++;
	rdy->subsrc = ft_substr(src, 0, i);
	rdy->submsk = get_submask(rdy->subsrc, mask);
	newsrc_len = e(sh, rdy);
	size = pipex_get_size(rdy->newsrc, newsrc_len);
	cmd = (char **)malloc(sizeof(char *) * (size + 1));
	if (!cmd)
		return (NULL);
	cmd = pipex_splited(rdy->newsrc, size, cmd);
	return (cmd);
}

int e(t_minish *sh, t_ready *rdy)
{
	int newsrc_fd;
	t_char_state char_state;
	char *src_regnrte;
	int len;

	newsrc_fd = open("newsrc_fd", O_RDWR | O_CREAT | O_TRUNC, 0644);
	init_char_state(&char_state, rdy->submsk);
	f(rdy->submsk, rdy->subsrc, newsrc_fd, sh);
	close(newsrc_fd);
	newsrc_fd = open("newsrc_fd", O_RDONLY);
	rdy->newsrc = read_maskfd(newsrc_fd, &len);
	close(newsrc_fd);
	unlink("newsrc_fd");
	return (len);
}

void f(char *submsk, char *subsrc, int fd, t_minish *sh)
{
	int i;
	char *env_value;

	i = 0;
	while (submsk[i] != '\0')
	{
		if (submsk[i] - 48 == NONE)
			i += write(fd, "", 1);
		else if (submsk[i] - 48 == TEXT)
			i += write(fd, &subsrc[i], 1);
		else if (submsk[i] - 48 == DOLLAR)
		{
			env_value = get_variable_new(&submsk[i], &subsrc[i], sh);
			i += check_env_value(env_value, fd, &submsk[i], &subsrc[i]);
			free(env_value);
		}
		else if (submsk[i] - 48 == QUOTE || (submsk[i] - 48 > TEXT && submsk[i] - 48 < DOLLAR))
			i++;
	}
}

int check_env_value(char *env_value, int fd, char *submsk, char *subsrc)
{
	int	i;

	i = 0;
	if (ft_strlen(env_value) == 1 && *env_value == '$')
		i += write(fd, env_value, ft_strlen(env_value));
	else if (ft_strlen(env_value) == 0)
		i += ft_strcspn(&submsk[i], "0");
	else
	{
		ft_putstr_fd(env_value, fd);
		if (subsrc[i + 1] == '?')
			i += 2;
		else
			i += ft_strcspn(&submsk[i], "0");
	}
	return (i);
}

char *get_variable_new(char *mask, char *src, t_minish *sh)
{
	int i;
	char *rsult;

	i = 1;
	if (mask[i] == '\0' || mask[i] - 48 == 0 || mask[i] - 48 == '\n')
		rsult = ft_substr(src, 0, 1);
	else if (src[i++] == '?')
		rsult = ft_itoa(*f_exitcode());
	else if (mask[--i] - 48 == QUOTE)
	{
		rsult = ft_substr(src, ++i, (ft_strspn(&mask[i], "1") - 1));
	}
	else
	{
		while (mask[i] - 48 == 1)
			i++;
		rsult = valid_env(ft_substr(src, 1, i - 1), sh);
	}
	return (rsult);
}

int pipex_get_size(char *s, int len)
{
	int i;
	int cnt;

	i = 0;
	cnt = 0;
	while (i < len)
	{
		if (s[i] != '\0')
		{
			cnt++;
			while (i < len && s[i] != '\0')
				i++;
		}
		if (i >= len)
			break;
		i++;
	}
	return (cnt);
}

char **pipex_splited(char *s_dup, int w, char **abs)
{
	int cnt;
	int index_jump;

	cnt = 0;
	while (cnt < w)
	{
		while (*s_dup == '\0')
			s_dup++;
		abs[cnt] = ft_strdup(s_dup);
		index_jump = ft_strlen(abs[cnt]);
		s_dup = s_dup + index_jump;
		cnt++;
	}
	abs[cnt] = NULL;
	return (abs);
}
