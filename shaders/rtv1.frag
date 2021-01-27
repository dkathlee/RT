#version 450
#extension GL_ARB_separate_shader_objects : enable

#define FLT_MAX 3.402823466e+38
#define FLT_MIN 1.175494351e-38
#define DBL_MAX 1.7976931348623158e+308
#define DBL_MIN 2.2250738585072014e-308
#define PI 3.1415926535897932384626433832795
#define EPSILON 0.0001f
#define RAY_DEPTH 5

layout(location = 0) out vec4 outColor;

const uint obj_null		= 0x00000000u;
const uint obj_sphere	= 0x00000001u;
const uint obj_plane	= 0x00000002u;
const uint obj_cone		= 0x00000003u;
const uint obj_cylinder	= 0x00000004u;

const uint light_ambient		= 0x00000005u;
const uint light_point			= 0x00000006u;
const uint light_directional	= 0x00000007u;

struct							s_camera
{
	vec4						position;
	vec4						forward;
	vec4						up;
	vec4						right;
	vec4						background_color;
	float						d;
	float						vh;
	float						vw;
	float						fill_to_aligment[1];
};

struct							s_texture
{
	uint						offset_in_buffer;
	uint						width;
	uint						height;
	int							index;
};

struct							s_light_info
{
	vec4						color;
	float						intensity;
};

struct							s_input
{
	vec3						position;
	vec3						direction;
	vec3						f_ver;
	vec3						basis[3];
	vec4						color;
	s_texture					texture;
	vec2						f_tiling;
	vec2						f_offset;
	uint						type;
	float						l_intensity;
	float 						f_radius;
	float						f_height;
	float						f_metalness;
	float						f_transparency;
	float						f_reflection;
	float						f_refraction;
};

struct							s_intersection_info
{
	s_input						object;
	vec3						ray_dir;
	float						d;
	vec3						hitpoint;
};

struct							s_node
{
	s_intersection_info			int_info;
	float						refr;
	float						fraq;
	int							depth;
};

int			tree_length = int(pow(2, RAY_DEPTH + 1)) - 1;
s_node		rt_node_buffer[int(pow(2, RAY_DEPTH + 1)) - 1];

layout(std430, binding = 0) readonly buffer Figures
{
	s_camera	camera;
	float		win_width;
	float		win_height;
	uint		n_fig;
	uint		n_lig;
	s_texture	ui_texture;
	s_input		sbo_input[];
};

layout(std430, binding = 1) readonly buffer Textures
{
	uint		textures[];
};

vec3	canvas_to_viewport(int i, int j)
{
	return normalize(camera.forward.xyz + camera.up.xyz * (i * camera.vh / win_height)
						+ cross(camera.up.xyz, camera.forward.xyz) * (j * camera.vw / win_width));
}

/*
	MATH
*/
vec2	quadratic_equation_solver(float a, float b, float c)
{
	float discriminant = b * b - 4 * a * c;
	float tmp = 1.0 / (2.0 * a);

	if (discriminant < 0.0)
		return vec2(FLT_MAX);
	discriminant = sqrt(discriminant);
	return vec2((-b - discriminant) * tmp, (-b + discriminant) * tmp);
}

vec4	get_color_from_uint(uint col)
{
	return vec4(float(col & uint(0x000000ff)) / 256, float(col >> 8 & uint(0x000000ff)) / 256, float(col >> 16 & 0x000000ff) / 256, 1);
}

vec4	permute(vec4 x) { return mod(((x * 34.0) + 1.0) * x, 289.0); }
vec2	fade(vec2 t) { return t * t * t * (t * (t * 6.0 - 15.0) + 10.0); }

