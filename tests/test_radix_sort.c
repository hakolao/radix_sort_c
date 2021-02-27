/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_radix_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:06:27 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/27 18:47:59 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oh_test.h"
#include "radix_sort.h"
#include "utils.h"

const char		*test_radix_sort_simple(void)
{
	t_thread_pool	*pool;
	uint32_t		array[8];
	uint32_t		check_array[8];
	size_t			array_size;
	size_t			num_threads;
	uint32_t		*padded_arr;
	size_t			padded_size;

	padded_arr = NULL;
	array[0] = 1115;
	array[1] = 80000;
	array[2] = 322410;
	array[3] = 1;
	array[4] = 112;
	array[5] = 1163515;
	array[6] = 2222;
	array[7] = 12345;
	array_size = 8;
	num_threads = 8;
	pool = thread_pool_create(num_threads);
	copy_array(check_array, array, array_size);
	sort_check_array(check_array, array_size);
	padded_size =
		radix_sort_pad_array(&padded_arr, array, array_size, num_threads, false);
	radix_sort(pool, padded_arr, padded_size, pool->num_threads);
	for (size_t i = 0; i < array_size; i++)
	{
		ft_printf("Array: %d, Check: %d\n", array[i], check_array[i]);
	}
	OH_ASSERT("Radix sort simple sorted wrong",
		arrays_match(check_array, array, array_size));
	thread_pool_destroy(pool);
	free(padded_arr);
	return (0);
}

const char		*test_radix_sort_randomized_small(void)
{
	t_thread_pool	*pool;
	uint32_t		array[128];
	uint32_t		check_array[128];
	size_t			array_size;
	size_t			num_threads;
	uint32_t		*padded_arr;
	size_t			padded_size;

	padded_arr = NULL;
	array_size = 128;
	num_threads = 8;
	pool = thread_pool_create(num_threads);
	rand_array(array, array_size);
	copy_array(check_array, array, array_size);
	sort_check_array(check_array, array_size);
	padded_size =
		radix_sort_pad_array(&padded_arr, array, array_size, num_threads, false);
	radix_sort(pool, padded_arr, padded_size, pool->num_threads);
	OH_ASSERT("Radix sort simple sorted wrong",
		arrays_match(check_array, array, array_size));
	thread_pool_destroy(pool);
	free(padded_arr);
	return (0);
}

const char		*test_radix_sort_randomized_large(void)
{
	t_thread_pool	*pool;
	uint32_t		array[131072];
	uint32_t		check_array[131072];
	size_t			array_size;
	size_t			num_threads;
	uint32_t		*padded_arr;
	size_t			padded_size;

	padded_arr = NULL;
	array_size = 131072;
	num_threads = 8;
	pool = thread_pool_create(num_threads);
	rand_array(array, array_size);
	copy_array(check_array, array, array_size);
	sort_check_array(check_array, array_size);
	padded_size =
		radix_sort_pad_array(&padded_arr, array, array_size, num_threads, false);
	radix_sort(pool, padded_arr, padded_size, pool->num_threads);
	OH_ASSERT("Radix sort simple sorted wrong",
		arrays_match(check_array, array, array_size));
	thread_pool_destroy(pool);
	free(padded_arr);
	return (0);
}