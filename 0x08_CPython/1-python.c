#include <Python.h>
#include <stdio.h>

/**
 * print_python_list - Prints basic info about Python lists
 * @p: PyObject pointer to the Python list
 */
void print_python_list(PyObject *p)
{
	PyListObject *list = (PyListObject *)p;
	Py_ssize_t size, alloc, i;

	printf("[*] Python list info\n");

	size = Py_SIZE(list);
	alloc = list->allocated;

	printf("[*] Size of the Python List = %zd\n", size);
	printf("[*] Allocated = %zd\n", alloc);

	for (i = 0; i < size; i++)
	{
		printf("Element %zd: %s\n", i, Py_TYPE(PyList_GetItem(p, i))->tp_name);
	}
}
