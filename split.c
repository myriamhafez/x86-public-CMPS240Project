#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#define BUF_SIZE 512

void make_filename(char *buf, int index){
buf[0] = 'x';
buf[1] = 'a' + (index / 26);
buf[2] = 'a' + (index % 26);
buf[3] = '\0';
}

void split(int fd, int chunk_size){
char buf[BUF_SIZE];
char outname[4];
int outfd = -1;
int file_index = 0;
int bytes_in_chunk = 0;
int n;
int to_write;
  
while((n = read(fd, buf, BUF_SIZE)) > 0){
int pos = 0;
while (pos < n) {
if(outfd < 0) {
make_filename(outname, file_index);
outfd = open(outname, O_CREATE | O_WRONLY);
if(outfd < 0) {
printf(2, "split: cannot create %s\n", outname);
exit();
}
bytes_in_chunk = 0;
}

int space_left = chunk_size - bytes_in_chunk;
to_write = n - pos;
if(to_write > space_left) to_write = space_left;
if(write(outfd, buf + pos, to_write) != to_write) {
printf(2, "split: write error\n");
exit();
}

pos += to_write;
bytes_in_chunk += to_write;
if(bytes_in_chunk >= chunk_size) {
close(outfd);
outfd = -1;
file_index++;
}
}
}

if(outfd >= 0) close(outfd);

if (n < 0) printf(2, "split: read error\n");
}

int main(int argc, char *argv[]) {
int fd;
int chunk_size;

if(argc != 3){
printf(2, "Usage: split <file> <chunk_size>\n");
exit();
}
chunk_size = atoi(argv[2]);
if(chunk_size <= 0) {
printf(2, "split: chunk size must be a positive number\n");
]exit();
}

fd = open(argv[1], 0);
if (fd < 0) {
printf(2, "split: cannot open %s\n", argv[1]);
]exit();
}

split(fd, chunk_size);

close(fd);
exit();
}
