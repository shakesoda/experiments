#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct
{
	void **data;

	size_t size;
	size_t data_size;

	int slots;
	int *slot_list;
} vector_t;

void vector_new(vector_t *o, size_t num, size_t data_size)
{
	o->slots		= num;
	o->size			= num;
	o->data_size	= data_size;
	o->data			= malloc(num*data_size);
	o->slot_list	= malloc(num*sizeof(int));
}

void vector_remove(vector_t *o, int i)
{
	assert(i < (int)o->size && i >= 0);
	o->slots++;
	o->slot_list = realloc(o->slot_list, o->slots*sizeof(int));
	o->slot_list[o->slots] = i;

	o->data[i] = (void*) -1;
}

/* you can call insert without an object to reserve slots */
void vector_insert(vector_t *o, int batch_size, void *obj)
{
	if (o->slots <= 0 || (obj == NULL && batch_size))
	{
		/* someone set a bad batch size if we've exhausted our slots */
		assert(batch_size);

		/* allocate batch_size additional slots so we can avoid this path */
		o->size		+= batch_size - o->slots;
		o->slots	= batch_size;
		o->data		= realloc(o->data, o->size*o->data_size);

		o->slot_list = realloc(o->slot_list, o->slots*sizeof(int));
	}

	if (obj == NULL) return;

	o->data[o->slot_list[o->slots]] = obj;

	o->slots--;
}

void vector_free(vector_t *o)
{
	free(o->data);
	free(o->slot_list);

	memset(o, 0, sizeof(o));
}

void vector_print(vector_t *o)
{
	size_t i = 0;
	for ( ; i < o->size; i++)
	{
		if (o->data[i] == (void*)-1) continue; /* removed index */
		printf("idx: %ld\n", i);
	}
}

int main()
{
	int i = 0;
	int *foo = malloc(32*sizeof(int));
	vector_t list;

	/* reserve 32 slots, int size */
	vector_new(&list, 32, sizeof(int));

	for (i = 0; i < 32; i++)
	{
		foo[i] = i;
		vector_insert(&list, 0, &foo[i]);
	}

	vector_remove(&list, 16);
	/* only insert with a zero-sized batch if there are slots free! */
	vector_insert(&list, 0, &foo[15]);

	vector_print(&list);

	vector_free(&list);

	return 0;
}
