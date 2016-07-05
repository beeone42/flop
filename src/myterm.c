#include "gen.h"

void	get_winsize(t_env	*e)
{
  e->sx = getmaxx(stdscr);
  e->sy = getmaxy(stdscr);
}

void	status(t_env	*e, char	*s)
{
  attron(A_REVERSE);
  move(e->sy - 1, 0);
  printw("%s", s);
  attroff(A_REVERSE);
}

void	add_trace(t_env	*e)
{
  int	i;
  for (i = 0; i < TRACE_SIZE; i++)
    {
      e->trace[TRACE_SIZE - i] = e->trace[TRACE_SIZE - i - 1];
    }
  e->trace[0] = e->size;
}

int	get_max(t_env	*e)
{
  int	res, i;

  res = e->trace[0];
  for (i = 1; i < e->sx; i++)
    if (res < e->trace[i])
      res = e->trace[i];
  return (res);
}

void	my_mvvline(int	y, int	x, char	ch, int	count)
{
  int	i;

  i = 0;
    while (i < count)
      {
	move(y - i, x);
	addch(ch);
	i++;
      }
}

void	sprint_bytes(char	*s, u_long	i)
{
  if (i < 1000)
    sprintf(s, "%lu bytes", i);
  else
    if (i < 1000 * 1000)
      sprintf(s, "%lu.%02lu KBytes", i / 1000, (i % 1000) / 10);
    else
      if (i < 1000 * 1000 * 1000)
	sprintf(s, "%lu.%02lu MBytes",
		i / (1000 * 1000), 
		((i / 1000) % 1000) / 10);
      else
	sprintf(s, "%lu.%02lu TBytes",
		i / (1000 * 1000 * 1000),
		((i / (1000 * 1000)) % 1000) / 10);
}

void	print_bytes(u_long	i)
{
  char	s[STR_LEN];

  sprint_bytes(s, i);
  printw(s);
}

void	status_bytes(t_env	*e)
{
  char	s[STR_LEN];
  char	t[STR_LEN];
  char	a[STR_LEN];
  int	l, l2, n;

  attron(A_REVERSE);
  move(e->sy - 1, 0);

  sprint_bytes(t, e->size_all);
  sprint_bytes(a, e->size_all / e->time_all);
  sprintf(s, " (total: %lu pkts %s, avg: %s/s)", e->count_all, t, a);
  printw(s);
  l = strlen(s);

  sprint_bytes(t, e->size);
  sprintf(s, " %lu pkts %s", e->count, t);
  l2 = strlen(s);

  n = e->sx - l - l2;

  //sprintf(t, "n=%d-%d-%d", e->sx, l, l2);
  //n -= strlen(t);
  //printw(t);

  while (n-- > 1)
    addch(' ');

  printw(s);
  attroff(A_REVERSE);
}

void	my_move(int	y, int	x)
{
  if (x < 0)
    x = 0;
  if (y < 0)
    y = 0;
  move(y,x);
}

void	draw_graph(t_env	*e)
{
  char	s[STR_LEN];
  int	i, m, v, v2;

  m = get_max(e);
  move(0,0);
  printw("%s:", e->pcap_dev);
  sprint_bytes(s, m);
  move(0, e->sx - strlen(s) - 1);
  printw(s);


  //my_mvvline(e->sy - 4, 0, '|', e->sy - 5);
  //  my_mvvline(e->sy - 4, e->sx - 1, '|', e->sy - 5);
  for (i = 0; i < e->sx - 1; i++)
    {
      v = e->trace[i];
      v2 = m ? ((e->sy - 5) * v) / m : 0;
      if (v2 > 0)
	my_mvvline(e->sy - 4, e->sx - i - 1, LINE_CHAR, v2);

      move(e->sy - 3, e->sx - i - 1);
      addch((i % 10) ? '-' : '+');
      move(1, e->sx - i - 1);
      addch((i % 10) ? '-' : '+');

      if (!(i % 10))
	{
	  my_move(e->sy - 2, e->sx - i - 2);
	  printw("%02d", i);
	}
    }
  move(e->sy - 3, e->sx - i - 1);
  addch((i % 10) ? '-' : '+');
  move(1, e->sx - i - 1);
  addch((i % 10) ? '-' : '+');

  status_bytes(e);
}
