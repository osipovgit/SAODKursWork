#include <bits/stdc++.h>
#define N 4000

using namespace std;

struct record {
    char fio[30];
    unsigned short int numDep;
    char position[22];
    char date[10];
};

struct queue_q {
  	record *q;
  	queue_q *next;
};

struct Vertex {
    record* data;
    Vertex *left, *right;
    int Balance;
};

bool Rost = true;
bool Ymen = true;
bool HR = false, VR = false;

inline bool key2(int q, int l, record** ind) {
	if(strcmp(ind[q]->fio, ind[l]->fio) >= 0)
		return true;
	else if(strcmp(ind[q]->fio, ind[l]->fio) < 0)
		return false;
}

inline bool key(int q, int l, record** ind) {
	if(ind[q]->date[0] > ind[l]->date[0] ||(ind[q]->date[0] == ind[l]->date[0] && ind[q]->date[1] > ind[l]->date[1]))
		return true;
	else if(ind[q]->date[0] == ind[l]->date[0] && ind[q]->date[1] == ind[l]->date[1])
		return key2(q, l, ind);
	else
		return false;
}

inline void heapPostr (record** ind, int l, int r) {
	int i = l, j;
	ind[N] = ind[l]; 
	while (1) {
		j = i << 1;
		if (j > r) break;
		if (j < r && (key(j + 1, j, ind))) ++j;
		if (key(N, j, ind)) break;
		ind[i] = ind[j];
		i = j;
	}
	ind[i] = ind[N];
}

inline void heapSort (record** ind, int n) {
	int l = n >> 1, r = n;
	while (l + 1 > 0) {
		heapPostr(ind, l, r);
		--l;
	}
	while (r > 1) {
		swap (ind[0], ind[r - 1]);
		--r;
		heapPostr (ind, 0, r - 1);
	}
}

inline int search_less(record** ind, string key, int M) {
	string s = key;
	for(int i = 0; i < 2; ++i)
		s[i] = ind[M]->date[i];
	if(key < s) 
		return -1;
	else if(key > s) 
		return 1;
	else if (key == s)
		return 0;
}

inline int binsearch(record** ind, string key, int L, int R) {
	int M;
	while(L < R){
		M = (L + R) >> 1;
		if(search_less(ind, key, M) <= 0)
			R = M;
		else
			L = M + 1;
	}
	if(search_less(ind, key, L) == 0)
		return L;
	else
		return -1;
}

inline void B2insert(record* D, Vertex *&p) {
    if (p == NULL) {
        p = new Vertex;
        p->data = D;
        p->left = p->right = NULL;
        p->Balance = 0;
        VR = true;
    } else {
        if (strcmp(D->fio, p->data->fio) < 0) {
            B2insert(D, p->left);
            if (VR) {
                if (p->Balance == 0) {
                    Vertex *q = NULL;
                    q = p->left;
                    p->left = q->right;
                    q->right = p;
                    p = q;
                    q->Balance = 1;
                    VR = true;
                    HR = false;
                } else {
                    p->Balance = 0;
                    VR = true;
                    HR = false;
                }
            } else
                HR = false;
        } else {
            if (strcmp(D->fio, p->data->fio) >= 0) {
                B2insert(D, p->right);
                if (VR) {
                    p->Balance = 1;
                    HR = true;
                    VR = false;
                } else {
                    if (HR) {
                        if (p->Balance == 1) {
                            Vertex *q = NULL;
                            q = p->right;
                            p->Balance = 0;
                            q->Balance = 0;
                            p->right = q->left;
                            q->left = p;
                            p = q;
                            VR = true;
                            HR = false;
                        } else {
                            HR = false;
                        }
                    }
                }
            }
        }
    }
}

void ocered(queue_q*& p, int t, record** ind, Vertex *&DBD) {
	if(!p) {
		p = new queue_q;
		p->q = ind[t];
		B2insert(p->q, DBD);
		p->next = NULL;
	}
	else
		ocered(p->next, t, ind, DBD);
}

void Obhod(Vertex *p) {
	if(p){
        Obhod(p->left);
		cout << setw(30) << p->data->fio << "  " << setw(3) << p->data->numDep << "  " << setw(22) << p->data->position << "  " << setw(10) << p->data->date << endl;
        Obhod(p->right);
	}
}

void printQueue(queue_q *&p, int i) {
	if(p){
		cout << setw(4) << ++i << ")" << setw(30) << p->q->fio << "  " << setw(3) << p->q->numDep << "  " << setw(22) << p->q->position << "  " << setw(10) << p->q->date << endl;
		printQueue(p->next, i);
	}
}

inline void delQueue(queue_q*& p) {
	queue_q* q;
	while(p){
		q = p;
		p = p->next;
		delete q;
	}
}

inline void print(record **ind) {
	bool exitcode;
	for(int i = 0; i < N; ++i){
		if(i % 20 == 0 && i != 0){
			cout << "Continue/Exit(1/0): ";
			cin >> exitcode;
			if(!exitcode)
				break;
		}
		cout << setw(4) << i + 1 << ")" << setw(30)<< ind[i]->fio << "  " << setw(3) << ind[i]->numDep << "  " << setw(22) << ind[i]->position << "  " << setw(10) << ind[i]->date << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
    FILE *fp = fopen("testBase2.dat", "rb");
    record* mas = new record[N];
	record** ind = new record*[N];
	for(int i = 0; i < N; ++i)
  		ind[i] = &mas[i];
	int j = 0, act;
	j = fread((record*)mas, sizeof(record), N, fp);
	cout << "Choose:" << endl << "1) Print" << endl <<"2) Sort" << endl << "3) Key" << endl << ">> ";
	cin >> act;
	if (act == 1)
		print(ind);
	else if (act == 2) {
		heapSort(ind, N);
		print(ind);
	}
	else if (act == 3) {
		heapSort(ind, N);
		string key;
		char less[2];
		while(1) {
  			retry:
  			queue_q *root = NULL;
			Vertex *DBD = NULL;
			cout << "Enter date: ";
//  			fflush(stdin);
//			gets(key);
//			if(strcmp(key, "-+") == 0) break;
			cin >> key;
  			if(key == "-+") break;
  			int t = binsearch(ind, key, 0, N - 1);
  			if(t > -1)
  				cout << "First element number is " << t + 1 << endl;
  			else {
  				cout << "Element not found. ";
  				goto retry;
			}
			bool lim = true;
			for (int a = 0, i = t; i > -1 && i < 4000; ++i) {
				if(ind[i]->date[1] != key[1])
					break;
				ocered(root, i, ind, DBD);
			}
			Obhod(DBD);
//			printQueue(root, t);
			delQueue(root);
			delete root;
  		}
	}
}

/*	for(int i = t; ochered_less(key, ind, i) == 0; ++i){
		cout << setw(4) << i + 1 << ")" << setw(30)<< ind[i]->fio << "  " << setw(3) << ind[i]->numDep << "  " << setw(22) << ind[i]->position << "  " << setw(10) << ind[i]->date << endl;
		++kol;
	}
	cout << "Amount of element: " << kol << endl;*/
