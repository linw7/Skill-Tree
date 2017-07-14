#ifndef RBTREE_H
#define RBTREE_H

typedef struct rb_tree *rb_tree;

/* Creates an empty Red-Black tree. */
rb_tree RBcreate();
/* Frees an entire tree. */
void RBfree(rb_tree tree);
/* Cleans up. Call this when you won't be using any more Red-Black trees. */
void RBcleanup();

/* Inserts an element with specified key into tree. */
int RBinsert(rb_tree tree, int key);

/* Deletes an element with a particular key. */
int RBdelete(rb_tree tree, int key);

/* Writes a tree to stdout in preorder format.
 * Outputs everything on the same line. */
void RBwrite(rb_tree tree);
/* Reads a tree in preorder format from file.
 * Warning: does NOT check to see if the resulting tree violates Red-Black
 * properties, and BOLDLY ASSUMES that the input file is well-formatted. Will
 * return once it sees something it doesn't understand. */
rb_tree RBread(char *fname);

/* Draws an SVG picture of the tree in the specified file. */
void RBdraw(rb_tree tree, char *fname);

#endif /* RBTREE_H */
