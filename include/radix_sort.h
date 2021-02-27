/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 13:11:01 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/27 18:44:31 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RADIX_SORT_H
# define RADIX_SORT_H

# include "libft.h"

size_t	radix_sort_pad_array(uint32_t **array_out, uint32_t *array,
			size_t size_in, int32_t divisible_by, t_bool is_free);
void	radix_sort(t_thread_pool *pool, uint32_t *array,
			size_t size, int32_t num_work);

#endif
