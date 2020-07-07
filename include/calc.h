// Copyright 2020 kkozlov

#ifndef CALC_H
# define CALC_H

# include <stdlib.h>
# include <ctype.h>
# include <stdio.h>
# include <stdarg.h>
# include <ctype.h>
# include <math.h>

typedef enum	e_token_type
{
  END = -1, NUMBER = 0x1,
  PLUS = '+', MINUS = '-', DIV = '/',
  MULT = '*', LPAREN = '(', RPAREN = ')',
  POW = '^', MOD = '%'
}				t_token_type;

typedef struct	s_token
{
  t_token_type	type;
  double		value;
  const char	*expr;
}				t_token;

/*
** nud => NULL detonate current token. It deals with prefix operators.
** led => LEFT detoante current token. It handles infix and postfix operators.
** bp => Binding power of the current infix/postfix operator.
*/

void			ft_next(void);
double			ft_expr(int rbp);
double			ft_nud(void);
double			ft_led(double left);
int				ft_bp(void);

void			ft_token_init(const char *expr);
void			ft_error(const char *fmt, ...);

#endif
