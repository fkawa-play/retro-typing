/******************************************************************************
MIT License

Copyright (c) 2018 yushiro_1121

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/
#include "logging.h"


// Global values in this file
// Log level structure
struct{
    enum loglevel code;
    char *name;
    int display;
} loglevels [] = {
    LOG(INFO, 0),
    LOG(DEBUG, 0),
    LOG(WARNING, 0),
    LOG(ERROR, 1),
    LOG(CRITICAL, 1)
};
FILE *fp_log;


/*-----------------------------------------------------------------------------
 = output message and logfile
 == Argument & Return value
    _code_ :: [enum loglevel] log levels as follows:
                                INFO DEBUG WARN ERROR CRITICAL
    _*msg_ :: [const Char] output message
    _..._  :: [valiable length args] ex. message's additional args
 === Return value
    nothing
------------------------------------------------------------------------------*/
void logger(enum loglevel code, const char *msg, ...) {
  va_list args;
  char time_str[TIME_STR_SIZE];
  time_t t;

  t = time(&t);
  strcpy(time_str, ctime(&t));
  time_str[strlen(time_str) - 6] = '\0';

  if (code >= sizeof(loglevels) / sizeof(loglevels[0])){
    puts("CRITICAL: illegal LOG_LEVEL is specified...");
    exit(EXIT_FAILURE);
  }
  if (loglevels[code].display){
    printf("%s:%s:", time_str, loglevels[code].name);
    va_start(args, msg);
    vprintf(msg, args); puts("");
    va_end(args);
  }
  if (fp_log != NULL){
    va_start(args, msg);
    switch(code) {
        case INFO:
           fprintf(fp_log, "\033[36m");
            break;
        case WARNING:
           fprintf(fp_log, "\033[33m");
            break;
        case DEBUG:
            break;
        case ERROR:
           fprintf(fp_log, "\033[31m");
            break;
        case CRITICAL:
           fprintf(fp_log, "\033[37m\033[41m");
            break;
        default:
            break;
    }
    fprintf(fp_log, "%s:%s:", time_str, loglevels[code].name);
    vfprintf(fp_log, msg, args); fprintf(fp_log, "\033[0m\n");
    va_end(args);
  } else {
    puts("CRITICAL: FILE is not opened yet...");
    exit(EXIT_FAILURE);
  }
  return;
}


/*-----------------------------------------------------------------------------
 = set log level to describe standard output
 == Argument & Return value
    _code_    :: [enum loglevel] log levels as follows:
                                 INFO DEBUG WARN ERROR CRITICAL
    _display_ :: [int] TRUE(1), FALSE(0)
------------------------------------------------------------------------------*/
void set_level(enum loglevel code, int display) {
  if (code >= sizeof(loglevels) / sizeof(loglevels[0])){
    puts("CRITICAL: illegal LOG_LEVEL is specified...");
    exit(EXIT_FAILURE);
  }
  loglevels[code].display = display;
}
