/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 19:35:11 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/27 20:12:20 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "radix_sort.h"

size_t			radix_sort_pad_array(uint32_t **array_out, uint32_t *array,
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
		(*array_out)[i] = INT32_MAX - 1;
	if (is_free)
		free(array);
	return (new_size);
}

t_bool			radix_sort_is_valid(size_t size, size_t num_threads)
{

	if ((size == 0) || (size % num_threads != 0))
	{
		ft_dprintf(2, "Sort size %d must be > 0 and div by num_threads %d\n",
			size, num_threads);
		return (false);
	}
	if (RADIXTOTALBITS % RADIXBITS != 0)
	{
		ft_dprintf(2, "RADIX_TOTALBITS must be divisible by RADIXBITS\n");
		return (false);
	}
	return (true);
}