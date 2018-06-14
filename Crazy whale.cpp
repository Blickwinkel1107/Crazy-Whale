#include"Integrity.h"

//��ʱ����

//ϵͳ����
bool buttondown;
bool buttonup;
bool gameover=false; //�ж��Ƿ���ײ
bool exitgame=false;
IMAGE wImg[Quantity],wImgx[Quantity];
IMAGE bkimg;
int cmd; //�û�����
int cmd_exit;
bool spawn_big=false; //�жϲ���������
bool moving=false; //�ж������Ƿ����ƶ�
int pos[4]={175,255,335,400}; //����yλ������
int level; //����λ��
errno_t err;

//��Ϸ����
int Difficulty;
int dv;
int Interval;
int talknum;
double V_X;
bool isgodmode;
bool talking;
int bonus_score;
int life;
int score_max;
int score;

char str_talk[TALKNUM][128]={
	"���ѽ(^��^)",
	"��ӭ��ŶO(��_��)O��  ",
	"�ҵ��������С�С������",
	"Ӣ�����С�����blue whale�� (��'��'��)",
	"��������ֲе������γ�����ѡ���ԲС��ؿ�(^o^)د",
	"�������six�Ļ����Ǿ�ѡ���������ؿ���(�V_�V)",
	"ɶ�������桮����ȥ����(:3_�c)_�ٺٺ١���",
	"����Ϊ������ȥ�����ܹ����׳��Ե���(��^��)"
	"������Ϊʲô�С�����ȥ�����r(�s���t)�q",
	"��Ҫ��ʵ������",
	"��Ҳû�취��ֹ�㲻��(��(I)��)",
	"��w��s���ߡ��͡����������ϣ�",
	"���ո���Ҿ���������~",
	"�ΰ��Σ��ε������(*/�أ�*)����",
	"���������_(:D)��)_",
	"���Ȳ���ѽ(��^��^) ",
	"ͷ�ϵĽ��ǲ��ǳ������أ������ĶԲ��ԣ�_(:3����)_ ",
	"�������ǰ������������˺ܶ๦����(/�أ�)",
	"emmmmmm�������ͩc(������)/",
	"���е�����_(:�١���)_",
	"���������˺þð�~(^��^)/��",
	"���ò���Ŷ��͵͵����|��^��"
};


//��������
Whale whale;
Rect rect[12];
Bonus bonus[4];
/*
//���������Ϣ�嵥	img		imgx			  x   y   w   h    v_x  v_y
Whale whale��     {wImg[0],wImgx[0]         {75 , 175,58, 48},
Rect comb��       {wImg[1],wImgx[1]			{1000,44, 262,160,V_X,0  },
Rect island1��    {wImg[2],wImgx[2]			{1000,109,57 ,94,V_X,0  },
Rect island2��    {wImg[3],wImgx[3]			{1000,110,70 ,98,V_X,0  },
Rect land��       {wImg[4],wImgx[4]			{1000,136,236,75 ,V_X,0  },
Rect rock��       {wImg[5],wImgx[5]			{1000,335,246,144,V_X,0  },
Rect shrimp��     {wImg[6],wImgx[6]			{1000,265,43, 58 ,V_X,0  },
Rect squid��      {wImg[7],wImgx[7]			{1000,279,12, 94,V_X,0  },
Rect star1��      {wImg[8],wImgx[8]			{1000,428,37, 36 ,V_X,0  },
Rect star2��      {wImg[9],wImgx[9]			{1000,265,43, 39 ,V_X,0  },
Rect weed1��      {wImg[10],wImgx[10]		{1000,261,31 ,219,V_X,0  },
Rect weed2��      {wImg[11],wImgx[11]		{1000,335,37,148,V_X,0  },
Bonus fish1��     {wImg[12],wImgx[12]		{1000,189,39, 32 ,V_X,0  },
Bonus fish2��     {wImg[13],wImgx[13]		{1000,270,51, 25 ,V_X,0  },
Bonus fish3��     {wImg[14],wImgx[14]		{1000,340,41, 20 ,V_X,0  },
Bonus fish4��     {wImg[15],wImgx[15]		{1000,442,42, 18 ,V_X,0  },
*/

