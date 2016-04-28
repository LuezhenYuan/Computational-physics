#ifndef HISTORY_H_INCLUDED
#define HISTORY_H_INCLUDED
#include <stdlib.h>
#include <iostream>
using namespace std;
class history{
private:
char* m_arr;//Store the history record: which side is win in the past m_size days.
int m_head;//the index in m_arr, wait for new result of a game.
int m_size;//the size of history record.
public:
history(int size);//generate random history record
~history(){free(m_arr);}
void PushPop(char success);//add new result into the m_arr
const char operator[](int index)const;//tracing back the history
};


#endif // HISTORY_H_INCLUDED
