#ifndef _API_H_
#define _API_H_

signed int read(unsigned int fd, char * buf, int count);
signed int write(unsigned int fd, const char * buf, int count);
void getRTC(date * current_date);
void setRTC(date * set_time);
void BCDtoBinary(date * date);

#endif