float	perlin_noise(vec2 P)
{
	vec4 Pi = floor(P.xyxy) + vec4(0.0, 0.0, 1.0, 1.0);
	vec4 Pf = fract(P.xyxy) - vec4(0.0, 0.0, 1.0, 1.0);
	Pi = mod(Pi, 289.0);
	vec4 ix = Pi.xzxz;
	vec4 iy = Pi.yyww;
	vec4 fx = Pf.xzxz;
	vec4 fy = Pf.yyww;
	vec4 i = permute(permute(ix) + iy);
	vec4 gx = 2.0 * fract(i * 0.0243902439) - 1.0;
	vec4 gy = abs(gx) - 0.5;
	vec4 tx = floor(gx + 0.5);
	gx = gx - tx;
	vec2 g00 = vec2(gx.x, gy.x);
	vec2 g10 = vec2(gx.y, gy.y);
	vec2 g01 = vec2(gx.z, gy.z);
	vec2 g11 = vec2(gx.w, gy.w);
	vec4 norm = 1.79284291400159 - 0.85373472095314 * vec4(dot(g00, g00), dot(g01, g01), dot(g10, g10), dot(g11, g11));
	g00 *= norm.x;
	g01 *= norm.y;
	g10 *= norm.z;
	g11 *= norm.w;
	float n00 = dot(g00, vec2(fx.x, fy.x));
	float n10 = dot(g10, vec2(fx.y, fy.y));
	float n01 = dot(g01, vec2(fx.z, fy.z));
	float n11 = dot(g11, vec2(fx.w, fy.w));
	vec2 fade_xy = fade(Pf.xy);
	vec2 n_x = mix(vec2(n00, n01), vec2(n10, n11), fade_xy.x);
	float n_xy = mix(n_x.x, n_x.y, fade_xy.y);
	return 2.3 * n_xy;
}

/*
	INTERCECTION FUNCTIONS
*/

vec2	intersect_ray_sphere(vec3 ray_start, vec3 ray_dir, s_input sphere)
{
	vec3	oc;
	vec2	res;

	oc = ray_start - sphere.position;
	res = quadratic_equation_solver(dot(ray_dir, ray_dir), dot(oc, ray_dir) * 2, dot(oc, oc) - sphere.f_radius * sphere.f_radius);
	if (res.x < EPSILON)
		res.x = FLT_MAX;
	if (res.y < EPSILON)
		res.y = FLT_MAX;
	return (res);
}

vec2	intersect_ray_plane(vec3 ray_start, vec3 ray_dir, s_input plane)
{
	float		tmp;

	tmp = dot(plane.direction, ray_dir);
	if (abs(tmp) < EPSILON)
		return (vec2(FLT_MAX, FLT_MAX));
	tmp = -dot(ray_start - plane.position, plane.direction) / tmp;
	if (tmp < EPSILON)
		return (vec2(FLT_MAX, FLT_MAX));
	return (vec2(tmp));
}

vec2	intersect_ray_cone(vec3 ray_start, vec3 ray_dir, s_input cone)
{
	vec3	ov;
	float	cos2;
	float	ovcd;
	float	dscd;
	vec2	res;

	cos2 = cone.f_height / sqrt(cone.f_height * cone.f_height + cone.f_radius * cone.f_radius);
	cos2 = cos2 * cos2;
	ov = cone.f_ver - ray_start;
	ovcd = dot(ov, cone.direction);
	dscd = dot(ray_dir, cone.direction);
	res = quadratic_equation_solver(cos2 * dot(ray_dir, ray_dir) - dscd * dscd, 2 * (ovcd * dscd - cos2 * dot(ray_dir, ov)), dot(ov, ov) * cos2 - ovcd * ovcd);
	//	Top part clipping
	if ((dot(ray_start, cone.direction) + res.x * dscd - dot(cone.f_ver, cone.direction)) > 0)
		res.x = FLT_MAX;
	if ((dot(ray_start, cone.direction) + res.y * dscd - dot(cone.f_ver, cone.direction)) > 0)
		res.y = FLT_MAX;
	//	Bottom part clipping
	float cone_side_len = sqrt(cone.f_height * cone.f_height + cone.f_radius * cone.f_radius);
	if (length(ray_start + ray_dir * res.x - cone.f_ver) > cone_side_len)
		res.x = FLT_MAX;
	if (length(ray_start + ray_dir * res.y - cone.f_ver) > cone_side_len)
		res.y = FLT_MAX;
	//	Bottom plane intersection check
	float a = dot(ray_dir, -cone.direction);
	if (abs(a) < EPSILON)
		return (res);
	float b = -dot(ray_start - cone.position, -cone.direction) / a;
	if (b < EPSILON || length(ray_start + b * ray_dir - cone.position) > cone.f_radius)
		return (res);
	if (res.x == FLT_MAX)
		res.x = b;
	if (res.y == FLT_MAX)
		res.y = b;
	return (res);
}

