#include "cachelab.h"
#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include<string.h>
#include<getopt.h>
#include<unistd.h>
int opc;
int traceOut;
char trace[100];
int s,e,b,snum;
char op;
int num;
int hit,miss,evection;
unsigned long long tagID,setID,adr;
int *point;
struct block
{
    /* data */
    int valid,use;
    unsigned long long tag;
}** cash;
void initial(){
    cash = (struct block**)calloc(s,sizeof(struct block *));
    int i;
    for(i=0;i<s;i++){
        cash[i] = (struct block*)calloc(e,sizeof(struct block));
    }
    point = (int*)calloc(s,sizeof(int));
}
int searchCache(){
    int i;
    for(i=0;i<e;i++){
        if(cash[setID][i].valid!=0&&cash[setID][i].tag==tagID){
            cash[setID][i].use = 1;
            return i;   
        }
    }
    return -1;//未命中
}
void changecache(){
    while(cash[setID][point[setID]].use!=0){
        cash[setID][point[setID]].use = 0;
        point[setID] = (point[setID]+1)%e;
    }
    if(cash[setID][point[setID]].valid!=0){    //如果是替换
        evection++;
        if(traceOut==1){
            printf("eviction ");
        }
    }
    cash[setID][point[setID]].use= 1;
    cash[setID][point[setID]].valid = 1;
    cash[setID][point[setID]].tag = tagID;
    point[setID] = (point[setID]+1)%e;
}
void checkCache(){
    if(searchCache()==-1){
        miss++;
        if(traceOut==1){
            printf("miss ");
        }
        changecache();
    }else{
        hit++;
        if(traceOut==1){
            printf("hit ");
        }
    }
}
void printS(int hits,int misses,int evictions){
    printf("hits:%d misses:%d evictions:%d\n",hits,misses,evictions);
    FILE * output_fp = fopen(".csim_results","w");
    assert(output_fp);
    fprintf(output_fp,"%d %d %d\n",hits,misses,evictions);
    fclose(output_fp);
}

int main(int argc,char *argv[])
{
    while((opc=getopt(argc,argv,"vs:E:b:t:"))!=-1){
        switch (opc)
        {
        case 'v':
            traceOut  = 1;
            break;
        case 's':
            s = 1<<atoi(optarg);   //总组数，2的s次方
            snum = atoi(optarg);
            break;
        case 'E':
            e = atoi(optarg);  //每组的行数
            break;
        case 'b':
            b = atoi(optarg);   //块的大小
            break;
        case 't':
            strcpy(trace,optarg);  //内存访问路径文件名
        default:
            break;
        }
    }
    initial();
    FILE *in = fopen(trace,"r");
    while (fscanf(in," %c%llx, %d",&op,&adr,&num) != EOF){
        if(traceOut==1){
            printf("%c %llx,%d ",op,adr,num);
        }
        setID = (adr>>b)&((1<<snum)-1);
        tagID = adr>>(b+snum);
        switch(op){
            case 'M':
                checkCache();
                checkCache();
                if(traceOut==1){
                    puts("");
                }
                break;
            case 'L':
                checkCache();
                if(traceOut==1){
                    puts("");
                }
                break;
            case 'S':
                checkCache();
                if(traceOut==1){
                    puts("");
                }
                break;
            default:
                if(traceOut==1){
                    puts("");
                }
                break;

        }
    }
    fclose(in);
    printS(hit, miss, evection);
    return 0;
}
