#include<bits/stdc++.h>
using namespace std;
char cad[100];
struct trie{
	trie *nx[30];
	trie(){
		for(int i=0;i<30;i++)
			nx[i]=NULL;
	}

	void insert(char *s){
		if(*s=='\0') return;
		if(nx[*s-'a']==NULL){
			nx[*s-'a'] = new trie;
		}
		
		(*nx[*s-'a']).insert(s+1);
	}

};

void recorro(trie &a){
	for(int i=0;i<30;i++){
		if(a.nx[i]!=NULL){
			char t = 'a'+i;
			cout << t;
			recorro(*(a.nx[i]));
			cout << " ";
		}
	}
}

int main(){
	trie a;
	cin >> cad;
	a.insert(cad);
	cin >> cad;
	a.insert(cad);
	recorro(a);
	return 0;
}