//ʱ�����
double dt;
int t0,t1;
int tmpt=t0;
int hit=0;
int start1;
int godtime;
int talktime;

//�ı���Ϣ
char str_score[128];
char str_interval[128];
char str_bonus[128];
char bgm[4][20]={"easy","medium","hard","insane"};

//������Ծ�õ��ı���
int times_jump=0,y0_jump,jumpornot=0;
double t0_jump,t1_jump,dt_jump,V_Y,A_Y;
bool jumping=false;
int cmd_jump;
bool buttonspace;

//������
int main(){
	int i;
	FILE *fpr,*fpw;
	if(err=fopen_s(&fpr,"max.txt","r"))
	{
		puts("Cannot open file max!");
		exit(1);
	}
	fscanf_s(fpr,"%d",&score_max);
	fclose(fpr);
	//����ͼƬ
	loadimgs();
	//������Ч
	loadsfx();
	while(1)
	{
		initgraph(640,SRC_H);
		Difficulty=inter_face();
		closegraph();
		initgraph(SRC_W,SRC_H);
		if(Difficulty==-1) break;
		switch(Difficulty) {
			case 1: {
				dv=1;
				Interval=2000;
				V_X=-125;
				V_Y=-0.2;
				A_Y=0.0002;
				break;
			}
			case 2: {
				dv=2;
				Interval=1000;
				V_X=-250;
				V_Y=-0.4;
				A_Y=0.0008;
				break;
			}
			case 3: {
				dv=5;
				Interval=500;
				V_X=-500;
				V_Y=-0.8;
				A_Y=0.0032;
				break;
			}
			case 4: {
				dv=15;
				Interval=250;
				V_X=-1000;
				V_Y=-1.6;
				A_Y=0.0128;
				break;
			}
		}
		Data data[Quantity]={
			{75,175,58,48,0,V_Y},
			{1000,44,262,160,V_X,0},
			{1000,109,57,94,V_X,0},
			{1000,110,70,98,V_X,0},
			{1000,136,236,75,V_X,0},
			{1000,335,246,144,V_X,0},
			{1000,265,43,58,V_X,0},
			{1000,279,12,94,V_X,0},
			{1000,428,37,36,V_X,0},
			{1000,265,43,39,V_X,0},
			{1000,261,31,219,V_X,0},
			{1000,335,37,148,V_X,0},
			{1000,189,39,32,V_X,0},
			{1000,270,51,25,V_X,0},
			{1000,340,41,20,V_X,0},
			{1000,442,42,18,V_X,0},
		};
		//Sleep(10000);
		//�����ʼ��
		whale.img=wImg[0];
		whale.imgx=wImgx[0];
		whale.x=data[0].x;
		whale.y=data[0].y;
		whale.h=data[0].h;
		whale.w=data[0].w;
		whale.v_x=data[0].v_x;
		whale.v_y=data[0].v_y;
		whale.a_y=A_Y;
		whale.st_x=data[0].st_x;
		whale.st_y=data[0].st_y;
		for(i=1; i<Quantity; i++) {
			if(i<Q_Rect) {
				rect[i].img=wImg[i];
				rect[i].imgx=wImgx[i];
				rect[i].x=data[i].x;
				rect[i].y=data[i].y;
				rect[i].h=data[i].h;
				rect[i].w=data[i].w;
				rect[i].v_x=data[i].v_x;
				rect[i].v_y=data[i].v_y;
				rect[i].st_x=data[i].st_x;
				rect[i].st_y=data[i].st_y;
			}
			else {
				bonus[i-Q_Rect].img=wImg[i];
				bonus[i-Q_Rect].imgx=wImgx[i];
				bonus[i-Q_Rect].x=data[i].x;
				bonus[i-Q_Rect].y=data[i].y;
				bonus[i-Q_Rect].h=data[i].h;
				bonus[i-Q_Rect].w=data[i].w;
				bonus[i-Q_Rect].v_x=data[i].v_x;
				bonus[i-Q_Rect].v_y=data[i].v_y;
				bonus[i-Q_Rect].st_x=data[i].st_x;
				bonus[i-Q_Rect].st_y=data[i].st_y;
			}
		}
		for(i=0; i<Quantity; i++) {
			if(i<Q_Rect) {
				rect[i].st_x=rect[i].x;
				rect[i].st_y=rect[i].y;
				rect[i].move=false;
			}
			else {
				bonus[i-Q_Rect].st_x=bonus[i-Q_Rect].x;
				bonus[i-Q_Rect].st_y=bonus[i-Q_Rect].y;
				bonus[i-Q_Rect].move=false;
			}
		}
		setlinestyle(PS_SOLID | PS_ENDCAP_ROUND,3);
		//���岿�ֲ�������
		//����
		//��Ϸ����
		//�����ʼ��
		settxt();
		settextcolor(WHITE);
		setbkmode(TRANSPARENT);
		//��������λ��
		/*
		BeginBatchDraw();
		for(i=0;i<Q_Rect;i++){
		MOUSEMSG m;
		while(true){
		m=GetMouseMsg();
		if(m.mkLButton) break;
		flush();
		outtxt(true);
		rect[i].x=m.x;
		rect[i].y=m.y;
		put(rect[i]);
		FlushBatchDraw();
		}
		}
		for(i=0;i<Q_Bonus;i++){
		MOUSEMSG m;
		while(true){
		m=GetMouseMsg();
		if(m.mkLButton) break;
		flush();
		outtxt(true);
		bonus[i].x=m.x;
		bonus[i].y=m.y;
		put(bonus[i]);
		FlushBatchDraw();
		}
		}
		EndBatchDraw();
		closegraph();
		return 0;
		*/
		while(1)
		{
			flush();
			BeginBatchDraw(); //��ʼ������ͼ
			t0=clock(); //��Ϸ��ʼʱ��
			start1=t0;
			life=3;
			bonus_score=0;
			gameover=false;
			exitgame=false;
			playbgm();
			while(!gameover&&life>0)
			{
				//��������
				settxt();
				//��ȡ��ʼʱ��
				srand((unsigned int)(time(NULL))); //�������������
				dice(true,false);
				level=1;
				godtime=0;
				isgodmode=false;
				talking=false;
				talktime=0;
				talknum=0;
				stopall();
				whale.y=175;
				jumping=false;
				moving=false;
				times_jump=0;
				//��ʼ��Ϸ
				while(true) {
					flush(); //�ػ汳��ͼ
					t1=clock(); //������ʱ��
					dt=(t1-tmpt)*0.001;
					outtxt(false); //������Ͻ��ı�
					if(gameover) {
						stopbgm();
						mciSendString("play gameover from 0",NULL,0,NULL);
						Sleep(1000);
						mciSendString("play youareweak from 0",NULL,0,NULL);
						cleardevice();
						char str[128];
						sprintf_s(str,"������ʣ��:%d",life-1);
						outtextxy(SRC_W/2-textwidth(str)/2,SRC_H/2-textheight(str)/2,str);
						FlushBatchDraw();
						Sleep(2000);
						playbgm();
						break;
					}
					if(exitgame) break;
					//�޵�״̬
					if(isgodmode) {
						if(godtime==0) godtime=t1;
						if(t1-godtime>Interval_godmode) {
							isgodmode=false;
							godtime=0;
						}
					}
					//˵��
					if(!talking && t1-talktime>Interval_notalk) {
						talking=true;
						talktime=t1;
					}
					if(talking && t1-talktime>Interval_talk) {
						talking=false;
						talknum++;
						talktime=t1;
					}
					if(!moving) {
						getcmd();
						switch(cmd) {
						case UP: {
							if(level>1) {
								level--;
								moving=true;
								mciSendString("play move from 0",NULL,0,NULL);
							}
							else {
								mciSendString("play cantmove from 0",NULL,0,NULL);
							}
							break;
						}
						case DOWN: {
							if(level<4) {
								level++;
								moving=true;
								mciSendString("play move from 0",NULL,0,NULL);
							}
							else {
								mciSendString("play cantmove from 0",NULL,0,NULL);
							}
							break;
						}
						case ESC:exitgame=true; break;
						}
					}
					if(moving) {
						switch(cmd) {
						case UP: {
							whale.y-=dv;
							if(fabs(whale.y-pos[level-1])<=dv) {
								moving=false;
								whale.y=pos[level-1];
							}
							break;
						}
						case DOWN: {
							whale.y+=dv;
							if(fabs(whale.y-pos[level-1])<=dv) {
								moving=false;
								whale.y=pos[level-1];
							}
							break;
						}
						case ESC:exitgame=true; break;
						}
					}
					if(level==1)
					{
						getcmd_jump();
						jump_main();
					}
					put(whale); //��������
					if((t1-start1)>Interval) {
						if(hit%20==0) {
							dice(false,true);
							start1=t1;
							hit++;
						}
						else {
							dice(true,false);
							start1=t1;
							hit++;
						}
					}
					moveall(); //�ƶ�����
					FlushBatchDraw(); //ˢ�»���
					Sleep(1);
				}
				life--;
				gameover=false;
			}
			if(!exitgame) gameover=true;
			EndBatchDraw(); //������������
			flush();
			if(gameover) {
				stopbgm();
				score=((t1-t0)/1000+bonus_score)*Difficulty*Difficulty;
				sprintf_s(str_score,"�������յ÷�:%d",score);
				outtextxy(SRC_W/2-textwidth(str_score)/2,SRC_H/2-textheight(str_score)/2,str_score);
				Sleep(3000);
				if(err=fopen_s(&fpw,"max.txt","w"))
				{
					puts("Cannot open file max.txt");
					exit(1);
				}
				if(score>=score_max)
				{
					flush();
					score_max=score;
					sprintf_s(str_score,"���������µļ�¼:%d��",score);
					outtextxy(SRC_W/2-textwidth(str_score)/2,SRC_H/2-textheight(str_score)/2,str_score);
					Sleep(3000);
				}
				fprintf(fpw,"%d",score_max);
				fclose(fpw);
			}
			flush();
			bool exitjudge=false;
			int t0_exitj,t1_exitj;
			t0_exitj=clock();
			BeginBatchDraw();
			while(1)
			{
				int dt,t;
				t1_exitj=clock();
				dt=t1_exitj-t0_exitj;
				if(dt<1000)
				{
					t=5;
					flush();
					print_exit(t);
				}
				else if(dt>=1000&&dt<2000)
				{
					t=4;
					flush();
					print_exit(t);
				}
				else if(dt>=2000&&dt<3000)
				{
					t=3;
					flush();
					print_exit(t);
				}
				else if(dt>=3000&&dt<4000)
				{
					t=2;
					flush();
					print_exit(t);
				}
				else if(dt>=4000)
				{
					t=1;
					flush();
					print_exit(t);
				}
				FlushBatchDraw();
				getcmd_exit();
				if(cmd_exit==ESC)
				{
					exitgame=true;
					break;
				}
				else if(cmd_exit==UP)
				{
					exitgame=false;
					break;
				}
				else if(t1_exitj-t0_exitj>5000)
				{
					exitgame=true;
					break;
				}
			}
			EndBatchDraw();
			flush();
			cmd=0;
			if(exitgame) {
				stopbgm();
				char str[128];
				sprintf_s(str,"лл���룡");
				outtextxy(SRC_W/2-textwidth(str)/2,SRC_H/2-textheight(str)/2,str);
				Sleep(2000);
				break;
			}
		}
	}
	closegraph();
	return 0;
}

