/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yuhyoon <yuhyoon@42student.gyeongsan.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 13:25:41 by yuhyoon           #+#    #+#             */
/*   Updated: 2024/07/15 10:58:02 by yuhyoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(char *ss, char c)
{
	int	cnt;

	cnt = 0;
	while (*ss != '\0')
	{
		if (*ss != c)
		{
			cnt++;
			while (*ss != '\0' && *ss != c)
				ss++;
		}
		if (*ss == '\0')
			break ;
		ss++;
	}
	return (cnt);
}

static void	free_array(char **abs, int cnt)
{
	int	i;

	i = 0;
	if (!abs)
		return ;
	while (i < cnt)
	{
		free(abs[i]);
		abs[i] = NULL;
		i++;
	}
	free(abs[i]);
	abs[i] = NULL;
	free(abs);
	abs = NULL;
}

char	*alloc_str(char *address, int j)
{
	char	*str;
	int		i;

	str = (char *)malloc((sizeof(char) * j) + 1);
	i = 0;
	while (i < j)
	{
		str[i] = address[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

static void	splited_ss(char *ss, char c, char **abs, int word)
{
	int		cnt;
	int		j;
	int		flg;

	cnt = 0;
	flg = 1;
	while (*ss && cnt < word && abs != NULL)
	{
		j = 0;
		if (*ss != c && flg == 1)
		{
			while (ss[j] != c && ss[j] != '\0')
				j++;
			abs[cnt] = alloc_str(ss, j);
			if (abs[cnt] == NULL)
				free_array(abs, word);
			cnt++;
			flg = 0;
		}
		if (*ss == c)
			flg = 1;
		ss++;
	}
	abs[cnt] = NULL;
}

char	**ft_split(char const *s, char c)
{
	char	**abs;
	char	*ss;
	int		w;

	ss = (char *)s;
	if (ss == NULL)
		return (0);
	w = get_size(ss, c);
	abs = (char **)malloc(sizeof(char *) * (w + 1));
	if (!abs)
		return (0);
	splited_ss(ss, c, abs, w);
	return (abs);
}
// int main(int argc, char **argv)
// {
//	 int n = get_size(argv[1], ' ');
//	 //printf("단어 갯수: %d\n", n);
//	 char **ss = ft_split(argv[1], ' ');
//	 printf("ft_split: %s\n", ss[0]);
//	 printf("ft_split: %s\n", ss[1]);
//	 printf("ft_split: %s\n", ss[2]);
//	 free_array(ss, 3);
// }
