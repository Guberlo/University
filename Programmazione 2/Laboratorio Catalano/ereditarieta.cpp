#include <iostream>

using namespace std;

const float PI=3.1415;

class Oggetto_Geometrico
{
    public:
      Oggetto_Geometrico(float x=0, float y=0): xC(x), yC(y) {}
      void stampa_centro()
      {
        cout << xC << " " << yC << endl;
      }

      float getX(){
        return xC;
      }

      float getY(){
        return yC;
      }

    private:
      float xC, yC;
};

class cerchio : public Oggetto_Geometrico
{
    public:
      cerchio(float x_C, float y_C, float r):Oggetto_Geometrico(x_C, y_C)
      {
        raggio=r;
      }
      float area()
      {
        return PI*raggio*raggio;
      }

    private:
      float raggio;
};

class quadrato : public Oggetto_Geometrico
{
    public:
      quadrato(float x_C, float y_C, float x, float y) : Oggetto_Geometrico(x_C, y_C)
      {
          xVertice=x; yVertice=y;
      }

      float area()
      {
          float a,b;
          a=xVertice-getX();
          b=yVertice-getY();
          return 2*(a*a+b*b);
      }

    private:
      float xVertice, yVertice;
};


class Punto
{
    public:
      Punto(int xx, int yy);
      void ScriviPunto();

    private:
      int x,y;
};

class Punto3D : public Punto
{
    public:
      Punto3D(int xx, int yy, int zz);
      void FissaZ(int zz);
      void Stampa3D();

    private:
      int z;

};

Punto :: Punto(int xx, int yy)
{
  x=xx; y=yy;
}

void Punto::ScriviPunto()
{
  cout << "Valore di x: " << x <<endl;
  cout << "Valore di y: " << y << endl;
}

Punto3D::Punto3D(int xx, int yy, int zz) : Punto(xx, yy)
{
    FissaZ(zz);
}

void Punto3D::Stampa3D()
{
    ScriviPunto();
    cout << "Valore di z: " << z << endl;
}

void Punto3D :: FissaZ(int zz)
{
    z=zz;
}

int main()
{
    //cerchio C(2,2.5,2);
    //quadrato Q(3,3.7,4,5.1);

    Punto p(2,7);
    Punto3D pp(3,4,5);

    p.ScriviPunto();
    pp.Stampa3D();
    //cout << "Centro del cerchio: " << C.stampa_centro();
    //cout << endl;

    //cout << "Centro del quadrato: " << Q.stampa_centro();
    //cout << endl;

    /*cout << "Area del cerchio: " << C.area();
    cout << endl;

    cout << "Area del quadrato: " << Q.area();
    cout << endl;*/
}
