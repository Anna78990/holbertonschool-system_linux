#include <Python.h>
#include <stdio.h>

/**
 * print_python_string - print string of a given python object
 * @p: pointer to python object
 */
void print_python_string(PyObject *p)
{
	printf("[.] string object info\n");
	if (!p || p->ob_type != &PyUnicode_Type)
	{
		printf("  [ERROR] Invalid String Object\n");
		return;
	}
	if (((PyASCIIObject *)p)->state.ascii)
		printf("  type: compact ascii\n");
	else
		printf("  type: compact unicode object\n");
	wprintf(L"  length: %ld\n", ((PyASCIIObject *)p)->length);
	wprintf(L"  value: %ls\n", PyUnicode_AS_UNICODE(p));
}
