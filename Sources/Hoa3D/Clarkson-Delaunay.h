/* Clarkson-Delaunay.h */
/*
 * Ken Clarkson wrote this.  Copyright (c) 1995 by AT&T..
 * Permission to use, copy, modify, and distribute this software for any
 * purpose without fee is hereby granted, provided that this entire notice
 * is included in all copies of any software which is or includes a copy
 * or modification of this software and in all copies of the supporting
 * documentation for such software.
 */


typedef double Coord;
typedef Coord* point;

#define max_blocks 10000
#define       Nobj 10000

#define MAXDIM 4
#define BLOCKSIZE 100000
#define MAXBLOCKS 1000

#define VA(x) ((x)->vecs+rdim)
#define VB(x) ((x)->vecs)

typedef point site;

typedef struct basis_s {
   struct basis_s *next; /* free list */
   int ref_count;   /* storage management */
   int lscale;    /* the log base 2 of total scaling of vector */
   Coord sqa, sqb; /* sums of squared norms of a part and b part */
   Coord vecs[1]; /* the actual vectors, extended by malloc'ing bigger */
} basis_s;

//STORAGE_GLOBALS(basis_s)
  extern size_t basis_s_size;
  extern basis_s *basis_s_list;
  extern basis_s *new_block_basis_s(int);
  extern void flush_basis_s_blocks(void);
  void free_basis_s_storage(void);


typedef struct neighbor {
   site vert; /* vertex of simplex */
   struct simplex *simp; /* neighbor sharing all vertices but vert */
   basis_s *basis; /* derived vectors */
} neighbor;


typedef struct simplex {
   struct simplex *next;   /* free list */
   long visit;      /* number of last site visiting this simplex */
   short mark;
   basis_s* normal;   /* normal vector pointing inward */
   neighbor peak;      /* if null, remaining vertices give facet */
   neighbor neigh[1];   /* neighbors of simplex */
} simplex;
// STORAGE_GLOBALS(simplex)
  extern size_t simplex_size;
  extern simplex *simplex_list;
  extern simplex *new_block_simplex(int);
  extern void flush_simplex_blocks(void);
  void free_simplex_storage(void);


typedef struct fg_node fg;
typedef struct tree_node Tree;
struct tree_node {
    Tree *left, *right;
    site key;
    int size;   /* maintained to be the number of nodes rooted here */
    fg *fgs;
    Tree *next; /* freelist */
};
// STORAGE_GLOBALS(Tree)
  extern size_t Tree_size;
  extern Tree *Tree_list;
  extern Tree *new_block_Tree(int);
  extern void flush_Tree_blocks(void);
  void free_Tree_storage(void);



typedef struct fg_node {
   Tree *facets;
   double dist, vol;   /* of Voronoi face dual to this */
   fg *next;        /* freelist */
   short mark;
   int ref_count;
} fg_node;
// STORAGE_GLOBALS(fg)
  extern size_t fg_size;
  extern fg *fg_list;
  extern fg *new_block_fg(int);
  extern void flush_fg_blocks(void);
  void free_fg_storage(void);



typedef simplex * visit_func(simplex *, void *);
typedef int test_func(simplex *, int, void *);

static int sees(site, simplex *);
static void buildhull(simplex *);
static simplex *facets_print(simplex *s, void *p);
static simplex *visit_triang_gen(simplex *s, visit_func *visit, test_func *test);



