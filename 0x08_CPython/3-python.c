#include <Python.h>
#include <stdio.h>

void print_python_bytes(PyObject *p);
void print_python_float(PyObject *p);

/**
 * print_python_list - print list informations of a given python object
 * @p: pointer to python object
 */
void print_python_list(PyObject *p)
{
	ssize_t size = ((PyVarObject *)p)->ob_size;
	ssize_t i;

	setbuf(stdout, NULL);

	if (!p || p->ob_type != &PyList_Type)
	{
		printf("  [ERROR] Invalid List Object\n");
		return;
	}
	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %ld\n", size);
	printf("[*] Allocated = %ld\n", ((PyListObject *)p)->allocated);

	for (i = 0; i < size; i++)
	{
		PyObject *item = ((PyListObject *)p)->ob_item[i];

		printf("Element %ld: %s\n", i, item->ob_type->tp_name);
		if (item->ob_type == &PyBytes_Type)
			print_python_bytes(item);
		else if (item->ob_type == &PyFloat_Type)
			print_python_float(item);
	}
}

/**
 * print_python_bytes - print byte informations of a given python object
 * @p: pointer to python object
 */
void print_python_bytes(PyObject *p)
{
	ssize_t size = 0;
	ssize_t i;

	setbuf(stdout, NULL);
	printf("[.] bytes object info\n");

	if (p->ob_type != &PyBytes_Type)
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}

	size = ((PyVarObject *)p)->ob_size;
	printf("  size: %ld\n", size);
	printf("  trying string: %s\n", ((PyBytesObject *)p)->ob_sval);
	size = size < 9 ? size + 1 : 10;
	printf("  first %ld bytes: ", size);
	for (i = 0; i < size ; i++)
	{
		printf("%02x", ((PyBytesObject *)p)->ob_sval[i]);
		if (i + 1 == size)
			printf("\n");
		else
			printf(" ");
	}

}

/**
 * print_python_float - print informations of a given python object
 * @p: pointer to python object
 */
void print_python_float(PyObject *p)
{
	char *str;

	setbuf(stdout, NULL);
	printf("[.] float object info\n");
	if (!p || p->ob_type != &PyFloat_Type)
	{
		printf("  [ERROR] Invalid Float Object\n");
		return;
	}
	str = PyOS_double_to_string(((PyFloatObject *)p)->ob_fval,
		'g', 16, 0, NULL);
	printf("  value: %s", str);
	if (strchr(str, '.'))
		printf("\n");
	else
		printf(".0\n");
}

