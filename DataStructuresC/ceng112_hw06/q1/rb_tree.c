#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <limits.h>

#include "student.h"

#define MAX_NAME 256
#define RBT_BLACK 0
#define RBT_RED 1

#define MAX_PATH 200

int i=0;

void print_student_info(int student_index);

struct RBTreeNode {
        int student_idx;

        int color;
        struct RBTreeNode *left;
        struct RBTreeNode *right;
};

struct RBTreeNode *new_node(int student_idx, int color);
void free_tree(struct RBTreeNode *root);

struct RBTreeNode *add_student(struct RBTreeNode *root, int student_idx, int sw);
int search_tree(struct RBTreeNode *root, const char *name);
void print_students(struct RBTreeNode *root);

int is_all_equal(int arr[], int size);
void count_black_nodes(struct RBTreeNode *root, int pathLen, int n_black_nodes[]);
int checkRBTree(struct RBTreeNode *root);

struct RBTreeNode *copy_RBTreeNode(struct RBTreeNode *reciever, struct RBTreeNode *source);
void query_students(struct RBTreeNode *root, int n_students);
int compare(struct RBTreeNode *root, int i);

static struct RBTreeNode z = {
        .student_idx = -1,
        .color = RBT_BLACK,
        .left = &z,
        .right = &z
};

int main(int argc, char **argv)
{
        // Enabling Turkish string comparison: Set LC_COLLATE variable to
        // Turkish locale.  You might also need to enable Turkish support in
        // your OS.  For Ubuntu install the necessary package:
        //   $ sudo apt-get install language-pack-tr
        // and reopen your terminal window.
        setlocale(LC_COLLATE, "tr_TR.UTF-8");

        int n_students = sizeof(ceng112_students) / sizeof(ceng112_students[0]);
        struct RBTreeNode *root = &z;

        for (int i = 0; i < n_students; ++i) {
                root = add_student(root, i, 0);
                root->color = RBT_BLACK;
        }

	printf("Number of black links from the root to every leaf node is ");
	int valid = checkRBTree(root);
	if(valid == -1)
		printf("not the same!\n");
	else
		printf("%d\n", valid);

	query_students(root, n_students);

        char name[MAX_NAME];
        printf("Enter student name: ");
        fgets(name, MAX_NAME, stdin);
        int lname = strlen(name);
        if (name[lname-1] == '\n')
                name[lname-1] = '\0';

        int student_idx = search_tree(root, name);
        if (student_idx >= 0) {
                print_student_info(student_idx);
        } else {
                print_students(root);
                fprintf(stderr, "There is no student named %s\n", name);
        }

        free_tree(root);

        return EXIT_SUCCESS;
}

struct RBTreeNode *new_node(int student_idx, int color)
{
        struct RBTreeNode *n = malloc(sizeof(*n));
        if (n == NULL) {
                fprintf(stderr, "Out of memory!\n");
                exit(EXIT_FAILURE);
        }

        n->student_idx = student_idx;
        n->left = &z;
        n->right = &z;
        n->color = color;

        return n;
}

void free_tree(struct RBTreeNode *root)
{
        if (root == &z)
                return;

        free_tree(root->left);
        free_tree(root->right);
        free(root);
}

struct RBTreeNode *rotate_left(struct RBTreeNode *n)
{
        struct RBTreeNode *x = n->right;
        n->right = x->left;
        x->left = n;
        return x;
}

struct RBTreeNode *rotate_right(struct RBTreeNode *n)
{
        struct RBTreeNode *x = n->left;
        n->left = x->right;
        x->right = n;
        return x;
}

struct RBTreeNode *add_student(struct RBTreeNode *root, int student_idx, int sw)
{
        if (root == &z)
                return new_node(student_idx, RBT_RED);

        if (root->left->color == RBT_RED
            && root->right->color == RBT_RED) {
                root->left->color = RBT_BLACK;
                root->right->color = RBT_BLACK;
                root->color = RBT_RED;
        }

