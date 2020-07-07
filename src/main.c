// Copyright 2020 kkozlov

#include "calc.h"

int	main(int argc, char **argv)
{
  double	ans;
  
  if (2 != argc)
  {
    fprintf(stderr, "usage: ./expr \"( 1 + 2) * 4\"");
    return (1);
  }
  ft_token_init(argv[1]);
  ft_next();
  ans = ft_expr(0);
  printf("%f\n", ans);
  return (0);
}
