#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define FILAS 4

struct		s_Data
{
	int		data;
	int		block;
};

const int	*generate_array(char *str_argumentos)
{
	static int	array[16];
	int			count;
	int			string_count;

	count = -1;
	string_count = 0;
	while (++count < 16)
	{
		array[count] = str_argumentos[string_count] - '0';
		string_count += 2;
	}
	return (array);
}

void	algorithm(int *array)
{
	static int	dic4[1] = {1234};
	static int	dic3[6] = {1243, 1324, 1342, 2134, 2314, 2341};
	static int	dic2[11] = {1423, 1432, 2143, 2413, 2431, 3124, 
    3142, 3214, 3241, 3412,	3421};
	static int	dic1[6] = {4123, 4132, 4213, 4231, 4312, 4321};
	int		**matriz;

	matriz = (int **)malloc(FILAS * sizeof(int));
}

int		check_sum(int *array) //Comprueba qeu en el array de numeros de los argumentos pasados por main no tiene ninguna suma de reversos que supere 5
{
	return (1);
}

int		check_num_one_four(int *array) //Comprueba que en el array de números pasados por argumento no puede haber en la region de colup, coldown, ... repetidos ni 1 ni 4
{
	return (1);
}

void	rush(char *str_argumentos)
{
	static int	*array;

	array = (int *)malloc(sizeof(int) * 16);
	array = generate_array(str_argumentos); //pasa string a int[]
	if (check(array))
		algorithm(array); //algoritmo para la ejecucion y extracción de un resultado para la matriz 
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