        /* // strcoll is like strcmp but respects language order */
        int cmp_res = strcoll(ceng112_students[student_idx].name, ceng112_students[root->student_idx].name);
        if (cmp_res < 0) {
                root->left = add_student(root->left, student_idx, 0);
                if (root->color == RBT_RED && root->left->color == RBT_RED && sw)
                        root = rotate_right(root);
                if (root->left->color == RBT_RED && root->left->left->color == RBT_RED) {
                        root = rotate_right(root);
                        root->color = RBT_BLACK;
                        root->right->color = RBT_RED;
                }
        } else {
                root->right = add_student(root->right, student_idx, 1);
                if (root->color == RBT_RED && root->right->color == RBT_RED && !sw)
                        root = rotate_left(root);
                if (root->right->color == RBT_RED && root->right->right->color == RBT_RED) {
                        root = rotate_left(root);
                        root->color = RBT_BLACK;
                        root->left->color = RBT_RED;
                }
        }

        return root;
}

int search_tree(struct RBTreeNode *root, const char *name)
{
        if (root == &z)
                return -1;

        // strcoll is like strcmp but respects language order
        int cmp_res = strcoll(name, ceng112_students[root->student_idx].name);
        if (cmp_res == 0)
                return root->student_idx;
        else if (cmp_res < 0)
                return search_tree(root->left, name);
        else
                return search_tree(root->right, name);
}

void print_students(struct RBTreeNode *root)
{
        if (root == &z)
                return;

        if (root->left != &z)
                print_students(root->left);

        print_student_info(root->student_idx);

        if (root->right != &z)
                print_students(root->right);
}

void print_student_info(int student_idx)
{
        printf("id/name: %u / %s\n", ceng112_students[student_idx].id,
               ceng112_students[student_idx].name);
}

void count_black_nodes(struct RBTreeNode *root, int black_nodes, int n_black_nodes[])
{
	if(root != &z && root->color == RBT_BLACK)
		black_nodes++;

	if(root == &z)
		n_black_nodes[i++]=black_nodes;
	else
	{
		count_black_nodes(root->left, black_nodes, n_black_nodes);
		count_black_nodes(root->right, black_nodes, n_black_nodes);
	}
}

int is_all_equal(int arr[], int size)
{
	for(int i=0; i<size-1; i++)
		if(arr[i] != arr[i+1])
			return 0;
	return 1;
}

int checkRBTree(struct RBTreeNode *root)
{
	int n_black_nodes[MAX_PATH];
	for(int j=0; j<MAX_PATH; j++)
		n_black_nodes[j]=0;
	count_black_nodes(root, 0, n_black_nodes);
	int valid;
	if(!is_all_equal(n_black_nodes, i))
		valid = -1;
	else if(n_black_nodes[0] == 1)
		valid = -1;
	else
		valid = n_black_nodes[0]-1; //We should return n_black_nodes-1 because the count_black_nodes function includes the root to the calculation.
	return valid;
}


struct RBTreeNode *copy_RBTreeNode(struct RBTreeNode *reciever, struct RBTreeNode *source)
{
	reciever->student_idx = source->student_idx;
	reciever->color = source->color;
	reciever->left = source->left;
	reciever->right = source->right;
	return reciever;
}

int compare(struct RBTreeNode *root, int j)
{
    int cmp_res = strcoll(ceng112_students[j].name, ceng112_students[root->student_idx].name);
    
    if (cmp_res == 0)
    	return 1;
    else if (cmp_res < 0)
        return 1+compare(root->left, j);
    else
        return 1+compare(root->right, j);
}

void query_students(struct RBTreeNode *root, int n_students)
{
	int max_comparison = -INT_MAX;
	int min_comparison = INT_MAX;
	int comparison;
	int sum=0;

	for(int j=0; j<n_students; j++)
	{
        	comparison = compare(root, j);
		printf("Number of comparison for the query of \"%s\" is %d\n", ceng112_students[j].name, comparison);

		sum+=comparison;
		if(comparison >= max_comparison)
			max_comparison = comparison;
		if(comparison < min_comparison)
			min_comparison = comparison;
	}
	printf("Max comparison: %d\n", max_comparison);
	printf("Min comparison: %d\n", min_comparison);
	printf("The average comparison: %d\n", sum/n_students);
}
