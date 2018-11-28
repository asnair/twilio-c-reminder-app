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
Things to do:
Scan for user input continuously
Check the time every minute for a new alarm continuously
Figure out the texting issue
Save user input in an array of structs (a structure containing the time and and message)


Following the guide from [https://www.twilio.com/docs/sms/tutorials/how-to-send-sms-messages-c](https://www.twilio.com/docs/sms/tutorials/how-to-send-sms-messages-c)
