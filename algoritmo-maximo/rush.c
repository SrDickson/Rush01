#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILAS 6
#define COLUMNAS 6

const int	dic4[1] = {1234};
const int	dic3[6] = {1243, 1324, 1342, 2134, 2314, 2341};
const int	dic2[11] = {1423, 1432, 2143, 2413, 2431, 3124, 3142, 3214, 3241, 3412, 3421};
const int	dic1[6] = {4123, 4132, 4213, 4231, 4312, 4321};

void	generate(char *str_argumentos, int **matrix)
{
	int		string_count;


	string_count = 0;
	matrix [0][1] = str_argumentos[string_count] - '0';
	matrix [0][2] = str_argumentos[string_count+=2] - '0';
	matrix [0][3] = str_argumentos[string_count+=2] - '0';
	matrix [0][4] = str_argumentos[string_count+=2] - '0';
	matrix [5][1] = str_argumentos[string_count+=2] - '0';
	matrix [5][2] = str_argumentos[string_count+=2] - '0';
	matrix [5][3] = str_argumentos[string_count+=2] - '0';
	matrix [5][4] = str_argumentos[string_count+=2] - '0';
	matrix [1][0] = str_argumentos[string_count+=2] - '0';
	matrix [2][0] = str_argumentos[string_count+=2] - '0';
	matrix [3][0] = str_argumentos[string_count+=2] - '0';
	matrix [4][0] = str_argumentos[string_count+=2] - '0';
	matrix [1][5] = str_argumentos[string_count+=2] - '0';
	matrix [2][5] = str_argumentos[string_count+=2] - '0';
	matrix [3][5] = str_argumentos[string_count+=2] - '0';
	matrix [4][5] = str_argumentos[string_count+=2] - '0';
}

int		in_row(int **matrix, int column, int row, int num_compare)
{
	int count;

	count = 0;
	while (++count < column)
		if (matrix[row][count] == num_compare)
			return (1);
	return (0);
}

 int	assign_num(int **matrix, int column, int cnt_dictionary) 
{
	int	count;
	int div;
	int num_2_assign;

	count = 0;
	div = 1000;
	switch(matrix[0][column]) {
		case 1:
				num_2_assign = dic1[cnt_dictionary];
				break;
			case 2:
				num_2_assign = dic2[cnt_dictionary];
				break;
			case 3:
				num_2_assign = dic3[cnt_dictionary];
				break;
			case 4:
				num_2_assign = dic4[cnt_dictionary];
				break;
	}
	while (++count <= 4)
	{
		matrix[count][column] = (num_2_assign) / (div);
		num_2_assign %= div;
		div /= 10;
		if (in_row(matrix,column, count, matrix[count][column])) {
			count = 5; //ha habido fallo en la escritura del número, es inválido porque hay un mismo dígito en alguna de sus filas
		}
	}
	return (count == 6);
}

int		dictionary_length(int limite)
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

int		check_column(int **matrix, int column)
{
	int count;
	int vista;
	int aux;

	count = 0;
	vista = 1;
	aux = matrix[4][column];
	while (++count < 4)
		if (matrix[4 - count][column] > aux)
		{
			vista++;
			aux = matrix[4- count][column];
		}
	return matrix[5][column] == vista;
}

int		check_left(int **matrix, int row)
{
	int count;
	int vista;
	int aux;

	count = 0;
	vista = 1;
	aux = matrix[row][1];
	while (++count < 4)
		if (matrix[row][count + 1] > aux)
		{
			vista++;
			aux = matrix[row][count + 1];
		}
	return matrix[row][0] == vista;
}

int		check_right(int **matrix, int row)
{
	int count;
	int vista;
	int aux;

	count = 0;
	vista = 1;
	aux = matrix[row][4];
	while (++count < 4)
		if (matrix[row][4 - count] > aux)
		{
			vista++;
			aux = matrix[row][4- count];
		}
	return matrix[row][5] == vista;
}

int		check_rows(int **matrix)
{
	int row;
	int check;

	row = 0;
	check = 1;
	while (++row <= 4 && check){
		check = (check_left(matrix, row) && check_right(matrix, row));
	}
	return (check);
}

void	recursive(int **matrix, int column, int *result)
{
	int cnt_dictionary = -1;
	int limite_diccionario = dictionary_length(matrix[0][column]);
	int assign_failure;

	while(++cnt_dictionary < limite_diccionario && !(*result))
	{
		assign_failure = assign_num(matrix, column, cnt_dictionary); //asigna el número que toca del diccionario en la n (columna) correspondiente
		if ((!assign_failure) && check_column(matrix, column)) //comprueba que la columna está bien en reverso 
		{
			if (column != 4)
				recursive(matrix, column + 1, result);
			else 
				*result = check_rows(matrix);
		} 
	}
	if (*result && (column == 4)) 
	{
		for(int i = 1; i <=4; i++) {
			for(int j = 1; j <= 4; j++) {
				printf("%d ", matrix[i][j]);
			}
			printf("\n");
		}
	} 
	else if (!(*result) && (column == 1))
		printf("Error, no hay solución posible");
}

void	map(int **matrix)
{
	int result;

	result = 0;
	recursive(matrix, 1, &result);
}

void	rush(char *str_argumentos)
{
	int		**matrix;
	int		count;

	count = -1;
	matrix = (int **)malloc(sizeof(int *) * FILAS);
	while (++count < 6) {
		matrix[count] = (int *)malloc(sizeof(int) * COLUMNAS);
	}
	generate(str_argumentos, matrix);
	map(matrix); //algoritmo para la ejecucion y extracción de un resultado para la matrix 
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
	{
		write(1, "Error", 5);
		exit(1);
	}
	else
		rush(argv[1]);
}
