#include "multithreading.h"
#include "list.h"
#include <pthread.h>

/**
 * create_task - create a task
 *
 * @entry: a pointer to the entry function of the task,
 * @param: the parameter that will later be passed to the entry function
 * Return: a pointer to the created task structure
 */
task_t *create_task(task_entry_t entry, void *param)
{
	task_t *task = (task_t *)malloc(sizeof(task_t));

	if (task == NULL)
		return (NULL);

	task->entry = entry;
	task->param = param;
	task->status = PENDING;
	task->result = NULL;
	return (task);
}

/**
 * destroy_task - destroy a task
 * @task: pointer to the task to destroy
 * Return: Always nothing
 */
void destroy_task(task_t *task)
{
	if (task->result)
	{
		list_destroy((list_t *) task->result, free);
		free((list_t *) task->result);
	}
	free(task);
}

/**
 * exec_tasks - execute task
 * @tasks: pointer to the list of tasks to be executed
 * Return: Always nothing
 */
void *exec_tasks(list_t const *tasks)
{
	task_t *task;
	int i = 0;
	node_t *current;

	if (tasks == NULL)
		return (NULL);

	current = tasks->head;
	while (current != NULL)
	{
		task = (task_t *)current->content;

		if (task->status == PENDING)
		{
			task->status = STARTED;
			tprintf("[%02d] Started\n", i);
			task->result = task->entry(task->param);
			tprintf("[%02d] Success\n", i);
			if (task->result == NULL)
				task->status = FAILURE;
			else
				task->status = SUCCESS;
		}
		current = current->next;
		i++;
	}
	return (NULL);
}
