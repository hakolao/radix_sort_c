/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:00:41 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/27 21:55:41 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "radix_sort.h"

static void		cleanup(uint32_t *padded_arr, uint32_t *tmp,
					t_radix_params *global_params)
{
	free(global_params);
	free(padded_arr);
	free(tmp);
}

static void		init_params(t_radix_params *thread_params, size_t padded_size)
{
	size_t	i;

	i = -1;
	while (++i < EXPECTED_THREADS)
		thread_params[i].bucket_size = padded_size / EXPECTED_THREADS;
}

static void		radix_sort_work(t_thread_pool *pool,
						t_radix_params *thread_params,
						size_t shift,
						uint32_t *arrays[2])
{
	histogram(pool, thread_params, shift, arrays);
	prefix_sum(thread_params);
	reorder(pool, thread_params, shift, arrays);
}

static t_bool	is_valid(void)
{
	return (RADIXTOTALBITS % RADIXBITS == 0);
}

/*
** 1. Pads incoming array to be divisible by EXPECTED_THREADS.
** 2. Sorts the padded array
** 3. Copies the padded array values to original array
** @pool, thread pool created earlier that will do the parallel work for sorting
** @array, array to be sorted
** @size, size of array
** @num_work, how many splits on the sort we'll perform, this should be similar
** to the number of threads on the pool, which in turn should be similar to the
** number of logical threads on your processor
*/

void			radix_sort(t_thread_pool *pool, uint32_t *array, size_t size)
{
	size_t			shift;
	uint32_t		*out;
	t_radix_params	*thread_params;
	size_t			padded_size;
	uint32_t		*padded_arr;

	padded_size = radix_sort_pad_array(&padded_arr, array, size);
	if (!is_valid() && ft_dprintf(2, "RADIXTOTALBITS % RADIXBITS != 0\n"))
		return ;
	thread_params = ft_calloc(sizeof(*thread_params) * EXPECTED_THREADS);
	out = ft_calloc(sizeof(*padded_arr) * padded_size);
	if ((!thread_params || !out) && ft_dprintf(2, "Radix total malloc err\n"))
		return ;
	copy_array(out, padded_arr, padded_size);
	init_params(thread_params, padded_size);
	shift = 0;
	while (shift < RADIXTOTALBITS)
	{
		radix_sort_work(pool, thread_params, shift,
			(uint32_t*[2]){padded_arr, out});
		shift += RADIXBITS;
	}
	copy_array(array, padded_arr, size);
	cleanup(padded_arr, out, thread_params);
}
