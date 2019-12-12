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
    Vertex *left, *right, *equal, *next;
    int Balance;
};

typedef pair<char, double> data_t;

bool second_less(const data_t& d1, const data_t& d2) {
 return d1.second < d2.second;
}

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
	if (ind[q]->date[0] > ind[l]->date[0] ||(ind[q]->date[0] == ind[l]->date[0] && ind[q]->date[1] > ind[l]->date[1]))
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
	while(L < R) {
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

int asd = 0;

inline void B2insert(record* D, Vertex *&p) {
    if (p == NULL) {
        p = new Vertex;
        p->data = D;
        ++asd;
		p->equal = NULL;
        p->left = NULL;
		p->right = NULL;
        p->Balance = 0;
        VR = true;
    } else {
        if (strcmp(D->date, p->data->date) < 0) {
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
        } else if (strcmp(D->date, p->data->date) > 0) {
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
        
        } else if (strcmp(D->date, p->data->date) == 0)
                B2insert(D, p->equal);
    }
}

void ocered(queue_q*& p, int &t, record** ind, Vertex *&DBD) {
	if (!p) {
		p = new queue_q;
		p->q = ind[t];
		B2insert(p->q, DBD);
		p->next = NULL;
	} else
		ocered(p->next, t, ind, DBD);
}

void Obhod(Vertex *&p) {
	if (p) {
		Obhod(p->equal);
		Obhod(p->left);
		cout << setw(30) << p->data->fio << "  " << setw(3) << p->data->numDep << "  " << setw(22) << p->data->position << "  " << setw(10) << p->data->date << endl;
        Obhod(p->right);
	}
}

void printQueue(queue_q *&p, int i) {
	if (p) {
		cout << setw(4) << ++i << ")" << setw(30) << p->q->fio << "  " << setw(3) << p->q->numDep << "  " << setw(22) << p->q->position << "  " << setw(10) << p->q->date << endl;
		printQueue(p->next, i);
	}
}

void search(Vertex *&p, string &key) {
	if (p) {
		if (p->data->date > key)
			search(p->left, key);
		else if (p->data->date < key)
			search(p->right, key);	
		if (p->data->date[0] == key[0] & p->data->date[1] == key[1] & p->data->date[2] == key[2] & p->data->date[3] == key[3] & p->data->date[4] == key[4] & p->data->date[5] == key[5] & p->data->date[6] == key[6] & p->data->date[7] == key[7]) {
			search(p->equal, key);
			cout << setw(30) << p->data->fio << "  " << setw(3) << p->data->numDep << "  " << setw(22) << p->data->position << "  " << setw(10) << p->data->date << endl;
		}
	}
}

void freeTree(Vertex *Tree) {
	if (Tree) {
		freeTree(Tree->equal);
		freeTree(Tree->left);
		delete Tree;
		freeTree(Tree->right);
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
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Mediana(int L, int R, vector<data_t> &P) {
	double Sl = 0;
	for (int i = L; i < R; ++i)
		Sl += P[i].second;
	double Sr = P[R].second;
	int m = R;
	while (Sl >= Sr) {
		--m;
		Sl -= P[m].second;
		Sr += P[m].second;
	}
	return m;
}

void Fano(int L, int R, int k, vector<data_t> &P, char **C, int *lenght) {
	if (L < R) {
		++k;
		int m = Mediana(L, R, P);
		for (int i = L; i <= R; ++i) {
			if (i <= m) {
				C[i][k] = 0 + '0'; 
				lenght[i]++;
			} else {
				C[i][k] = 1 + '0'; 
				lenght[i]++;
			}
		}
		Fano(L, m, k, P, C, lenght);
		Fano(m + 1, R, k, P, C, lenght);
	}
}

void ReadBase(vector<data_t> &P_Vect){
	FILE *Base;
	
	map<char, double> DigitP;
	auto Found = DigitP.begin();
	char str;
	unsigned short int digit;
	Base = fopen("testBase2.dat", "rb");
	if (Base == NULL) {
		cout << endl << "!!!  Error open base  !!!" << endl;
		exit(1); 
	} else cout << endl << ">>> File base is OPEN <<<" << endl;
	int count = 0;
	int count_struct = -1;
	while (!feof(Base)) {
		++count_struct;
	
		for (count = 0; count < 64; ++count) {
			fread(&str, sizeof(char), 1, Base);
			Found = DigitP.find(str);
			if (Found == DigitP.end())
				DigitP.insert(pair<char,int>(str,1));
			else 
				(*Found).second++;
		}
	}

	
	double sum = 0;
//	DigitP.erase(' ');
//	DigitP.erase('\0');
	
	for (auto it = DigitP.begin(); it != DigitP.end(); ++it){
//		cout << (*it).first << " ";
		sum += (*it).second;
	}
	cout << endl << "Number of characters in DataBase:  " << sum;
	cout << endl << "Number of structures read:  " << count_struct;
	double P_multipl = 1 / (double)sum;
	double control = 0;
	int i = 0;
	for (auto it = DigitP.begin(); it != DigitP.end(); ++it, ++i) {
	 P_Vect.push_back((*it));
	 P_Vect[i].second *= P_multipl;
	}
	sort(P_Vect.begin(), P_Vect.end(), second_less);
	reverse(P_Vect.begin(), P_Vect.end());
	for (int i = 0; i < P_Vect.size(); ++i)
		control += P_Vect[i].second;
	cout << endl << "Control:  " << control << "(the sum of the probabilities)" << endl;
}

double Entropy(vector<data_t> &P) {
	double sum = 0;
	for (int i = 0; i < P.size(); ++i)
		sum += (P[i].second * log(P[i].second) / log(2));
	sum *= -1;
	return sum;
}

double SrDlin(vector<data_t> &P, int *L){
	double sum = 0;
	for (int i = 0; i < P.size(); ++i)
		sum += P[i].second * L[i];
	return sum;
}

void CoddingBase() {
	vector<data_t> P;
	ReadBase(P);
	int size = P.size();
	
	char **Count_F = new char*[size];
	int *Lenght_F = new int[size];
	for (int i = 0; i < size; ++i) {
		Count_F[i] = new char[30];
		Lenght_F[i] = 0;
		for (int j = 0; j < 30; ++j) 
			Count_F[i][j] = '\0';
	}
	Fano(0, size - 1, 1, P, Count_F, Lenght_F);
	for (int i = 0; i < size; ++i) {
		cout << P[i].first << "   ";
		cout << P[i].second << "\t";
		for (int j = 0; j < 30; ++j) {
			cout << Count_F[i][j];
		}
		cout << "\t" << Lenght_F[i] << endl;
	}
	cout << endl << "Entropy:\t" << Entropy(P) << endl;
	cout << "Average length:\t" << SrDlin(P, Lenght_F) << endl << endl;
	delete []Lenght_F; 	
}

int main() {
	ios_base::sync_with_stdio(false);
    FILE *fp = fopen("testBase2.dat", "rb");
    record* mas = new record[N];
	record** ind = new record*[N];
	for (int i = 0; i < N; ++i)
		ind[i] = &mas[i];
	auto j = fread((record*)mas, sizeof(record), N, fp);
	cout << "Choose:" << endl << "1) Print" << endl <<"2) Sort" << endl << "3) Key" << endl << "4) Coding" << endl << ">> ";
	int act;
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
		while(1) {
  			retry:
  			queue_q *root = NULL;
			Vertex *DBD = NULL;
			cout << "Enter date: ";
			cin >> key;
  			if (key == "-+")
				break;
  			int t = binsearch(ind, key, 0, N - 1);
  			if (t > -1)
  				cout << "First element number is " << t + 1 << endl;
  			else {
  				cout << "Element not found. ";
  				goto retry;
			}
			asd = 0;
			for (int a = 0, i = t; i > -1 && i < 4000; ++i) {
				if(ind[i]->date[1] != key[1])
					break;
				ocered(root, i, ind, DBD);
			}
			Obhod(DBD);
			cout << "->" << asd << "<-" << endl;
//			printQueue(root, t);
			while (1) {
				string key;
				cout << "Enter search key: ";
				cin >> key;
				if (key[0] == '-')
					break;
				search(DBD, key);
			}
			freeTree(DBD);
			delQueue(root);
			delete root;
  		}
	} else if (act == 4) {
		CoddingBase();
	}
}
