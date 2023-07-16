/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmedina- <jmedina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 10:38:24 by jmedina-          #+#    #+#             */
/*   Updated: 2023/07/16 13:06:28 by jmedina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILAS 6
#define COLUMNAS 6

const int	g_dic4[1] = {1234};
const int	g_dic3[6] = {1243, 1324, 1342, 2134, 2314, 2341};
const int	g_dic2[11] = {1423, 1432, 2143, 2413, 2431, 3124,
	3142, 3214, 3241, 3412, 3421};
const int	g_dic1[6] = {4123, 4132, 4213, 4231, 4312, 4321};

int	check_arg(char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
	{
		if (count % 2 == 0)
		{
			if (!(str[count] >= '1' && str[count] <= '4'))
				return (0);
		}
		else
			if (!(str[count] == ' '))
				return (0);
		count += 2;
	}
	return (1);
}

void	generate(char *str_argumentos, int **matrix)
{
	int		string_count;
	int		count;
	int		it;
	int		z_f_it;

	string_count = 0;
	count = -1;
	it = 1;
	z_f_it = 0;
	while (++count < 16) 
	{
		if ((count / 4) % 2 == 0)
			z_f_it = 0;
		else
			z_f_it = 5;
		if (count < 8)
			matrix [z_f_it][it] = str_argumentos[string_count] - '0';
		else
			matrix [it][z_f_it] = str_argumentos[string_count] - '0';
		if (it == 4)
			it = 1;
		else
			it++;
		string_count += 2;
	}
}

int	in_row(int **matrix, int column, int row, int num_compare)
{
	int	count;

	count = 0;
	while (++count < column)
	{
		if (matrix[row][count] == num_compare)
			return (1);
	}
	return (0);
}

int	assign_num(int **matrix, int column, int cnt_dictionary)
{
	int	count;
	int	div;
	int	num_2_assign;

	count = 0;
	div = 1000;
	if (matrix[0][column] == 1) 
		num_2_assign = g_dic1[cnt_dictionary];
	else if (matrix[0][column] == 2) 
		num_2_assign = g_dic2[cnt_dictionary];
	else if (matrix[0][column] == 3)
		num_2_assign = g_dic3[cnt_dictionary];
	else
		num_2_assign = g_dic4[cnt_dictionary];
	while (++count <= 4)
	{
		matrix[count][column] = (num_2_assign) / (div);
		num_2_assign %= div;
		div /= 10;
		if (in_row(matrix, column, count, matrix[count][column]))
			count = 5;
	}
	return (count == 6);
}

int	dictionary_length(int limite)
{
	if (limite == 1)
		return (6);
	else if (limite == 2)
		return (11);
	else if (limite == 3)
		return (6);
	else if (limite == 4)
		return (1);
	else 
		return (0);
}

int	check_column(int **matrix, int column)
{
	int	count;
	int	vista;
	int	aux;

	count = 0;
	vista = 1;
	aux = matrix[4][column];
	while (++count < 4)
	{
		if (matrix[4 - count][column] > aux)
		{
			vista++;
			aux = matrix[4 - count][column];
		}
	}
	return (matrix[5][column] == vista);
}

int	check_left(int **matrix, int row)
{
	int	count;
	int	vista;
	int	aux;

	count = 0;
	vista = 1;
	aux = matrix[row][1];
	while (++count < 4)
	{
		if (matrix[row][count + 1] > aux)
		{
			vista++;
			aux = matrix[row][count + 1];
		}
	}
	return (matrix[row][0] == vista);
}

int	check_right(int **matrix, int row)
{
	int	count;
	int	vista;
	int	aux;

	count = 0;
	vista = 1;
	aux = matrix[row][4];
	while (++count < 4)
	{
		if (matrix[row][4 - count] > aux)
		{
			vista++;
			aux = matrix[row][4 - count];
		}
	}
	return (matrix[row][5] == vista);
}

int	check_rows(int **matrix)
{
	int	row;
	int	check;

	row = 0;
	check = 1;
	while (++row <= 4 && check)
	{
		check = (check_left(matrix, row) && check_right(matrix, row));
	}
	return (check);
}

void	recursive(int **matrix, int column, int *result)
{
	int	cnt_dictionary;
	int	limite_diccionario;
	int	assign_failure;
	int	i;
	int	j;

	i = 1;
	j = 1;
	cnt_dictionary = -1;
	limite_diccionario = dictionary_length(matrix[0][column]);
	while (++cnt_dictionary < limite_diccionario && !(*result))
	{
		assign_failure = assign_num(matrix, column, cnt_dictionary);
		if ((!assign_failure) && check_column(matrix, column))
		{
			if (column != 4)
				recursive(matrix, column + 1, result);
			else 
				*result = check_rows(matrix);
		}
	}
	if (*result && (column == 4)) 
	{
		int	number;
		while (i <= 4)
		{
			while (j <= 4)
			{
				number = matrix[i][j] + '0';
				write(1, &(number), 1);
				write(1, " ", 1);
				j++;
			}
			i++;
			j = 1;
			write(1, "\n", 1);
		}
	}
	else if (!(*result) && (column == 1))
		printf("Error, no hay solución posible");
}

void	map(int **matrix)
{
	int	result;

	result = 0;
	recursive(matrix, 1, &result);
}

void	rush(char *str_argumentos)
{
	int		**matrix;
	int		count;

	count = -1;
	matrix = (int **)malloc(sizeof(int *) * FILAS);
	while (++count < 6)
		matrix[count] = (int *)malloc(sizeof(int) * COLUMNAS);
	generate(str_argumentos, matrix);
	map(matrix);
	free(matrix);
}

int	main(int argc, char *argv[])
{
	argv[1] = "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2";
	if (argc != 2)
	{
		write(1, "Error: argumento no introducido", 5);
		exit(1);
	}
	else
	{
		if (!check_arg(argv[1]))
			perror("Error: argumentos inválidos");
		rush(argv[1]);
	}
}
