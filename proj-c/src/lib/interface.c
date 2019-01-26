#include "interface.h"

struct TCD_community{
  GTree *Posts;
  GTree *Users;
  GHashTable *Hdates;
  GTree *Tags;
};

/**
  *@brief   Para todos os Users introduz numa heap ordenada pela reputação.
  *@param   gpointer ID do User.
  *@param   gpointer User.
  *@param   gpointer HeapU.
  *return   gboolean True quando itera por todos os Users.
*/
static gboolean user_heap (gpointer key, gpointer value,gpointer user_data);

/**
  *@brief   Função que devolve uma LONG_list com os id's dos N users com mais reputação.
  *@param   TAD_community estrutura com todos os dados úteis provenientes do xml.
  *@param   int tamanho da LONG_list e do número de users.
  *return   LONG_list preenchida com os id's.
*/
static LONG_list topN (TAD_community com ,int N);

/**
  *@brief   Função verifica se determinada tag está num array de pares Tag-Num (ATNum).
  *@param   ATNum array de pares Tag-Num.
  *@param   char* string com o nome da tag.
  *return   int índice da posição da tag caso exista, ou -1 caso não exista.
*/
static int checkT(ATNum a, char* tag);

/**
  *@brief   Função que obtém todas as tags de vários posts.
  *@param   TAD_community estrutura com todos os dados úteis provenientes do xml.
  *@param   ATNum array de pares Tag-Num.
  *@param   LONG_list lista com os top N users.
  *@param   int tamanho da LONG_list.
  *@param   Date data de início.
  *@param   Date data final.
  *return   ATNum array de pares Tag-Num com todas as tags e seu número de ocorrências.
*/
static ATNum get_allTags(TAD_community com,ATNum pairs,LONG_list ll,int N, Date begin, Date end);

/**
  *@brief   Para cada Tag compara-a com a tag do par TNum.
  *@param   gpointer ID da Tag.
  *@param   gpointer Tag.
  *@param   gpointer Duplos.
  *return   gboolean True quando itera por todos as Tags.
*/
static gboolean tags_tree (gpointer key, gpointer value,gpointer user_data);

/**
  *@brief   Função que concatena duas strings.
  *@param   char* string 1.
  *@param   char* string 2.
  *return   char* string resultante.
*/
static char* myconcat(const char *s1, const char *s2);

/**
  *@brief   Para todos os Users, insere os seus IDs numa heap e ordena-os segundo o número de posts do User correspondente ao ID.
  *@param   gpointer ID do User.
  *@param   gpointer User.
  *@param   gpointer HeapU.
  *return   gboolean True quando itera por todos os Users.
*/
static gboolean nrposts (gpointer key, gpointer value, gpointer user_data);

/**
  *@brief   Verifica se uma dada tag se encontra no array de tags de um dado Post.  *@param   gpointer ID do User.
  *@param   Post post.
  *@param   char* tag a procurar.
  *return   int 1 se ela existir, 0 se não existir.
*/
static int existeTag(Post p, char* tag);

/**
  *@brief   Insere todos os Posts numa heap (ordenada por ordem cronologica inversa) todos os posts que contêm no seu titulo uma dada palavra.
  *@param   gpointer ID do Post.
  *@param   gpointer Post.
  *@param   gpointer Heap.
  *return   gboolean True quando itera na totalidade a árvore os Posts.
*/
static gboolean pContainsWord(gpointer key, gpointer value, gpointer user_data);

/**
  *@brief   Para todos os Posts de tipo resposta, insere-os numa heap e ordena-os segundo a classificação média do post.
  *@param   gpointer ID do Post.
  *@param   gpointer Post.
  *@param   gpointer estrutura ResPost.
  *return   gboolean True quando itera por todos os Posts.
*/
static gboolean getScCom(gpointer key, gpointer value, gpointer user_data);


