#include "multithreading.h"
#include <pthread.h>

/**
 * struct thread_s - thread structure to execute the program
 * @index: index in the thread array
 * @id: id given by pthread_create()
 * @pixels: pointer to dimensional array of pixels of a image
 * @portion: pointer to blur_portion_s structure
 */
typedef struct thread_s
{
	int index;
	pthread_t tid;
	pixel_t **array_pixels;
	blur_portion_t *portion;
} thread_t;


/**
 * blur_by_thread - blur a part of image, using thread
 *
 * @thread: pointer to thread
 *
 * Return: Always nothing
 */
void blur_by_thread(thread_t *thread)
{
	size_t i, j, pixel_index, start, stop_x, stop_y;
	blur_portion_t *portion = thread->portion;

	if (!portion)
		return;
	start = portion->x + portion->y * portion->img->w;
	pixel_index = start;
	stop_x = start + portion->w;
	stop_y = stop_x + portion->img->w * (portion->h - 1);
	for (i = portion->x; i < portion->w + portion->x; ++i)
	{
		for (j = portion->y; j < portion->h + portion->y; ++j)
		{
			blur_pixel(portion, (const pixel_t **)thread->array_pixels, i, j, pixel_index);
			pixel_index += portion->img->w;
			if (pixel_index >= stop_y)
			{
				pixel_index = start += 1;
				if (pixel_index >= stop_x)
					break;
			}
		}

	}
}

/**
 * start_thread - entry point for thread
 *
 * @arg: pointer to thread
 *
 * Return: NULL
 */
void *start_thread(void *arg)
{
	blur_by_thread((thread_t *)arg);
	pthread_exit(NULL);
}

/**
 * init - initialise dynamic memory
 * @thread: double pointer to thread to execute the program
 * @portion: double pointer to potion information
 * @pixels: pointer to dimentional array of pixels
 * @img: pointer to source image
 * @img_blur: pointer to image to blur
 * @kernel: pointer to kernel
 *
 * Return: 0 on success or 1 when malloc fails
 */
int init(thread_t **thread, blur_portion_t **portion, pixel_t ***pixels,
		img_t const *img, img_t *img_blur, kernel_t const *kernel)
{
	int i;
	size_t offset;

	*thread= malloc(THREADS * sizeof(**thread));
	if (!*thread)
		return (1);
	*portion = malloc(THREADS * sizeof(**portion));
	if (!*portion)
		return (1);
	for (i = 0; i < THREADS; ++i)
	{
		(*portion)[i].img = img, (*portion)[i].img_blur = img_blur;
		(*portion)[i].kernel = kernel;
		if ((*portion)[i].img->w <= THREADS &&
				(size_t) i < (*portion)[i].img->w)
		{
			(*portion)[i].x = i;
			(*portion)[i].y = 0;
			(*portion)[i].w = 1;
			(*portion)[i].h = (*portion)[i].img->h;
		}
		else
		{
			offset = (*portion)[i].img->w / THREADS;
			(*portion)[i].x = offset * i;
			(*portion)[i].y = 0;
			(*portion)[i].w = offset;
			(*portion)[i].h = (*portion)[i].img->h;
		}
	}
	*pixels = create_array(img);
	if (!*pixels)
		return (1);
	return (0);
}

/**
 * blur_image - blur entire image using Gaussian blur
 * @img_blur: pointer to destination image
 * @img: pointer to source image
 * @kernel: pointer to convolution kernel
 */
void blur_image(img_t *img_blur, img_t const *img, kernel_t const *kernel)
{
	thread_t *thread;
	blur_portion_t *portion;
	pixel_t **pixels;
	int i, s;

	if (!img_blur || !img || !kernel)
		return;
	threads = get_nprocs();
	if (init(&thread, threads, &portion, &pixels, img, img_blur, kernel))
		return;
	for (i = 0; i < THREADS; ++i)
	{
		thread[i].index = i;
		thread[i].portion = &portion[i];
		thread[i].array_pixels = pixels;
		s = pthread_create(&thread[i].tid, NULL, &start_thread, thread + i);
		if (s != 0)
			return;
	}
	for (i = 0; i < THREADS; ++i)
	{
		s = pthread_join(thread[i].tid, NULL);
		if (s != 0)
			return;
	}
	for (i = 0; (size_t) i < img->h; ++i)
		free(pixels[i]);
	free(pixels);
	free(portion);
	free(thread);
}
