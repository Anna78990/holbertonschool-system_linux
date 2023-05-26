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
	pthread_mutex_init(&(task->lock), NULL);

	return (task);
}

/**
 * destroy_task - destroy a task
 * @task: pointer to the task to destroy
 * Return: Always nothing
 */
void destroy_task(task_t *task)
{
	if (task == NULL)
		return;

	pthread_mutex_destroy(&(task->lock));
	free(task);
}

/**
 * exec_tasks - execute task
 * @tasks: pointer to the list of tasks to be executed
 * Return: Always nothing
 */
void *exec_tasks(list_t const *tasks)
{
	if (tasks == NULL)
		return (NULL);

	node_t *current = tasks->head;

	while (current != NULL)
	{
		task_t *task = (task_t *)current->content;

		pthread_mutex_lock(&(task->lock));

		if (task->status == PENDING)
		{
			task->status = STARTED;
			pthread_mutex_unlock(&(task->lock));

			tprintf("[%lu] [%lu] Started\n", pthread_self(), task->param);

			task->result = task->entry(task->param);

			pthread_mutex_lock(&(task->lock));
			task->status = SUCCESS;
			pthread_mutex_unlock(&(task->lock));

			tprintf("[%lu] [%lu] Success\n", pthread_self(), task->param);
		} else
			pthread_mutex_unlock(&(task->lock));

		current = current->next;
	}

	return (NULL);
}
