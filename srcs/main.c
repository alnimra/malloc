#include "malloc.h"
#include <stdio.h>

void print_mlist_elem(t_mlist *elem)
{
	printf("elem_addr: %p | ptr_start: %p | length %d | status %d | page_start "
		   "%p | next %p\n",
		   elem, elem->ptr_start, elem->length, elem->status, elem->page_start,
		   elem->next);
}
void print_mlist(t_mlist *list_head)
{
	t_mlist *iter;
	iter = list_head;
	while (iter)
	{
		print_mlist_elem(iter);
		iter = iter->next;
	}
}
void print_hippocampus()
{

	printf("-------- PRINTING HIPPOCAMPUS --------\n");
	printf("Tiny:\n");
	print_mlist(true_hippocampus->tiny_head);
	printf("Small:\n");
	print_mlist(true_hippocampus->small_head);
	printf("Large:\n");
	print_mlist(true_hippocampus->large_head);
}

int calc_size_as_multiple_of_page_size(int size, int page_size)
{
	if (size % page_size == 0)
		return size;
	return ((size / page_size) + 1) * page_size;
}
void create_true_hippocampus()
{
	int page_size;
	int hippocampus_size;

	ft_putstr("HERE\n");
	page_size = getpagesize();
	printf("Page Size: %d | ", page_size);
	hippocampus_size =
		calc_size_as_multiple_of_page_size(sizeof(t_hippocampus), page_size);
	true_hippocampus =
		(t_hippocampus *)mmap(0, hippocampus_size, PROT_READ | PROT_WRITE,
							  MAP_ANON | MAP_PRIVATE, -1, 0);
	true_hippocampus->page_size = page_size;
	// REMOVE
	ft_putendl("Created true hippocampus");
}

int find_mem_size(int size)
{
	if (size <= TINY)
		return TINY;
	else if (size <= SMALL)
		return SMALL;
	return LARGE;
}

void set_new_size_for_cache_allocations(int *size)
{
	if (*size <= SMALL)
		*size *= 100;
}

void add_to_end_of_mlist(t_mlist **last, void *ptr_start, int length,
						 int status)
{
	t_mlist *ptr_to_insert_mlist_at;

	ptr_to_insert_mlist_at = ptr_start + length;
	ptr_to_insert_mlist_at->ptr_start = ptr_start;
	ptr_to_insert_mlist_at->length = length;
	ptr_to_insert_mlist_at->status = status;
	ptr_to_insert_mlist_at->next = NULL;
	if (!*last)
		*last = ptr_to_insert_mlist_at;
	else
	{
		(*last)->next = ptr_to_insert_mlist_at;
		*last = ptr_to_insert_mlist_at;
	}
}

void *allocate_inefficient(int mem_size, int size)
{
	printf("Allocated inefficiently\n");
	void *   allocated_ptr;
	t_mlist *temp_last;
	int		 size_of_mmap_alloc;
	void *   ptr_start_of_cache_left;
	int		 length_of_cache_left;

	set_new_size_for_cache_allocations(&size);
	size_of_mmap_alloc = calc_size_as_multiple_of_page_size(
		size + (2 * sizeof(t_mlist)) + TINY + sizeof(t_mlist),
		true_hippocampus->page_size);
	allocated_ptr = mmap(0, size_of_mmap_alloc, PROT_READ | PROT_WRITE,
						 MAP_ANON | MAP_PRIVATE, -1, 0);
	ptr_start_of_cache_left = allocated_ptr + size + sizeof(t_mlist);
	length_of_cache_left = size_of_mmap_alloc - (size + (2 * sizeof(t_mlist)));
	if (mem_size == TINY)
	{
		add_to_end_of_mlist(&(true_hippocampus->tiny_last), allocated_ptr, size,
							STATUS_INUSE);
		temp_last = true_hippocampus->tiny_last;
		temp_last->page_start = temp_last;
		add_to_end_of_mlist(&(true_hippocampus->tiny_last),
							ptr_start_of_cache_left, length_of_cache_left,
							STATUS_FREE);
		true_hippocampus->tiny_last->page_start = temp_last;
	}
	else if (mem_size == SMALL)
	{
		add_to_end_of_mlist(&(true_hippocampus->small_last), allocated_ptr,
							size, STATUS_INUSE);
		temp_last = true_hippocampus->small_last;
		temp_last->page_start = temp_last;
		add_to_end_of_mlist(&(true_hippocampus->small_last),
							ptr_start_of_cache_left, length_of_cache_left,
							STATUS_FREE);
		true_hippocampus->small_last->page_start = temp_last;
	}
	else
	{
		add_to_end_of_mlist(&(true_hippocampus->large_last), allocated_ptr,
							size, STATUS_INUSE);
		temp_last = true_hippocampus->large_last;
		temp_last->page_start = temp_last;
		add_to_end_of_mlist(&(true_hippocampus->large_last),
							ptr_start_of_cache_left, length_of_cache_left,
							STATUS_FREE);
		true_hippocampus->large_last->page_start = temp_last;
	}
	return allocated_ptr;
}

