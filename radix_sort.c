/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:00:41 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/27 18:43:46 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "radix_sort.h"

size_t		radix_sort_pad_array(uint32_t **array_out, uint32_t *array,
				size_t size_in, int32_t divisible_by, t_bool is_free)
{
	size_t		i;
	size_t		new_size;
	size_t		remainder;

	remainder = size_in % divisible_by;
	new_size = remainder == 0 ? size_in : (size_in + divisible_by - remainder);
	*array_out = ft_calloc(sizeof(uint32_t) * new_size);
	i = -1;
	while (++i < size_in)
		(*array_out)[i] = array[i];
	i = size_in - 1;
	while (++i < new_size)
		(*array_out)[i] = UINT32_MAX;
	if (is_free)
		free(array);
	return (new_size);
}

/*
** @pool, thread pool created earlier that will do the parallel work for sorting
** @array, array to be sorted
** @size, size of array
** @num_work, how many splits on the sort we'll perform, this should be similar
** to the number of threads on the pool, which in turn should be similar to the
** number of logical threads on your processor
*/

void	radix_sort(t_thread_pool *pool, uint32_t *array,
			size_t size, int32_t num_work)
{
	(void)pool;
	(void)array;
	(void)size;
	(void)num_work;
	// size_t	i;
	// size_t	j;
	// size_t	shift;
	// size_t	next_index;

	// if (size == 0)
	// 	return ;
	// /* numbers of elements to be sorted must be multiple of number of threads */
	// assert(n % N_THREADS == 0);

	// for (shift = 0; shift < 32; shift += 8){
	// 	/* divide elements to be sorted into N_THREAD many ranges and sort those */
	// 	for (j = 0; j < N_THREADS; j++){
	// 		struct radix_args *arg = &args[j];
	// 		arg->n = n / N_THREADS;
	// 		arg->a = a + j*arg->n;
	// 		arg->b = b + j*arg->n;
	// 		arg->shift = shift;
	// 		pthread_create(&arg->thread, NULL, sort_range, arg);
	// 	}

	// 	/* wait until all threads are done */
	// 	for (j = 0; j < N_THREADS; j++){
	// 		pthread_join(args[j].thread, NULL);
	// 	}

	// 	/* calculate indices for buckets after merge */
	// 	next_index = 0;
	// 	for (i = 0; i < 256; i++){
	// 		for (j = 0; j < N_THREADS; j++){
	// 			args[j].index[i] = next_index;
	// 			next_index += args[j].count[i];
	// 		}
	// 	}

	// 	/* merge buckets of threads */
	// 	for (j = 0; j < N_THREADS; j++){
	// 		struct radix_args *arg = &args[j];
	// 		arg->n = n / N_THREADS;
	// 		arg->a = b + j*arg->n;
	// 		arg->b = a;
	// 		arg->shift = shift;
	// 		pthread_create(&arg->thread, NULL, put_into_buckets, arg);
	// 	}

	// 	/* wait until all threads are done */
	// 	for (j = 0; j < N_THREADS; j++){
	// 		pthread_join(args[j].thread, NULL);
	// 	}
	// }
}
