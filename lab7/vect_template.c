#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STR_LEN 64

typedef struct Vector {
	void *data;
	size_t element_size;
	size_t size;
	size_t capacity;
} Vector;

typedef struct Person {
	int age;
	char first_name[MAX_STR_LEN];
	char last_name[MAX_STR_LEN];
} Person;

typedef int(*cmp_ptr)(const void*, const void*);
typedef int(*predicate_ptr)(void*);
typedef void(*read_ptr)(void*);
typedef void(*print_ptr)(const void*);

// Allocate vector to initial capacity (block_size elements),
// Set element_size, size (to 0), capacity
void init_vector(Vector *vector, size_t block_size, size_t element_size) {
	vector->capacity = block_size;
	vector->element_size = element_size;
	vector->size = 0;
	vector->data = malloc(block_size * element_size);
}

// If new_capacity is greater than the current capacity,
// new storage is allocated, otherwise the function does nothing.
void reserve(Vector *vector, size_t new_capacity) {
	if (vector->capacity < new_capacity) {
		vector->capacity = new_capacity;
		void *newData = malloc(new_capacity * vector->element_size);
		memcpy(newData, vector->data, vector->size * vector->element_size);
		free(vector->data);
		vector->data = newData;
	}
}

// Resizes the vector to contain new_size elements.
// If the current size is greater than new_size, the container is
// reduced to its first new_size elements.

// If the current size is less than new_size,
// additional zero-initialized elements are appended
void resize(Vector *vector, size_t new_size) {
	if(vector->size > new_size) vector->size = new_size;
	else if(vector->size < new_size) {
		reserve(vector, new_size);
		size_t additional_el = new_size-vector->size; //dodac additional bytes jak nie zadziala
		memset((char *)vector->data+(vector->size*vector->element_size), 0, additional_el);
		vector->size = new_size;
	}
}

// Add element to the end of the vector
void push_back(Vector *vector, void *value) {
	if(vector->capacity == vector->size) {
		reserve(vector, vector->capacity * 2);
	}
	char *dest = (char *)vector->data + (vector->size*vector->element_size);
	/* memset((void *) dest, *(int *)value,1); //zmienic na memcpy jak nie zadziala */
	memcpy((void *) dest, value, vector->element_size);
	vector->size++;
}

// Remove all elements from the vector
void clear(Vector *vector) {
	vector->size=0;
}

// Insert new element at index (0 <= index <= size) position
void insert(Vector *vector, size_t index, void *value) {
	if (index < 0 || index > vector->size) return;
	if (index == vector->size-1) {
		push_back(vector, value);
		return;
	}
	if(vector->size == vector->capacity) reserve(vector, vector->capacity*2);
	memmove((char *)vector->data + (index+1)*vector->element_size, (char *)vector->data + index * vector->element_size, (vector->size - index)*vector->element_size);
	/* memmove((char *)vector->data + (index+1), (char *)vector->data + index, vector->size - index); //albo gora albo dol zadziala */
	memcpy((char *)vector->data + index*vector->element_size, value, vector->element_size);
	/* memset((char *) vector->data+index*vector->element_size, *(int *)value,2); //znow, albo gora albo dol */
	vector->size++;
}

// Erase element at position index
void erase(Vector *vector, size_t index) {
	if(index < 0 || index > vector->size) return;
	if(index == vector->size-1) {vector->size--; return;}
	memmove((char *)vector->data + ((index)*vector->element_size), (char *)vector->data + (index+1)*vector->element_size, (vector->size - index)*vector->element_size);
	vector->size--;
}

// Erase all elements that compare equal to value from the container
void erase_value(Vector *vector, void *value, cmp_ptr cmp) {
	for(int i = 0; i < vector->size; i++){
		char *indexAt = (char *) vector->data + i*vector->element_size;
		if(cmp(value, indexAt) == 0){
			erase(vector, i);
			i--;
		}
	}
}

// Erase all elements that satisfy the predicate from the vector
void erase_if(Vector *vector, int (*predicate)(void *)) {
	for(int i = 0; i < vector->size; i++) {
		char *indexAt = (char *) vector->data + i*vector->element_size;
		if(predicate(indexAt)) {
			erase(vector, i);
			i--;
		}
	}
}

// Request the removal of unused capacity
void shrink_to_fit(Vector *vector) {
	if(vector->size == vector->capacity) return;
	vector->capacity = vector->size;
	char *newData = malloc(vector->size * vector->element_size);
	memcpy(newData, vector->data, vector->size*vector->element_size);
	free(vector->data);
	vector->data=newData;
}

