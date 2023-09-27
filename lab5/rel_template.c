#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REL_SIZE 100
#define MAX_RANGE 100

typedef struct {
	int first;
	int second;
} pair;

// Add pair to existing relation if not already there
int add_relation (pair*, int, pair);
int is_connected(pair*, int);
int get_domain(pair*, int, int*);

// Case 1:

// The relation R is reflexive if xRx for every x in X
int is_reflexive(pair* tab, int n) {
	for(int i = 0; i < n; i++) {
		if (tab[i].first == tab[i].second) return 1;
	}
	return 0;
}

// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
int is_irreflexive(pair* tab, int n) {
	for(int i = 0; i < n; i++) {
		if (tab[i].first == tab[i].second) return 0;
	}
	return 1;
}

// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(pair* tab, int n) {
	int flag = 0;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if (tab[i].first == tab[j].second && tab[i].second == tab[j].first) flag = 1;

			if (!flag) return 0;

			flag = 0;
		}
	}
	return 1;
}

// A binary relation R over a set X is antisymmetric if:
// for all x,y in X if xRy and yRx then x=y
int is_antisymmetric(pair* tab, int n) {
	int flag = 0;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if (tab[i].first == tab[j].second && tab[i].second == tab[j].first) flag = 1;

			if(flag && tab[i].first != tab[i].second) return 0;

			flag = 0;
		}
	}
	return 1;
}

// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
// from wiki
// A relation is asymmetric if and only if it is both antisymmetric and irreflexive.
int is_asymmetric(pair* tab, int n) {
	if(is_antisymmetric(tab, n) && is_irreflexive(tab, n)) return 1;
	else return 0;
}

// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
int is_transitive(pair* tab, int n){
	int flag;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {

			if(tab[i].second == tab[j].first) {
				flag = 0;
				for(int k = 0; k < n; k++) {
					if(tab[k].first == tab[i].first && tab[k].second == tab[j].first) flag = 1;
				}
				if(!flag) return 0;
			}

		}
	}
	return 1;
}

// Case 2:

// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
int is_partial_order(pair* tab, int n) {
	if(is_reflexive(tab, n) && is_transitive(tab,n) && is_antisymmetric(tab,n)) return 1;
	else return 0;
}

// A total order relation is a partial order relation that is connected
int is_total_order(pair* tab, int n) {
	if(is_partial_order(tab,n) && is_connected(tab, n)) return 1;
	else return 0;
}

// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
int is_connected(pair* tab, int n) {
	int domain[MAX_REL_SIZE];
	int n_domain = get_domain(tab, n, domain);

	int flag = 0;
	for(int i = 0; i < n_domain; i++) {
		for(int j = 0; j < n_domain; j++) {
			for(int k = 0; k < n; k++) {
				if((domain[i] == tab[k].first && domain[j] == tab[k].second) || (domain[i] == tab[k].second && domain[j] == tab[k].first)) flag = 1;
			}
			if (!flag) return 0;
			flag = 0;
		}
	}
	return 1;
}

int find_max_elements(pair* tab, int n, int* max) {
	int domain[MAX_REL_SIZE];
	int n_domain = get_domain(tab, n, domain);
	
	int flag = 1;
	int cnt = 0;

	for(int i = 0; i < n_domain; i++) {
		for(int j = 0; j < n; j++) {
			if (domain[i] == tab[j].first && tab[j].first != tab[j].second) flag = 0;
		}
		if(flag) {
			max[cnt] = domain[i];
			cnt++;
		}
		flag = 1;
	}
	return cnt;
}
int find_min_elements(pair* tab, int n, int* min) {
	int domain[MAX_REL_SIZE];
	int n_domain = get_domain(tab, n, domain);
	
	int flag = 1;
	int cnt = 0;

	for(int i = 0; i < n_domain; i++) {
		for(int j = 0; j < n; j++) {
			if (domain[i] == tab[j].second && tab[j].first != tab[j].second) flag = 0;
		}
		if(flag) {
			min[cnt] = domain[i];
			cnt++;
		}
		flag = 1;
	}
	return cnt;
}

