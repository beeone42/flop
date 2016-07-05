/*
** my_types.h for  in 
** 
** Made by 
** Login   <vianney@epita.fr>
** 
** Started on  Tue Oct  5 05:50:36 1999 
** Last update Mon Jun  1 23:28:03 2020 Charlie Root
*/
#ifndef MY_TYPES_H
#define MY_TYPES_H	1

typedef int			t_boolean;

typedef unsigned char		t_u8;
typedef unsigned short		t_u16;
typedef unsigned int		t_u32;

#define ABS(Num)		(((Num) < 0)?-(Num):(Num))
#define FBCOPY(Src,Dst,Len)	bcopy((char *)(Src),(char *)(Dst),(Len))

#endif
