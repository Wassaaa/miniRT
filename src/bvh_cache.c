#include <miniRT.h>

t_bvh_cache	*bvh_cache_init(void)
{
	t_bvh_cache	*cache;
	int			i;

	rtx()->bvh_node_id = 0;
	rtx()->cache_hits = 0;
	cache = ft_calloc(1, sizeof(t_bvh_cache));
	if (!cache)
		return (NULL);
	i = 0;
	while (i < CACHE_SIZE)
	{
		cache->entries[i].node_id = -1;
		cache->entries[i].hit = 0;
		i++;
	}
	cache->current_index = 0;
	return (cache);
}

void	bvh_cache_free(t_bvh_cache *cache)
{
	if (cache)
		free(cache);
}

bool	bvh_cache_check(t_bvh_cache *cache, int node_id)
{
	int	i;

	i = 0;
	while (i < CACHE_SIZE)
	{
		if (cache->entries[i].node_id == node_id)
			return (cache->entries[i].hit);
		i++;
	}
	return (false);
}

void bvh_cache_update(t_bvh_cache *cache, int node_id, bool hit)
{
	cache->entries[cache->current_index].node_id = node_id;
	cache->entries[cache->current_index].hit = hit;
	cache->current_index = (cache->current_index + 1) % CACHE_SIZE;
}
