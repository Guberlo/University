template <class H> class Vector{
private:
  H* nodes;
  int len;
  int n;

public:
  Vector(int len = 100){
    this->len = len;
    nodes = new H[len];
    n = 0;
  }

  void addNode(H key){
    nodes[n] = key;
    n++;
    sort(nodes, nodes+n);
  }

  int findIndex(H key){
    for(int i=0; i<len; i++)
      if(key == nodes[i]) return i;
    return -1;
  }

  H findKey(int i){
    return nodes[i];
  }
};