vec2	intersect_ray_cylinder(vec3 ray_start, vec3 ray_dir, s_input cyl)
{
	vec3	oc;
	vec2	res;

	oc = ray_start - cyl.position;
	vec3 cr_rd_v = cross(ray_dir.xyz, cyl.direction.xyz);
	vec3 cr_oc_v = cross(oc.xyz, cyl.direction.xyz);
	res = quadratic_equation_solver(dot(cr_rd_v, cr_rd_v), 2 * dot(cr_rd_v, cr_oc_v), dot(cr_oc_v, cr_oc_v) - cyl.f_radius * cyl.f_radius);
	return (res);
}

s_intersection_info	closest_intersection(vec3 ray_start, vec3 ray_dir)
{
	s_intersection_info	int_info;
	int					i;
	vec2				t;
	
	int_info.d = FLT_MAX;
	int_info.object.type = obj_null;
	i = 0;
	while (i < n_fig)
	{			
		if (sbo_input[i].type == obj_sphere)
			t = intersect_ray_sphere(ray_start, ray_dir, sbo_input[i]);
		else if (sbo_input[i].type == obj_plane)
			t = intersect_ray_plane(ray_start, ray_dir, sbo_input[i]);
		else if (sbo_input[i].type == obj_cylinder)
			t = intersect_ray_cylinder(ray_start, ray_dir, sbo_input[i]);
		else if (sbo_input[i].type == obj_cone)
			t = intersect_ray_cone(ray_start, ray_dir, sbo_input[i]);
		if (t.x > EPSILON && t.x < int_info.d)
		{
			int_info.d = t.x;
			int_info.object = sbo_input[i];
		}
		if (t.y > EPSILON && t.y < int_info.d)
		{
			int_info.d = t.y;
			int_info.object = sbo_input[i];
		}
		i++;
	}
	int_info.ray_dir = ray_dir;
	int_info.hitpoint = ray_start + ray_dir * int_info.d;
	return (int_info);
}

/*
	CALCULATING UV
*/

vec2	get_sphere_uv(s_input sphere, vec3 hitpoint)
{
	vec3 basis0;
	vec3 basis1;
	vec3 basis2;

	basis0 = vec3(1, 0, 0);
	basis1 = vec3(0, 1, 0);
	basis2 = vec3(0, 0, -1);

	vec3				vect;

	vect = normalize(hitpoint - sphere.position).xyz;
	vect = vec3(dot(basis0, vect), dot(basis1, vect), dot(basis2, vect));
	return vec2(0.5 + atan(vect.z, vect.x) / PI, 0.5 - asin(vect.y) / PI);
}

vec2	get_plane_uv(s_input plane, vec3 hitpoint)
{
	vec3 basis0;
	vec3 basis1;
	vec2	res;

	basis0 = normalize(vec3(plane.direction.y, -plane.direction.x, 0));
	basis1 = normalize(cross(plane.direction.xyz, basis0));

	res.x = modf(0.5 + dot(basis0, hitpoint.xyz) / 2, res.x);
	res.y = modf(0.5 + dot(basis1, hitpoint.xyz) / 2, res.y);
	if (res.x < 0)
		res.x += 1;
	if (res.y < 0)
		res.y += 1;
	return res;
}

vec2	get_cone_uv(s_input cone, vec3 hitpoint)
{
	vec3				vect;
	vec3				a;
	vec2				res;
	vec3 basis0;
	vec3 basis1;
	vec3 basis2;
	
	basis0 = normalize(vec3(cone.direction.y, -cone.direction.x, 0));
	basis1 = cross(cone.direction.xyz, basis0);
	basis2 = cross(basis0, basis1);

	vect = hitpoint.xyz - (cone.position.xyz + cone.direction.xyz * cone.f_height);
	a.y = length(vect) * length(vect) / (dot(cone.direction.xyz, vect) * 2);
	a.x = -dot(vect, basis0);
	a.z = dot(vect, basis1);
	res.x = 0.5 + atan(a.z, a.x) / PI;
	res.y = modf(0.5 + a.y * 1 / 2, res.y);
	if (res.y < 0)
		res.y += 1;
	return res;
}

