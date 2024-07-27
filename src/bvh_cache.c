#include <miniRT.h>

void	cache_init(t_cache *cache)
{
	int	i;

	i = 0;
	while (i < CACHE_SIZE)
	{
		cache->entries->hit = false;
		cache->entries->node_id = -1;
		i++;
	}
}

static inline bool	cache_chk_upd(t_cache *cache, int node_id, bool hit)
{
	int				index;
	t_cache_entry	*entry;
	bool			cached_hit;
	
	index = node_id & (CACHE_SIZE - 1);
	entry = &cache->entries[index];
	if (entry->node_id == node_id)
	{
		cached_hit = entry->hit;
		entry->hit |= hit;
		return (cached_hit);
	}
	entry->node_id = node_id;
	entry->hit = hit;
	return (false);
}

bool	intersect_bvh(t_bvh *node, t_ray ray, t_intersection *old_t)
{
	bool			cached;
	bool			hit;
	t_intersection	t;

	t = (t_intersection){INFINITY, NULL, false, VV, VV};
	cached = false;
	hit = false;
	if (CACHE_SIZE > 0)
	{
		cached = cache_chk_upd(rtx()->cache, node->id, false);
		if (cached)
		{
			rtx()->cache_hits++;
			if (node->shape)
				hit = update_hit(node, &t, ray);
			else
				hit = next_branches(node, ray, &t);
		}
	}
	if (!cached)
	{
		if (!intersect_aabb(ray, node->box, t.distance))
			return (false);
		if (node->shape)
			hit = update_hit(node, &t, ray);
		else
			hit = next_branches(node, ray, &t);
	}
	if (CACHE_SIZE > 0 && hit && node->shape)
		cache_chk_upd(rtx()->cache, node->id, hit);
	if (hit && t.distance < old_t->distance)
		*old_t = t;
	return (hit);
}
