#ifndef MINISHELL_H
# define MINISHELL_H
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
# include <sys/stat.h>
# include <fcntl.h>
#include <readline/readline.h> 
#include <readline/history.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define BUFFER_SIZE 1024

typedef struct s_data{
	char	**cmd1;
	char	*path1;
	char	**cmd2;
	char	*path2;
	int		read_file;
	int		write_file;
	int		pid1;
	int		pid2;
	int		pipefd[2];
}				t_data;

typedef struct	s_comm
{
	char **cmd;
    int nb_pipe;
    int redir_output;
    int redir_input;
    int single_quote;
    int double_quote;
}				t_comm;

void	ft_lstadd_front(t_comm **alst, t_comm *new);
t_comm	*ft_add_back(t_comm **alst, t_comm *new);
char	**ft_split(char *s, char c);
int	ft_strncmp( char *s1,  char *s2, int n);
int	ft_strlen(char *s);
int if_builtin(char **str);
char	*ft_strcat(char *dest, char *src);
int	ft_strchr(char *s, int c);
t_comm	fill_comm(t_comm comm, char *cmd);
char			*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcat_cmd(char *dest, char *src);
t_data	path2(t_data data, char *command);
t_data	path1(char *command);
void	free_str(char **str);
int	pipex(t_comm comm);
void	create_process(t_data data, t_comm comm);
t_data	uniq_path(t_data data, t_comm comm);
int	get_next_line(int fd, char **line);
void	*ft_calloc(int count, int size);
char	*ft_strdup(char *s);
char	*ft_strjoin_free(char *s1, char *s2, int f);
char	*ft_substr(char *s, int start, int len);
char	*ft_strchr_gnl(char *s, int c);
void	print_comm(t_comm *comm);

#endif