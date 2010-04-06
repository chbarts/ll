typedef struct ll {
    int tag;
    void *data;
    struct ll *nxt;
} ll;

ll *get_next(ll * node);
int get_tag(ll * node);
void *get_data(ll * node);
ll *get_end(ll * node);
ll *append_node(ll * cur, ll * new);
ll *prepend_node(ll * cur, ll * new);
ll *new_node(int tag, void *data, ll * next);
void free_all_nodes(ll * beg, int d);