static char* myconcat(const char *s1, const char *s2){
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


/**
  *@brief   Inicializa a estrutura TAD_community com as árvores dos Posts, Users e Tags e a tabela de Hash de Posts.
  *return   Devolve a nova estrutura.
*/
TAD_community init(){
  TAD_community tad = (TAD_community)malloc(sizeof(struct TCD_community));
  tad->Users = g_tree_new_full((GCompareDataFunc) idusercompare, NULL, free, myfreeUser);
  tad->Posts = g_tree_new_full((GCompareDataFunc) idpostcompare, NULL, free, freePost);
  tad->Hdates = g_hash_table_new_full((GHashFunc) hash, (GEqualFunc) iguais, destroyDate, freeArray);
  tad->Tags = g_tree_new_full((GCompareDataFunc) idtagcompare,NULL, free, freeTag);
  return tad;
}

//--- QUERY 0 ---//
/**
  *@brief   Faz o carregamento dos dados dos ficheiros .xml para as estruturas.
  *@param   TAD_community estrutura que guarda toda a informação.
  *@param   char* path onde se encontram os ficheiros .xml.
  *return   TAD_community estrutura carregada com toda a informação útil.
*/
TAD_community load(TAD_community com, char* dump_path){
  char* us = (char*) myconcat(dump_path,"/Users.xml");
  xmlDocPtr us2 = xmlParseFile(us);
  userInfo(us2, com->Users);
  free(us);
  xmlFreeDoc(us2);

  char* pos = (char*) myconcat(dump_path, "/Posts.xml");
  xmlDocPtr pos2 = xmlParseFile(pos);
  postsInfo(pos2, com->Posts, com->Hdates, com->Users);
  free(pos);
  xmlFreeDoc(pos2);

  char* tg = (char*)myconcat(dump_path,"/Tags.xml");
  xmlDocPtr tg2 = xmlParseFile(tg);
  tagsInfo(tg2,com->Tags);
  free(tg);
  xmlFreeDoc(tg2);

  return com;
}

//--- QUERY 1 ---//
/**
  *@brief   Retorna o título e o nome do autor de um post, dado o id do mesmo.
  *@param   TAD_community estrutura que guarda toda a informação.
  *@param   long id do post.
  *return   STR_pair par com título e nome do autor.
*/
STR_pair info_from_post(TAD_community com, long id){
  Key k = createKey(id);
  Post p = (Post)g_tree_lookup(com->Posts, k);
  Key pid,owner;
  User u;
  STR_pair res;
  char* tit,*name;
  freekey(k);

  if(getPostType(p) == 1){
    owner = createKey(getPostOwner(p));
    u = g_tree_lookup(com->Users, owner);
    tit = getPostTitulo(p);
    name = getUserName(u);
    res = create_str_pair(tit,name);
    freekey(owner);
    free(tit);
    free(name);
    return res;
  }
  if(getPostType(p) == 2){
    pid = createKey(getPid(p));
    p = g_tree_lookup(com->Posts, pid);
    owner = createKey(getPostOwner(p));
    u = g_tree_lookup(com->Users, owner);
    tit = getPostTitulo(p);
    name = getUserName(u);
    res = create_str_pair(tit,name);
    freekey(pid);
    freekey(owner);
    free(tit);
    free(name);
    return res;
  }
  res = create_str_pair("","");
  return res;
}


static gboolean nrposts (gpointer key, gpointer value, gpointer user_data){
  Key k = (Key) key;
  long id = getKey(k);
  User user = (User)value;
  HeapU heap = (HeapU) user_data;

  heap_pushU(heap, id,cont_RP(getUserHeap(user)));

  return FALSE;
}

/**
  *@brief   Retorna o top N utilizadores com maior número de posts de sempre.
  *@param   TAD_community estrutura que guarda toda a informação.
  *@param   int N.
  *return   LONG_list lista dos top N utilizadores.
*/
LONG_list top_most_active(TAD_community com, int N){
  int i;
  long id;
  LONG_list res = create_list(N);
  HeapU heap = initHeapU();
  g_tree_foreach(com->Users,(GTraverseFunc)nrposts, heap);

  for(i=0; i<N; i++){
    id = heap_popU(heap);
    set_list(res, i, id);
  }
  heap_freeU(heap);
  return res;
}


//--- QUERY 3 ---//
/**
  *@brief   Retorna o número total de posts efetuados num dado período de tempo.
  *@param   TAD_community estrutura que guarda toda a informação.
  *@param   Date data inicial.
  *@param   Date data final.
  *return   LONG_pair (número de perguntas,número de respostas).
*/
LONG_pair total_posts(TAD_community com, Date begin, Date end){
  long fst = 0;
  long snd = 0; 
  //long r = 0;
  gpointer x;
  ArrayD d;
  while(date_equal(begin,end) > 0){
          x = g_hash_table_lookup(com->Hdates, begin);
          d = (ArrayD) x;
          if (d){
            fst += getPer(d);
            snd += getRes(d);
          }
          begin = incrementaData(begin);
  }
  x = g_hash_table_lookup(com->Hdates, end);
  d = (ArrayD) x;
  if (d){
    fst += getPer(d);
    snd += getRes(d);
  } 
  free_date(begin);
  free_date(end);
  LONG_pair pair = create_long_pair(fst,snd);
  return pair;
}


//--- QUERY 4 ---//
static int existeTag(Post p, char* tag){
    int i, c = 0;
    char** tags = getPostTags(p);
    int ntags = getPostNTags(p);
    for(i=0; i<ntags && c == 0; i++){
        if(strcmp(tag, tags[i]) == 0)
            c = 1;
    }
    return c;
}

/**
  *@brief   Retorna os IDs de todas as perguntas de um dado intervalo de tempo que contém uma dada tag.
  *@param   TAD_community estrutura que guarda toda a informação.
  *@param   char* tag.
  *@param   Date data inicial.
  *@param   Date data final.
  *return   LONG_list lista de IDs ordenada por ordem cronológica inversa.
*/
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end){
    int i, c;
    gpointer x;
    ArrayD d;
    LONG_list r;
    Heap h = initHeap();
    Post p;
    while(date_equal(begin,end) > 0){
        x = g_hash_table_lookup(com->Hdates, begin);
        d = (ArrayD) x;
        if (d){
            for(i=0; i<getUsed(d); i++){
                p = getInd(d,i);
                if(getPostType(p) == 1){
                int cenas = existeTag(p,tag);
                if(cenas == 1)
                    heap_push(h,p,'D');
                }
            }
        }
        begin = incrementaData(begin);
    }
    x = g_hash_table_lookup(com->Hdates, end);
    d = (ArrayD) x;
    if (d){
      for(i=0; i<getUsed(d); i++){
        p = getInd(d,i);
        int eta =existeTag(p,tag);
        if(eta == 1)
          heap_push(h,p,'D');
        }
    }
    c = heap_count(h);
    r = create_list(c);
    for(i=0; i<c; i++){
      Post p = heap_pop(h,'D');
      set_list(r, i, getPostId(p));
    }
    free_date(begin);
    free_date(end);
    heap_free(h);
    return r;
}


