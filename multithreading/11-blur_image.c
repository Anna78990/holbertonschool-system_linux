#include "multithreading.h"
#include <pthread.h>


/**
 * start_thread - entry point for thread
 *
 * @arg: pointer to thread
 *
 * Return: NULL
 */
void *start_thread(void *arg)
{
	blur_portion((blur_portion_t const *) arg);
	pthread_exit(NULL);
}


/**
 * blur_image - blur entire image using Gaussian blur
 * @img_blur: pointer to destination image
 * @img: pointer to source image
 * @kernel: pointer to convolution kernel
 */
void blur_image(img_t *img_blur, img_t const *img, kernel_t const *kernel)
{
	pthread_t *threads;
	blur_portion_t *portions;
	int i, aborted_pixels = 0;

	if (!img_blur || !img || !kernel)
		return;
	threads = calloc(THREADS, sizeof(pthread_t));
	portions = calloc(THREADS, sizeof(blur_portion_t));
	if (img->w % THREADS)
		aborted_pixels = img->w % THREADS;

	for (i = 0; i < THREADS; i++)
	{
		portions[i].img = img;
		portions[i].img_blur = img_blur;
		portions[i].kernel = kernel;
		portions[i].w = img->w / THREADS;
		portions[i].h = img->h;
		portions[i].x = i * portions[i].w;
		portions[i].y = 0;
		if (i + 1 == THREADS && aborted_pixels)
			portions[i].w += aborted_pixels;
		pthread_create(&threads[i], NULL, &start_thread, &portions[i]);
	}
	for (i = 0; i < THREADS; ++i)
		pthread_join(threads[i], NULL);
	free(portions);
	free(threads);
}
