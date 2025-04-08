#include "main.h"

void	create_range_list(t_ready *rdy, char *src, char *mask, t_minish *sh)
{
	int		i;

	i = 0;
	while (mask[i] != '\n' && mask[i] != PIPE)
		i++;
	rdy->subsrc = ft_substr(src, 0, i);
	rdy->submsk = get_submask(rdy, rdy->subsrc, mask);
	rdy->text = get_compare_list(rdy, i);
	//ft_lstmap(sh, sep_redirect, del_compare);
	//expension(rdy->text, sh);
}
/*
void	*sep_redirect(void *sh)
{
	t_list	*rdylst;
	t_ready *rdy;
	t_compare	*cmpr;

	rdylst = ((t_list *)((t_minish *)sh)->ready);
	while (rdylst)
	{
		cmpr = rdy->text;
		while (cmpr)
		{
			if (ft_ismetas() )
			{}
			cmpr = cmpr->
		}
		rdy = rdy->next;
	}
	return ();
}
*/
char	*get_submask(t_ready *rdy, char *subsrc, char *mask)
{
	char	*printable_msk;
	int		i;
	int		len;

	i = 0;
	len = ft_strlen(subsrc);
	printable_msk = mask_to_str(len, mask);
	while (i < len)
	{
		printable_msk[i] += 48;
		i++;
	}
	return (printable_msk);
}

t_list	*get_compare_list(t_ready *rdy, int len)
{
	int			start;
	int			end;
	int			cur_idx;
	t_compare	*compare;
	t_list		*lst;
	
	cur_idx = 0;
	lst = NULL;
	while (cur_idx < len)
	{
		start = strspn(&rdy->submsk[cur_idx], "0");
		cur_idx += start;
		end = strcspn(&rdy->submsk[cur_idx], "0");
		compare = create_compare(rdy, cur_idx, end);
		ft_lstadd_back(&lst, ft_lstnew(compare));
		cur_idx += end;
	}
	return (lst);
}

t_compare	*create_compare(t_ready *rdy, int cur_idx, int end)
{
	char	*src_span;
	char	*msk_span;
	t_compare	*cmpare;

	src_span = ft_substr(rdy->subsrc, cur_idx, end);
	msk_span = ft_substr(rdy->submsk, cur_idx, end);
	cmpare = malloc(sizeof(t_compare));
	cmpare->src_span = src_span;
	cmpare->msk_span = msk_span;
	return (cmpare);
}

