/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 19:35:11 by ohakola           #+#    #+#             */
/*   Updated: 2021/03/27 20:28:11 by ohakola          ###   ########.fr       */
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

void			copy_array(uint32_t *dst, uint32_t *src,
					size_t arrays_size)
{
	size_t	i;

	i = -1;
	while (++i < arrays_size)
		dst[i] = src[i];
}

void			cleanup(uint32_t *padded_arr, uint32_t *tmp,
					t_radix_params *global_params)
{
	free(global_params);
	free(padded_arr);
	free(tmp);
}