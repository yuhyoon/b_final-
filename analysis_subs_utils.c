#include "main.h"

char	*mask_to_str(int len, char *mask)
{
	char	*str;

	str = malloc(sizeof(char) * (len + 1));
	ft_memset(str, 0, len + 1);
	str = ft_memcpy(str, mask, len);
	return (str);
}

int	ft_ismetas(char *msk)
{
	int	len;
	int	i;
	int	flg;
	int	metas;

	len = ft_strlen(msk);
	i = 0;
	flg = 0;
	metas = 1;
	while(i < len)
	{
		if ((msk[i] - 48) == DOLLAR || (msk[i] - 48) == PIPE)
		{
			flg = flg + (metas * (msk[i] - 48));
			metas *= 10;
		}
		i++;
	}
	return (flg);
}

void	*sep_rdrct(void *con)
{
	t_compare	*cmpr;
	char		*msk_spn;
	char		*src_spn;
	t_compare	*new_cmpr;

	cmpr = con;
	msk_spn = ft_strdup(cmpr->msk_span);
	src_spn = ft_strdup(cmpr->src_span);
	new_cmpr = malloc(sizeof(t_compare));
	new_cmpr->msk_span = msk_spn;
	new_cmpr->src_span = src_spn;
	return (new_cmpr);
}

char	*create_str_1(t_list **head)
{
	char	*str;
	char	*cur;
	char	*next;
	t_list	*lst;

	lst = *head;
	str = NULL;
	while(lst->next != NULL)
	{
		cur = lst->content;
		if (str != NULL)
			cur = str;
		next = lst->next->content;
		str = ft_strjoin(cur, next);
		lst = lst->next;
	}
	if (ft_lstsize(*head) == 1)
		str = ft_strdup((char *)lst->content);
	return (str);
}

