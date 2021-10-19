/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jceia <jceia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 10:58:52 by jceia             #+#    #+#             */
/*   Updated: 2021/10/19 10:25:41 by jceia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft.h"
# include "vec.h"
# include "matrix.h"

# define WIN_WIDTH		1920
# define WIN_HEIGHT		1080

# ifdef OS_Linux
#  define K_LEFT_ARROW	65361
#  define K_RIGHT_ARROW	65363
#  define K_UP_ARROW	65362
#  define K_DOWN_ARROW	65364
#  define K_ESC			65307
#  define K_A			97
#  define K_D			100
#  define K_W			119
#  define K_S			115
# else
#  define K_LEFT_ARROW	123
#  define K_RIGHT_ARROW	124
#  define K_UP_ARROW	126
#  define K_DOWN_ARROW	125
#  define K_ESC			53
#  define K_A			0
#  define K_D			2
#  define K_W			13
#  define K_S			1
# endif

/*
 * X11 Events
 */

# define KEY_PRESS		02
# define KEY_RELEASE	03
# define BUTTON_PRESS	04
# define BUTTON_RELEASE 05
# define MOTION_NOTIFY	06
# define DESTROY_NOTIFY	17

/*
 * X11 Masks
 */
# define M_NO_EVENT			0L
# define M_KEY_PRESS		1L
# define M_KEY_RELEASE		2L
# define M_BUTTON_PRESS 	4L
# define M_BUTTON_RELEASE	8L
# define M_POINTER_MOTION	64L

/*
 * 3D Ray
 */
typedef struct s_ray3d
{
	t_vec3d	origin;
	t_vec3d	direction;
}	t_ray3d;

t_ray3d		ray3d_create(t_vec3d origin, t_vec3d direction);
t_ray3d		ray3d_from_two_points(t_vec3d p, t_vec3d q);
t_vec3d		ray3d_at(const t_ray3d *ray, float t);
t_ray3d		ray3d_reflected(const t_ray3d *ray, t_vec3d normal);

/*
 * Color
 */
typedef t_vec3d	t_rgb;

int			create_trgb(t_rgb color);
int			get_t(int trgb);
int			get_r(int trgb);
int			get_g(int trgb);
int			get_b(int trgb);

/*
 * 3D Objects
 */
typedef enum e_object_type {
	PLANE,
	TRIANGLE,
	DISK,
	SPHERE,
	CYLINDER,
	CONE
}	t_object_type;

typedef enum e_proj
{
	PROJ,
	PARALLEL
}	t_proj;

typedef struct s_ambient_light
{
	float	ratio;
	t_rgb	color;
}	t_ambient_light;

typedef struct s_camera
{
	t_vec3d		origin;
	t_vec3d		direction;
	float		fov;
	t_matrix	*basis;
	int			pixels_width;
	int			pixels_height;
	float		view_width;
	float		view_height;
	t_proj		proj_type;
}	t_camera;

typedef struct s_light
{
	t_vec3d	origin;
	float	ratio;
	t_rgb	color;
}	t_light;

typedef struct s_sphere
{
	t_vec3d	center;
	float	radius;
	t_rgb	color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3d	p;
	t_vec3d	n;
	t_rgb	color;
}	t_plane;

typedef struct s_triangle
{
	t_vec3d	p1;
	t_vec3d	p2;
	t_vec3d	p3;
	t_rgb	color;
}	t_triangle;

typedef struct s_disk
{
	t_vec3d	center;
	t_vec3d	n;
	float	radius;
	t_rgb	color;
}	t_disk;

typedef struct s_cylinder
{
	t_vec3d	p;
	t_vec3d	direction;
	float	radius;
	float	height;
	t_rgb	color;
}	t_cylinder;

typedef struct s_object
{
	t_object_type	obj_type;
	void			*data;
}	t_object;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	t_ambient_light
			ambient;
	t_camera
			*camera;
	t_list	*lights;
	t_list	*objects;
	t_rgb	*buf;
}	t_data;

typedef struct s_args
{
	char	*fname;
	char	*title;
	int		width;
	int		height;
}	t_args;

/*
 * Parser
 */
int			check_file_extension(char *fname, char const *ext);
t_data		*parse_data_from_file(t_data *vars, char *fname);
t_rgb		*parse_color(t_rgb *color, char *s);
t_vec3d		*parse_vec3d(t_vec3d *p, char *s);
t_data		*parse_ambient_from_line(t_data *vars, char *line);
t_data		*parse_camera_from_line(t_data *vars, char *line);
t_data		*parse_light_from_line(t_data *vars, char *line);
t_data		*parse_object_from_line(t_data *vars, char *line);
t_object	*parse_sphere_from_line(t_object *obj, char *line);
t_object	*parse_plane_from_line(t_object *obj, char *line);
t_object	*parse_cylinder_from_line(t_object *obj, char *line);
t_object	*parse_triangle_from_line(t_object *obj, char *line);
t_object	*parse_disk_from_line(t_object *obj, char *line);

/*
 * MLX UTILS
 */

void		plot_pixel(t_data *data, float x, float y, t_rgb color);
void		update_image_from_buf(t_data *data);
void		mlx_data_init(t_data *vars, const t_args *args);
void		mlx_data_update_image(t_data *vars);
int			key_press(int keycode, t_data *vars);
int			exit_handle(t_data *vars);

/*
 * Clear
 */
void		mlx_data_clean(void *vars);
void		*clean_exit(void *ptr, char *msg, void (*del)(void *), int do_exit);

/*
 * Camera
 */
void		calculate_camera_params(t_camera *cam,
				int win_width, int win_height);
void		camera_clean(void *ptr);

/*
 * 2nd degree equations
 */

typedef struct s_float_pair
{
	float		min;
	float		max;
}	t_float_pair;

typedef struct s_deg2_eq_coefs
{
	float	a;
	float	b;
	float	c;
}	t_deg2_eq_coefs;

t_bool		deg2_eq_solutions(const t_deg2_eq_coefs *params, t_float_pair *t);

/*
 * Raytracer (Core)
 */
typedef struct s_hit_record
{
	t_vec3d		p;
	t_vec3d		n;
	t_object	*obj;
	t_rgb		base_color;
	float		t;
}	t_hit_record;

t_rgb		hit_color(
				const t_ray3d *reflected_ray,
				const t_hit_record *hit_record,
				const t_data *vars);
void		raytrace_scenario(t_data *vars);
t_rgb		raytrace_single(const t_ray3d *ray, const t_data *vars);

t_bool		raytrace_hit(const t_ray3d *ray, const t_data *vars,
				float t_min, t_hit_record *record);

t_bool		hit_object(const t_ray3d *ray, t_object *obj,
				float t_min, t_hit_record *record);

t_bool		hit_sphere(const t_ray3d *ray, const t_sphere *sphere,
				float t_min, t_hit_record *record);
t_bool		hit_plane(const t_ray3d *ray, const t_plane *plane,
				float t_min, t_hit_record *record);
t_bool		hit_cylinder(const t_ray3d *ray, const t_cylinder *cyclinder,
				float t_min, t_hit_record *record);
t_bool		hit_triangle(const t_ray3d *ray, const t_triangle *triangle,
				float t_min, t_hit_record *record);
t_bool		hit_disk(const t_ray3d *ray, const t_disk *disk,
				float t_min, t_hit_record *record);

#endif
