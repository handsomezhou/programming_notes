/*************************************************************************
    Function:实现国际象棋中的马遍历棋盘
    Purpose: 深入对栈的理解，熟悉算法思想的具体实现
    Author:  ZJQ
    Date:	 2013-06-20
    Remark:  本程序采用深度优先搜索的思想,在CHESS_UNIT*CHESS_UNIT的棋盘中,
            从编号为START_POS位置按一定的方向(一个格子最多可走的方向为8个,
            最少可走的为2个)顺序开始遍历棋盘,直至找到一条可行路径或确认无
            可达路径.理论上可以从任意棋盘大小的任意位置开始遍历棋盘,但实际
            上限于计算机的性能,实现棋盘大小(5*5)/(6*6)任意位置的遍历路径的
            快速查找,(7*7)/(8*8)部分位置的遍历路径的快速查找.
    Version: 0.1
*************************************************************************/

#include <stdio.h>
#include <assert.h>

#define TRUE	1
#define FALSE   0
typedef int BOOL;

#define CHESS_UNIT     8    //国际象棋棋盘格子数(8*8),也可设置为7/6/5
#define START_POS      9    //起始位置,从棋盘编号为0及(0,0)位置往右数起,此位置(y,x)也就是(START_POS/CHESS_UNIT,START_POS%CHESS_UNIT)


#define CHESS_CELL_NUM  CHESS_UNIT*CHESS_UNIT
#define CHESS_CELL_MIN	0
#define CHESS_CELL_MAX  CHESS_CELL_NUM-1


#define CHESS_DIRECTION 8
#define CHESS_DIREC_MAX 7
#define CHESS_DIREC_MIN 0

#define CHESS_MAX_X		CHESS_UNIT-1
#define CHESS_MAX_Y		CHESS_UNIT-1
#define CHESS_MIN_X		0
#define CHESS_MIN_Y 	0

#define CHESS_NO_CELL	-1

//栈操作相关
#define PUSH_FALIED		-1
#define PUSH_SUCCESS	0
#define POP_FALIED		-1
#define POP_SUCCESS		0

#define START	1
#define END		0

//国际象棋格子
typedef struct{
	int x;
	int y;
}Cell;


//马移动方向最多8个:
#if 0
(y-2,x+1);
(y-2,x-1);
(y-1,x+2);
(y-1,x-2);

(y+1,x+2);
(y+1,x-2);
(y+2,x+1);
(y+2,x-1)
#endif

//国际象棋马移动方向
typedef struct{
	int x;
	int y;
}Direction;

typedef struct{
	Cell cell;	//棋格坐标
	Direction direction;//下一步所走方向
	int w;//方向下标
	int n;//棋盘格子标号:0~63
	int m;//遍历顺序标号
	BOOL isempty;//判断此处是否为空(即是否下子)
}Chess;

typedef struct{
    Chess chess[CHESS_CELL_NUM];
    int start;//开始位置
    int finish;//结束位置
    int point;//堆指针指向位置
}Stack;


/*初始化马走的方向*/

void init_direc(Direction *dir);	//ok
void set_direc(Direction *dir, int y, int x);//ok
void show_direc(Direction *dir);	//ok
Direction get_direc_y_x(const Direction *dir, int w);


//初始化棋盘
void init_chess(Chess *chess);	//OK
void show_chess(Chess *chess);//OK

//根据当前格子标号,然后方向w ,得出下一个格子的位置
int next_chess(Chess *chess, int n, const Direction *direc, int w);
//判断下一个格子是否合法(越界)
BOOL is_legal_next_chess(Chess *chess, int n,const Direction *direc,int w);
BOOL is_legal_curr_chess(Chess *chess, int n);	//当前棋格是否合法

void chess_push_status(Chess *chess, int n, const Direction *direc, int w, const Stack * sk);

void chess_pop_status(Chess *chess, int n);



//根据坐标(y,x)得到棋格标号n(0~CHESS_UNIT*CHESS_UNIT-1)
int get_cell_n(Cell *cell);		//OK
//根据棋格标号n(0~63)得到(y,x)
Cell get_cell_y_x(int n);			//OK

