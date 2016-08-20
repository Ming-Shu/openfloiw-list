#include <stdio.h>
#include <stdlib.h>
#include "openflow_1_3.h"

struct list 
  {
	int no;          //list of number   
	int num;		//data of number
	char *data;		// pointer of any data
	struct list *next;	// Next list element. 	
  };

struct list *getnode (void);
void list_init(struct list *list);
void assign_value(struct list *list,int no,int num,char *data);
struct list *list_insert(struct list *now ,struct list *newPtr); 
void save_match_data(int num,char *data);
void copy_match_to_table(char* buffer,int buf_len,int out_port);
void print_match_tmp_table(void);
void remove_list_node(char *match);
int count_match_entry(int output);
char *cache_match_data(struct list **nowP,int output);
void remove_match_in_table(char* buffer,int buf_len);
void all_remove_entry(void);

