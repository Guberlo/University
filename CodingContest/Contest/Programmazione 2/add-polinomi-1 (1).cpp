#include <iostream>
#include <sstream>
#include <fstream>
#include <cstring>

using namespace std;

class Monomio{
	private:
	Monomio *prev, *next;
	int coef, elev;
	
	char* converti(string str){
		char* out=new char[str.length()];
		for(unsigned i=0; i<str.length(); i++)
			out[i]=str[i];
		return out;
	}
	
	public:
	Monomio(){
		prev=NULL;
		next=NULL;
		coef=0;
		elev=0;
	}
	void insert(string str){
		string str_c="", str_e="";
		bool ok=false;
		if(str[0]=='-')
			str_c+='-';
		if(isNumber(str[0]) || str[0]=='+' || str[0]=='x')
			str_c+='+';
		for(unsigned int i=0; i<str.length(); i++){
			if(isNumber(str[i]) && !ok)
				str_c+=str[i];
			if(str[i]=='x'){
				ok=true;
				elev=coef=1;
				i+=2;
			}
			if(ok && i<str.length())
				str_e+=str[i];
		}
		if(str_e.length())
			elev=atoi(converti(str_e));
		if(str_c=="-")
			coef=-1;
		else if(str_c=="+")
			coef=1;
		else
			coef=atoi(converti(str_c));
	}
	void setPrev(Monomio* prev){
		this->prev=prev;
	}
	void setNext(Monomio* next){
		this->next=next;
	}	
	void setCoef(int coef){
		this->coef=coef;
	}
	void setElev(int elev){
		this->elev=elev;
	}
	Monomio* getPrev(){
		return prev;
	}
	Monomio* getNext(){
		return next;
	}
	int getCoef(){
		return coef;
	}
	int getElev(){
		return elev;
	}
	static bool isNumber(char a){
		return (a>47 && a<58);
	}
};

class Polinomio{
	private:
	Monomio *testa, *coda;
	int n, grado, k;
	char segno;
	
	Monomio* insertMon(){
		Monomio* newm=new Monomio();
		Monomio* prev=coda->getPrev();
		prev->setNext(newm);
		newm->setPrev(prev);
		newm->setNext(coda);
		coda->setPrev(newm);
		n++;
		return newm;
		
	}
	
	public:
	Polinomio(){
		testa=new Monomio();
		coda=new Monomio();
		testa->setNext(coda);
		coda->setPrev(testa);
		n=0;
		setSegno('+');
		grado=0;
	}
	void setSegno(char s){
		if(s=='+')
			segno='+';
		else
			segno='-';
	}
	Polinomio* insert(string str){
		string mon="";/*
		int k=1;
		if(str[0]=='+'){
			setSegno('+');
			k++;
		}
		else if(str[0]=='-'){
			setSegno('-');
			k++;
		}*/
		for(unsigned int i=1; i<str.length(); i++){
			if(str[i]==')' || str[i]=='+' || (str[i]=='-' && mon.length())){
				Monomio* newm=insertMon();
				newm->insert(mon);
				if(segno=='-')
					newm->setCoef(newm->getCoef()*(-1));
				if(newm->getElev()>grado)
					grado=newm->getElev();
			cout<<newm->getCoef()<<" "<<newm->getElev()<<" ";
				mon="";
			}
			mon+=str[i];
		}
		cout<<endl;
		return this;
	}
	string risultato(){
		stringstream ss;
		int sum=0;
		for(int i=grado; i>-1; i--){
			Monomio* tmp=testa->getNext();
			sum=0;
			while(tmp!=coda){
				if(tmp->getElev()==i)
					sum+=tmp->getCoef();
				tmp=tmp->getNext();
			}
			if(sum)				
				ss<<showpos<<sum<<"x^"<<noshowpos<<i;
		}
		string out=ss.str();
		if(out.substr(out.length()-3)=="x^0")
			out.erase(out.length()-3);
		if(out[0]=='+')
			out.erase(0,1);
		for(unsigned int i=0; i<out.length(); i++){
			if(out[i]=='^' && out[i+1]=='1' && ((out[i+2]=='+' || out[i+2]=='-') || i+2>=out.length()))
				out.erase(i,2);
			if((out[i]=='+' || out[i]=='-') && out[i+1]=='1' && out[i+2]=='x')
				out.erase(i+1,1);
		}
		if(out[0]=='1' && out[1]=='x')
			out.erase(0,1);
		return out;	
	}
};

int main(){
	ifstream fin("input.txt");
	ofstream fout("output.txt");
	for(int i=0; i<100; i++){
		int n;
		fin>>n;
		Polinomio* pol=new Polinomio();
		for(int j=0; j<n; j++){
			
			string str;
			fin>>str;
			cout<<str<<" ";
			if(str=="+" || str=="-"){
				pol->setSegno(str[0]);
				j--;
			}
			else
				pol->insert(str);
			}
		fout<<pol->risultato()<<endl;
		cout<<endl;
		}/*
	Polinomio* pol=new Polinomio();
	pol->insert("(8x^9+13x^8+2x^4-7x^2+9x)");
	pol->setSegno('+'); 
	pol->insert("(15x^7+12x^5-2x^3+6x^2-11x)");
	pol->setSegno('-');
	pol->insert("(4x^12+19x^10+19x^7+9x^3-3x^2)");
	pol->insert("(4x^12)");
	cout<<pol->risultato()<<endl;*/
	return 0;
}
