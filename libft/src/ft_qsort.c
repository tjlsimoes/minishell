/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_qsort.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asafrono <asafrono@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 14:14:59 by asafrono          #+#    #+#             */
/*   Updated: 2024/12/06 14:18:03 by asafrono         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

static int	ft_partition(int *arr, int low, int high)
{
	int	pivot;
	int	i;
	int	j;

	pivot = arr[high];
	i = low - 1;
	j = low;
	while (j < high)
	{
		if (arr[j] <= pivot)
		{
			i++;
			ft_swap(&arr[i], &arr[j]);
		}
		j++;
	}
	ft_swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void	ft_qsort(int *arr, int low, int high)
{
	int	pi;

	if (low < high)
	{
		pi = ft_partition(arr, low, high);
		ft_qsort(arr, low, pi - 1);
		ft_qsort(arr, pi + 1, high);
	}
}
