
#include "./../include/LocalTime.h"

void getTime()
{
    time_t tt = time(NULL);
    tm *t = localtime(&tt);
    std::cout << t->tm_hour << ":" << t->tm_min << ":" << t->tm_sec << " ";
}