//--- QUERY 5 ---//
/**
  *@brief   Retorna a informação do perfil e as últimas dez publicações de um user do qual é dado o ID.
  *@param   TAD_community estrutura que guarda toda a informação.
  *@param   long ID.
  *return   USER estrutura que contém a biografia e 10 últimos posts.
*/
USER get_user_info(TAD_community com, long id){
  int i;
  long* post_history = malloc(10 * sizeof(long));
  Key kid = createKey(id);
  User u = (User)g_tree_lookup(com->Users,kid);
  char *bio = mygetUserBio(u);
  Heap uposts = getUserHeap(u);
  for(i=0; i<10; i++){
    post_history[i] = getPostId(heap_pop(uposts,'D'));
  }
  USER user = create_user(bio,post_history);
  free(bio);
  free(post_history);
  free(kid);
  return user;
}


//--- QUERY 6 ---//
/**
  *@brief   Retorna os ids das N respostas com mais votos feitas num dado intervalo de tempo, por ordem descrescente dos votos.
  *@param   TAD_community estrutura que guarda toda a informação.
  *@param   int N.
  *@param   Date data inicial.
  *@param   Date data final.
  *return   LONG_list ID's das respostas.
*/
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end){
  int i;
  gpointer x;
  ArrayD d;
  LONG_list r = create_list(N);
  Heap h = initHeap();
  while(date_equal(begin,end) > 0){
          x = g_hash_table_lookup(com->Hdates, begin);
          d = (ArrayD) x;
          if (d){
            for(i=0; i<getUsed(d); i++){
              if(getPostType(getInd(d,i)) == 2)
                heap_push(h,getInd(d,i),'S');
            }
          }
          begin = incrementaData(begin);
    }
    x = g_hash_table_lookup(com->Hdates, end);
    d = (ArrayD) x;
    if (d){
      for(i=0; i<getUsed(d); i++){
        if(getPostType(getInd(d,i)) == 2)
          heap_push(h,getInd(d,i),'S');
      }
    }
    for(i=0; i<N; i++){
      Post p = heap_pop(h,'S');
      set_list(r, i, getPostId(p));
    }
    free_date(begin);
    free_date(end);
    heap_free(h);
    return r;
}



