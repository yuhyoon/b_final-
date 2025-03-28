#include "main.h"
#include "a_static.h"

int *f_exitcode(void)
{
	static int	i;

	return (&i);
}

static t_struct	**get_allocation_list(void)
{
	static t_struct	*allocations;
	
	allocations = NULL;
	return (&allocations);
}

// 1. malloc -> ft_malloc으로 교체
// 2. free 없애기
// 3. exit할 때 ft_free_all(); 사용하면된다.

void	*ft_malloc(size_t size)
{
	void		*ptr;
	t_struct	*new_node;
	t_struct	**allocations;
	ptr = malloc(size);
	if (!ptr)
		*f_exitcode() = 1;
		// sh->exit = 1;
		//exit
	new_node = malloc(sizeof(t_struct));
	if (!new_node)
	{
		free(ptr);
		*f_exitcode() = 1;
	}
	new_node->ptr = ptr;
	allocations = get_allocation_list();
	new_node->next = *allocations;
	*allocations = new_node;
	return (ptr);
}

void	ft_free_all(void)
{
	t_struct	**allocations;
	t_struct	*cur;
	t_struct	*next;
	allocations = get_allocation_list();
	cur = *allocations;
	while (cur)
	{
		next = cur->next;
		free(cur->ptr);
		free(cur);
		cur = next;
	}
	*allocations = NULL;
}
