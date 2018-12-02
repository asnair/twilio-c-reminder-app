#include <string.h>
#include<stdlib.h>
#include <curl/curl.h>
#include <time.h>


int size = 10;
char key = 0;
struct user{
		char name[30];
		long num;
		char call[20];
		int year;
	};

void bubble_num(struct user student[],int);
int main()
{
	int i;
  char sid[] = "AC4d2aa5e7fdc7e0923dcbdd5970608d60";
  char auth[] = "76d4c2951b30b4f21da0025b7462b52b";
  char msg[] = "testing";
  char from[] = "+18142470271";
  char to[] = "+13174305963";
  int ret = 0;
  int verb = 0;
  char times[30];
	struct user student[10] =	{            // 구조체 배열에 초기화될 정보들
	{"apolo",20181220813,"765438192",22},
	{"cypers",20181220810,"765382913",20},
	{"bear",20181220801,"2198467382",20},
	{"griffis",20181220811,"765193892",19},
	{"stella",20181220805,"2938472019",20},
	{"nancy",20181220820,"7116473829",20},
	{"rose",20181220817,"9604938249",21},
	{"yellowpete",20181220819,"96784893930",20},
	{"welch",20181220822,"86948362843",21},
	{"ustar",20181220806,"97058472894",22}};


  char *sidptr = sid;
  char *authptr = auth;
  char *msgptr = msg;
  char *fromptr = from;
  char *toptr = to;
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  sprintf(times,"%d%d%d%d%d",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday, tm.tm_hour, tm.tm_min );
  // This is puts times into array times[30]
  printf("Right now the time is: %d-%d-%d %d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday+10, tm.tm_hour, tm.tm_min);
  printf("%s\n", times);
  //This prints times array.

	printf("====================================\n");
	printf("Account Information\n");
	for(i=0;i<10;i++)
	printf("name : %s\nDate/time : %ld\nPhone : %s\nAge : %d\n\n",student[i].name,student[i].num,student[i].call,student[i].year);


	printf("====================================\n");
	printf("Account Sorted by times\n");

	bubble_num(student,size);
	for(i=0;i<10;i++)
	printf("name : %s\nDate/time : %ld\nPhone : %s\nAge : %d\n\n",student[i].name,student[i].num,student[i].call,student[i].year);



}

void bubble_num(struct user student[],int size)
{
long i,j,temp;
for(i=0;i<size-1;i++)
	for(j=0;j<size-i-1;j++)
		if(student[j].num>student[j+1].num)
		{
			temp=student[j].num;
			student[j].num=student[j+1].num;
			student[j+1].num=temp;

		}
}
