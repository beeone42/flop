/*
** common.h for  in 
** 
** Made by 
** Login   <vianney@epita.fr>
** 
** Started on  Wed Nov 10 10:58:23 1999 
** Last update Wed Nov 10 11:02:07 1999 
*/
#ifndef COMMON_H
#define COMMON_H	1

#define RAND(Num)	(rand() % (Num))

pcap_t			*open_pcap();
struct ether_addr	*xether_aton();
void			*xmalloc();
char			*xstrdup();
extern char		*optarg;
extern int		optind;

#endif