vec2	get_cylinder_uv(s_input cylinder, vec3 hitpoint)
{
	vec3				vect;
	vec3				a;
	vec2				res;
	vec3 basis0;
	vec3 basis1;
	vec3 basis2;
	
	if (cylinder.direction.x != 0.0f || cylinder.direction.y != 0.0f)
		basis0 = normalize(vec3(cylinder.direction.y, -cylinder.direction.x, 0));
	else
		basis0 = vec3(0.0f, 1.0f, 0.0f);
	basis1 = cross(basis0, cylinder.direction.xyz);
	basis2 = vec3(0.0, 0.0, 1.0);

	vect = hitpoint.xyz - cylinder.position.xyz;
	a.y = dot(cylinder.direction.xyz, vect);
	a.x = -dot(vect, basis0);
	a.z = dot(vect, basis1) + 0;
	res.x = 0.5 + atan(a.z, a.x) / PI;
	res.y = modf(0.5 + a.y * 1 / 2, res.y);
	if (res.y < 0)
		res.y += 1;
	return res;
}

vec2	get_uv(s_input object, vec3 hitpoint)
{
	if (object.type == obj_sphere)
		return get_sphere_uv(object, hitpoint);
	if (object.type == obj_plane)
		return get_plane_uv(object, hitpoint);
	if (object.type == obj_cylinder)
		return get_cylinder_uv(object, hitpoint);
	if (object.type == obj_cone)
		return get_cone_uv(object, hitpoint);
}

/*
	GET OBJECT COLOR
*/

vec4	get_color(s_input obj, vec2 uv)
{
	if (obj.texture.index >= 0)
	{
		uint col = textures[obj.texture.offset_in_buffer + (int(uv.y * obj.texture.height) * obj.texture.width) + (int(uv.x * obj.texture.width))];
		if (obj.f_transparency == 0)
		{
			obj.f_transparency = 1.0 - float(col >> 24 & uint(0x000000ff)) / 256;
			if (obj.f_transparency >= 1.0)
				return (vec4(1.0));
		}
		return get_color_from_uint(col);
	}
	else if (obj.texture.index == -1)
	{
		int x = int(floor((uv.x + obj.f_offset.x) * 2 * obj.f_tiling.x)) % 2;
		int y = int(floor((uv.y + obj.f_offset.y) * 2 * obj.f_tiling.y)) % 2;
		if (x == y)
			return vec4(1);
		else
			return obj.color;
	}
	else if (obj.texture.index == -2)
	{
		return obj.color * (1 - perlin_noise(vec2(uv.x * obj.f_tiling.x, uv.y * obj.f_tiling.y)));
	}
	else if (obj.texture.index == -3)
	{
		float len = length((uv - vec2(0.5f)) * obj.f_tiling * 2 * PI * 10);
		return (obj.color * (sin(len) * 0.5f + 0.5f));
	}
	else
		return obj.color;
}

/*
	GET OBJECT NORMAL
*/

vec3	get_normal(s_input obj, vec3 point)
{
	vec3	norm;
	if (obj.type == obj_sphere)
	{
		norm = point - obj.position.xyz;
		norm = norm * (1.0 / length(norm));	
	}
	else if (obj.type == obj_plane)
	{
		norm = obj.direction.xyz;
	}
	else if (obj.type == obj_cylinder)
	{
		vec3 tmp = obj.position.xyz - point;
		norm = (obj.direction.xyz * dot(tmp, obj.direction.xyz) - tmp) / length(obj.direction.xyz);
	}
	else if (obj.type == obj_cone)
	{
		if (dot(-obj.direction.xyz, obj.position.xyz - point) < EPSILON)
			norm = -obj.direction.xyz;
		else
		{
			vec3	pc = point - obj.position.xyz;
			vec3	pv = point - obj.f_ver.xyz;
			float	cos = obj.f_height / sqrt(obj.f_height * obj.f_height + obj.f_radius * obj.f_radius);
			norm = vec3(obj.position.xyz + obj.direction.xyz * (obj.f_height - length(pv) / cos));
			norm = point - norm;
		}
		norm = norm / length(norm);
	}
	return (norm);
}

