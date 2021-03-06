//Implementation of Trie data structure for binary numbers
//Method taken from http://codeforces.com/contest/706/submission/20966455
/*  Usage details:
 *  First call init() in main
 *  for add, call add(number, count), count can be both positive (insertion) or negative (deletion)
 *  for finding maximum value of "n xor m" for given n, call max(n)
 */

const int LN  = 29;                 //equals ceil(log2(n)), where n is the maximum number to be inserted
const int MAX = 2e5 + 5;            //equals number of elements which can be inserted
const int LIM = MAX * LN;

struct node {
	int cnt;
	node *go[2];
};

static node trie_allocator[LIM] = {};
static int trie_allocated = 0;

node* trie = NULL;

inline node* alloc_item() {
	node *res = trie_allocator + (trie_allocated++);
	res->cnt = 0;
	res->go[0] = res->go[1] = NULL;
	return res;
}

inline int cnt(node* t) {
	return t ? t->cnt : 0;
}

//Complexity : O(LN)
void add(node* t, int n, int idx, int inc) {
	t->cnt += inc;
	if (idx == -1) {
		return;
	}
	int i = ((n & (1 << idx)) != 0) ? 1 : 0;
	if (!t->go[i]) {
		t->go[i] = alloc_item();
	}
	add(t->go[i], n, idx - 1, inc);
}

//Complexity : O(LN)
void max(node* t, int n, int idx, int *res) {
	if (!(cnt(t->go[0]) || cnt(t->go[1]))) {
		return;
	}
	int i = ((n & (1 << idx)) != 0) ? 0 : 1;
	if (!cnt(t->go[i])) {
		i = !i;
		(*res) = (*res) * 2;
	}
	else {
		(*res) = (*res) * 2 + 1;
	}
	max(t->go[i], n, idx - 1, res);
}

//Prints the content of Trie for debugging purpose
void print(node* t) {
	static char out_buffer[1000];
	static char* bufptr = out_buffer;
	if (!t) {
		return;
	}
	*bufptr = '\0';
	int i, outcnt = cnt(t) - cnt(t->go[0]) - cnt(t->go[1]);
	for (i = 0; i < outcnt; i++) {
		puts(out_buffer);
	}
	for (i = 0; i < 2; i++) {
		*(bufptr++) = '0' + i;
		print(t->go[i]);
		bufptr--;
	}
}

void add(int n, int inc) {
	add(trie, n, LN, inc);
}

int max(int n) {
	int res = 0;
	max(trie, n, LN, &res);
	return res;
}

void init() {
	trie = alloc_item();
	add(0, 1);
}