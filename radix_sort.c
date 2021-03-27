/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:00:41 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/27 20:18:36 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "radix_sort.h"

static void		place_to_buckets(void *args)
{
	t_radix_params	*params;
	uint32_t		*arr;
	uint32_t		*tmp;
	size_t			i;
	size_t			bucket;
	
	params = args;
	arr = params->arr;
	tmp = params->tmp;
	i = -1;
	while (++i < params->bucket_size)
	{
		bucket = (arr[i] >> params->shift) & (RADIX - 1);
		tmp[params->index[bucket]++] = arr[i];
	}
}

static void		histogram_and_sort(void *args)
{
	t_radix_params	*params;
	uint32_t		*arr;
	size_t			i;
	size_t			next_index;

	params = args;
	arr = params->arr;
	i = -1;
	while (++i < HISTOLEN)
		params->count[i] = 0;
	i = -1;
	while (++i < params->bucket_size)
		params->count[(arr[i] >> params->shift) & (RADIX - 1)]++;
	next_index = 0;
	i = -1;
	while (++i < HISTOLEN)
	{
		params->index[i] = next_index;
		next_index += params->count[i];
	}
	place_to_buckets(params);
}

static void		split_to_buckets_and_sort(t_thread_pool *pool,
						t_radix_params *global_params,
						size_t shift_pass,
						uint32_t *array,
						uint32_t *tmp,
						size_t bucket_size)
{
	size_t			i;
	t_radix_params	*param;

	i = -1;
	while (++i < EXPECTED_THREADS)
	{
		param = global_params + i;
		param->bucket_size = bucket_size;
		param->arr = array + i * param->bucket_size;
		param->tmp = tmp + i * param->bucket_size;
		param->shift = shift_pass;
		thread_pool_add_work(pool, histogram_and_sort, param);
	}
	thread_pool_wait(pool);
}

/*
** ToDo: Parallelize prefix sum
*/

static void		prefix_sum(t_radix_params *global_params)
{
	size_t			i;
	size_t			j;
	size_t			next_index;

	next_index = 0;
	i = -1;
	while (++i < HISTOLEN)
	{
		j = -1;
		while (++j < EXPECTED_THREADS)
		{
			global_params[j].index[i] = next_index;
			next_index += global_params[j].count[i];
		}
	}
}

static void		merge_buckets(t_thread_pool *pool,
						t_radix_params *global_params,
						size_t shift_pass,
						uint32_t *array,
						uint32_t *tmp,
						size_t bucket_size)
{
	size_t			i;
	t_radix_params	*param;

	i = -1;
	while (++i < EXPECTED_THREADS)
	{
		param = global_params + i;
		param->bucket_size = bucket_size;
		param->arr = tmp + i * param->bucket_size;
		param->tmp = array;
		param->shift = shift_pass;
		thread_pool_add_work(pool, place_to_buckets, param);
	}
	thread_pool_wait(pool);
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
	size_t			shift_pass;
	uint32_t		*tmp;
	t_radix_params	*global_params;
	size_t			padded_size;
	uint32_t		*padded_arr;

	padded_size = radix_sort_pad_array(&padded_arr, array, size,
			EXPECTED_THREADS, false);
	if (RADIXTOTALBITS % RADIXBITS != 0)
	{
		ft_dprintf(2, "Radix total bits must be divisible by radix bits\n");
		return ;
	}
	global_params = ft_calloc(sizeof(*global_params) * EXPECTED_THREADS);
	tmp = ft_calloc(sizeof(*padded_arr) * padded_size);
	copy_array(tmp, padded_arr, padded_size);
	shift_pass = 0;
	while (shift_pass < RADIXTOTALBITS)
	{
		split_to_buckets_and_sort(pool, global_params, shift_pass, array, tmp,
			padded_size / EXPECTED_THREADS);
		prefix_sum(global_params);
		merge_buckets(pool, global_params, shift_pass, array, tmp,
			padded_size / EXPECTED_THREADS);
		shift_pass += RADIXBITS;  
	}
	free(global_params);
	free(tmp);
	copy_array(array, padded_arr, size);
	free(padded_arr);
}
