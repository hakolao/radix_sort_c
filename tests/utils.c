/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:57:02 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/27 17:58:45 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void			rand_array(int32_t *array, int32_t array_size)
{
	int32_t	i;

	i = -1;
	while (++i < array_size)
		array[i] = rand();
}

void			copy_array(int32_t *dst, int32_t *src,
					int32_t arrays_size)
{
	int32_t	i;

	i = -1;
	while (++i < arrays_size)
		dst[i] = src[i];
}

t_bool			arrays_match(int32_t *arr1, int32_t *arr2,
					int32_t arrays_size)
{
	int32_t	i;

	i = -1;
	while (++i < arrays_size)
		if (arr1[i] != arr2[i])
			return (false);
	return (true);	
}

int				check_comp(const void *a, const void *b) 
{
	int32_t	f;
	int32_t	s;

	f = *((int*)a);
	s = *((int*)b);
	if (f > s)
		return  (1);
	if (f < s)
		return (-1);
	return (0);
}

void			sort_check_array(int32_t *check_array, int32_t array_size)
{
	qsort(check_array, array_size, sizeof(*check_array), check_comp);
}