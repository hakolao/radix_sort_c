/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:00:41 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/27 20:09:41 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "radix_sort.h"

static void		reorder_work(void *args)
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
	while (++i < params->n)
	{
		bucket = (arr[i] >> params->shift) & (HISTOLEN - 1);
		tmp[params->index[bucket]++] = arr[i];
	}
}

static void		histogram_work(void *args)
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
	while (++i < params->n)
		params->count[(arr[i] >> params->shift) & (HISTOLEN - 1)]++;
	next_index = 0;
	i = -1;
	while (++i < params->n)
	{
		params->index[i] = next_index;
		next_index += params->count[i];
	}
	reorder_work(params);
}

static void		histogram(t_thread_pool *pool,
						t_radix_params *global_params,
						size_t shift_pass,
						uint32_t *array,
						uint32_t *tmp,
						size_t size)
{
	size_t			i;
	t_radix_params	*param;

	i = -1;
	while (++i < pool->num_threads)
	{
		param = &global_params[i];
		param->n = size / pool->num_threads;
		param->arr = array + i * param->n;
		param->tmp = tmp + i * param->n;
		param->shift = shift_pass;
		thread_pool_add_work(pool, histogram_work, param);
	}
	thread_pool_wait(pool);
}

/*
** ToDo: Parallelize prefix sum
*/

static void		prefix_sum(t_thread_pool *pool, t_radix_params *global_params)
{
	size_t			i;
	size_t			j;
	size_t			next_index;

	next_index = 0;
	i = -1;
	while (++i < HISTOLEN)
	{
		j = -1;
		while (++j < pool->num_threads)
		{
			global_params[j].index[i] = next_index;
			next_index += global_params[j].count[i];
		}
	}
}

static void		reorder(t_thread_pool *pool,
						t_radix_params *global_params,
						size_t shift_pass,
						uint32_t *array,
						uint32_t *tmp,
						size_t size)
{
	size_t			i;
	t_radix_params	*param;

	i = -1;
	while (++i < pool->num_threads)
	{
		param = &global_params[i];
		param->n = size / pool->num_threads;
		param->arr = tmp + i * param->n;
		param->tmp = array;
		param->shift = shift_pass;
		thread_pool_add_work(pool, reorder_work, param);
	}
	thread_pool_wait(pool);
}

/*
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

	if (!radix_sort_is_valid(size, pool->num_threads))
		return ;
	global_params = ft_calloc(sizeof(*global_params) * pool->num_threads);
	tmp = ft_calloc(sizeof(*array) * size);
	shift_pass = 0;
	while (shift_pass < RADIXTOTALBITS)
	{
		// Histogram
		histogram(pool, global_params, shift_pass, array, tmp, size);
		// Calculate indices (prefix sum)
		prefix_sum(pool, global_params);
		// Merge buckets of threads (reorder)
		reorder(pool, global_params, shift_pass, array, tmp, size);
		shift_pass += RADIXBITS;
	}
	free(global_params);
	free(tmp);
}
