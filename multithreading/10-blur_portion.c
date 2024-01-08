#include "multithreading.h"

/**
 * free_array - free the given arrays
 * @h: size of array
 * @pix: array to free
 */
void free_array(size_t h, pixel_t ***pix)
{
	size_t i;

	for (i = 0; i < h; i++)
		free(pix[i]);
	free(pix);
}

/**
 * conv - convlusions for rgb and kernel
 * @portion: pointer to structure with information needed to blur
 * @i: start of height
 * @j: start of width
 * @img: double array of pixels
 * Return: convluisoned pixel
 */
pixel_t *conv(blur_portion_t const *portion, size_t i, size_t j,
		pixel_t ***img)
{
	pixel_t *new_pixel = NULL;
	float sum = 0.0, **kernel = NULL;
	float red = 0.0, blue = 0.0, green = 0.0;
	ssize_t size_kernel = 0, mid = 0, start_x = 0, start_y = 0,
		end_x = 0, end_y = 0;

	new_pixel = calloc(1, sizeof(pixel_t));
	size_kernel = portion->kernel->size;
	mid = size_kernel / 2;
	kernel = portion->kernel->matrix;

	end_y = i + mid;
	end_x = j + mid;
	for (start_y = i - mid; start_y <= end_y; start_y++)
	{
		for (start_x = j - mid; start_x <= end_x; start_x++)
		{
			if (start_y > -1 && start_x > -1 &&
					start_x < (ssize_t) portion->img->w &&
					start_y < (ssize_t) portion->img->h)
			{
				red += (img[start_y][start_x]->r *
						kernel[start_y - i + mid][start_x - j + mid]);
				blue += (img[start_y][start_x]->b *
						kernel[start_y - i + mid][start_x - j + mid]);
				green += (img[start_y][start_x]->g *
						kernel[start_y - i + mid][start_x - j + mid]);
				sum += kernel[start_y - i + mid][start_x - j + mid];
			}
		}
	}
	new_pixel->r = red / sum;
	new_pixel->b = blue / sum;
	new_pixel->g = green / sum;

	return (new_pixel);
}

/**
 * create_array - create dimentional pixel_t array from an original array
 * @img: pointer to img struct containing pixel_t array
 * @pxl: pointer to pixel to refer
 * Return: created array or NULL if malloc fails
 */
pixel_t ***create_array(const img_t *img, pixel_t *pxl)
{
	size_t i, j;
	pixel_t ***pixels;

	pixels = calloc(img->h, sizeof(img_t **));
	for (i = 0; i < img->h; i++)
		pixels[i] = calloc(img->w, sizeof(img_t *));

	for (i = 0; i < img->h; i++)
	{
		for (j = 0; j < img->w; j++)
			pixels[i][j] = &(pxl[(img->w * i) + j]);
	}
	return (pixels);
}

/**
 * blur_portion - blur portion of an image using Gaussian blur
 * @portion: pointer to structure with information needed to blur
 */
void blur_portion(blur_portion_t const *portion)
{
	pixel_t ***blur_img = NULL, ***img = NULL, *conved = NULL;
	size_t i, j;

	if (!portion)
		return;
	blur_img = create_array(portion->img, portion->img_blur->pixels);
	img = create_array(portion->img, portion->img->pixels);
	for (i = portion->y; i < portion->y + portion->h; i++)
	{
		for (j = portion->x; j < portion->x + portion->w; j++)
		{
			conved = conv(portion, i, j, img);
			(blur_img[i][j])->r = conved->r;
			(blur_img[i][j])->b = conved->b;
			(blur_img[i][j])->g = conved->g;
			free(conved);
		}
	}
	free_array(portion->img->h, blur_img);
	free_array(portion->img->h, img);
}
