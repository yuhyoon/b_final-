#include "main.h"

char	**create_str_3(t_list **head);
t_list	*get_text_list(t_ready *rdy, int len);
void	create_range_list(t_ready *rdy, char *src, char *mask, t_minish *sh)
{
	int		i;
	char	*tmp;
	
	i = 0;
	while (mask[i] != '\n' && mask[i] != PIPE)
		i++;
	rdy->subsrc = ft_substr(src, 0, i);
	rdy->submsk = get_submask(rdy, rdy->subsrc, mask);
	printf("%s\n", rdy->submsk);
	while (ft_strchr(rdy->submsk, IN_RD + 48) || ft_strchr(rdy->submsk, OUT_RD + 48))
	{
			tmp = ft_strtrim(rdy->submsk, "023");
			free(rdy->submsk);
			rdy->submsk = tmp;			
		printf("%s\n", rdy->submsk);
	}
	if (ft_strchr(rdy->submsk, DOLLAR + 48))
	{
		rdy->text = get_compare_list(rdy, i);
		expension(rdy->text, sh);
		rdy->cmd = create_str_2(&rdy->text);
	}
	else
	{
		rdy->text = get_text_list(rdy, ft_strlen(rdy->submsk));
		rdy->cmd = create_str_3(&rdy->text);
	}
}

t_list	*get_text_list(t_ready *rdy, int len)
{
	int			start;
	int			end;
	int			cur_idx;
	char		*str;
	t_list		*lst;
	
	cur_idx = 0;
	lst = NULL;
	while (cur_idx < len)
	{
		start = strspn(&rdy->submsk[cur_idx], "0");
		cur_idx += start;
		end = strcspn(&rdy->submsk[cur_idx], "0");
		str = ft_substr(rdy->subsrc, cur_idx, end);
		if (ft_strlen(str) == 0)
			free(str);
		else
			ft_lstadd_back(&lst, ft_lstnew(str));
		cur_idx += end;
	}
	return (lst);
}

char	**create_str_3(t_list **head)
{
	int		size;
	char	**str;
	t_list	*tmp;
	int		i;

	size = ft_lstsize(*head);
	str = malloc(sizeof(char *) * (size + 1));
	i = 0;
	tmp = *head;
	while (i < size)
	{
		str[i] = ft_strdup((char *)tmp->content);
		i++;
		tmp = tmp->next;
	}
	str[i] = '\0';
	return (str);
}

void	swap_sub(t_ready *rdy, int cur_idx, int end);
char	*ft_strtrim_all(t_ready *rdy)
{
	int	len;
	int	start;
	int	end;
	int	cur_idx;

	len = ft_strlen(rdy->submsk);
	cur_idx = 0;
	while (cur_idx < len)
	{
		start = strspn(&rdy->submsk[cur_idx], "034");
		cur_idx += start;
		end = strcspn(&rdy->submsk[cur_idx], "034");
		swap_sub(rdy, cur_idx, end);
		cur_idx += end;
	}
}

void	swap_sub(t_ready *rdy, int cur_idx, int end)
{
	char	*srctmp;
	char	*msktmp;

	srctmp = rdy->subsrc;
	msktmp = rdy->submsk;
	rdy->subsrc = ft_substr(srctmp, cur_idx, end);
	rdy->submsk = ft_substr(msktmp, cur_idx, end);
	free(srctmp);
	free(msktmp);
}

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

