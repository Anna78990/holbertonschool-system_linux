#include <Python.h>
#include <stdio.h>

void print_python_list(PyObject *p);
void print_python_bytes(PyObject *p);

/**
 * print_python_list - print list information of a given python object
 * @p: pointer to python object
 */
void print_python_list(PyObject *p)
{
	ssize_t size = ((PyVarObject *)p)->ob_size;
	ssize_t i;

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %ld\n", size);
	printf("[*] Allocated = %ld\n", ((PyListObject *)p)->allocated);

	for (i = 0; i < size; i++)
	{
		PyObject *item = ((PyListObject *)p)->ob_item[i];
		printf("Element %ld: %s\n", i, item->ob_type->tp_name);
		if (item->ob_type == &PyBytes_Type)
			print_python_bytes(item);
	}
}

/**
 * print_python_bytes - print byte information of a given python object
 * @p: pointer to python object
 */
void print_python_bytes(PyObject *p)
{
	ssize_t size = 0;
	ssize_t i;

	printf("[.] bytes object info\n");

	if (p->ob_type != &PyBytes_Type)
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}

	size = ((PyVarObject *)p)->ob_size;
	printf("  size: %ld\n", size);
	printf("  trying string: %s\n", ((PyBytesObject *)p)->ob_sval);

	printf("  first %ld bytes: ", size < 9 ? size + 1 : 10);
	for (i = 0; i + 1 < size && i < 10; i++)
	{
		printf("%02x", ((PyBytesObject *)p)->ob_sval[i]);
		if (i + 1 == size || (i + 1) == 9)
		{
			printf("\n");
			break;
		}
		else
			printf(" ");
		
	}

}
