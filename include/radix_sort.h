/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:11:01 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/27 21:53:53 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RADIX_SORT_H
# define RADIX_SORT_H

# include "libft.h"

/*
** Dont change
*/
# define RADIXBITS 8
# define RADIXTOTALBITS 32
# define RADIX (1 << RADIXBITS)
# define HISTOLEN RADIX
# define EXPECTED_THREADS 8

typedef struct 	s_radix_params
{
	size_t		work_index;
	uint32_t	*arr;
	uint32_t	*out;
	size_t		shift;
	size_t		bucket_size;
	size_t		count[HISTOLEN];
	size_t		index[HISTOLEN];
}				t_radix_params;

void			radix_sort(t_thread_pool *pool, uint32_t *array,
					size_t size);

/*
** Radix utils
*/

size_t			radix_sort_pad_array(uint32_t **array_out, uint32_t *array,
					size_t size_in);
void			copy_array(uint32_t *dst, uint32_t *src,
					size_t arrays_size);

/*
** Radix work
*/

void			reorder(t_thread_pool *pool,
						t_radix_params *thread_params,
						size_t shift_pass,
						uint32_t *arrays[2]);
void			prefix_sum(t_radix_params *thread_params);
void			histogram(t_thread_pool *pool,
						t_radix_params *thread_params,
						size_t shift_pass,
						uint32_t *arrays[2]);
void			histogram_and_local_reorder(void *args);
void			reorder_work(void *args);

#endif