/*
	Compute lightning
*/

s_light_info	light_strength_and_color(vec3 ray_start, vec3 ray_dir, float light_strength, uint l_type)
{
	int					i;
	vec2				t;
	s_light_info		res;
	
	res.intensity = light_strength;
	res.color = vec4(1.0, 1.0, 1.0, 1.0);
	i = 0;
	while (i < n_fig)
	{
		if (sbo_input[i].type == obj_sphere)
			t = intersect_ray_sphere(ray_start, ray_dir, sbo_input[i]);
		else if (sbo_input[i].type == obj_plane)
			t = intersect_ray_plane(ray_start, ray_dir, sbo_input[i]);
		else if (sbo_input[i].type == obj_cylinder)
			t = intersect_ray_cylinder(ray_start, ray_dir, sbo_input[i]);
		else if (sbo_input[i].type == obj_cone)
			t = intersect_ray_cone(ray_start, ray_dir, sbo_input[i]);
		if (t.x == FLT_MAX && t.y == FLT_MAX || t.x <= EPSILON && t.y <= EPSILON || l_type == light_point && t.x >= 1.0 && t.y >= 1.0)
		{
			i++;
			continue;
		}

		vec3 p1 = t.x == FLT_MAX || t.x <= EPSILON ? ray_start : ray_start + ray_dir * t.x;
		vec3 p2 = t.y == FLT_MAX || t.y <= EPSILON ? ray_start : ray_start + ray_dir * t.y;
		float d = distance(p1, p2);
		if (d > 1.1)
		{
			if (sbo_input[i].f_transparency == 0.0f)
			{
				res.intensity = 0.0f;
				res.color = vec4(1, 1, 1, 1);
				return res;
			}
			else
			{
				res.intensity *= sbo_input[i].f_transparency;
			}
		}
		else if (sbo_input[i].f_transparency == 0.0)
			res.intensity *= ((1.1 - d) / 1.1);
		else
			res.intensity *= ((1.1 - d) / 1.1 + sbo_input[i].f_transparency);
		if (sbo_input[i].f_transparency != 0)
		{
			vec2 uv = get_uv(sbo_input[i], ray_start + ray_dir * t.x);
			res.color = mix(res.color, get_color(sbo_input[i], uv), sbo_input[i].f_transparency);
		}
		i++;
	}
	return (res);
}

s_light_info	compute_lighting(vec3 hitpoint, vec3 normal, int metalness, vec3 ray_dir)
{
	s_light_info		res;
	uint				i;
	vec3				dir_to_light;
	float				n_scal_l;
	float				shadow_t;
	s_intersection_info	int_info;

	res.intensity = 0.0;
	res.color = vec4(1.0, 1.0, 1.0, 1.0);
	i = n_fig;
	while (i < n_fig + n_lig)
	{
		if (sbo_input[i].type < 5)
		{
			i++;
			continue;
		}
		if (sbo_input[i].type == light_ambient)
			res.intensity += sbo_input[i].l_intensity;
		else 
		{
			if (sbo_input[i].type == light_point)
				dir_to_light = sbo_input[i].position - hitpoint;
			else
				dir_to_light = -sbo_input[i].direction;
			
			//Проверка тени
			s_light_info l_info = light_strength_and_color(hitpoint, dir_to_light, sbo_input[i].l_intensity, sbo_input[i].type);
			if (l_info.intensity < EPSILON)
			{
				i++;
				continue;
			}
			res.color = mix(res.color, l_info.color, 0.5);
			
			//Диффузность
			n_scal_l = dot(normal, dir_to_light);
			if (n_scal_l > 0)
				res.intensity += l_info.intensity * n_scal_l / (length(normal) * length(dir_to_light));

			//Блик
			if (metalness > 0)
			{
				vec3 r_v = normal * n_scal_l * 2 - dir_to_light;
				float rv_scal_v = dot(r_v, -ray_dir);
				if (rv_scal_v > 0)
					res.intensity += l_info.intensity * pow(rv_scal_v / (length(r_v) * length(-ray_dir)), metalness);
			}
		}
		i++;
	}
	if (res.intensity >= 1.0)
		res.intensity = 1.0;
	return (res);
}

