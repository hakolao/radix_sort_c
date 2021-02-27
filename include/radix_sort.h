/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:11:01 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/27 20:11:24 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RADIX_SORT_H
# define RADIX_SORT_H

# include "libft.h"

/*
** Dont change
*/
# define HISTOLEN 256
# define RADIXTOTALBITS 32
# define RADIXBITS 8
# define RADIX (1 << RADIXBITS)

typedef struct 	s_radix_params
{
	size_t		work_index;
	uint32_t	*arr;
	uint32_t	*tmp;
	size_t		shift;
	size_t		n;
	size_t		count[HISTOLEN];
	size_t		index[HISTOLEN];
}				t_radix_params;

size_t			radix_sort_pad_array(uint32_t **array_out, uint32_t *array,
					size_t size_in, int32_t divisible_by, t_bool is_free);
void			radix_sort(t_thread_pool *pool, uint32_t *array,
					size_t size);
t_bool			radix_sort_is_valid(size_t size, size_t num_threads);

#endif
