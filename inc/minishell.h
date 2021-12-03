/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glaverdu <glaverdu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:07:30 by glaverdu          #+#    #+#             */
/*   Updated: 2021/12/03 16:27:28 by glaverdu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <string.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h> 
# include <readline/history.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
# define BUFFER_SIZE 1024
# define CD_TYPE 0
# define ECHO_TYPE 1
# define PWD_TYPE 2
# define EXPORT_TYPE 3
# define UNSET_TYPE 4
# define ENV_TYPE 5
# define EXIT_TYPE 6
# define INFILE 0
# define OUTFILE 1
# define ERROR_RED 1

extern int	g_retval;

typedef struct s_pipe
{
	char			**env;
	int				pipefd[2];
	char			**expenv;
	char			**cmd;
	char			*path;
	int				nb_pipe;
	int				redir_output;
	int				redir_input;
	int				redir_double_input;
	int				single_quote;
	int				double_quote;
	int				retclone;
	char			**redir_temp;
	char			**redir;
	char			*file_to_out;
	char			*file_to_in;
	int				error_parse_red;
	int				read_file;
	int				write_file;
	int				error_syn_red;
	struct s_pipe	*next;
}				t_pipe;

typedef struct s_comm
{
	char			**env;
	char			**expenv;
	char			**cmd;
	char			*path;
	int				nb_pipe;
	int				redir_output;
	int				redir_input;
	int				redir_double_input;
	int				single_quote;
	int				double_quote;
	int				retclone;
	char			**redir_temp;
	char			**redir;
	int				error_parse_red;
	int				read_file;
	int				write_file;
	struct s_comm	*next;
}				t_comm;

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
	t_comm			pipecomm;
}					t_list;

typedef struct s_unset
{
	char	*str;
	char	*s;
	int		i;
	int		type;
	t_list	*temp;
	t_list	*del;
}				t_unset;

typedef struct s_cat
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	k;
	char			*tmp;
}				t_cat;

typedef struct s_red
{
	int	i;
	int	count;
	int	count_temp;
	int	temp_index;
}				t_lred;

typedef struct s_doll
{
	char	*str;
	char	*temp;
	char	*temp2;
	int		i;
	int		j;
	int		c;
}				t_doll;

typedef struct s_pars
{
	int		i;
	int		j;
	int		c;
	char	*cmd_tsplit;
	int		pass_space_for_redir;
}				t_pars;

typedef struct s_uniq
{
	int	k;
	int	retnd;
	int	i;
	int	to_read;
	int	to_write;
	int	status;
}				t_uniq;

typedef struct s_uniqq
{
	char	**path;
	int		k;
	char	*str;
	int		i;
	int		j;
	int		ret;
	int		status;
	char	*tmp;
	int		write_file ;
}				t_uniqq;

typedef struct s_open
{
	int	retnd;
	int	i;
	int	to_read;
	int	to_write;
}				t_open;

typedef struct s_fill
{
	int	i;
	int	red;
	int	redindex;
	int	arg;
	int	argindex;
}				t_fill;

typedef struct s_del
{
	int		i;
	int		j;
	int		k;
	int		c;
	int		type;
	char	*str;
	char	*temp;
	char	*temp2[2];
}				t_del;

// PRINT FUNCTION
void	print_comm(t_comm comm);
void	print_env(t_list **b_list);

// PARSING
void	parsing_pipes(t_comm comm);
int		where_redir(char **str);
int		if_builtin(char **str);
t_comm	fill_comm(char *cmd);
char	*ft_split_command(char *str);
int		error_in_red(char *str);
t_comm	ft_redir_single(char *str);

// BUILD BUILTIN
int		builtin(char **cmd, t_list **a_list, t_list **b_list);
int		build_cd(char **cmd);
int		build_echo(char **cmd);
int		build_pwd(void);
int		build_export(char **cmd, t_list **a_list, t_list **b_list);
int		build_unset(char **cmd, t_list **a_list, t_list **b_list, int type);
int		build_env(t_list **a_list);
int		build_exit(char **cmd);

// EXECUTION
void	exec_cmd(char *s, t_comm comm);

// UTILS
	// flst category
void	make_list(t_list **a_list, char **envp);
void	flstadd_back(t_list **alst, t_list *new);
void	flstclear(t_list **lst, void (*del)(void*));
void	flstadd_front(t_list **alst, t_list *new);
void	flstdelone(t_list *lst, void (*del)(void *));
void	flstiter(t_list *lst, void (*f)(void *));
t_list	*flstlast(t_list *lst);
t_list	*flstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*flstnew(void *content);
int		flstsize(t_list *lst);
	// strcat category
char	*ft_strcat_cote(char *dest, char *src);
char	*ft_strcat(char *dest, char *src);
char	*ft_strcat_red(char *dest, char *src);
char	*ft_strcat_redf(char *dest, char *src);
char	*ft_strcat_red_glu(char *dest, char *src);
char	*ft_strcat_w(char *dest, char *src);
char	*ft_strcat_ns(char *dest, char *src);
char	*ft_strcat_red_glu2(char *dest, char *src);
	// others
void	add_line2(t_list **b_list, char **cmd, int j);
int		ft_atoi(const char *str);
int		is_same(char *s1, char *s2);
char	*getenv2(char *s, t_list **a_list);
void	already_in(t_list **a_list, char *str, int j);
int		is_alphanum(char *s);
void	free_str(char **str);
int		what_path(char **path, char *cmd);
char	*path(char *command, t_list **a_list);
int		ft_count_str(char *s1, char *s2);
char	*ft_itoa(int n);
char	**ft_split(char *s, char c);
int		ft_strncmp( char *s1, char *s2, int n);
int		ft_strlen(char *s);
int		ft_strchr(char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcat_cmd(char *dest, char *src);
void	pipex(t_pipe *data, int i, t_list **a_list, t_list **b_list);
// void	pipex_for_one(t_pip *parse_pip);
void	pipex_read(t_pipe *comm_pip, int i, t_list **a_list, t_list **b_list);
void	pipex_write(t_pipe *comm_pip, int i, t_list **a_list,
			t_list **b_list);
void	pipex_write_read(t_pipe *comm_pip, int i, t_list **a_list,
			t_list **b_list);
int		get_next_line(int fd, char **line);
void	*ft_calloc(int count, int size);
char	*ft_strjoin_free(char *s1, char *s2, int f);
char	*ft_substr(char *s, int start, int len);
char	*ft_strchr_gnl(char *s, int c);
void	ft_lstadd_front(t_comm **alst, t_comm *new);
t_comm	*ft_add_back(t_comm **alst, t_comm *new);
int		ft_double_strchr(char *s, int c);
int		ft_redir_strchr(char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
int		check_fulln(char *str);
int		check_inenv(char *str, t_list **a_list);
void	sort_env(t_list **b_list);
int		check_sorted(t_list **b_list);
void	add_declare(t_list **b_list);
void	add_line(t_list **b_list, char **cmd, int j);
char	*ft_strdup(char *s1);
char	**make_expenv(t_comm comm);
char	*parse_quotes(char **s, t_list **a_list);
int		open_file2(char *file);
int		open_file(char *filename);
int		verif_the_builtin(char **str);
int		ft_double_strchr_file(char *s, int c);

int		no_quotes(char *s);
int		check_doll(char *s);
int		char_alphanum(char c);
char	*after_env(char *s);
char	*fill_doll(char *s, t_list **a_list);
int		unclosed_quotes(char *s);
char	*split_glitch(char *cmd_all);
int		is_red(char c);
int		is_quott(char c);
int		ft_error_parse_red(char **str);
int		pipe_glitch(char *line, t_list **a_list, t_list **b_list);
void	print_pipe(t_pipe *parse_pip);
t_list	*flstnew_comm(t_comm comm);
void	flstadd_back_comm(t_list **alst, t_list *new);
t_pipe	*fill_comm_pip(t_pipe *comm, char *cmd);
void	print_pipe(t_pipe *parse_pip);
void	pipex_suits(t_pipe *parse_pip);
t_pipe	*fill_redir_attribut(t_pipe *parse_pip, int to_read, int to_write);
t_pipe	*open_file_redir(t_pipe *parse_pip);
int		find_builtin(char **str);
int		ft_strlen_glitch(char *s);
char	*remove_glitch(char *s);
int		w_redirection(t_comm comm, t_list **a_list, t_list **b_list, char *str);
int		r_redirection(t_comm comm, t_list **a_list, t_list **b_list, char *str);
int		rw_redirection(t_comm comm, t_list **a_list, t_list **b_list,
			char *str);
int		red_uniq_comm(t_comm comm, char *str, t_list **a_list, t_list **b_list);
int		uniq_cmd(t_comm comm, t_list **a_list, t_list **b_list);
t_pipe	*new_parcing_comm_pip(char *all_cmd, t_pipe *pipe,
			t_list **a_list);
t_pipe	*parcing_comm_pip(char *all_cmd, t_list **a_list);
int		only_space(char *s);
t_comm	ft_double_left_red(t_comm comm);
void	ft_redir_temp(char **str, int input);
char	**double_in(char *all_cmd, t_list **a_list);
int		parcing(char *all_cmd, t_list **a_list, t_list **b_list);
int		is_echo(char *s);
int		is_red(char c);
int		is_quott(char c);
t_pipe	*open_file_redir_out(t_pipe *parse_pip);
void	free_comm(t_comm comm);
char	*unset_str(char *cmd);
t_list	*unset_tlist(t_list **a_list, t_list **b_list, int type);
char	*unset_s(t_list *temp, int type);
t_lred	*fill_dred(void);
t_lred	*dred_setup(t_lred *dred, int i);
t_doll	*doll_cut(t_doll *doll, char *s, t_list **a_list);
int		char_alphanum2(char c);
t_doll	*incr_doll(t_doll *doll);
t_doll	*doll_setup(t_doll *doll);
t_doll	*incr_doll2(t_doll *doll, char *s);
t_pars	*cut_pglitch(t_pars *glitch, char *cmd_all);
t_pars	*cut_pglitch2(t_pars *glitch, char *cmd_all);
int		fill_if(t_uniqq *uniqq, t_comm comm);
void	fill_while(t_uniqq *uniqq, t_comm comm);
int		uniqq_setup(t_uniqq **uniqq, t_comm comm, t_list **a_list,
			t_list **b_list);
int		fill_ret(t_uniqq *uniqq, t_comm comm, t_list **a_list,
			t_list **b_list);
void	uniqq_exec(t_uniqq *uniqq, t_comm comm);
char	*make_test(char *s);
int		is_valid(char *s);
t_open	open_setup(t_open open);
void	dup_read(t_pipe *comm_pip, t_list **a_list,
			t_list **b_list);
void	dup_read_norme(int i, int *pipefd);
void	dup_write(t_pipe *comm_pip, t_list **a_list,
			t_list **b_list, int *pipefd);
t_comm	replace_space(t_comm comm);
t_comm	replace_space2(t_comm comm);
char	*build_sret(char *sret, char *s);
t_comm	setup_cmd(t_comm comm, int i, int arg, int red);
void	fill_else4(t_comm comm, t_fill *fill);
void	fill_else3(t_comm comm, t_fill *fill, char *cmd);
void	fill_else2(t_comm comm, t_fill *fill);
void	fill_else1(t_comm comm, t_fill *fill, char *cmd);
void	fill_if1(t_comm comm, t_fill *fill, char *cmd);
t_fill	*fill_setup(void);
void	fill_if1pip(t_pipe *comm, t_fill *fill, char *cmd);
void	fill_elsepip1(t_pipe *comm, t_fill *fill, char *cmd);
void	fill_elsepip3(t_pipe *comm, t_fill *fill);
void	fill_elsepip4(t_pipe *comm, t_fill *fill, char *cmd);
void	fill_elsepip2(t_pipe *comm, t_fill *fill, char *cmd);
t_del	*setup_del(void);
void	del_if1(t_del *del, char *s);
void	del_if2(t_del *del, char *s, t_list **a_list);
void	del_if3(t_del *del, char *s, t_list **a_list);
void	del_else(t_del *del);
void	del_else2(t_del *del, char *s);
void	del_free(t_del *del, char *s);
int		ret_racks(int simple, int duble);
void	del_if4(t_del *del, char *s, t_list **a_list);
void	free_uniqq(t_uniqq *uniqq);

#endif