//栈相关函数
void init_stack(Stack *sk);//初始化栈
int push_stack(Stack *sk, const Chess *Chess);//入栈
int pop_stack(Stack *sk);//出栈
BOOL is_full_stack(Stack *sk);//是否栈满
BOOL is_empty_stack(Stack *sk);//是否为空栈
Chess get_top_stack(Stack *sk);//获取栈顶元素
int get_depth_stack(const Stack *sk);//获取栈中元素个数
void show_stack(Stack *sk);

/*一些基本拷贝函数*/
Cell *cell_cpy(Cell *dest,const Cell *src);
Direction *direction_cpy(Direction *dest, const Direction *src);
Chess *chess_cpy(Chess *dest, const Chess *src);


int main(void)
{
	Direction direc[8];
    init_direc(direc);
    //show_direc(direc);

	Chess chess[CHESS_CELL_NUM];
	Chess ces;
	init_chess(chess);
	//printf("如果经过一段时间没有出现结果,那么这个位置遍历棋盘将会需要很久的时间,建议换个位置(n)进行遍历,或将棋盘边长(CHESS_UNIT)设置小些!\n");
	printf("If the results do not appear after a period of time, then the board will need to traverse this position long time,\
	it is recommended to change the position (n) traversal, or the board side (CHESS_UNIT) set smaller!\n");
	Stack stk;
	init_stack(&stk);
	int runnig=START;
	int i=0;
	int n=START_POS;//起始格子编号为n(0<=n<CHESS_UNIT*CHESS_UNIT)
	int w=0;//方向
	int m=0;//格子编号

	while(runnig){
		for(i=w; i<CHESS_DIRECTION; i++){
		//printf("2\n");
			if((m=next_chess(chess,n,direc,w))!=CHESS_NO_CELL){
				//将当前格子状态保存在栈中
				chess_push_status(chess,n,direc,w,&stk);//保存棋盘状态
				push_stack(&stk,&chess[n]);	//入栈

				if(get_depth_stack(&stk)==stk.finish-1){
					n=m;
					w=-1;
					chess_push_status(chess,n,direc,w,&stk);//保存棋盘状态
					push_stack(&stk,&chess[n]);	//入栈
				}

				if(TRUE==is_full_stack(&stk)){	//严格按照符合条件入栈,则栈满了就证明棋盘遍历了一遍
					runnig=END;
					break;
				}

				n = m;//进入下一个格子继续进行判断
				w = 0;//从规定方向开始
				break;
			}else{
				w++;
				if(w>CHESS_DIREC_MAX){//如果大于最大方向证明这个点无路可走,返回上一个点
					//出栈
					//将栈顶格子所在位置恢复为未入栈状态,继续使用
					do{
						if(TRUE==is_empty_stack(&stk)){
							printf("No reachable route!\n");
							runnig=END;
							break;
						}else{
							ces=get_top_stack(&stk);
							n=ces.n;
							w=++ces.w;

							chess_pop_status(chess,n);
							pop_stack(&stk);
						}
					}while(w>CHESS_DIREC_MAX);

					break;
				}
				continue;
			}
		}

	}

	show_stack(&stk);
	printf("\n");
	show_chess(chess);

	return 0;
}

void init_direc(Direction *dir)
{
#if 0
    dir[0].y = -2;
    (*(dir+0)).x = 1;

    (*(dir+1)).y = -2;
    (*(dir+1)).x = -1;

     dir[2].y = -1;
     dir[2].x = 2;

     dir[3].y = -1;
     dir[3].x = -2;

     dir[4].y = 1;
     dir[4].x = 2;

     dir[5].y = 1;
     dir[5].x = -2;

     dir[6].y = 2;
     dir[6].x = 1;

     dir[7].y = 2;
     dir[7].x = -1;
#else
	set_direc(&dir[0],-2,1);
	set_direc(&dir[1],-2,-1);
	set_direc(&dir[2],-1,2);
	set_direc(&dir[3],-1,-2);
	set_direc(&dir[4],1,2);
	set_direc(&dir[5],1,-2);
	set_direc(&dir[6],2,1);
	set_direc(&dir[7],2,-1);
#endif
}

void set_direc(Direction *dir, int y, int x)
{
	dir->y = y;
	dir->x = x;

}

void show_direc(Direction *dir)
{
    int n = 8;
    int i = 0;
    for(i=0; i<n; i++){
        printf("(y,x)<->(%2d,%2d)\n",dir[i].y,dir[i].x);
    }
}

