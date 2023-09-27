#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

#define TAB_SIZE  1000
#define BUF_SIZE  1000

int get(int cols, int row, int col, const int *A) {
	return A[cols*row+col];
}

void set(int cols, int row, int col, int *A, int value) {
	int id = row*cols + col;
	A[id] = value;
}

void prod_mat(int rowsA, int colsA, int colsB, int *A, int *B, int *AB) {
	int sum = 0;
	for(int y = 0; y < rowsA; y++){
		for(int x = 0; x < colsB; x++) {
			for(int z = 0; z < colsA; z++) {
				sum+=get(colsA,y,z,A) * get(colsB, z, x, B);
			}
			set(colsB, y, x, AB, sum);
			sum = 0;
		}
	}
}

void read_mat(int rows, int cols, int *t) {
	for (int y = 0; y < rows*cols; y++) {
		scanf("%d", &t[y]);
	}
}

void print_mat(int rows, int cols, int *t) {
	for(int x=0; x < rows*cols; x++) {
		if(x % cols == 0) printf("\n");
		printf("%d ", t[x]);
	}
}

int read_char_lines(char *array[]) {
	int n;
	int i = 0;
	int line = 0;
	char string[BUF_SIZE];

	while((n=getchar()) != EOF) {
		if(n != '\n') {
			string[i]=n;
			i++;
		} 
		if(n == '\n') {
			string[i]='\0';
			char *p1 = malloc(i*sizeof(char));
			array[line] = p1;
			line++;

			for(int j = 0; j <= i; j++) {
				*p1 = string[j];
				string[j]=' ';
				p1++;
			}
			i=0;
		}
	}
	return line;
}

void write_char_line(char *array[], int n) {
	char *p=array[n];
	while(*p != '\0') {
		printf("%c", *p);
		p++;
	}
}

void delete_lines(char *array[]) {
}

int read_int_lines_cont(int *ptr_array[]) {
	char line[BUF_SIZE];
	int *numbers=ptr_array[0];
	int n=0;

	while (fgets(line, sizeof(line), stdin) != NULL && strlen(line) != 1) {
		char *token = strtok(line, " ");
		ptr_array[n]=numbers;
		while(token != NULL) {
			int d = atoi(token);
			*numbers = d;
			numbers++;
			token = strtok(NULL, " ");
		}
		n++;
	}
	ptr_array[n]=numbers;
	return n;
}

void write_int_line_cont(int *ptr_array[], int n) {
	int *line = ptr_array[n];
	int *end = ptr_array[n+1];
	while(line != end){
		printf("%d ", *line);
		line++;
	} printf("\n");
}

typedef struct {
	int *values;
	int len;
	double average;
} line_type;

int read_int_lines(line_type lines_array[]) {
	int i=0, k=0, j=0;
	int c;
	char *out;
	int buf[BUF_SIZE];
	char str[20];

	while((c=getchar()) != EOF){
		if(c != '\n' && c != ' ') {
			str[k] = c;
			k++;
		}
		if(c == ' '){
			buf[i] = strtol(str, &out, 10);
			i++;

			for(int n = 0; n < k;str[n]=' ', n++);
			k = 0;
		}
		if(c == '\n'){
			buf[i] = strtol(str, &out, 10);
			int *p1 = malloc(i * sizeof(int));
			line_type line;
			line.values = p1;
			line.len = i;
			

			for(int n = 0; n < k;str[n] = ' ', n++);

			double sum  = 0;
			for(int l = 0; l <= i; l++){
				*p1=buf[l];
				sum+=buf[l];
				p1++;
			}
			sum/=(i+1);

			line.average = sum;
			k=0;
			i=0;
			lines_array[j]=line;
			j++;
		}
	}
	return j;
}

void write_int_line(line_type lines_array[], int n) {
	int *p1 = lines_array[n].values;
	int len = lines_array[n].len;
	int i = 0;

	while(i<=len){
		printf("%d ", *p1);
		p1++;
		i++;
	}
	printf("\n%.2f", lines_array[n].average);
}

void delete_int_lines(line_type array[], int line_count) {
}

int cmp (const void *a, const void *b) {
	line_type a1 = *(line_type*)a;
	line_type b1 = *(line_type*)b;

	if(a1.average > b1.average) return 1;
	if(b1.average > a1.average) return -1;
	return 0;
}

void sort_by_average(line_type lines_array[], int line_count) {
	qsort(lines_array, line_count, sizeof(line_type), cmp);
}

typedef struct {
	int r, c, v;
} triplet;

int read_sparse(triplet *triplet_array, int n_triplets) {
    int c;
    int i = 0, k = 0,j=0;
    char *out;
    int buf[BUF_SIZE];
    char str[20];
    int first=0;
    while ((c = getchar()) != EOF) {
        if(first==1) {
            if (c != '\n' && c != ' ') {
                str[k] = c;
                k += 1;
            }
            if (c == ' ') {
                buf[i] = strtol(str, &out, 10);
                i += 1;
                for (int n = 0; n < k; n++) {
                    str[n] = ' ';
                }
                k = 0;
            }
            if (c == '\n') {
                buf[i] = strtol(str, &out, 10);
                triplet trio;
                for (int n = 0; n < k; n++) {
                    str[n] = ' ';
                }
                trio.r = buf[0];
                trio.c = buf[1];
                trio.v = buf[2];
                triplet_array[j] = trio;
                k = 0;
                i = 0;
                j += 1;
                if(j>=n_triplets){
                    break;
                }
            }
        }
        if (c == '\n') {
            first = 1;
        }
    }

    return j;
}

