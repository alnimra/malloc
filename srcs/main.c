#include "malloc.h"
#include <stdio.h>

void print_mlist_elem(t_mlist *elem)
{
	printf("ptr_start: %p | length %d | status %d | page_start %p | next %p\n",
		elem->ptr_start, elem->length, elem->status, elem->page_start,
		elem->next);
}
void print_mlist(t_mlist *list_head)
{
	t_mlist *iter;
	iter = list_head;
	while(iter)
	{
		print_mlist_elem(iter);
		iter = iter->next;
	}
}
void print_hippocampus()
{
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
	return ((size / page_size) + 1) *
		page_size;
}
void create_true_hippocampus()
{
	int page_size;
	int hippocampus_size;

	ft_putstr("HERE\n");
	page_size = getpagesize();
	hippocampus_size = calc_size_as_multiple_of_page_size(sizeof(t_hippocampus), page_size);
	true_hippocampus = (t_hippocampus *)mmap(
		0, hippocampus_size,
		PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	true_hippocampus->page_size = page_size;
	// REMOVE
	ft_putendl("Created true hippocampus");
}

int find_mem_size(int size)
{
	if (size <= TINY)
		return 0;
	else if (size <= SMALL)
		return 1;
	return 2;
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
	void *   allocated_ptr;
	t_mlist *temp_last;
	int		 size_of_mmap_alloc;

	set_new_size_for_cache_allocations(&size);
	size_of_mmap_alloc = calc_size_as_multiple_of_page_size(
		size + (2 * sizeof(t_mlist)) + TINY + sizeof(t_mlist), true_hippocampus->page_size);
	allocated_ptr = mmap(0, size_of_mmap_alloc, PROT_READ | PROT_WRITE,
						 MAP_ANON | MAP_PRIVATE, -1, 0);
	if (mem_size == 0)
	{
		add_to_end_of_mlist(&(true_hippocampus->tiny_last), allocated_ptr, size,
							STATUS_INUSE);
		temp_last = true_hippocampus->tiny_last;
		add_to_end_of_mlist(&(true_hippocampus->tiny_last),
							allocated_ptr + size + sizeof(t_mlist),
							size_of_mmap_alloc - (size + (2 * sizeof(t_mlist))),
							STATUS_FREE);
		true_hippocampus->tiny_last->page_start = temp_last;
	}
	else if (mem_size == 1)
	{
		add_to_end_of_mlist(&(true_hippocampus->small_last), allocated_ptr,
							size, STATUS_INUSE);
		temp_last = true_hippocampus->small_last;
		add_to_end_of_mlist(&(true_hippocampus->small_last),
							allocated_ptr + size + sizeof(t_mlist),
							size_of_mmap_alloc - (size + (2 * sizeof(t_mlist))),
							STATUS_FREE);
		true_hippocampus->small_last->page_start = temp_last;
	}
	else
	{
		add_to_end_of_mlist(&(true_hippocampus->large_last), allocated_ptr,
							size, STATUS_INUSE);
		temp_last = true_hippocampus->large_last;
		add_to_end_of_mlist(&(true_hippocampus->large_last),
							allocated_ptr + size + sizeof(t_mlist),
							size_of_mmap_alloc - (size + (2 * sizeof(t_mlist))),
							STATUS_FREE);
		true_hippocampus->large_last->page_start = temp_last;
	}
	return allocated_ptr;
}

// int search_for_free
void allocate_space_if_needed(void **ret, int mem_size, int size)
{
	if (mem_size == 0)
	{
		if (!true_hippocampus->tiny_head)
		{
			*ret = allocate_inefficient(mem_size, size);
			true_hippocampus->tiny_head =
				true_hippocampus->tiny_last->page_start;
		}
	}
	else if (mem_size == 1)
	{
		if (!true_hippocampus->small_head)
		{
			*ret = allocate_inefficient(mem_size, size);
			true_hippocampus->small_head =
				true_hippocampus->small_last->page_start;
		}
	}
	else if (mem_size == 2)
	{
		if (!true_hippocampus->large_head)
		{
			*ret = allocate_inefficient(mem_size, size);
			true_hippocampus->large_head =
				true_hippocampus->large_last->page_start;
		}
	}
}
void *malloc(size_t size)
{
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

int main()
{
	char hello = (char)malloc(50);
	printf("%c", hello);
	print_hippocampus();
}
