#include "multithreading.h"

/**
 * get_sums - initialise sums for rgb and kernel
 * @r_sum: pointer to sum of red values
 * @g_sum: pointer to sum of green values
 * @b_sum: pointer to sum of blue values
 * @kernel_sum:	pointer to sum of kernel values
 * @portion: pointer to structure with information needed to blur
 * @pixels: double array of pixels
 * @x: x position for pixels array of pixel to blur
 * @y: y position for pixels array of pixel to blur
 */
void get_sums(float *r_sum, float *g_sum, float *b_sum, float *kernel_sum,
		const blur_portion_t *portion, const pixel_t **pixels,
		size_t x, size_t y)
{
	ssize_t grid_x, grid_y, grid_stop_x, grid_stop_y;
	size_t half_kernel, kernel_x, kernel_y;

	half_kernel = portion->kernel->size / 2;
	grid_x = x - half_kernel;
	grid_y = y - half_kernel;
	grid_stop_y = grid_y + portion->kernel->size;
	grid_stop_x = grid_x + portion->kernel->size;
	for (grid_y = y - half_kernel,
			kernel_y = *r_sum = *g_sum = *b_sum = *kernel_sum = 0;
			grid_y < grid_stop_y; grid_y++, kernel_y++)
	{
		for (grid_x = x - half_kernel, kernel_x = 0; grid_x < grid_stop_x;
				grid_x++, kernel_x++)
		{
			if (grid_x > -1 && grid_y > -1 &&
					grid_x < (ssize_t) portion->img->w &&
					grid_y < (ssize_t) portion->img->h)
			{
				*r_sum += portion->kernel->matrix[kernel_y][kernel_x] *
					pixels[grid_y][grid_x].r;
				*g_sum += portion->kernel->matrix[kernel_y][kernel_x] *
					pixels[grid_y][grid_x].g;
				*b_sum += portion->kernel->matrix[kernel_y][kernel_x] *
					pixels[grid_y][grid_x].b;
				*kernel_sum += portion->kernel->matrix[kernel_y][kernel_x];
			}
		}
	}
}

/**
 * blur_pixel - blur individual pixel
 *
 * @portion: pointer to structure with information needed to blur
 * @pixels: double array of pixels
 * @x: x position for pixels array of pixel to blur
 * @y: y position for pixels array of pixel to blur
 * @pidx: index of pixel to blur for output array
 *
 * Using pixels double array for simplified 1 to 1 traversal of image with
 * kernel
 */
void blur_pixel(const blur_portion_t *portion, const pixel_t **pixels,
		size_t x, size_t y, size_t pidx)
{
	float r_avg, g_avg, b_avg, kernel_sum;

	get_sums(&r_avg, &g_avg, &b_avg, &kernel_sum, portion, pixels, x, y);
	r_avg /= kernel_sum, g_avg /= kernel_sum, b_avg /= kernel_sum;
	portion->img_blur->pixels[pidx].r = r_avg;
	portion->img_blur->pixels[pidx].g = g_avg;
	portion->img_blur->pixels[pidx].b = b_avg;
}

/**
 * create_array - create dimentional pixel_t array from an original array
 * @img: pointer to img struct containing pixel_t array
 *
 * Return: created array or NULL if malloc fails
 */
pixel_t **create_array(const img_t *img)
{
	pixel_t **pixels;
	size_t i, j, k = 0;

	if (!img || img->w == 0 || img->h == 0)
		return (NULL);
	pixels = malloc(img->h * sizeof(*pixels));
	if (!pixels)
		return (NULL);
	for (i = 0; i < img->h; i++)
	{
		pixels[i] = malloc(img->w * sizeof(**pixels));
		if (!pixels[i])
			return (NULL);
		for (j = 0; j < img->w; j++, k++)
			pixels[i][j] = img->pixels[k];
	}
	return (pixels);
}

/**
 * blur_portion - blur portion of an image using Gaussian blur
 * @portion: pointer to structure with information needed to blur
 */
void blur_portion(blur_portion_t const *portion)
{
	size_t i, j, img_idx, start, stop_x, stop_y;
	pixel_t **array_pixels;

	if (!portion)
		return;
	array_pixels = create_array(portion->img);
	if (!array_pixels)
		return;
	start = portion->x + (portion->y * portion->img->w);
	img_idx = start;
	stop_x = start + portion->w;
	stop_y = stop_x + (portion->img->w * (portion->h - 1));
	for (i = portion->x; i < portion->w + portion->x; i++)
	{
		for (j = portion->y; j < portion->h + portion->y; j++)
		{
			blur_pixel(portion, (const pixel_t **)array_pixels, i, j, img_idx);
			img_idx += portion->img->w;
			if (img_idx >= stop_y)
			{
				img_idx += 1;
				if (img_idx >= stop_x)
					break;
			}
		}
	}
	for (i = 0; i < portion->img->h; i++)
		free(array_pixels[i]);
	free(array_pixels);
}
