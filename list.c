#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

struct list *head = NULL; 
struct list *now  = NULL; 

struct list *getnode (void) 
{
 printf("list a getnode is created\n");	
	struct list *p;
	p = (struct list*) malloc(sizeof(struct list));
	if( p == NULL){
		printf("memory is not enough\n");
		exit(EXIT_FAILURE);
        }
	return(p);
}

/* Initializes 'list' as an empty list. */
void list_init(struct list *list)
{
 printf("pointer inital of list\n");
	list->no=0;
	list->num=0;
	list->data = NULL;    	
	list->next = NULL;
    		
}

void assign_value(struct list *list,int no,int num,char *data)
{
    list->no= no; 
  	list->num = num;
	list->data = data;     
}//assign_value

/* Inserts 'elem' just next. */
struct list *list_insert(struct list *now ,struct list *newPtr)
{
 printf("---------pointer insert of list----------\n\n");
		if(head == NULL){
			head = now =newPtr;
			now->next = NULL;
		}else{
              while(now!=NULL){      
                               printf("now!=NULL\n");
			                   if(now->next==NULL){
				                                   now->next = newPtr;
				                                   newPtr->next = NULL;	
				                                   break ;
                                 }
                    now = now->next;             
              }//while
		}//else
	return(now);	
}//list_insert

void save_match_data(int num,char *data)
{
 printf("\n---------------- save_match_data--------------\n"); 
 struct list *new_p;    
 static int no;
 no++;      
 new_p= getnode();
 list_init(new_p);
 printf("no:%d,outport:%d\n\n",no,num);
 assign_value(new_p,no,num,data);      
 now = list_insert(now,new_p); 
      
}//save_match_data

void copy_match_to_table(char* buffer,int buf_len,int out_port)
{
  printf("\n----------------copy_match_to_table--------------\n");    
  char*p;    
  struct ofp_flow_mod *flow_mod;    
  struct ofp_match *match;
  flow_mod = (struct ofp_flow_mod *)buffer;	
  match = &flow_mod->match;
  p = (char*) malloc(sizeof(char)*(htons(match->length)));    
  memset(p, 0,htons(match->length));	
  memcpy(p,match,htons(match->length));
  printf("match_length:%d,match_type:%d,out_port:%d\n\n",htons(match->length),htons(match->type),out_port);  
  save_match_data(out_port,p);    
}//copy_match

void remove_match_in_table(char* buffer,int buf_len)
{
  printf("\n---------------remove_match_in_table-------------\n");    
  char*p;    
  struct ofp_flow_mod *flow_mod;    
  struct ofp_match *match;
  flow_mod = (struct ofp_flow_mod *)buffer;	
  match = &flow_mod->match;
  p =(char*)match;	
  printf("match_length:%d,match_type:%d\n\n",htons(match->length),htons(match->type));
  remove_list_node(p);  
}//remove_match_in_table


void all_remove_entry(void)
{
  struct list *p;
  struct ofp_match *match;
  p = head;
  match=p->data;
  while(p!=NULL){
        printf("\n----------------all_remove_entry-------------\n");                
	list_init(p);                
        p = p->next;             
  }//while 
}//all_remove

void print_match_tmp_table(void)
{
  struct list *p;
  struct ofp_match *match;
  p = head;
  match=p->data;
  while(p!=NULL){
        printf("\n----------------print_match_tmp_table--------------\n");                
        printf("no:%d,outport:%d\n",p->no,p->num);
        printf("match_length:%d,match_type:%d\n\n",htons(match->length),htons(match->type));                
        p = p->next;             
  }//while 
}//print_match_tmp_table

void remove_list_node(char *match)
{
    printf("\n---------------- remove_list_node--------------\n");   
    struct list *del,*p,*prev;
    p = head;  
    while(p!=NULL){
          if(strcmp(p->data,match)==0)
          {
            del=p;
            prev->next = p->next;         
          } 
          prev = p;        
          p = p->next;               
    }//while             
    free(del);
}// remove_list_node

int count_match_entry(int output)
{
    printf("\n----- Staring output(%d) of count amount of match condition...... ---\n",output); 
    int count=0;
    struct list *p;
    p = head;  
    while(p!=NULL){               
        printf("no:%d,p->num:%d,outport:%d\n",p->no,p->num,output);
          if(p->num == output)
             	count++;
	  p = p->next;                
    }//while    
    printf("--- The sum total of count amount:(%d) ......---- \n\n",count);
  
  return count;           
}//count_match_entry

char *cache_match_data(struct list **nowP,int output)
{
     printf("\n---------------- Staring cache data of match condition...... --------------\n");
     char * data;
     struct list *p;
     
     if(*nowP==NULL)
        p = head;
     else               
        p = *nowP;
        
     do{
          if(p->num==output){
             data = p->data;
             *nowP=p->next;
              break; 
          }//if  
 	  p = p->next;             
    }while(p!=NULL);//while 
 return data;           
}//cache_match_data
