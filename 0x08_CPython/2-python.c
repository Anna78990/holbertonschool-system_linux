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
	Py_ssize_t size = PyObject_Size(p);
	Py_ssize_t i;
	PyObject *item;

	printf("[*] Python list info\n");
	printf("[*] Size of the Python List = %ld\n", size);
	printf("[*] Allocated = %ld\n", ((PyListObject *)p)->allocated);

	for (i = 0; i < size; i++)
	{
		item = PyObject_GetItem(p, PyLong_FromSsize_t(i));
		printf("Element %ld: %s\n", i, Py_TYPE(item)->tp_name);
		Py_DECREF(item);
	}
}

/**
 * print_python_bytes - print byte information of a given python object
 * @p: pointer to python object
 */
void print_python_bytes(PyObject *p)
{
	Py_ssize_t size;
	Py_ssize_t i;
	unsigned char *str;

	printf("[.] bytes object info\n");

	if (!PyBytes_Check(p))
	{
		printf("  [ERROR] Invalid Bytes Object\n");
		return;
	}

	size = ((PyVarObject *)p)->ob_size;
	printf("  size: %ld\n", size);

	str = (unsigned char *)PyBytes_AsString(p);
	printf("  trying string: %s\n", ((PyBytesObject *)p)->ob_sval);

	printf("  first %ld bytes: ", size < 10 ? size + 1 : 10);
	for (i = 0; i <= size && i < 10; i++)
		printf("%02x%s", str[i], i < size - 1 && i < 9 ? " " : "\n");
}
