int	ft_isalpha(int c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_iswhitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

void	ft_skip_wspaces(char **ptr)
{
	while (ft_iswhitespace(**ptr))
		(*ptr)++;
}