void add_after_mlist_elem(t_mlist **elem_to_add_after, void *ptr_start,
						  int length, int status)
{
	t_mlist *ptr_to_insert_mlist_at;

	ptr_to_insert_mlist_at = ptr_start + length;
	ptr_to_insert_mlist_at->ptr_start = ptr_start;
	ptr_to_insert_mlist_at->length = length;
	ptr_to_insert_mlist_at->status = status;
	ptr_to_insert_mlist_at->next = (*elem_to_add_after)->next;
	(*elem_to_add_after)->next = ptr_to_insert_mlist_at;
}

void *find_cached_space(t_mlist *list_head, int size)
{
	t_mlist *iter;

	iter = list_head;
	while (iter)
	{
		if (iter->length >= size && iter->status == STATUS_FREE)
			return iter;
		iter = iter->next;
	}
	return NULL;
}
void replace_last_elem_if_found_elem_is_last_elem(int	  mem_size,
												  t_mlist *found_elem,
												  t_mlist *replace_elem)
{
	if (mem_size == TINY)
	{
		if (found_elem == true_hippocampus->tiny_last)
			true_hippocampus->tiny_last = replace_elem;
	}
	else if (mem_size == SMALL)
	{
		if (found_elem == true_hippocampus->small_last)
			true_hippocampus->small_last = replace_elem;
	}
	else
	{
		if (found_elem == true_hippocampus->large_last)
			true_hippocampus->large_last = replace_elem;
	}
}
void *get_and_manage_cached_space(int size, int mem_size,
								  t_mlist **found_elem_for_cache)
{
	int store_found_elem_for_cache_org_size;

	(*found_elem_for_cache)->status = STATUS_INUSE;
	if ((*found_elem_for_cache)->length <
		(int)(size + mem_size + sizeof(t_mlist)))
		return (*found_elem_for_cache)->ptr_start;
	store_found_elem_for_cache_org_size = (*found_elem_for_cache)->length;
	(*found_elem_for_cache)->length = size;
	add_after_mlist_elem(
		found_elem_for_cache, (*found_elem_for_cache)->ptr_start + size,
		store_found_elem_for_cache_org_size - size - sizeof(t_mlist),
		STATUS_FREE);
	replace_last_elem_if_found_elem_is_last_elem(
		mem_size, *found_elem_for_cache, (*found_elem_for_cache)->next);
	if ((*found_elem_for_cache)->page_start == NULL)
		(*found_elem_for_cache)->next->page_start = *found_elem_for_cache;
	else
		(*found_elem_for_cache)->next->page_start =
			(*found_elem_for_cache)->page_start;
	return (*found_elem_for_cache)->ptr_start;
}

void *allocate_efficient(int mem_size, int size)
{
	printf("Trying to allocating efficiently\n");
	t_mlist *found_elem_for_cache;
	if (mem_size == TINY)
	{
		if (!(found_elem_for_cache =
				  find_cached_space(true_hippocampus->tiny_head, size)))
			return NULL;
	}
	else if (mem_size == SMALL)
	{
		if (!(found_elem_for_cache =
				  find_cached_space(true_hippocampus->small_head, size)))
			return NULL;
	}
	else
	{
		if (!(found_elem_for_cache =
				  find_cached_space(true_hippocampus->large_head, size)))
			return NULL;
	}
	return get_and_manage_cached_space(size, mem_size, &found_elem_for_cache);
}

