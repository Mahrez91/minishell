int check_fulln(char *str)
{
    int i;
    
    i = 1;
    while (str[i])
    {
        if (str[i] != 'n')
            return (1);
        i++;
    }
    return (0);
}

int check_inenv(char *str);