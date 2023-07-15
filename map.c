/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmedina- <jmedina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:44:09 by jamedina          #+#    #+#             */
/*   Updated: 2023/07/15 15:47:16 by jmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include"lib_ft.h"

void	ft_fill_map(int **matriz, int filas, int columnas)
{
	int	i;
	int	j;
	int	nb;

	i = 0;
	nb = 1;
	while (i < filas)
	{
		j = 0;
		nb = 1;
		while (j < columnas)
		{
			if (i >= 1)
				{
				if ((matriz[i-1][j] + 1) > 4)
					matriz[i][j] = 1;
				else
					matriz[i][j] = matriz[i-1][j] + 1;
				}
			else
				matriz[i][j] = nb;
			j++;
			nb++;
			if (nb > 4)
				nb = 1;
		}
		i++;
	}
}

int	**ft_map(int filas, int columnas)
{
	int	**matriz;
	int	i;
	int	j;
	int	nb;

	nb = 1;
	matriz = (int **)malloc(filas * sizeof(int *));
	i = 0;
	while (i < filas)
	{
		matriz[i] = (int *)malloc(columnas * sizeof(int));
		i++;
	}
	ft_fill_map(matriz, filas, columnas);
	return (matriz);
}

void	ft_print_map(int **matriz, int filas, int columnas)
{
	int	i;
	int	j;

	i = 0;
	printf("La matriz generada es:\n");
	while (i < filas)
	{
		j = 0;
		while (j < columnas)
		{
			printf("%d ", matriz[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

/* 
int main() {
    int filas, columnas;
    printf("Ingrese el número de filas: ");
    scanf("%d", &filas);
    printf("Ingrese el número de columnas: ");
    scanf("%d", &columnas);

    int **matriz = ft_map(filas, columnas);
    ft_print_map(matriz, filas, columnas);

    // Liberar la memoria asignada
    for (int i = 0; i < filas; i++) {
        free(matriz[i]);
    }
    free(matriz);

    return 0;
}
*/