void allocate_space_if_needed(void **ret, int mem_size, int size)
{
	if (mem_size == TINY)
	{
		if (!true_hippocampus->tiny_head)
		{
			*ret = allocate_inefficient(mem_size, size);
			true_hippocampus->tiny_head =
				true_hippocampus->tiny_last->page_start;
			return;
		}
		if (!(*ret = allocate_efficient(mem_size, size)))
			*ret = allocate_inefficient(mem_size, size);
	}
	else if (mem_size == SMALL)
	{
		if (!true_hippocampus->small_head)
		{
			*ret = allocate_inefficient(mem_size, size);
			true_hippocampus->small_head =
				true_hippocampus->small_last->page_start;
			return;
		}
	}
	else if (mem_size == LARGE)
	{
		if (!true_hippocampus->large_head)
		{
			*ret = allocate_inefficient(mem_size, size);
			true_hippocampus->large_head =
				true_hippocampus->large_last->page_start;
			return;
		}
	}
}
void *malloc(size_t size)
{
	printf("MALLOCING!\n");
	int   mem_size;
	void *ret;
	if (!size)
		return NULL;
	mem_size = find_mem_size(size);
	if (!true_hippocampus)
		create_true_hippocampus();
	allocate_space_if_needed(&ret, mem_size, size);
	return ret;
}

t_mlist *find_mem_to_be_freed(void *ptr, t_mlist **page_start_elem,
							  t_mlist **head_type_for_search)
{
	t_mlist *iter;
	t_mlist *prev;

	iter = true_hippocampus->tiny_head;
	*head_type_for_search = iter;
	(*page_start_elem) = iter;
	while (iter)
	{
		if (iter->page_start != (*page_start_elem)->page_start)
			(*page_start_elem) = prev;
		if (iter->ptr_start == ptr)
			return iter;
		prev = iter;
		iter = iter->next;
	}
	iter = true_hippocampus->small_head;
	*head_type_for_search = iter;
	(*page_start_elem) = iter;
	while (iter)
	{
		if (iter->page_start != (*page_start_elem)->page_start)
			(*page_start_elem) = prev;
		if (iter->ptr_start == ptr)
			return iter;
		prev = iter;
		iter = iter->next;
	}
	iter = true_hippocampus->large_head;
	*head_type_for_search = iter;
	(*page_start_elem) = iter;
	while (iter)
	{
		if (iter->page_start != (*page_start_elem)->page_start)
			(*page_start_elem) = prev;
		if (iter->ptr_start == ptr)
			return iter;
		prev = iter;
		iter = iter->next;
	}
	return NULL;
}

void if_unmap_possible_then_do(t_mlist *found_ptr,
							   t_mlist *head_type_for_search,
							   t_mlist *page_start_elem_prev)
{
	t_mlist *iter;
	int		 size;

	size = 0;
	iter = found_ptr->page_start;
	while (iter && iter->page_start == found_ptr->page_start)
	{
		if (iter->status == STATUS_INUSE)
			return;
		size += iter->length;
		iter = iter->next;
	}
	if (page_start_elem_prev != head_type_for_search)
		page_start_elem_prev->next = iter;
	else
	{
		if(head_type_for_search == true_hippocampus->tiny_head)
			true_hippocampus->tiny_head = iter;
		if(head_type_for_search == true_hippocampus->small_head)
			true_hippocampus->small_head = iter;
		if(head_type_for_search == true_hippocampus->large_head)
			true_hippocampus->large_head = iter;
	}
	printf("Head Type for search: %p | Size of UNMAP: %d\n", head_type_for_search, size);
	printf("MEMUNMAPING");
	munmap(found_ptr->page_start->ptr_start, size);
}
void free(void *ptr)
{
	t_mlist *found_ptr;
	t_mlist *page_start_elem_for_munmap_search;
	t_mlist *head_type_for_search;
	printf("FREEING -> %p\n", ptr);
	found_ptr = find_mem_to_be_freed(ptr, &page_start_elem_for_munmap_search,
									 &head_type_for_search);
	found_ptr->status = STATUS_FREE;
	if_unmap_possible_then_do(found_ptr, head_type_for_search,
							  page_start_elem_for_munmap_search);
}
int main(void)
{
	void *hello = malloc(18);
	printf("Size of t_mlist: %d\n", (int)sizeof(t_mlist));
	printf("Size of t_hippocampus: %d\n", (int)sizeof(t_hippocampus));
	print_hippocampus();
	int i = -1;
		free(hello);
	while (++i < 2)
	{
		hello = malloc(16);
		print_hippocampus();
		print_hippocampus();
	}
		free(hello);
		print_hippocampus();
	// printf("%c", hello);
}
