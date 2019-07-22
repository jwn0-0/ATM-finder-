#define _CRT_SECURE_NO_WARNINGS_
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define TEAM 8

void cal();
void data(int, int, int);
void sort();
void dist(int);
void dist_print();
void team();

int month = 0;
int point[TEAM] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int point2[TEAM] = { 0, 0, 0, 0, 0, 0, 0, 0 };
int point3[TEAM] = { 0, 0, 0, 0, 0, 0, 0, 0 };
struct travel {
	int num;
	char name[10];
};
struct travel_index {
	int num;
	struct travel *key;
};
typedef struct pp {
	char team[15];
	int point;
	int point2;
	int point3;
	int t_bonus;
	char country[10];
	int pref;
}pp;
struct travel travel[8] = { 0,"" };
struct travel_index travel_index[8];
pp dat[TEAM];
pp bl;

void main()
{

	int bonus;
	printf("Our program provides each department's total average by maximum heap sort.\nWe recieve department's score by text file.\n");
	for (int i = 0; i < TEAM; i++) {
		dat[i].point = 0;
		dat[i].point2 = 0;
	}
	printf("\nPlease enter the Bonus(Quarter of the year)\nBONUS : ");
	scanf("%d", &bonus);

	FILE *fp;
	fp = fopen("first.txt", "r");
	if (fp == NULL);
	else {
		printf("\n==========First Quarter Of The Year(1/4)===========\n");
		month++;
		cal(fp);
	}

	fp = fopen("second.txt", "r");
	if (fp == NULL);
	else {
		printf("\n==========Second Quarter Of The Year(2/4)===========\n");
		month++;
		cal(fp);
	}

	fp = fopen("third.txt", "r");
	if (fp == NULL);
	else {
		printf("\n==========Third Quarter Of The Year(3/4)===========\n");
		month++;
		cal(fp);
	}

	fp = fopen("fourth.txt", "r");
	if (fp == NULL);
	else {
		printf("\n==========Fourth Quarter Of The Year(4/4)===========\n");
		month++;
		cal(fp);
	}
	sort();
	dist(bonus);

	printf("\n=======FINISHED=============\n");
}

void sort()
{
	int i, j, c, root, temp;
	printf("\n\nCalculate score : (0.7 * Working Score) + (0.3 * Manner Score) ");
	printf("\n===============================================================\n");
	for (int i = 0; i < TEAM; i++) {
		dat[i].point = dat[i].point / month;
		dat[i].point2 = dat[i].point2 / month;
		dat[i].point3 = (dat[i].point * 0.7) + (dat[i].point2 * 0.3);
		printf("\n%s TEAMS AVERAGE POINT UNTIL %d th MONTH : (0.7 * %d) + (0.3 * %d) = %d\n", dat[i].team, month, dat[i].point, dat[i].point2, dat[i].point3);
	}
	printf("\n\n===============================================================");
	printf("\nArray before sort : ");
	for (i = 0; i < TEAM; i++)
		printf("%d ", dat[i].point3);
	for (i = 1; i < TEAM; i++)
	{
		c = i;
		do
		{
			root = (c - 1) / 2;
			if (dat[root].point3 < dat[c].point3)
			{
				bl = dat[root];
				dat[root] = dat[c];
				dat[c] = bl;
			}
			c = root;
		} while (c != 0);
	}
	for (j = TEAM - 1; j >= 0; j--)
	{
		bl = dat[0];
		dat[0] = dat[j];
		dat[j] = bl;
		root = 0;
		do
		{
			c = 2 * root + 1;
			if ((dat[c].point3 < dat[c + 1].point3) && c < j - 1)
				c++;
			if (dat[root].point3 < dat[c].point3 && c < j)
			{
				bl = dat[root];
				dat[root] = dat[c];
				dat[c] = bl;
			}
			root = c;
		} while (c  < j);
	}

	printf("\n\nUsing Maximum heap sort array : \n");
	for (i = TEAM - 1; i >= 0; i--) {
		printf("\t%d / ", dat[i].point3);
		puts(dat[i].team);
	}
	team();
}

void cal(FILE *fp)
{
	int point, point2;
	int str[15];


	for (int i = 0; i < TEAM; i++) {
		fscanf(fp, "%s %d %d", dat[i].team, &point, &point2);
		data(i, point, point2);
	}
}

void data(int num, int this_point, int that_point)
{
	dat[num].point = dat[num].point + this_point;
	dat[num].point2 = dat[num].point2 + that_point;
	printf("%s - WORKING SCORE: %d  MANNER SCORE: %d\n", dat[num].team, dat[num].point, dat[num].point2);
}

void dist(int bonus)
{
	dat[TEAM - 1].t_bonus = (int)bonus * 0.3;
	dat[TEAM - 2].t_bonus = (int)bonus * 0.15;
	dat[TEAM - 3].t_bonus = (int)bonus * 0.15;
	dat[TEAM - 4].t_bonus = (int)bonus * 0.1;
	dat[TEAM - 5].t_bonus = (int)bonus * 0.1;
	dat[TEAM - 6].t_bonus = (int)bonus * 0.1;
	dat[TEAM - 7].t_bonus = (int)bonus * 0.1;
	dat[TEAM - 8].t_bonus = (int)bonus * 0.0;
	for (int i = 0; i < TEAM; i++) {
		strcpy(dat[i].country, travel_index[i].key->name);
		dat[i].pref = travel_index[i].key->num;
	}
	printf("\n===========================BONUS===============================\n");
	for (int i = TEAM - 1; i >= 0; i--) {
		dist_print(dat[i]);
	}
}

void dist_print(pp dat)
{
	printf("%s / BONUS : %d\n", dat.team, dat.t_bonus);
}
void team() {
	char qwp[10];
	printf("\n===========================ENTER===============================\n");
	gets_s(qwp, 10);
	for (int i = 0; i < 8; i++) {
		printf("\ntype %d travel spot : ", i + 1);
		gets_s(travel[i].name, 10);
	}
	int sp[160]; 
	srand((unsigned)time(NULL));
//	srand(time((unsigned)NULL));
	for (int i = 0; i < 160; i++) {
		
		sp[i] = rand() % 8;
		for (int count = 0; count < 8; count++) {
			if (sp[i] == count)
				travel[count].num++;
		}
	}
	for (int i = 0; i < 8; i++) {
		travel_index[i].num = travel[i].num;
		travel_index[i].key = &travel[i];

	}
	struct travel_index temp;
	for (int i = 1; i < 8; i++) {
		for (int j = 0; j < 8 - i; j++) {
			if (travel_index[j].num > travel_index[j + 1].num) {
				temp = travel_index[j];
				travel_index[j] = travel_index[j + 1];
				travel_index[j + 1] = temp;
			}
		}
	}
	printf("\n===========================PREFERENCE===============================\n");
	for (int i = 0; i < 8; i++) {
		printf("\n%s preference : %d", travel_index[i].key->name, travel_index[i].key->num);
	}
	printf("\n\n===========================DESTINATION===============================\n\n");
	for (int i = TEAM - 1; i >= 0; i--) {
		printf("%s / can goes to %s : %d\n", dat[i].team, travel_index[i].key->name, travel_index[i].key->num);
	}
}