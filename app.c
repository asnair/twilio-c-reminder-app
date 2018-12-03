#include <string.h>
#include<stdlib.h>
#include<stdio.h>
#include <curl/curl.h>
#include <time.h>

#define MAX_TWILIO_MESSAGE_SIZE 10000
typedef enum { false, true }    bool;
/*#include "twilio.h"*/

/*
* _twilio_null_write is a portable way to ignore the response from 
* curl_easy_perform
*/
size_t _twilio_null_write(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    return size * nmemb;
}

/*
* twilio_send_message gathers the necessary parameters for a Twilio SMS or MMS.
* 
* Inputs:
*         - account_sid: Account SID from the Twilio console.
*         - auth_token: Authorization from the Twilio console.
*         - to_number: Where to send the MMS or SMS
*         - from_number: Number in your Twilio account to use as a sender.
*         - message_body: (Max: 1600 characters) The body of the MMS or SMS 
*               message which will be sent to the to_number.
*         - verbose: Whether to print all the responses
* 
*  Optional:
*         - picture_url: If picture URL is not NULL and is a valid image url, a
                MMS will be sent by Twilio.
*/
int twilio_send_message(char *account_sid,
                        char *auth_token,
                        char *message,
                        char *from_number,
                        char *to_number,
                        bool verbose)
{

        /* See: https://www.twilio.com/docs/api/rest/sending-messages for
         information on Twilio body size limits. */
        if (strlen(message) > 1600) 
		{
            fprintf(stderr, "SMS send failed.\n"
                    "Message body must be less than 1601 characters.\n"
                    "The message had %zu characters.\n", strlen(message));
            return -1;
        }

        CURL *curl;
        CURLcode res;
        curl_global_init(CURL_GLOBAL_ALL);
        curl = curl_easy_init();

        char url[MAX_TWILIO_MESSAGE_SIZE];
        snprintf(url,
                 sizeof(url),
                 "%s%s%s",
                 "https://api.twilio.com/2010-04-01/Accounts/",
                 account_sid,
                 "/Messages");

        char parameters[MAX_TWILIO_MESSAGE_SIZE];

            snprintf(parameters,
                     sizeof(parameters),
                     "%s%s%s%s%s%s",
                     "To=",
                     to_number,
                     "&From=",
                     from_number,
                     "&Body=",
                     message);


        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parameters);
        curl_easy_setopt(curl, CURLOPT_USERNAME, account_sid);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, auth_token);

        if (!verbose) 
		{
                curl_easy_setopt(curl, 
                                 CURLOPT_WRITEFUNCTION, 
                                 _twilio_null_write);
        }

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        long http_code = 0;
        curl_easy_getinfo (curl, CURLINFO_RESPONSE_CODE, &http_code);

        if (res != CURLE_OK) 
		{
                if (verbose) 
				{
                        fprintf(stderr,
                                "SMS send failed: %s.\n",
                                curl_easy_strerror(res));
                }
                return -1;
        } 
		else if (http_code != 200 && http_code != 201) 
		{
                if (verbose) 
				{
                        fprintf(stderr,
                                "SMS send failed, HTTP Status Code: %ld.\n",
                                http_code);
                }
                return -1;
        } 
		else 
		{
                if (verbose) 
				{
                        fprintf(stderr, "SMS sent successfully!\n");
                }
                return 0;
        }

}

<<<<<<< HEAD
struct User 
{
	char name[30];
	long num;
	char call[20];
	int year;
};

struct Notification
{
	char message[50];
	long time;
	long timeBeforeRemind;
	char phoneNum[11];
};

void bubble_num(struct User student[], int );
=======
int size = 10;
struct alarm{
    char msg[1000];
    long time;
    char num[12];
    int alarmwarning;

};

void bubble_num(struct alarm alarm[], int);

void bubble_num(struct alarm alarm[], int size)
{
    long i, j, temp;
    for(i=0;i<size-1;i++){
            for(j=0;j<size-i-1;j++){
                        if(alarm[j].time>alarm[j+1].time){
                            temp=alarm[j].time;
                            alarm[j].time = alarm[j + 1].time;
                            alarm[j + 1].time = temp;

                        }
            }
    }

}
>>>>>>> 33fef4d59eab5fec78961e2afca85504362dc0b3