// integer comparator
int int_cmp(const void *v1, const void *v2) {
	if(*(int *)v1 > *(int *)v2) return 1;
	else if(*(int *)v1 < *(int *)v2) return -1;
	return 0;
}

// char comparator
int char_cmp(const void *v1, const void *v2) {
	if(*(char *) v1 > *(char *)v2) return 1;
	else if(*(char *)v1 < *(char *)v2) return -1;
	return 0;
}

// Person comparator:
// Sort according to age (decreasing)
// When ages equal compare first name and then last name
int person_cmp(const void *p1, const void *p2) {
	Person *pr1 = (Person *) p1;
	Person *pr2 = (Person *) p2;

	if(pr1->age > pr2->age) return -1;
	if(pr1->age < pr2->age) return 1;

	int i = strcmp(pr1->first_name, pr2->first_name);
	if(!i) i = strcmp(pr1->last_name, pr2->last_name);

	return i;
}

// predicate: check if number is even
int is_even(void *value) {
	return *(int *)value%2==0 ? 1 : 0;
}

// predicate: check if char is a vowel
int is_vowel(void *value) {
	char tab[12] = {'a', 'e', 'i', 'o', 'u', 'y', 'A', 'E', 'I', 'O', 'U', 'Y'};
	for(int i = 0; i < sizeof(tab); i++) {
		if(*(char *)value == tab[i]) return 1;
	}
	return 0;
}

// predicate: check if person is older than 25
int is_older_than_25(void *person) {
	Person *p = (Person *)person;
	if(p->age > 25) return 1;
	return 0;
}

// print integer value
void print_int(const void *v) {
	printf("%d ",*(int *)v);
}

// print char value
void print_char(const void *v) {
	printf("%c ", *(char *)v);
}

// print structure Person
void print_person(const void *v) {
	Person *p = (Person *) v;
	printf("%d %s %s\n", p->age, p->first_name, p->last_name);
}

// print capacity of the vector and its elements
void print_vector(Vector *vector, print_ptr print) {
	printf("%ld\n", vector->capacity);
	for(int i = 0; i < vector->size; i++){
		char *value = (char *)vector->data+vector->element_size*i;
		print(value);
	}
	printf("\n");
}

// read int value
void read_int(void* value) {
	scanf("%d", (int *)value);
}

// read char value
void read_char(void* value) {
	char c[2];
	scanf("%s", c);
	*(char *) value = c[0];
}

// read struct Person
void read_person(void* value) {
	Person *person = (Person *) value;
	scanf("%d %s %s", &person->age, person->first_name, person->last_name);
}

void vector_test(Vector *vector, size_t block_size, size_t elem_size, int n, read_ptr read,
		 cmp_ptr cmp, predicate_ptr predicate, print_ptr print) {
	init_vector(vector, block_size, elem_size);
	void *v = malloc(vector->element_size);
	size_t index, size;
	for (int i = 0; i < n; ++i) {
		char op;
		scanf(" %c", &op);
		switch (op) {
			case 'p': // push_back
				read(v);
				push_back(vector, v);
				break;
			case 'i': // insert
				scanf("%zu", &index);
				read(v);
				insert(vector, index, v);
				break;
			case 'e': // erase
				scanf("%zu", &index);
				erase(vector, index);
				break;
			case 'v': // erase
				read(v);
				erase_value(vector, v, cmp);
				break;
			case 'd': // erase (predicate)
				erase_if(vector, predicate);
				break;
			case 'r': // resize
				scanf("%zu", &size);
				resize(vector, size);
				break;
			case 'c': // clear
				clear(vector);
				break;
			case 'f': // shrink
				shrink_to_fit(vector);
				break;
			case 's': // sort
				qsort(vector->data, vector->size,
				      vector->element_size, cmp);
				break;
			default:
				printf("No such operation: %c\n", op);
				break;
		}
	}
	print_vector(vector, print);
	free(vector->data);
	free(v);
}

int main(void) {
	int to_do, n;
	Vector vector_int, vector_char, vector_person;

	scanf("%d%d", &to_do, &n);

	switch (to_do) {
		case 1:
			vector_test(&vector_int, 4, sizeof(int), n, read_int, int_cmp,
				is_even, print_int);
			break;
		case 2:
			vector_test(&vector_char, 2, sizeof(char), n, read_char, char_cmp,
				is_vowel, print_char);
			break;
		case 3:
			vector_test(&vector_person, 2, sizeof(Person), n, read_person,
				person_cmp, is_older_than_25, print_person);
			break;
		default:
			printf("Nothing to do for %d\n", to_do);
			break;
	}

	return 0;
}

