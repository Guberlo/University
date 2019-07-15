template <class H> class Queue{
private:
  H** v;
  int head, tail;
  int len;

public:
  Queue(int len = 100){
    this->len = len;
    head = tail = 0;
    v = new H*[len];
  }

  int isEmpty(){return head == tail;}

  void enqueue(H x){v[tail++] = new H(x);}
  H* dequeue(){
    if(isEmpty()) return NULL;
    else  return v[head++];
  }
};

#define WHITE 0
#define GRAY 1
#define BLACK 2
#define INF -1
void bfs(H s){
  //inizializzazione
  for(int i=0; i<key->size(); i++){
    color[i] = WHITE;
    p[i] = -1;
    d[i] = INF;
  }
  //ciclo principale
  int i = key->findIndex(s);
  Queue<int> * q = new Queue<int>(key->size());
  q->enqueue(i);
  color[i] = GRAY;
  d[i] = 0;
  while(!q->isEmpty()){
    i = *q->dequeue();
    for(int j=0; j<k->size(); j++){
      if(m[i][j] && color[j] == WHITE){
        color[j] = GRAY;
        q->enqueue(j);
        d[j] = d[i] + 1;
        p[j] = i;
      }
    }
    color[i] = BLACK;
  }
}

int getDistance(H x, H y){
  int i = key->findIndex(x);
  int j = key->findIndex(y);
  if(i == -1 || j == -1)  return INF;
  if (d[i] != 0)  bfs(x);
  return d[j];
}

void printPath(int j){
  if(p[j] != -1){
    printPath(p[j]);
    cout << "-->" ;
  }
  cout << *key->findKey(j);    
}

void getPath(H x, H y){
  int i = key->findIndex(x);
  int j = key->findIndex(y);
  if(i == -1 || j == -1)  cout << "Cammino non esistente";
  if(d[j] == -1)  cout << "Cammino non esistente";

  int tmp = j;
  cout << y;
  tmp = p[tmp];
  while(tmp != -1){
    cout << " <-- " <<  *key->findKey();
    tmp = p[tmp];
  }
  cout << endl;
}