int main()
{
	int i;
	int size = 10;
	char key = 0;
    char sid[] = "AC4d2aa5e7fdc7e0923dcbdd5970608d60";
    char auth[] = "76d4c2951b30b4f21da0025b7462b52b";
    char msg[] = "testing";
    char from[] = "+18142470271";
    char to[] = "+17657145071";
    int ret = 0;
    int verb = 0;
	char times[30];

	struct User student[10] = { { "apolo", 20181220813, "765438192", 22 },
								{ "cypers", 20181220810, "765382913", 20 },
								{ "bear", 20181220801, "2198467382", 20 },
								{ "griffis", 20181220811, "765193892", 19 },
								{ "stella", 20181220805, "2938472019", 20 },
								{ "nancy", 20181220820, "7116473829", 20 },
								{ "rose", 20181220817, "9604938249", 21 },
								{ "yellowpete", 20181220819, "96784893930", 20 },
								{ "welch", 20181220822, "86948362843", 21 },
								{ "ustar", 20181220806, "97058472894", 22 } };

	struct Notification notification[size];

    char *sidptr = sid;
    char *authptr = auth;
    char *msgptr = msg;
    char *fromptr = from;
    char *toptr = to;
<<<<<<< HEAD
=======

    struct alarm alarm[10] = {
        {"test message", 201812031230, "+13174305963", 30}};
    
    
>>>>>>> 33fef4d59eab5fec78961e2afca85504362dc0b3
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

	//printf(times, "%d%d%d%d%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min); doesn't appear in console

    printf("Right now the time is: %d-%d-%d %d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);

	//printf("%s\n", times); doesn't apear in console

	printf("====================================\n");
	printf("Account Information\n");
	for (i = 0; i<10; i++)
		printf("name : %s\nDate/time : %ld\nPhone : %s\nAge : %d\n\n", student[i].name, student[i].num, student[i].call, student[i].year);


	printf("====================================\n");
	printf("Account Sorted by times\n");

	bubble_num(student, size);
	for (i = 0; i < 10; i++)
		printf("name : %s\nDate/time : %ld\nPhone : %s\nAge : %d\n\n", student[i].name, student[i].num, student[i].call, student[i].year);

	for (i = 0; i < size; i++)
	{
		printf("Enter alarm message text: ");
		scanf("%s", notification[i].message);
		printf("Enter a time of alarm (yyyymmddhhmm) as in year month day hour minute: ");
		scanf("%ld", &notification[i].time);
		printf("Enter a time of when alarm goes off minutes before the time (mm) as in minutes: ");
		scanf("%ld", &notification[i].timeBeforeRemind);
		printf("Enter a phone number (+xxxxxxxxxxx): ");
		scanf("%s", notification[i].phoneNum);
	}
	
	for (i = 0; i < size; i++)
	{
		printf("\nAlarm Message: %s\nAlarm Time: %ld\nTime before alarm: %ld\nPhone Number: %s\n\n", notification[i].message, notification[i].time, notification[i].timeBeforeRemind, notification[i].phoneNum);
	}

    ret = twilio_send_message(sidptr, authptr, msgptr, fromptr, toptr, verb);

    int i;
    bubble_num(alarm,size);
        for(i=0;i<10;i++)
                printf("name : %s\nDate/time : %ld\nPhone : %s\nAge : %d\n\n",alarm[i].msg,alarm[i].time,alarm[i].num,alarm[i].alarmwarning);


    
    return ret;
}

void bubble_num(struct User student[], int size)
{
	long i, j, temp;
	for (i = 0; i < size - 1; i++)
		for (j = 0; j<size - i - 1; j++)
			if (student[j].num > student[j + 1].num)
			{
				temp = student[j].num;
				student[j].num = student[j + 1].num;
				student[j + 1].num = temp;

			}
}