Direction get_direc_y_x(const Direction *dir, int w)
{
	assert(NULL!=dir);
	assert(w>=CHESS_DIREC_MIN-1&&w<=CHESS_DIREC_MAX);
	Direction direction;
	if(w==CHESS_DIREC_MIN-1){
		direction.y=0;
		direction.x=0;
	}else{
		direction.y = dir[w].y;
		direction.x = dir[w].x;
	}


	return direction;
}

void init_chess(Chess *chess)
{
	int x=0;
	int y=0;
	int k=0;

	for(y=0; y<CHESS_UNIT; y++){
		for(x=0; x<CHESS_UNIT; x++,k++){
			chess[k].cell.x=x;
			chess[k].cell.y=y;

			chess[k].direction.x=0;
			chess[k].direction.y=0;

			chess[k].w = -1;
			chess[k].m = 0;
			chess[k].n = k;

			chess[k].isempty=TRUE;
		}
	}
}

void show_chess(Chess *chess)
{
	int x=0;
	int y=0;
	int k=0;

	for(y=0; y<CHESS_UNIT; y++){
		for(x=0; x<CHESS_UNIT; x++,k++){
			printf("%2d ",chess[k].m);
			// printf("%2d:(%2d,%2d) ",chess[k].n,chess[k].cell.y,chess[k].cell.x);
		}
		printf("\n");
	}
}


int next_chess(Chess *chess, int n, const Direction *direc, int w)
{
	assert(NULL!=chess);
	assert(NULL!=direc);
	assert(n>=CHESS_CELL_MIN&&n<=CHESS_CELL_MAX);
	assert(w>=CHESS_DIREC_MIN&&w<=CHESS_DIREC_MAX);
	Cell cell;
	int m;
	if(is_legal_next_chess(chess,n,direc,w)==TRUE){
		cell.x=chess[n].cell.x+direc[w].x;
		cell.y=chess[n].cell.y+direc[w].y;
		m=get_cell_n(&cell);
		return m;
	}else{
		return CHESS_NO_CELL;
	}
}

//判断下一个格子是否合法(越界),并且是否已经下子
BOOL is_legal_next_chess(Chess *chess, int n,const Direction *direc,int w)
{
	assert(NULL!=chess);
	assert(NULL!=direc);
	assert(n>=CHESS_CELL_MIN&&n<=CHESS_CELL_MAX);
	assert(w>=CHESS_DIREC_MIN&&w<=CHESS_DIREC_MAX);

	int m;
	Cell cell;

	chess[n].direction.x = direc[w].x;
	chess[n].direction.y = direc[w].y;
	cell.x=chess[n].cell.x+chess[n].direction.x;
	cell.y=chess[n].cell.y+chess[n].direction.y;
	m=get_cell_n(&cell);

	if(cell.x>=CHESS_MIN_X&&cell.x<=CHESS_MAX_X\
		&&cell.y>=CHESS_MIN_Y&&cell.y<=CHESS_MAX_Y){
		if(TRUE==chess[m].isempty){
			return TRUE;
		}else{
			return FALSE;
		}
	}else{
		return FALSE;
	}
}

BOOL is_legal_curr_chess(Chess *chess, int n)
{
	assert(NULL!=chess);
	//assert(n>=CHESS_CELL_MIN&&n<=CHESS_CELL_MAX);

	if(n>=CHESS_CELL_MIN&&n<=CHESS_CELL_MAX){
		if(TRUE==chess[n].isempty){
			return TRUE;
		}else{
			return FALSE;
		}
	}else{
		return FALSE;
	}

}

void chess_push_status(Chess *chess, int n, const Direction *direc, int w, const Stack * sk)
{
		assert(NULL!=chess);
		assert(NULL!=direc);
		assert(n>=CHESS_CELL_MIN&&n<=CHESS_CELL_MAX);
		assert(w>=CHESS_DIREC_MIN-1&&w<=CHESS_DIREC_MAX);

		chess[n].cell=get_cell_y_x(n);
		chess[n].direction=get_direc_y_x(direc,w);
		chess[n].isempty=FALSE;
		chess[n].n = n;
		chess[n].m = get_depth_stack(sk);
		chess[n].w = w;
		//printf("(%d,%d),(%d,%d)",chess[n].cell.y,chess[n].cell.x,chess[n].direction.y,chess[n].direction.x);
}

