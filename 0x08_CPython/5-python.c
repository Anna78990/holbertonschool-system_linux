#include <Python.h>

/**
 * print_python_int - print Python integers of a given python object
 * @p: pointer to python object
 */
void print_python_int(PyObject *p)
{
	ssize_t size, i;
	unsigned long num = 0;

	if (!p || !PyLong_Check(p))
	{
		printf("Invalid Int Object\n");
		return;
	}
	size = ((PyVarObject *)(p))->ob_size;
	if (abs(size) > 3 || (abs(size) == 3 &&
			((PyLongObject *)(p))->ob_digit[2] > 15))
	{
		printf("C unsigned long int overflow\n");
		return;
	}
	for (i = 0; i < abs(size); i++)
		num += ((PyLongObject *)(p))->ob_digit[i] * (1UL
			<< (i * PyLong_SHIFT));
	if (size < 0)
		printf("-");
	printf("%lu\n", num);
}
