#include "cachelab.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define rep(i, a, b) for(int i = a; i <= b; i++)
#define per(i, a, b) for(int i = a; i >= b; i--)

int h, v, s, b, E, t, S;

int hit_cnt, miss_cnt, alter_cnt;

char path[1005];

typedef struct {
    int valid;
    unsigned long long tag;
    int stamp;
}Cache_line, *Cache_gro, **Cache;

Cache cache = NULL;

void init_cache() {
    cache = (Cache)malloc(sizeof(Cache_gro) * S);
    rep(i, 0, S - 1) {
        cache[i] = (Cache_gro)malloc(sizeof(Cache_line) * E);
        rep(j, 0, E - 1) {
            cache[i][j].valid = 0;
            cache[i][j].tag = -1;
            cache[i][j].stamp = -1;
        }
    }
}

void update_stamp() {
    rep(i, 0, S - 1) rep(j, 0, E - 1)
        if(cache[i][j].valid == 1)
            cache[i][j].stamp++;
}

void update(unsigned long long address) {
    int setIndex = (address >> b) & ((-1ull) >> (64 - s));
    unsigned long long tag_add = address >> (b + s);
    
    // whether hit
    rep(i, 0, E - 1) {
        if(cache[setIndex][i].tag == tag_add) {
            cache[setIndex][i].stamp = 0;
            hit_cnt++;
            if(v) printf(" hit");
            return;
        }
    }
    miss_cnt++;
    if(v) printf(" miss");

    // whether empty line
    rep(i, 0, E - 1) {
        if(cache[setIndex][i].valid == 0) {
            cache[setIndex][i].tag = tag_add;
            cache[setIndex][i].valid = 1;
            cache[setIndex][i].stamp = 0;
            return;
        }
    }
    alter_cnt++;
    if(v) printf(" eviction");

    // alter
    int mx = -1, id = -1;
    rep(i, 0, E - 1) {
        if(cache[setIndex][i].stamp > mx) {
            mx = cache[setIndex][i].stamp;
            id = i;
        }
    }
    cache[setIndex][id].stamp = 0;
    cache[setIndex][id].tag = tag_add;
}

void process() {
    FILE *f = fopen(path, "r");

    char opt;
    unsigned long long address;
    int size;

    while(fscanf(f, " %c %llx,%d", &opt, &address, &size) != EOF) {
        if(v) printf("%c %llx,%d", opt, address, size);
        switch(opt) {
            case 'I': break;
            case 'L': update(address); break;
            case 'M': update(address); update(address); break;
            case 'S': update(address); break;
        }
        if(v) printf("\n");
        update_stamp();
    }

    fclose(f);
}

void free_cache() {
    rep(i, 0, S - 1)
        free(cache[i]);
    free(cache);
}

int main(int argc, char* argv[]) {

    int opt;
    while(-1 != (opt = (getopt(argc, argv, "hvs:E:b:t:")))) {
        switch(opt) {
            case 'h': h = 1; break; // pass
            case 'v': v = 1; break;
            case 's': s = atoi(optarg); S = 1 << s; break;
            case 'E': E = atoi(optarg); break;
            case 'b': b = atoi(optarg); break;
            case 't': strcpy(path, optarg); break;
            default: break;
        }
    }

    init_cache();
    process();
    free_cache();
    printSummary(hit_cnt, miss_cnt, alter_cnt);

    return 0;
}
