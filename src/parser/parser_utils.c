#include <miniRT.h>

int	array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

void	error_exit(char *err_msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

char	**split_line(char *line)
{
	char **element;

	line = ft_strtrim(line, " \t\n");
	if (*line == '\0' || *line == '\n')
		return (NULL);
	element = ft_safe_split(line, '\t'); //need to free later
	return (element);
}

char	**ft_safe_split(char const *s, char c)
{
	char	**str;

	str = ft_split(s, c);
	if (!str)
		error();
	return (str);
}