void chess_pop_status(Chess *chess, int n)
{
	assert(NULL!=chess);
	assert(n>=CHESS_CELL_MIN&&n<=CHESS_CELL_MAX);

	chess[n].cell=get_cell_y_x(n);
	chess[n].direction.x=0;
	chess[n].direction.y=0;
	chess[n].w=-1;
	chess[n].isempty=TRUE;
	chess[n].n = n;
	chess[n].m = 0;
}

int get_cell_n(Cell *cell)
{
	int n;
	assert(NULL!=cell);
	n=(cell->y)*CHESS_UNIT+cell->x;

	return n;
}
Cell get_cell_y_x(int n)
{
	Cell cell;
	assert(n>=CHESS_CELL_MIN&&n<=CHESS_CELL_MAX);
	cell.y = n/CHESS_UNIT;
	cell.x = n%CHESS_UNIT;

	return cell;
}


void init_stack(Stack *sk)
{
    int x=0;
    int y=0;
    int k=0;

    sk->start=0;	//在栈操作过程中保持不变
    sk->finish=CHESS_CELL_NUM;//在栈操作过程中保持不变

    sk->point=0;

    for(y=0; y<CHESS_UNIT; y++){
        for(x=0; x<CHESS_UNIT; x++,k++){
            sk->chess[k].cell.x=0;
            sk->chess[k].cell.y=0;

          	sk->chess[k].direction.x=0;
          	sk->chess[k].direction.y=0;

			sk->chess[k].w=-1;

			sk->chess[k].n=k;

			sk->chess[k].isempty=TRUE;
        }
    }
}


int push_stack(Stack *sk, const Chess *chess)
{
	assert(NULL!=sk&&NULL!=chess);
	if(TRUE==is_full_stack(sk)){
		return PUSH_FALIED;
	}
	chess_cpy(&(sk->chess[sk->point]),chess);
	sk->point++;

	return PUSH_SUCCESS;
}

int pop_stack(Stack *sk){
	assert(NULL!=sk);
	if(TRUE==is_empty_stack(sk)){
		return POP_FALIED;
	}else{
		sk->point--;
		//没有清除
		return POP_SUCCESS;
	}
}

BOOL is_full_stack(Stack *sk)
{
	assert(NULL!=sk);

	if((sk->point)>=sk->finish){
		return TRUE;
	}else{
		return FALSE;
	}

}

BOOL is_empty_stack(Stack *sk)
{
	assert(NULL!=sk);
	if(sk->point==sk->start){
		return TRUE;
	}else{
		return FALSE;
	}
}

Chess get_top_stack(Stack *sk)
{
	assert(NULL!=sk);

	Chess chess;
	chess_cpy(&chess,&(sk->chess[sk->point - 1]));

	return chess;
}

int get_depth_stack(const Stack *sk)
{
	int depth;
	depth = (sk->point)-(sk->start);

	return depth;
}


void show_stack(Stack *sk)
{
	int i=0;
	for(i=0; i<sk->point; i++){
		#if 0
		printf("\n%2d:(%2d,%2d)->[%d]-[%d]\n",sk->chess[i].n,sk->chess[i].cell.y,sk->chess[i].cell.x,\
			sk->chess[i].w,sk->chess[i].isempty);
		#endif
		printf("%d:(%d,%d)\n",sk->chess[i].n,sk->chess[i].cell.y,sk->chess[i].cell.x);
	}
}



/*一些基本拷贝函数*/
Cell *cell_cpy(Cell *dest,const Cell *src)
{
	assert(NULL!=dest&&NULL!=src);
	Cell *addr = dest;
	addr->y = src->y;
	addr->x = src->x;

	return addr;
}

Direction *direction_cpy(Direction *dest,const Direction *src)
{
	assert(NULL!=dest&&NULL!=src);
	Direction *addr=dest;
	addr->y = src->y;
	addr->x = src->x;

	return addr;
}

Chess *chess_cpy(Chess *dest, const Chess *src)
{
	assert(NULL!=dest&&NULL!=src);
	Chess *addr=dest;
	cell_cpy(&addr->cell,&src->cell);
	direction_cpy(&addr->direction,&src->direction);
	addr->m = src->m;
	addr->n = src->n;
	addr->w = src->w;
	addr->isempty = src->isempty;

	return addr;

}

