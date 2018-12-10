#include <string.h>
#include<stdlib.h>
#include<stdio.h>
#include <curl/curl.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#define MAX_TWILIO_MESSAGE_SIZE 1000
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

int twilio_send_message(char *account_sid, char *auth_token, char *message,
						char *from_number, char *to_number, bool verbose)
{

	/* See: https://www.twilio.com/docs/api/rest/sending-messages for
	 information on Twilio body size limits. */

	if (strlen(message) > 1600)
	{
		fprintf(stderr, "SMS send failed.\n" "Message body must be less than 1601 characters.\n" "The message had %zu characters.\n", strlen(message));
		return -1;
	}

	CURL *curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();

	char url[MAX_TWILIO_MESSAGE_SIZE];
	snprintf(url, sizeof(url), "%s%s%s", "https://api.twilio.com/2010-04-01/Accounts/", account_sid, "/Messages");

	char parameters[MAX_TWILIO_MESSAGE_SIZE];

	snprintf(parameters, sizeof(parameters), "%s%s%s%s%s%s", "To=", to_number, "&From=", from_number, "&Body=", message);


	curl_easy_setopt(curl, CURLOPT_POST, 1);
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, parameters);
	curl_easy_setopt(curl, CURLOPT_USERNAME, account_sid);
	curl_easy_setopt(curl, CURLOPT_PASSWORD, auth_token);

	if (!verbose)
	{
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, _twilio_null_write);
	}

	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	long http_code = 0;
	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);

	if (res != CURLE_OK)
	{
		if (verbose)
		{
			fprintf(stderr, "SMS send failed: %s.\n", curl_easy_strerror(res));
		}
		return -1;
	}
	else if (http_code != 200 && http_code != 201)
	{
		if (verbose)
		{
			fprintf(stderr, "SMS send failed, HTTP Status Code: %ld.\n", http_code);
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

struct alarm2
{
    char msg[1000];
    long time;
	int alarmwarning;
    char num[12];
};

void bubble_num(struct alarm2 alarm1[], int size)
{
    long i, j, temp;
    for(i = 0; i < size - 1; i++)
	{
		for(j = 0; j < size - i - 1; j++)
		{
			if(alarm1[j].time > alarm1[j + 1].time)
			{
				temp = alarm1[j].time;
                alarm1[j].time = alarm1[j + 1].time;
                alarm1[j + 1].time = temp;
            }
        }
    }
}

int main()
{
	int i, z;
	int count = 0;
	int size;
	char sid[] = "AC4d2aa5e7fdc7e0923dcbdd5970608d60";
	char auth[] = "76d4c2951b30b4f21da0025b7462b52b";
	char msg[] = "testing";
	char from[] = "+18142470271";
	char to[] = "0";
	int ret = 0;

	char *sidptr = sid;
	char *authptr = auth;
	char *msgptr = msg;
	char *fromptr = from;
	char *toptr = to;
	bool verb = true;

	struct alarm2 alarm1[MAX_TWILIO_MESSAGE_SIZE], *alarm1PTR;
	size = sizeof(alarm1) / sizeof(alarm1[0]);

	time_t t = time(NULL);
	struct tm tm = *localtime(&t);


    alarm1PTR = &alarm1;
	/*printf(times, "%d%d%d%d%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);*/

	printf("\n-------------------------------------\n");
	printf("Right now the time is: %d%d%d %d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min);
	printf("-------------------------------------\n\n");

	/*printf("%s\n", times);*/

	int answer;
	do
	{
		if (count < size)
		{
			printf("Enter message text: ");
			scanf("%[^'\n']s", alarm1[count].msg);
			getchar();
			printf("Enter a time of (yyyymmddhhmm) as in year month day hour minute: ");
			scanf("%ld", &alarm1[count].time);
			getchar();
			printf("Enter a time of when goes off minutes before the time (mm) as in minutes: ");
			scanf("%d", &alarm1[count].alarmwarning);
			getchar();
			printf("Enter a phone number (+xxxxxxxxxxx): ");
			scanf("%s", alarm1[count].num);
			getchar();
			printf("\nDo you want to continue entering information(y/n)?: ");
			answer = getchar();
			getchar();
		}
		else
		{
			break;
		}
		count++;
	} 
	while (tolower(answer) == 'y');

    char *numsptr[count + 1];
	for (i = 0; i < count; i++)
    {
/*numsptr[i] = &(alarm[i].num);*/
		printf("\nMessage: %s\nalarm1 Time: %ld\nTime before alarm: %d\nPhone Number: %s\n", alarm1[i].msg, alarm1[i].time, alarm1[i].alarmwarning, alarm1[i].num);
	}

	printf("\n--------------------------------\n");
	printf("Information sorted by time\n");
	printf("--------------------------------\n");

	bubble_num(alarm1, count);
	for (i = 0; i < count; i++)
	{
		printf("\nMessage: %s\nalarm1 Time: %ld\nTime before alarm: %d\nPhone Number: %s\n", alarm1[i].msg, alarm1[i].time, alarm1[i].alarmwarning, alarm1[i].num);
	}

    unsigned int alarm(unsigned int seconds);
    int year = 0;
    int month = 0;
    int day = 0;
    int hr = 0;
    int min = 0;
    unsigned int dif = 0;
	
	long tempTime;
    for (i = 0; i < count; i++)
    {
		tempTime = alarm1[i].time;
		min = tempTime % 100;
		tempTime /= 100;
		hr = tempTime % 100;
		tempTime /= 100;
		day = tempTime % 100;
		tempTime /= 100;
		month = tempTime % 100;
		tempTime /= 100;
		year = tempTime % 10000;
    }
	
	printf("\n%d %d %d %d %d\n", year, month, day, hr, min);

	dif = ((year - (tm.tm_year + 1900)) * 31556900) + ((month - (tm.tm_mon + 1)) * 2628000) + ((day - (tm.tm_mday)) * 86400) + ((hr - tm.tm_hour) * 3600) + ((min - tm.tm_min) * 60);
	printf("\ndifference: %d\n\n", dif);

	while (1)
	{
		printf("%u seconds left until \n", alarm(dif));
		t = time(NULL);
		tm = *localtime(&t);
		dif = ((year - (tm.tm_year + 1900)) * 31556900) + ((month - (tm.tm_mon + 1)) * 2628000) + ((day - (tm.tm_mday)) * 86400) + ((hr - tm.tm_hour) * 3600) + ((min - tm.tm_min) * 60);
		if (dif == 0)
			break;
	}

    ret = twilio_send_message(sidptr, authptr, alarm1PTR->msg, fromptr, alarm1PTR->num, verb);

	printf("\n\n");

	return ret;
}
