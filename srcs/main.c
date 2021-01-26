/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 10:25:25 by celva             #+#    #+#             */
/*   Updated: 2020/09/14 23:36:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	init_struct(t_rt *r, char *fname)
{
	uint32_t	i;

	*r = (t_rt){
		.n_lig = 0,
		.n_fig = 0
	};
	read_scene(fname, r);
	i = 0;
	while (i < r->n_fig)
	{
		if (r->sbo_figures[i].type == obj_cone)
			r->sbo_figures[i].f_ver = vec4_add_vec4(
				r->sbo_figures[i].position,
				vec4_mul_f(r->sbo_figures[i].direction,
							r->sbo_figures[i].f_height));
		i++;
	}
	r->camera.d = 1.0;
}

int		main(int ac, char **av)
{
	t_app	app;

	if (ac == 1)
		return (0);
	setenv("VK_ICD_FILENAMES", VK_ICD_FILENAMES, 1);
	setenv("VK_LAYER_PATH", VK_LAYER_PATH, 1);
	app.appname = "RTv1";
	init_struct(&(app.r), av[1]);
	rtv_app_create(&app);
	app.r.camera.vh = 1.0;
	app.r.camera.vw = app.r.win_width
								/ app.r.win_height;
	ft_printf("App created\n");
	rtv_app_run(&app);
	return (0);
}