//--- QUERY 7 ---//
/**
  *@brief   Retorna os IDs das N perguntas num dado intervalo de tempo com mais respostas.
  *@param   TAD_community estrutura que guarda toda a informação.
  *@param   int N.
  *@param   Date data inicial.
  *@param   Date data final.
  *return   LONG_list ID's das perguntas.
*/
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end){
  int i;
  gpointer x;
  ArrayD d;
  Heap h = initHeap();
  LONG_list r = create_list(N);
  while(date_equal(begin,end) > 0){
    x = g_hash_table_lookup(com->Hdates, begin);
    d = (ArrayD) x;
    if (d){
      for(i=0; i<getUsed(d); i++){
        heap_push(h,getInd(d,i),'R');
      }
    }
    begin = incrementaData(begin);
  }
  x = g_hash_table_lookup(com->Hdates, end);
  d = (ArrayD) x;
  if (d){
    for(i=0; i<getUsed(d); i++){
      heap_push(h,getInd(d,i),'R');
    }
  }
  for(i=0; i<N; i++){
    Post p = heap_pop(h,'R');
    set_list(r, i, getPostId(p));
  }
  free_date(begin);
  free_date(end);
  heap_free(h);
  return r;
}

//--- QUERY 8 ---//
/**
  *@brief   Iterador da árvore dos Posts que insere aqueles que contêm no seu título uma dada palavra numa max heap ordenada pela data.
  *@param   gpointer id.
  *@param   gpointer Post.
  *@param   gpointer Heap (que guarda a palavra em questão).
  *return   gboolean.
*/
static gboolean pContainsWord(gpointer key, gpointer value, gpointer user_data){
  Key k = (Key) key;
  getKey(k);
  Post p = (Post)value;
  Heap h = (Heap) user_data;
  char* tit = getPostTitulo(p);
  if(getPostType(p) == 1){
    if(strstr(tit,getHeapPal(h)))
      heap_push(h,p,'D');
  }
  free(tit);
  return FALSE;
}

/**
  *@brief   Retorna os IDs das N perguntas cujos títulos contêm uma dada palavra, por ordem cronológica inversa.
  *@param   TAD_community estrutura que guarda toda a informação.
  *@param   char* palavra.
  *@param   int N.
  *return   LONG_list ID's das perguntas.
*/
LONG_list contains_word(TAD_community com, char* word, int N){
  int i;
  Post p;
  LONG_list r = create_list(N);
  Heap h = initHeapPal(word);
  g_tree_foreach(com->Posts, (GTraverseFunc)pContainsWord, h);
  for(i=0; i<N; i++){
    p = heap_pop(h,'D');
    set_list(r, i, getPostId(p));
  }
  heap_free(h);
  return r;
}