vec3 reflect_ray(vec3 vector, vec3 n)
{
    return vector - 2 * dot(vector, n) * n;
}

vec3 refract_ray(vec3 I, vec3 N, float etai, float etat) 
{
    float cosi = clamp(dot(I, N), -1.0, 1.0);
	vec3 n = N;
    if (cosi < 0)
		cosi = -cosi;
	else
	{
		float tmp = etai;
		etai = etat;
		etat = tmp;
		n = -N;
	}
    float eta = etai / etat;
    float k = 1 - eta * eta * (1 - cosi * cosi);
    return k < 0 ? reflect_ray(I, dot(I, N) > 0.0f ? -N : N) : normalize(eta * I + (eta * cosi - sqrt(k)) * n);
}

vec4	trace_ray(vec3 ray_start, vec3 ray_dir)
{
	int					i;
	int					j;
	vec3				norm;
	vec4				final_color;
	vec4				local_color;
	s_intersection_info	int_info;
	float				frac;

	final_color = vec4(0.0);
	frac = 1.0;
	
	/*
		Find closest intersection & save it to node
	*/
	int_info = closest_intersection(ray_start, ray_dir);
	if (int_info.object.type == obj_null)
		return camera.background_color;
	rt_node_buffer[0].depth = 0;
	rt_node_buffer[0].int_info = int_info;
	rt_node_buffer[0].fraq = 1.0;

	/*
		Calculate first color
	*/
	vec2 uv = get_uv(int_info.object, int_info.hitpoint);
	vec4 col = get_color(int_info.object, uv);
	norm = get_normal(int_info.object, int_info.hitpoint);
	if (dot(ray_dir, norm) > 0)
		norm = -norm;
	s_light_info l_info = compute_lighting(int_info.hitpoint, norm, int(int_info.object.f_metalness), ray_dir);
	final_color = col * (1 - int_info.object.f_transparency) * (1 - int_info.object.f_reflection) * l_info.color * l_info.intensity;

	/*
		Calculate start refraction
	*/
	if (int_info.object.f_transparency == 0 || dot(ray_dir, get_normal(int_info.object, int_info.hitpoint)) < 0)
		rt_node_buffer[0].refr = 1.0;
	else
		rt_node_buffer[0].refr = int_info.object.f_refraction;
	
	i = 0;
	j = 0;
	int q = 1;
	int noe = 1;
	while (i < RAY_DEPTH)
	{
		for (; j < q; j++)
		{
			if (rt_node_buffer[j].depth != i || rt_node_buffer[j].int_info.object.type == obj_null)
				continue;
			norm = get_normal(rt_node_buffer[j].int_info.object, rt_node_buffer[j].int_info.hitpoint);
			if (dot(ray_dir, norm) > 0)
				norm = -norm;
			ray_start = rt_node_buffer[j].int_info.hitpoint;
			float cur_fraq = rt_node_buffer[j].fraq * (1 - rt_node_buffer[j].int_info.object.f_transparency)
												* rt_node_buffer[j].int_info.object.f_reflection;
			int index = int(pow(2, i + 1)) - 1 + j * 2;
			if (rt_node_buffer[j].int_info.object.f_reflection != 0 && cur_fraq > 0.05f)
			{
				ray_dir = reflect_ray(rt_node_buffer[j].int_info.ray_dir, norm);
				int_info = closest_intersection(ray_start, ray_dir);

				vec4 col;
				if (int_info.object.type == obj_null)
				{
					rt_node_buffer[index].depth = -1;
					final_color += camera.background_color * cur_fraq;
				}
				else
				{
					rt_node_buffer[index].depth = i + 1;
					rt_node_buffer[index].int_info = int_info;
					rt_node_buffer[index].fraq = cur_fraq;
					rt_node_buffer[index].refr = rt_node_buffer[j].refr;
					vec2 uv = get_uv(int_info.object, int_info.hitpoint);
					col = get_color(int_info.object, uv);
					s_light_info l_info = compute_lighting(int_info.hitpoint, norm, int(int_info.object.f_metalness), ray_dir);
					final_color += col * cur_fraq * l_info.color * l_info.intensity;
				}
			}
			cur_fraq = rt_node_buffer[j].fraq * rt_node_buffer[j].int_info.object.f_transparency;
			if (rt_node_buffer[j].int_info.object.f_transparency != 0 && cur_fraq > 0.05f)
			{
				ray_dir = refract_ray(rt_node_buffer[j].int_info.ray_dir, norm, rt_node_buffer[j].refr, rt_node_buffer[j].int_info.object.f_refraction);
				int_info = closest_intersection(ray_start, ray_dir);
				if (int_info.object.type == obj_null)
				{
					rt_node_buffer[index + 1].depth = -1;
					final_color += camera.background_color * cur_fraq;
				}
				else
				{
					rt_node_buffer[index + 1].depth = i + 1;
					rt_node_buffer[index + 1].int_info = int_info;
					rt_node_buffer[index + 1].fraq = cur_fraq;
					if (dot(ray_dir, get_normal(int_info.object, int_info.hitpoint)) < 0)
						rt_node_buffer[index + 1].refr = 1.0;
					else
						rt_node_buffer[index + 1].refr = int_info.object.f_refraction;
					vec4 col;
					vec2 uv = get_uv(int_info.object, int_info.hitpoint);
					col = get_color(int_info.object, uv);
					s_light_info l_info = compute_lighting(int_info.hitpoint, norm, int(int_info.object.f_metalness), ray_dir);
					final_color += col * cur_fraq * l_info.color * l_info.intensity;
				}
			}
		}
		i++;
		noe *= 2;
		q += noe;
	}
	return (final_color);
}

