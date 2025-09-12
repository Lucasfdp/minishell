#include "libft.h"

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\f')
		return (1);
	return (0);
}