//--- QUERY 9 ---//
/**
  *@brief   Retorna as últimas N perguntas (por ordem cronológica inversa) em que participaram dois utilizadores específicos.
  *@param   TAD_community estrutura que guarda toda a informação.
  *@param   long id do user 1.
  *@param   long id do user 2.
  *@param   int N.
  *return   LONG_list ID's das perguntas.
*/
LONG_list both_participated(TAD_community com, long id1, long id2, int N){
  int i,j;
  Post p,p1,p2,p3;
  LONG_list r = create_list(N);
  Heap heap = initHeap();
  Key k1 = createKey(id1);
  Key k2 = createKey(id2);
  User u1 = (User) g_tree_lookup(com->Users,k1);
  User u2 = (User) g_tree_lookup(com->Users,k2);
  freekey(k1);
  freekey(k2);
  Heap h1 = getUserHeap(u1);
  Heap h2 = getUserHeap(u2);
  if(h1){
  for(i=0; i< heap_count(h1); i++){
      p1 = getIndP(h1,i);
      if(h2){
        for(j=0; j<heap_count(h2); j++){
            p2 = getIndP(h2,j);
            if(getPostType(p1) == 2 && getPostType(p2) == 1 && getPostId(p2) == getPid(p1))
               if(p2) heap = heap_push(heap,p2,'D');
            if(getPostType(p1) == 2 && getPostType(p2) == 2 && getPid(p2) == getPid(p1)){
                Key k3 = createKey(getPid(p1));
                p3 = (Post) g_tree_lookup(com->Posts,k3);
                freekey(k3);
                if(p3) heap = heap_push(heap,p3,'D');
            }
            if(getPostType(p1) == 1 && getPostType(p2) == 2 && getPid(p2) == getPostId(p1))
                if(p1) heap = heap_push(heap,p1,'D');
        }
      }
  }
  }
  for(i=0; i<N; i++){
    p = heap_pop(heap,'D');
    set_list(r, i, getPostId(p));
  }
  heap_free(heap);
  return r;
}

//--- QUERY 10 ---//
static gboolean getScCom(gpointer key, gpointer value, gpointer user_data){
  Post p = (Post)value;
  ResPost r = (ResPost) user_data;
  long pid = getKey(getResPostParent(r));
  if(getPostType(p) == 2 && getPid(p) == pid){
    heap_push(getResPostHeap(r),p,'M');
  }
  return FALSE;
}

/**
  *@brief   Retorna a melhor resposta dada a uma certa pergunta, da qual é passada o ID.
  *@param   TAD_community estrutura que guarda toda a informação.
  *@param   long ID.
  *return   long ID da resposta.
*/
long better_answer(TAD_community com, long id){
  Post p;
  ResPost r = initResPost(id);
  g_tree_foreach(com->Posts, (GTraverseFunc)getScCom, r);
  p = heap_pop(getResPostHeap(r),'M');
  freeResPost(r);
  return getPostId(p);
}


//--- QUERY 11 ---//
static gboolean user_heap(gpointer key, gpointer value,gpointer user_data){
  User u = (User) value;
  HeapU us = (HeapU) user_data;
  long id = getUserId(u);
  long rep =(long) getUserRep(u);
  us = heap_pushU(us,id,rep);
  return FALSE;
}

static LONG_list topN(TAD_community com ,int N){
  LONG_list ll = init_ll(N);
  HeapU us = initHeapU();
  g_tree_foreach(com->Users, (GTraverseFunc)user_heap, us);
  for(int i = 0; i < N; i++) {
    set_list(ll,i,heap_popU(us));
  }
  heap_freeU(us);
  return ll;
}

// 0 se não pertence, o valor do índice se pertence
static int checkT(ATNum a, char* tag){
  long l = get_atnum_used(a); //Pega no número de casas usadas;
  if(l==0){
    return -1;
  }
  int i;
  char* c = NULL;
  TNum par = NULL;
  for(i = 0 ; i < l ; i++){
    par = get_atnum_tnum(a,i); //Pega no par;
    c = get_tag_tnum(par); //obtém a tag
    if (c != NULL) //se a tag existe
      if (strcmp (c,tag) == 0 ) return i; //compara as tags, e se forem iguais retorna o indice
  }
return -1;
}

