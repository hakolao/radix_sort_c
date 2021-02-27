/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohakola <ohakola@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 17:57:40 by ohakola           #+#    #+#             */
/*   Updated: 2021/02/27 17:58:51 by ohakola          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

void			rand_array(int32_t *array, int32_t array_size);
void			copy_array(int32_t *dst, int32_t *src,
					int32_t arrays_size);
t_bool			arrays_match(int32_t *arr1, int32_t *arr2,
					int32_t arrays_size);
int				check_comp(const void *a, const void *b);
void			sort_check_array(int32_t *check_array, int32_t array_size);

#endif