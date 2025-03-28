#ifndef A_STATIC_H
# define A_STATIC_H

#include "main.h"

typedef struct s_struct
{
	void			*ptr;
	struct s_struct	*next;
} t_struct;


int		*f_exitcode(void);
void	*ft_malloc(size_t size);
void	ft_free_all(void);

#endif
