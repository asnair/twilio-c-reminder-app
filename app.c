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
			printf("Enter a time of when  goes off minutes before the time (mm) as in minutes: ");
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
	printf(" information sorted by time\n");
	printf("--------------------------------\n");

	bubble_num(alarm1, count);
	for (i = 0; i < count; i++)
	{
		printf("\nMessage: %s\nalarm1 Time: %ld\nTime before alarm: %d\nPhone Number: %s\n", alarm1[i].msg, alarm1[i].time, alarm1[i].alarmwarning, alarm1[i].num);
	}

    unsigned int alarm(unsigned int seconds);
    long time[14];
    int year = 0;
    int month = 0;
    int day = 0;
    int hr = 0;
    int min = 0;
    int dif = 0;
    int y;

    for (y = 0; y < count; y++)
    {
        int c = 0; /* digit position */
        int n = alarm1[y].time;

        /* extract each digit */
        while (n != 0)
        {
			printf("test1\n");
            time[c] = n % 10;
            n /= 10;
            c++;
        }


        for (i = 0; i < 4; i++)
        {
            year = 10 * year + time[i];
        }
        for (i = 4; i < 7; i++)
        {
            month = 10 * month + time[i];
        }
        for (i = 7; i < 9; i++)
        {
            day = 10 * day + time[i];
        }
        for (i = 9; i < 11; i++)
        {
            hr = 10 * hr + time[i];
        }
        for (i = 11; i < 13; i++)
        {
            min = 10 * min + time[i];
        }
    }

    dif = ((year - (tm.tm_year + 1900))/31536000) + ((month - (tm.tm_mon + 1))/2628000) + ((day - (tm.tm_mday))/86400) + ((hr -tm.tm_hour)/3600) + ((min - tm.tm_min)/60);
    
    printf("\ndifference: %d", dif);
	while (alarm(dif) != 0)
	{
		printf("test2\n");
		printf("\n%u seconds left until ", alarm(dif));
	}

    ret = twilio_send_message(sidptr, authptr, msgptr, fromptr, alarm1PTR->num, verb);

	printf("\n\n");

	return ret;
}
