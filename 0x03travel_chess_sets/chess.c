/*************************************************************************
    Function:ʵ�ֹ��������е����������
    Purpose: �����ջ����⣬��Ϥ�㷨˼��ľ���ʵ��
    Author:  ZJQ
    Date:	 2013-06-20
    Remark:  ����������������������˼��,��CHESS_UNIT*CHESS_UNIT��������,
            �ӱ��ΪSTART_POSλ�ð�һ���ķ���(һ�����������ߵķ���Ϊ8��,
            ���ٿ��ߵ�Ϊ2��)˳��ʼ��������,ֱ���ҵ�һ������·����ȷ����
            �ɴ�·��.�����Ͽ��Դ��������̴�С������λ�ÿ�ʼ��������,��ʵ��
            �����ڼ����������,ʵ�����̴�С(5*5)/(6*6)����λ�õı���·����
            ���ٲ���,(7*7)/(8*8)����λ�õı���·���Ŀ��ٲ���.
    Version: 0.1
*************************************************************************/

#include <stdio.h>
#include <assert.h>

#define TRUE	1
#define FALSE   0
typedef int BOOL;

#define CHESS_UNIT     8    //�����������̸�����(8*8),Ҳ������Ϊ7/6/5
#define START_POS      9    //��ʼλ��,�����̱��Ϊ0��(0,0)λ����������,��λ��(y,x)Ҳ����(START_POS/CHESS_UNIT,START_POS%CHESS_UNIT)


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

//ջ�������
#define PUSH_FALIED		-1
#define PUSH_SUCCESS	0
#define POP_FALIED		-1
#define POP_SUCCESS		0

#define START	1
#define END		0

//�����������
typedef struct{
	int x;
	int y;
}Cell;


//���ƶ��������8��:
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

//�����������ƶ�����
typedef struct{
	int x;
	int y;
}Direction;

typedef struct{
	Cell cell;	//�������
	Direction direction;//��һ�����߷���
	int w;//�����±�
	int n;//���̸��ӱ��:0~63
	int m;//����˳����
	BOOL isempty;//�жϴ˴��Ƿ�Ϊ��(���Ƿ�����)
}Chess;

typedef struct{
    Chess chess[CHESS_CELL_NUM];
    int start;//��ʼλ��
    int finish;//����λ��
    int point;//��ָ��ָ��λ��
}Stack;


/*��ʼ�����ߵķ���*/

void init_direc(Direction *dir);	//ok
void set_direc(Direction *dir, int y, int x);//ok
void show_direc(Direction *dir);	//ok
Direction get_direc_y_x(const Direction *dir, int w);


//��ʼ������
void init_chess(Chess *chess);	//OK
void show_chess(Chess *chess);//OK

//���ݵ�ǰ���ӱ��,Ȼ����w ,�ó���һ�����ӵ�λ��
int next_chess(Chess *chess, int n, const Direction *direc, int w);
//�ж���һ�������Ƿ�Ϸ�(Խ��)
BOOL is_legal_next_chess(Chess *chess, int n,const Direction *direc,int w);
BOOL is_legal_curr_chess(Chess *chess, int n);	//��ǰ����Ƿ�Ϸ�

void chess_push_status(Chess *chess, int n, const Direction *direc, int w, const Stack * sk);

void chess_pop_status(Chess *chess, int n);



//��������(y,x)�õ������n(0~CHESS_UNIT*CHESS_UNIT-1)
int get_cell_n(Cell *cell);		//OK
//���������n(0~63)�õ�(y,x)
Cell get_cell_y_x(int n);			//OK

//ջ��غ���
void init_stack(Stack *sk);//��ʼ��ջ
int push_stack(Stack *sk, const Chess *Chess);//��ջ
int pop_stack(Stack *sk);//��ջ
BOOL is_full_stack(Stack *sk);//�Ƿ�ջ��
BOOL is_empty_stack(Stack *sk);//�Ƿ�Ϊ��ջ
Chess get_top_stack(Stack *sk);//��ȡջ��Ԫ��
int get_depth_stack(const Stack *sk);//��ȡջ��Ԫ�ظ���
void show_stack(Stack *sk);

/*һЩ������������*/
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
	//printf("�������һ��ʱ��û�г��ֽ��,��ô���λ�ñ������̽�����Ҫ�ܾõ�ʱ��,���黻��λ��(n)���б���,�����̱߳�(CHESS_UNIT)����СЩ!\n");
	printf("If the results do not appear after a period of time, then the board will need to traverse this position long time,\
	it is recommended to change the position (n) traversal, or the board side (CHESS_UNIT) set smaller!\n");
	Stack stk;
	init_stack(&stk);
	int runnig=START;
	int i=0;
	int n=START_POS;//��ʼ���ӱ��Ϊn(0<=n<CHESS_UNIT*CHESS_UNIT)
	int w=0;//����
	int m=0;//���ӱ��

	while(runnig){
		for(i=w; i<CHESS_DIRECTION; i++){
		//printf("2\n");
			if((m=next_chess(chess,n,direc,w))!=CHESS_NO_CELL){
				//����ǰ����״̬������ջ��
				chess_push_status(chess,n,direc,w,&stk);//��������״̬
				push_stack(&stk,&chess[n]);	//��ջ

				if(get_depth_stack(&stk)==stk.finish-1){
					n=m;
					w=-1;
					chess_push_status(chess,n,direc,w,&stk);//��������״̬
					push_stack(&stk,&chess[n]);	//��ջ
				}

				if(TRUE==is_full_stack(&stk)){	//�ϸ��շ���������ջ,��ջ���˾�֤�����̱�����һ��
					runnig=END;
					break;
				}

				n = m;//������һ�����Ӽ��������ж�
				w = 0;//�ӹ涨����ʼ
				break;
			}else{
				w++;
				if(w>CHESS_DIREC_MAX){//������������֤���������·����,������һ����
					//��ջ
					//��ջ����������λ�ûָ�Ϊδ��ջ״̬,����ʹ��
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

//�ж���һ�������Ƿ�Ϸ�(Խ��),�����Ƿ��Ѿ�����
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

    sk->start=0;	//��ջ���������б��ֲ���
    sk->finish=CHESS_CELL_NUM;//��ջ���������б��ֲ���

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
		//û�����
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



/*һЩ������������*/
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

