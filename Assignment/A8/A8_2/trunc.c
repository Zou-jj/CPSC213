#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

void to_int(element_t* n,element_t str) {
	int* res = malloc(sizeof(int));
	char * endptr;
	*res = strtol(str, &endptr, 10);
	if(!(((char*)str)[0] != '\0' && endptr[0] == '\0')) {
		*res = -1;
	}
	*n = res;
}

void num_to_null(element_t* out, element_t orig, element_t ref) {
	char* inStr = orig;
	char* outStr = malloc((strlen(inStr) + 1) * sizeof(char));
	if (*((int*)ref) == -1) {
		strcpy(outStr, inStr);
		*out = outStr;
	} else {
		*outStr = NULL;
		*out = outStr;
	}
}

int is_pos(element_t n) {
	return (*((int *)n) != -1);
	//return (n != -1);
}

int not_null(element_t str) {
	char *s = str;
	return (*s != NULL);
}

void print_int (element_t ev) {
  int* e = ev;
  printf ("%d\n", *e);
}

void print_str (element_t ev) {
  char* e = ev;
  printf ("%s\n", e);
//   if (*e == NULL) {
// 	  printf("NULL\n");
//   } else {
// 	printf ("%s\n", e);
//   }
}

void truncate(element_t* out, element_t orig, element_t size) {
	int s = *((int*)size);
	char* res = malloc((s+1) * sizeof(char));
	
	strncpy(res, orig, s);
	res[s] = '\0';
	*out = res;
}

void join(element_t* res, element_t left, element_t right) {
	// //printf("%s, %s\n", left, right);
	// char* l = left;
	// char* r = right;
	// char* s = " ";
	// char* new;
	// // if (*res != NULL) {
	// 	// free(*res);
	// // } else {
	// 	// printf("%s\n",*res);	
	// // }
	// l = realloc(l, (strlen(l) + strlen(r) + 1) * sizeof(char));
	
	// // strcpy(newStr, l);
	// strcat(new, r);
	// strcat(new, s);

	// // *res = new;
	// // free(left);
		//printf("%s, %s\n", left, right);
	char* l = left;
	char* r = right;
	char* s = (char*) *res;
	printf("\ns: %s\n", s);
	// if (*res != NULL) {
		// free(*res);
	// } else {
		// printf("%s\n",*res);	
	// }

	*res = malloc((strlen(left) + strlen(right) + 1) * sizeof(char));
	
	strcpy(*res, l);
	strcat(*res, r);

	if (s[0] != '\0'){
		free(s);
	}
}

void max_num (element_t* rv, element_t av, element_t bv) {
  int *a = av, *b = bv, **r = (int**) rv;
  if (*r == NULL)
    *r = malloc(sizeof(int));
  if (*a > *b) {
	**r = *a;
  } else {
	**r = *b;
  }
}

int main(int argc, char **argv) {
	struct list* input = list_create();
	for (int i=0; i<argc-1; i++) {
		char* e = malloc(sizeof(char) * (strlen(argv[i+1]) + 1));
		strcpy(e,argv[i+1]);
		list_append(input,(element_t)e);
		//list_append(input,(element_t)argv[i+1]);
	}
	
	struct list* num_list = list_create();
	
	list_map1(to_int, num_list, input);
	
	struct list* str_list = list_create();
	list_map2(num_to_null, str_list, input, num_list);
	
	struct list* nl = list_create();
	list_filter(is_pos, nl,num_list);
	
	struct list* sl = list_create();
	list_filter(not_null, sl,str_list);
	
	 // list_foreach(print_int, nl);
	 // list_foreach(print_str, sl);
	 
	struct list* tl = list_create();
	list_map2(truncate, tl, sl, nl);
	list_foreach(print_str, tl);

	// char* joined = " ";
	// char** strp = &joined;
	// list_foldl(join, (element_t*) &strp, tl);
	// print_str(joined);

	char* joined = "";
	list_foldl(join, &joined, tl);
	print_str(joined);
	
	int max = 0;
	int* vmax = &max;
	list_foldl(max_num, &vmax, nl);
	print_int(vmax);
	
	free(joined);
	list_foreach (free, input);
	list_foreach (free, num_list);  // free elements allocated in list
	list_foreach (free, str_list);
	list_foreach (free, tl);
	list_destroy(input);
	list_destroy(num_list);
	list_destroy(str_list);
	list_destroy(nl);
	list_destroy(sl);
	list_destroy(tl);
}