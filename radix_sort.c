/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:00:41 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/27 21:40:04 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "radix_sort.h"

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
	size_t			shift_pass;
	uint32_t		*out;
	t_radix_params	*thread_params;
	size_t			padded_size;
	uint32_t		*padded_arr;

	padded_size = radix_sort_pad_array(&padded_arr, array, size,
			EXPECTED_THREADS, false);
	if (RADIXTOTALBITS % RADIXBITS != 0 &&
		ft_dprintf(2, "Radix total bits must be divisible by radix bits\n"))
		return ;
	thread_params = ft_calloc(sizeof(*thread_params) * EXPECTED_THREADS);
	out = ft_calloc(sizeof(*padded_arr) * padded_size);
	if ((!thread_params || !out) && ft_dprintf(2, "Radix total malloc err\n"))
		return ;
	copy_array(out, padded_arr, padded_size);
	shift_pass = 0;
	while (shift_pass < RADIXTOTALBITS)
	{
		histogram(pool, thread_params, shift_pass, (uint32_t*[2]){padded_arr, out},
			padded_size / EXPECTED_THREADS);
		prefix_sum(thread_params);
		reorder(pool, thread_params, shift_pass, (uint32_t*[2]){padded_arr, out},
			padded_size / EXPECTED_THREADS);
		shift_pass += RADIXBITS;  
	}
	copy_array(array, padded_arr, size);
	cleanup(padded_arr, out, thread_params);
}