static ATNum get_allTags(TAD_community com,ATNum pairs,LONG_list ll, int N, Date begin, Date end){
  User u = NULL; Heap posts = NULL;
  Post p = NULL; TNum new = create_tnum_pair(NULL, 0);
  //Date d;
  int i,j,k,t = 0,c;
  char* aux;
  for(i = 0; i < N;i++){            //Percorre a long-list com os top N users
    u = g_tree_lookup(com->Users,createKey(get_list(ll,i)));      //procura o User da long list, na Àrvore dos users;
    posts = getUserHeap(u);     //vai buscar todos os posts desse gajo
    t = heap_count(posts);    //conta o numero total de posts
    for(j = 0; j < t; j++){     //Percorre a àrvore com todos os posts desse men
      p = getIndP(posts,j);     //Pega no post
      Date d = getPostDate(p);
      if((maisRecente (begin,d)== 1 || maisRecente (begin,d) == 0 ) && (maisRecente (d,end)==1 || maisRecente (d,end) == 0)){ //compara se a data está nesse intervalo
        int numtags =getPostNTags(p);
   //vê o nº de tags do post
        free_date(d);    
        for(k = 0; k < numtags;k++){
          //Percorre asx tags todas
          aux = getTagI(p,k);
          if(aux) {
            c=checkT(pairs,aux);      //Verifica se determinada tag já está no array de pares
              if(c == -1) {
                TNum aux2 = create_tnum_pair(aux,1);       //se não estiver, cria um par e introduz no array
                insere_tagnum(pairs,aux2);
            }
            else{
            new = get_atnum_tnum(pairs,c);
            new = incTNum(new);
            }
          }
        }
      }
    }
  }
  free_date(begin);
  free_date(end);
  return pairs;
}


static gboolean tags_tree (gpointer key, gpointer value,gpointer user_data){
  Tag t = (Tag) value;
  long id = getTagId(t);
  Duplos dup = (Duplos) user_data;
  TNum tn = get_duplos_tnum(dup);
  LONG_list ll = get_duplos_ll(dup);
    if (strcmp(getTagName(t),get_tag_tnum(tn))==0) {
        set_list(ll,get_duplos_pos(dup),id);
        return TRUE;
    }
    return FALSE;
  }

/**
  *@brief   Retorna, dado um intervalo de tempo, os IDs das N tags mais utilizadas nesse período pelos N utilizadores com melhor reputação.
  *@param   TAD_community estrutura que guarda toda a informação.
  *@param   int N.
  *@param   Date data inicial.
  *@param   Date data final. 
  *return   LONG_list IDs das tags.
*/
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end){
  LONG_list ll = topN(com,N);
  LONG_list tagsmu = init_ll(N);
  ATNum tn = init_atnum(N);
  TNum aux = NULL;
  tn = get_allTags(com,tn,ll,N,begin,end);
  bubbleTNumSort(tn);
  Duplos dup = insere_Duplos(tagsmu, NULL ,N,0);
  int i;
  for(i = 0; i < N; i++){
    aux = get_atnum_tnum(tn,i);
    set_duplos_tnum(dup,aux);
    set_duplos_pos(dup,i);
    g_tree_foreach(com->Tags,(GTraverseFunc)tags_tree,dup);
    free_tnum(aux);
  }
  free_date(begin);
  free_date(end);
  return tagsmu;
}


/**
  *@brief   Limpa da memória todos os dados guardados no load da TAD_community.
  *return   Devolve a estrutura limpa.
*/
TAD_community clean(TAD_community com){
  g_tree_destroy(com->Posts);
  g_hash_table_destroy(com->Hdates);
  g_tree_destroy(com->Users);
  g_tree_destroy(com->Tags);
  return com;   
}
