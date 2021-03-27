/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_radix_sort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:06:27 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/27 21:37:23 by ohakola          ###   ########.fr       */
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
	radix_sort(pool, array, array_size);
	OH_ASSERT("Radix sort simple sorted wrong",
		arrays_match(check_array, array, array_size));
	thread_pool_destroy(pool);
	return (0);
}

const char		*test_radix_sort_randomized_small(void)
{
	t_thread_pool	*pool;
	uint32_t		array[16];
	uint32_t		check_array[16];
	size_t			array_size;
	size_t			num_threads;

	array_size = 16;
	num_threads = 8;
	pool = thread_pool_create(num_threads);
	rand_array(array, array_size);
	copy_array(check_array, array, array_size);
	sort_check_array(check_array, array_size);
	radix_sort(pool, array, array_size);
	OH_ASSERT("Radix sort randomized small sorted wrong",
		arrays_match(check_array, array, array_size));
	thread_pool_destroy(pool);
	return (0);
}

const char		*test_radix_sort_randomized_large(void)
{
	t_thread_pool	*pool;
	uint32_t		array[131072];
	uint32_t		check_array[131072];
	size_t			array_size;
	size_t			num_threads;

	array_size = 131072;
	num_threads = 8;
	pool = thread_pool_create(num_threads);
	rand_array(array, array_size);
	copy_array(check_array, array, array_size);
	sort_check_array(check_array, array_size);
	radix_sort(pool, array, array_size);
	OH_ASSERT("Radix sort randomized large sorted wrong",
		arrays_match(check_array, array, array_size));
	thread_pool_destroy(pool);
	return (0);
}