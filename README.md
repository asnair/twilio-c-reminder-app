# twilio-c-reminder-app

## Pre-Reqs

You must install libcurl (available by default on Mac?)
On linux:
```sh
sudo apt-get install libcurl4-openssl-dev
```

Use the make file to build the program

To use this repo:
```
git clone https://github.com/asnair/twilio-c-reminder-app
cd twilio-c-reminder-app
git remote add master git@github.com:asnair/twilio-c-reminder-app.git
```
You can now edit the code, and `git pull` to update your local version. When you are ready to add changes back in, you do the following:
```
git add .
git commit -m "update message"
git push origin master
```
UPDATE Saturday Night:

Testing now works, you can see it called in the 'main' function. When taking user input and saving to a string, you can use msg[] and *msgptr to text the user the string they input. To compile the code you can run either `make` or `./compile.sh`

I've removed extra files, including /example and /include, as well as twilio.c and twilio.h, both of which I integrated into app.c. This app works with my phone number currently, we can change the phone number but any number we use must first be verified by Twilio. Subin's phone number is verified so the 'to[]' can be changed to his for testing.



Things to do:

- [ ] Scan for user input continuously
- [ ] Check the time every minute for a new alarm continuously
- [x] Figure out the texting issue
- [ ] Save user input in an array of structs (a structure containing the time and and message)

Following the guide from [https://www.twilio.com/docs/sms/tutorials/how-to-send-sms-messages-c](https://www.twilio.com/docs/sms/tutorials/how-to-send-sms-messages-c)

This link is useful for troubleshooting the POST requests: https://curl.haxx.se/libcurl/c/http-post.html

Verify future phone numbers here: https://www.twilio.com/console/phone-numbers/verified

Useful git commands: https://akrabat.com/the-beginners-guide-to-contributing-to-a-github-project/