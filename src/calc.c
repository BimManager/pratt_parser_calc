// Copyright 2020 kkozlov

#include "calc.h"

static char		g_tokens[128] =
{
  ['+'] = PLUS, ['-'] = MINUS, ['*'] = MULT,
  ['/'] = DIV, ['('] = LPAREN, [')'] = RPAREN
};

static t_token	g_token;

void	ft_token_init(const char *expr)
{
  g_token.type = END;
  g_token.value = 0;
  g_token.expr = expr;
}

void	ft_error(const char *fmt, ...)
{
  va_list	ap;

  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  exit(1);
}

void	ft_next(void)
{
  int	nb;
  char	c;
  
  while ((c = *g_token.expr))
  {
    if (isdigit(c))
    {
      nb = 0;
      while (isdigit(*g_token.expr))
        nb = 10 * nb + *g_token.expr++ - '0';
      g_token.type = NUMBER;
      g_token.value = nb;
      printf("nb: %d\n", g_token.value);
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
      printf("token: %x\n", g_token.type);
      ++g_token.expr;
      if (!g_token.type)
        ft_error("An unexpected token\n");
      return ;
    }
  }
  g_token.type = END;
  printf("end\n");
}

double	ft_expr(int rbp)
{
  double	left;

  left = ft_nud();
  printf("## expr: left: %f\n", left);
  while (rbp < ft_bp())
    left = ft_led(left);
  return (left);
}

double	ft_nud(void)
{
  double		v;
  t_token_type	type;

  type = g_token.type;
  printf("## nud: %x\n", type);
  if (NUMBER == type)
  {
    v = g_token.value;
    printf("v: %f\n", v);
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
  printf("## led: %x\n", type);
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
  else
    ft_error("Expected operator\n");
  return (-1);
}

int		ft_bp(void)
{
  t_token_type	type;

  type = g_token.type;
  printf("bp: type: %x\n", type);
  if (PLUS == type || MINUS == type)
    return (10);
  else if (DIV == type || MULT == type)
    return (20);
  else if (RPAREN == type)
    return (0);
  else if (END == type)
    return (0);
  else
    ft_error("%x Unexpected token\n", type);
  return (-1);
}
