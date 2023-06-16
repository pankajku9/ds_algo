
/*https://cp-algorithms.com/data_structures/disjoint_set_union.html#union-by-size-rank*/ 

#include <stdlib.h>
#include <assert.h>

//typedef  unsigned idx_type_t;

#define SWAP(x, y) do { \
typeof(x) _x = x;       \
typeof(y) _y = y;       \
x = _y;                 \
y = _x;                 \
} while(0)

static int set_find(unsigned *parent, size_t n, unsigned x)
{
    if (parent[x] != x)
        parent[x] = set_find(parent, n, parent[x]);
    return parent[x];
}

static int set_union(unsigned *parent, unsigned *rank, size_t n, unsigned x, unsigned y)
{
    unsigned a = set_find(parent, n, x);
    unsigned b = set_find(parent, n, y);

    if (a == b)
        return -1;
    /* if a is smaller tree, swap to make it larger*/
    if (rank[a] < rank[b])
        SWAP(a, b);
    /* Make smaller tree(b), child of larger tree (a) */
    parent[b] = a;
    /* if same depth, increment rank of parent node */
    if (rank[a] == rank[b])
        rank[a] += 1; 

    return 0;
}

typedef struct disjoint_set_s {
    unsigned *parent;
    unsigned *rank; /* depth of tree */
    size_t n;
} disjoint_set_t;

disjoint_set_t* disjoint_set_make(int n)
{
    disjoint_set_t *tmp = malloc(sizeof(disjoint_set_t));
    tmp->parent = malloc(sizeof(unsigned) * n);
    tmp->rank = calloc(n, sizeof(unsigned));
    for (int i = 0; i < n; i++)
        tmp->parent[i] = i;
    tmp->n = n;
    return tmp;
}

void free_set(disjoint_set_t** ds_ref)
{   
    disjoint_set_t* ds = *ds_ref;
    free(ds->parent);
    free(ds->rank);
    free(ds);
    *ds_ref = NULL;
}

int disjoint_set_union(disjoint_set_t *ds, unsigned x, unsigned y)
{
    return set_union(ds->parent, ds->rank, ds->n, x, y);
}

unsigned disjoint_set_find(disjoint_set_t *ds, unsigned x)
{
    return set_find(ds->parent, ds->n, x);
}

int main()
{
    disjoint_set_t *ds = disjoint_set_make(4);
    assert(disjoint_set_union(ds, 1, 3) == 0);
    assert(disjoint_set_union(ds, 0, 1) == 0);
    assert(disjoint_set_union(ds, 0, 2) == 0);
    assert(disjoint_set_union(ds, 2, 1) == -1);
}