int cmp_triplets(const void *t1, const void *t2) {
	triplet* trio1 = (triplet *)t1;
	triplet* trio2 = (triplet *)t2;

	if(trio1->r > trio2->r) return 1;
	else if(trio1->r < trio2->r) return -1;
	else{
		if(trio1->c > trio2->c) return 1;
		else if(trio1->c < trio2->c) return -1;
	}
}

void make_CSR(triplet *triplet_array, int n_triplets, int rows, int *V, int *C, int *R) {
	qsort(triplet_array, n_triplets, sizeof(triplet), cmp_triplets);

	for(int i = 0; i <= rows; i++){
		V[i]=triplet_array[i].v;
		C[i]=triplet_array[i].c;
	}

	for(int i = 0; i <= rows; ++i) {
		int sum = 0;
		for(int j = 0; j < n_triplets; ++j){
			if(triplet_array[j].r < i) sum++;
		}
		R[i]=sum;
	}
}

void multiply_by_vector(int rows, const int *V, const int *C, const int *R, const int *x, int *y) {
	for(int i = 0; i < rows; ++i){
		y[i] = 0;
		int start = R[i];
		int end = R[i+1];

		for(int j = start; j < end; ++j){
			y[i]+=V[j]*x[C[j]];
		}
	}
}

void read_vector(int *v, int n) {
    int c;
    int i = 0, k = 0;
    char *out;
    int buf[BUF_SIZE];
    char str[20];
    while ((c = getchar()) != EOF) {
        if (c != '\n' && c != ' ') {
            str[k] = c;
            k += 1;
        }

        if (c == ' ') {
            buf[i] = strtol(str, &out, 10);
            i += 1;
            for (int n = 0; n < k; n++) {
                str[n] = ' ';
            }
            k = 0;
        }

        if (c == '\n') {
            buf[i] = strtol(str, &out, 10);
            for(int l=0;l<n;l++){
                v[l]=buf[l];
            }
        }

    }
}

void write_vector(int *v, int n) {
    for(int i=0;i<n;++i){
        printf("%d ",v[i]);
    }
    printf("\n");
}

int read_int() {
	char c_buf[BUF_SIZE];
	fgets(c_buf, BUF_SIZE, stdin);
	return (int)strtol(c_buf, NULL, 10);
}

int main(void) {
	int to_do = read_int();

	int A[TAB_SIZE], B[TAB_SIZE], AB[TAB_SIZE];
	int n, lines_counter, rowsA, colsA, rowsB, colsB;
	int rows, cols, n_triplets;
	char *char_lines_array[TAB_SIZE] = { NULL };
	int continuous_array[TAB_SIZE];
	int *ptr_array[TAB_SIZE];
	triplet triplet_array[TAB_SIZE];
	int V[TAB_SIZE], C[TAB_SIZE], R[TAB_SIZE];
	int x[TAB_SIZE], y[TAB_SIZE];
	line_type int_lines_array[TAB_SIZE];

	switch (to_do) {
		case 1:
			scanf("%d %d", &rowsA, &colsA);
			read_mat(rowsA, colsA, A);
			scanf("%d %d", &rowsB, &colsB);
			read_mat(rowsB, colsB, B);
			prod_mat(rowsA, colsA, colsB, A, B, AB);
			print_mat(rowsA, colsB, AB);
			break;
		case 2:
			n = read_int() - 1; // we count from 1 :)
			ptr_array[0] = continuous_array;
			read_int_lines_cont(ptr_array);
			write_int_line_cont(ptr_array, n);
			break;
		case 3:
			n = read_int() - 1;
			read_char_lines(char_lines_array);
			write_char_line(char_lines_array, n);
			delete_lines(char_lines_array);
			break;
		case 4:
			n = read_int() - 1;
			lines_counter = read_int_lines(int_lines_array);
			sort_by_average(int_lines_array, lines_counter);
			write_int_line(int_lines_array, n);
			delete_int_lines(int_lines_array, lines_counter);
			break;
		case 5:
			scanf("%d %d %d", &rows, &cols, &n_triplets);
			n_triplets = read_sparse(triplet_array, n_triplets);
			read_vector(x, cols);
			make_CSR(triplet_array, n_triplets, rows, V, C, R);
			multiply_by_vector(rows, V, C, R, x, y);
			write_vector(V, n_triplets);
			write_vector(C, n_triplets);
			write_vector(R, rows + 1);
			write_vector(y, rows);
			break;
		default:
			printf("NOTHING TO DO FOR %d\n", to_do);
			break;
	}
	return 0;
}

