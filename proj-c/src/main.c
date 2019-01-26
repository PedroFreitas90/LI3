#include <date.h>
#include <stdio.h>
#include <time.h>
#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#include <glib.h>
#include "user.h"
#include "parser.h"
#include "interface.h"
#include "mypost.h"
#include "myuser.h"
#include "key.h"
#include "heap.h"

//4,5,8


int main(){
  TAD_community tad = init();
  int i;
  clock_t t1, t2, t3, t4, t5, t6, t7,t8, t9, t10, t11;
  char* path = "/home/pedro90/Desktop/Universidade/2ºAno/2ºSemestre/LI3/dump/ubuntu/";

  load(tad,path);

  t1 = clock();
  STR_pair q1 = info_from_post(tad, 801049);
  char* c1 = get_fst_str(q1);
  char* c2 = get_snd_str(q1);
  printf("%s %s\n", c1, c2);
  t1 = clock() - t1;
  double a1 = ((double) t1) /CLOCKS_PER_SEC *1000;
  printf("Q1: %f ms \n",a1 );
  free_str_pair(q1);
  free(c1);
  free(c2);


  t2 = clock();
  LONG_list l2 = top_most_active(tad, 10);
  for(i=0; i<10; i++)
  printf("%ld\n", get_list(l2,i));
  t2 = clock() - t2;
  a1 = ((double) t2) /CLOCKS_PER_SEC *1000;
  printf("Q2: %f ms \n",a1);
  free_list(l2);


  t3 =clock();
  Date begin1 = createDate(1,7,2016);
  Date end1 = createDate(31,7,2016);
  LONG_pair pair = total_posts(tad, begin1, end1);
  t3 =clock()-t3;
  long fst = get_fst_long(pair);
  long snd = get_snd_long(pair);
  printf("Perguntas: %ld e Respostas: %ld\n", fst,snd );
  a1 = ((double) t3) / CLOCKS_PER_SEC *1000;
  printf("Q3:%f ms\n",a1 );
  free_long_pair(pair);

  t4 = clock();
  Date data1 = createDate(1,3,2013);
  Date data2 = createDate(31,3,2013);
  LONG_list l3 = questions_with_tag(tad, "package-management", data1, data2);
  for(i=0; i<2; i++)
  printf("%ld\n", get_list(l3,i));

  t4 = clock() - t4;
  a1 = ((double) t4) /CLOCKS_PER_SEC *1000;
  printf("Q4: %f ms \n",a1 );
  free_list(l3);

  t5 = clock();
  USER u = get_user_info(tad, 15811);

  t5 = clock() - t5;
  a1 = ((double) t5) /CLOCKS_PER_SEC *1000;
  printf("Q5: %f ms \n",a1 );
  free_user(u);


  t6 = clock();
  Date begin = createDate(1,11,2015);
  Date end = createDate(30,11,2015);
  LONG_list l6 = most_voted_answers(tad, 5, begin, end);
  for(i=0; i<5; i++)
    printf("%ld\n", get_list(l6,i));
  t6 = clock() - t6;
  a1 = ((double) t6) /CLOCKS_PER_SEC *1000;
  printf("Q6: %f ms \n",a1 );
  free_list (l6);


  t7 = clock();
  Date begin2 = createDate(1,8,2014);
  Date end2 = createDate(10,8,2014);
  LONG_list l7 = most_answered_questions(tad, 10, begin2, end2);
  for(i=0; i<10; i++)
    printf("%ld\n", get_list(l7,i));
  t7 = clock() - t7;
  a1 = ((double) t7) /CLOCKS_PER_SEC *1000;
  printf("Q7: %f ms \n",a1 );
  free_list(l7);

  t8 = clock();
  LONG_list l8 = contains_word(tad, "kde", 10);
  for(i=0; i<10; i++)
    printf("%ld\n", get_list(l8,i));
  t8 = clock() - t8;
  a1 = ((double) t8) /CLOCKS_PER_SEC *1000;
  printf("Q8: %f ms \n",a1);
  free_list(l8);

  t9 = clock();
  LONG_list l9 =  both_participated(tad, 87, 5691, 10);
  for(i=0; i<10; i++)
    printf("%ld\n", get_list(l9,i));
  t9 = clock() - t9;
  a1 = ((double) t9) /CLOCKS_PER_SEC *1000;
  printf("Q9: %f ms \n",a1);
  free_list(l9);


  t10 = clock();
  long l10= better_answer(tad, 30334);
  printf("%ld\n", l10);
  t10 = clock() - t10;
  a1 = ((double) t10) /CLOCKS_PER_SEC *1000;
  printf("Q10: %f ms \n",a1);

  begin = createDate(1,11,2013);
  end = createDate(30,11,2013);
  t11 = clock();
  LONG_list l11 = most_used_best_rep(tad,5,begin,end);
  for(i = 0;  i < 5; i++)
    printf("%ld\n",get_list(l11,i));
  t11 = clock() - t11;
  a1 = ((double) t11) /CLOCKS_PER_SEC *1000;
  printf("Q11: %f ms \n",a1);
  free_list(l11);

  tad = clean(tad);
  free(tad);
return 0;
}
