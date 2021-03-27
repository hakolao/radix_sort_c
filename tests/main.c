/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 19:23:49 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/28 01:33:28 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "oh_test.h"
#include "tests.h"

int g_tests_run = 0;
t_test_state g_test_states[MAX_TESTS];

static void		all_tests(void)
{
	t_thread_pool	*pool;

	pool = thread_pool_create(8);
	ft_printf("Radix Sort tests:\n");
	OH_RUN_TEST_POOLED(test_radix_sort_simple, pool);
	OH_RUN_TEST_POOLED(test_radix_sort_randomized_small, pool);
	OH_RUN_TEST_POOLED(test_radix_sort_randomized_large, pool);
	OH_RUN_TEST_POOLED(test_radix_sort_simple_key_val, pool);
	OH_RUN_TEST_POOLED(test_radix_sort_large_key_val, pool);
	thread_pool_destroy(pool);
}

int				main(void)
{
	t_bool				success;
	int					failures;
	int					i;

	all_tests();
	success = true;
	failures = 0;
	i = -1;
	while (++i < g_tests_run)
	{
		if (!g_test_states[i].success)
		{
			success = false;
			failures++;
		}
	}
	ft_printf("===========\n");
	if (!success)
		ft_printf("%d out of %d TESTS FAILED\n", failures, g_tests_run);
	else
		ft_printf("ALL %d TESTS PASSED\n", g_tests_run);
	return (!success);
}
