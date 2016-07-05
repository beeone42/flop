#ifndef GEN_H_
#define GEN_H_

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <pcap.h>
#include <libnet.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>

#define STR_LEN		256
#define BUF_LEN		2048
#define TRACE_SIZE	2048

#define	LINE_CHAR	'#'

#define u_long		unsigned long

typedef struct			s_env
{
  struct libnet_link_int	*libnet;
  char				*libnet_dev;
  char				*pcap_dev;
  int				verbose;
  u_long			size;
  u_long			count;
  u_long			size_all;
  u_long			count_all;
  u_long			time_all;
  int				sx;
  int				sy;
  int				trace[TRACE_SIZE + 1];
}				t_env;

#include "myterm.h"

#endif /* GEN_H_ */