int get_domain(pair* tab, int n, int* domain) {
	int bool[MAX_REL_SIZE]={0};
	int cnt = 0; 	
	for(int i = 0; i < n; i++) {
		if(!bool[tab[i].first]) {
			bool[tab[i].first] = 1;
			domain[cnt]=tab[i].first;
			cnt++;
		}
		if(!bool[tab[i].second]) {
			bool[tab[i].second] = 1;
			domain[cnt]=tab[i].second;
			cnt++;
		}
	}

	//sorting domain
	int change = 0;
	for(int i = 0; i < cnt-1; i++) {
		for(int j = 1; j < cnt - i; j++) {
			if(domain[j-1] > domain[j]) {
				int temp = domain[j-1];
				domain[j-1] = domain[j];
				domain[j] = temp;
				change = 1;
			}
		}
		if(!change) break;
		change = 0;
	}

	return cnt;
}

// Case 3:

int composition(pair* tab1, int n1, pair* tab2, int n2, pair* comp_relation) {
	int nCompostions = 0;
	int cnt = 0;
	for(int i = 0; i < n1; i++) {
		for(int j = 0; j < n2; j++) {
			if(tab1[i].second == tab2[j].first) {
				pair new_pair;
				new_pair.first = tab1[i].first;
				new_pair.second = tab2[j].second;
				cnt=add_relation(comp_relation, cnt, new_pair);
				nCompostions++;
			}
		}
	}
	return cnt;
}

// Comparator for pair
/* int cmp_pair (const void *a, const void *b) { */
/* } */

/* int insert_int (int *tab, int n, int new_element) { */
/* } */

// Add pair to existing relation if not already there
int add_relation (pair *tab, int n, pair new_pair) {
	for (int i = 0; i < n; i++) {
		if (tab[i].first == new_pair.first && tab[i].second == new_pair.second) return n;
	}
	tab[n++] = new_pair;
	return n;
}

// Read number of pairs, n, and then n pairs of ints
int read_relation(pair *relation) {
	int n;
	scanf("%d\n", &n);
	
	pair new_pair;
	for(int i = 0; i < n; i++) {
		scanf("%d %d", &new_pair.first, &new_pair.second);
		add_relation(relation, i, new_pair);
	}
	return n;
}

void print_int_array(int *array, int n) {
	printf("%d\n", n);
	for(int i = 0; i < n; printf("%d ", array[i]), i++);
	printf("\n");
}

int main(void) {
	int to_do;
	pair relation[MAX_REL_SIZE];
	pair relation_2[MAX_REL_SIZE];
	pair comp_relation[MAX_REL_SIZE];
	int domain[MAX_REL_SIZE];
	int max_elements[MAX_REL_SIZE];
	int min_elements[MAX_REL_SIZE];

	scanf("%d",&to_do);
	int size = read_relation(relation);
	int ordered, size_2, n_domain;

	switch (to_do) {
		case 1:
			printf("%d ", is_reflexive(relation, size));
			printf("%d ", is_irreflexive(relation, size));
			printf("%d ", is_symmetric(relation, size));
			printf("%d ", is_antisymmetric(relation, size));
			printf("%d ", is_asymmetric(relation, size));
			printf("%d\n", is_transitive(relation, size));
			break;
		case 2:
			ordered = is_partial_order(relation, size);
			n_domain = get_domain(relation, size, domain);
			printf("%d %d\n", ordered, is_total_order(relation, size));
			print_int_array(domain, n_domain);
			if (!ordered) break;
			int no_max_elements = find_max_elements(relation, size, max_elements);
			int no_min_elements = find_min_elements(relation, size, min_elements);
			print_int_array(max_elements, no_max_elements);
			print_int_array(min_elements, no_min_elements);
			break;
		case 3:
			size_2 = read_relation(relation_2);
			printf("%d\n", composition(relation, size, relation_2, size_2, comp_relation));
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

