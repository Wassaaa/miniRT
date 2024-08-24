#include <miniRT.h>

int	array_len(char **array)
{
	int	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}

void	free_parser(char **element, char *err_msg)
{
	if (!element)
		error_exit(err_msg);
	while (*element)
	{
		ft_free((void **)&(*element));
		element++;
	}
	ft_free((void **)element);
	if (err_msg)
		error_exit(err_msg);
}

void	error_exit(char *err_msg)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	clear_lal();
	exit(EXIT_FAILURE);
}

char	**split_line(char *line)
{
	char	**element;
	char	*line_trim;

	line_trim = ft_safe_strtrim(line, " \t\n\v\f\r");
	if (*line_trim == '\0' || *line_trim == '\n')
		return (NULL);
	element = ft_safe_split(line_trim, " \t\n\v\f\r"); //need to free later
	ft_free((void **)&line_trim);
	return (element);
}

char	**ft_safe_split(char const *s, char *set)
{
	char	**str;
	char	**tmp;

	str = ft_split_new(s, set);
	if (!str)
		error();
	tmp = str;
	while (*tmp)
	{
		add_to_lal(*tmp);
		tmp++;
	}
	add_to_lal(str);
	return (str);
}

t_list	*ft_safe_lstnew(void *content)
{
	t_list	*new_list;

	new_list = ft_lstnew(content);
	if (!new_list)
		error();
	add_to_lal(new_list);
	return (new_list);
}

char	*ft_safe_strtrim(char const *s1, char const *set)
{
	char	*s1_trim;

	s1_trim = ft_strtrim(s1, set);
	if (!s1_trim)
		error();
	add_to_lal(s1_trim);
	return (s1_trim);
}
