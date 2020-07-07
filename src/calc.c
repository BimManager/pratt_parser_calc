// Copyright 2020 kkozlov

#include "calc.h"

static char		g_tokens[128] =
{
  ['+'] = PLUS, ['-'] = MINUS, ['*'] = MULT,
  ['/'] = DIV, ['('] = LPAREN, [')'] = RPAREN,
  ['^'] = POW, ['%'] = MOD
};

t_token			g_token;

void	ft_next(void)
{
  double	nb;
  char		c;

  printf("## next\n");
  while ((c = *g_token.expr))
  {
    if (isdigit(c))
    {
      nb = atof(g_token.expr);
      while ('.' == *g_token.expr
             || isdigit(*g_token.expr))
        ++g_token.expr;
      g_token.type = NUMBER;
      g_token.value = nb;
      return ;
    }
    else if (isspace(c))
    {
      while (isspace(*g_token.expr))
        ++g_token.expr;
      continue ;
    }
    else
    {
      g_token.type = g_tokens[(int)c];
      ++g_token.expr;
      if (!g_token.type)
        ft_error("'%c' is an unexpected token.\n", c);
      return ;
    }
  }
  g_token.type = END;
}

double	ft_expr(int rbp)
{
  double	left;

  left = ft_nud();
  printf("## expr\n");
  while (rbp < ft_bp())
    left = ft_led(left);
  return (left);
}

double	ft_nud(void)
{
  double		v;
  t_token_type	type;

  type = g_token.type;
  printf("## nud\n");
  if (NUMBER == type)
  {
    v = g_token.value;
    ft_next();
    return (v);
  }
  else if (MINUS == type)
  {
    ft_next();
    return (-ft_expr(30));
  }
  else if (LPAREN == type)
  {
    ft_next();
    v = ft_expr(0);
    if (RPAREN != g_token.type)
      ft_error("Expected )");
    ft_next();
    return (v);
  }
  else
    ft_error("Expected (");
  return (-1);
}
  
double	ft_led(double left)
{    
  t_token_type	type;

  type = g_token.type;
  printf("## led\n");
  if (PLUS == type)
  {
    ft_next();
    return (left + ft_expr(10));
  }
  else if (MINUS == type)
  {
    ft_next();
    return (left - ft_expr(10));
  }
  else if (MULT == type)
  {
    ft_next();
    return (left * ft_expr(20));
  }
  else if (DIV == type)
  {
    ft_next();
    return (left / ft_expr(20));
  }
  else if (POW == type)
  {
    ft_next();
    return (pow(left, ft_expr(40 - 1)));
  }
  else if (MOD == type)
  {
    ft_next();
    return (fmod(left, ft_expr(20)));
  }
  else
    ft_error("Expected operator\n");
  return (-1);
}

int		ft_bp(void)
{
  t_token_type	type;

  type = g_token.type;
  printf("## bp\n");
  if (PLUS == type || MINUS == type)
    return (10);
  else if (DIV == type || MULT == type || MOD == type)
    return (20);
  else if (POW == type)
    return (40);
  else if (RPAREN == type || END == type)
    return (0);
  else if (NUMBER == type)
    ft_error("An operator is expected\n");
  else
    ft_error("An unexpected token\n");
  return (-1);
}
