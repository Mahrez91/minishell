#include "minishell.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	if (n <= 0)
		return (0);
	printf("s1 = '%s' et s2 = '%s' \n", s1, s2);
	while (n > 1 && (*s1 != '\0' && *s2 != '\0') && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}