// Copyright 2020 kkozlov

#include "calc.h"

extern t_token	g_token;

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

