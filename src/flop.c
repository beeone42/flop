#include "gen.h"

int	loop;
void	*old_func;
t_env	gl_e;

pcap_t			*open_pcap(char	*dev,
				   int	snaplen,
				   int	to_ms,
				   char	*filter)
{
  char			errbuf[STR_LEN];
  pcap_t		*p;
  struct bpf_program    bp;

  if (!(p = pcap_open_live(dev, snaplen, TRUE, to_ms, errbuf)))
    {
      perror("pcap_open_live");
      exit(1);
    }
  if (pcap_compile(p, &bp, filter, 0, 0) < 0)
    {
      fprintf(stderr,"pcap_compile `%s'\n", filter);
      exit(1);
    }
  if (pcap_setfilter(p, &bp) < 0)
    {
      fprintf(stderr,"pcap_setfilter\n");
      exit(1);
    }
  
  return (p);
}

void	cleanup(int	code)
{
  endwin();
  signal(SIGINT, old_func);
  exit(code);
}

void	sig_int(int	s)
{
  cleanup(0);
}

void	onalarm()
{
  gl_e.time_all++;
  gl_e.size_all += gl_e.size;
  gl_e.count_all += gl_e.count;
  clear();
  add_trace(&gl_e);
  get_winsize(&gl_e);
  draw_graph(&gl_e);
  refresh();
  gl_e.count = 0;
  gl_e.size = 0;
  alarm(1);
  signal(SIGALRM, onalarm);
}

void	if_ether(char	*user,
		 struct pcap_pkthdr	*h,
		 register u_char	*p)
{
      gl_e.count++;
      gl_e.size += h->caplen;
}

pcap_handler	flop_handler(t_env	*e)
{
  return((void*)if_ether);
}

int			main(int	argc,
			     char	**argv)
{
  pcap_t		*p;
  char			*filter;
  char			err[STR_LEN];
  int			i;

  bzero(&gl_e, sizeof(gl_e));
  old_func = signal(SIGINT, sig_int);
  if (argc == 3)
    {
      filter = argv[2];
    }
  else
    {
      filter = NULL;
    }
  gl_e.pcap_dev = argv[1];
  if (gl_e.pcap_dev == NULL)
    {
      if (NULL == (gl_e.pcap_dev = pcap_lookupdev(err)))
	{
	  fprintf(stderr,"%s\n", err);
	  exit(1);
	}
      printf("Using default network interface: %s\n", gl_e.pcap_dev);
    }
  else
    printf("Using network interface: %s\n", gl_e.pcap_dev);

  p = open_pcap(gl_e.pcap_dev, BUF_LEN, 2, filter);

  initscr();
  clear();
  get_winsize(&gl_e);
  status(&gl_e, " Please wait...");
  refresh();

  for (i = 0; i < TRACE_SIZE; i++)
    gl_e.trace[i] = 0;

  alarm(1);
  signal(SIGALRM, onalarm);

  if (pcap_loop(p, -1, flop_handler(&gl_e), NULL) < 0)
    perror("pcap_loop");
  pcap_close(p);

  cleanup(0);

  return(0);
}

