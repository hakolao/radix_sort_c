/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/16 19:23:54 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/28 01:25:14 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

const char		*test_radix_sort_simple(t_thread_pool *pool);
const char		*test_radix_sort_randomized_small(t_thread_pool *pool);
const char		*test_radix_sort_randomized_large(t_thread_pool *pool);
const char		*test_radix_sort_simple_key_val(t_thread_pool *pool);
const char		*test_radix_sort_large_key_val(t_thread_pool *pool);

#endif
