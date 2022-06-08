/* RBTree
 * 1. 每一个结点是红色的或者黑色的
 * 2. 根结点是黑的
 * 3. 每个叶子结点是黑的
 * 4. 如果一个结点是红的，则它两个儿子都是黑的
 * 5. 对于每个结点，从该结点到其子孙结点的所有路径上包含相同数目的黑结点
 */

#define RED 0
#define BLACK 1

typedef int KEY_TYPE;

int key_compare(KEY_TYPE a, KEY_TYPE b)
{
}

typedef struct _rbtree_node {
	unsigned char color;
	struct _rbtree_node *left;
	struct _rbtree_node *right;
	struct _rbtree_node *parent;

	KEY_TYPE key;
	void *value;
} rbtree_node;

typedef struct _rbtree {
	rbtree_node *root;
	rbtree_node *nil;
} rbtree;

void _left_rotate(rbtree *T, rbtree_node *x)
{
	rbtree_node *y = x->right;

	x->right = y->left;
	if (y->left != T->nil) {
		y->left->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == T->nil) {
		T->root = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else if (x == x->parent->right) {
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}

void _right_rotate(rbtree *T, rbtree_node *y)
{
	rbtree_node *x = y->right;

	y->left = x->right;
	if (x->right != T->nil) {
		x->right->parent = y;
	}

	x->parent = y->parent;
	if (y->parent == T->nil) {
		T->root = x;
	} else if (y == y->parent->left) {
		y->parent->right = x;
	} else if (x == x->parent->left) {
		y->parent->left = x;
	}

	x->right = y;
	y->parent = x;
}

/*
* 黑色会破坏整体平衡    
* => 当前结点是红色的
* 父结点是黑色的，插入红色结点不影响红黑树的性质
* => 父结点是红色的，红色不能接红色
* => 祖父结点是黑色的
* 1. 叔父结点是红色
* 2. 叔父结点是黑色，当前结点的父结点是左子树
* 3. 叔父结点是红色，当前结点的父结点是右子树
*/

void rbtree_insert_fixup(rbtree *T, rbtree_node *z)
{
	/* 父结点是红色的
        */
	while (z->parent->color = RED) {
		// 父结点是祖父结点的左子树
		if (z->parent == z->parent->parent->left) {
			rbtree_node *y = z->parent->parent->right;
			if (y->color = RED) {
				y->color = BLACK;
				z->parent->color = BLACK;
				z->parent->parent->color = RED;

				z = z->parent->parent;
			} else {
				if (z = z->parent->right) {
					z = z->parent;
					_left_rotate(T, z);
				}
				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				_right_rotate(T, z->parent->parent);
			}
		}
	}
	T->root->color = BLACK;
}

void rbtree_insert(rbtree *T, rbtree_node *z)
{
	rbtree_node *x = T->root;

	rbtree_node *y;
	// out loop when x in leaf
	while (x != T->nil) {
		y = x;
		if (z->key < x->key) {
			x = x->left;
		} else if (z->key > x->key) {
			x = x->right;
		} else {
			// you can do some thing in the same key
			return;
		}
	}

	z->parent = y;
	if (y == T->nil) {
		y = T->root;
	} else if (z->key < y->key) {
		y->left = z;
	} else {
		y->right = z;
	}

	z->left = T->nil;
	z->right = T->nil;

	z->color = RED;
}