vec3	rotate_x(vec3 t, float angle)
{
	float		prev_y;
	float		prev_z;

	prev_y = t.y;
	prev_z = t.z;
	t.y = (prev_y * cos(angle) - prev_z * sin(angle));
	t.z = (prev_y * sin(angle) + prev_z * cos(angle));
	return (t);
}

vec3	rotate_y(vec3 t, float angle)
{
	float		prev_x;
	float		prev_z;

	prev_x = t.x;
	prev_z = t.z;
	t.x = (prev_x * cos(angle) + prev_z * sin(angle));
	t.z = (prev_z * cos(angle) - prev_x * sin(angle));
	return (t);
}

vec3	rotate_z(vec3 t, float angle)
{
	float		prev_x;
	float		prev_y;

	prev_x = t.x;
	prev_y = t.y;
	t.x = (prev_x * cos(angle) - prev_y * sin(angle));
	t.y = (prev_x * sin(angle) + prev_y * cos(angle));
	return (t);
}

void main()
{
	vec3 d;
	if (gl_FragCoord.y < ui_texture.height && gl_FragCoord.x < ui_texture.width)
	{
		uint col = textures[int(gl_FragCoord.y) * ui_texture.width + int(gl_FragCoord.x)];
		if (((col >> 24) & 0x000000ff) == 255)
		{
			outColor = get_color_from_uint(col);
			return;
		}
		else if (((col >> 24) & 0x000000ff) > 0)
		{
			d = canvas_to_viewport(int(win_height/2 - gl_FragCoord.y), int(gl_FragCoord.x - win_width/2));
			vec4 color = trace_ray(camera.position.xyz, d);
			outColor = mix(get_color_from_uint(col), trace_ray(camera.position.xyz, d), 1.0 - (col >> 24) / 255.0);
			return;
		}
	}
	for (int i = 0; i < tree_length; i++)
	{
		rt_node_buffer[i].depth = -1;
	}
	d = canvas_to_viewport(int(win_height/2 - gl_FragCoord.y), int(gl_FragCoord.x - win_width/2));
	outColor = trace_ray(camera.position.xyz, d);
}
