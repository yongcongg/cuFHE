#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <arpa/inet.h>
#include <fstream>
#define SIZE 1024

void write_file(int sockfd){
  int n, fileChoice;
  int count = 0;
  FILE *fp;
  char *filename = "recv.txt";
  char buffer[SIZE];

  //Create list of file names into a list 
  const char* filenames[32]
	  = { "Ptx0", "Ptx1", "Ptx2", "Ptx3", "Ptx4", "Ptx5", "Ptx6", "Ptx7", "Ptx8", "Ptx9", "Ptx10", "Ptx11", "Ptx12", "Ptx13", "Ptx14", "Ptx15", "Ptx16", "Ptx17", "Ptx18", "Ptx19", "Ptx20", "Ptx21", "Ptx22", "Ptx23", "Ptx24", "Ptx25", "Ptx26", "Ptx27", "Ptx28", "Ptx29", "Ptx30", "Ptx31"};
  
  while (1) {
    n = recv(sockfd, buffer, SIZE, 0);
    if (n <= 0){
      break;
      return;
    }
    
    std::ofstream outfile;
    fileChoice = floor(count/2);

    outfile.open(filenames[fileChoice], std::ios_base::app);
    outfile << ("%s", buffer);
    bzero(buffer, SIZE);
    count += 1;
  }
  return;
}

int main(){
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;

  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[SIZE];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e < 0) {
    perror("[-]Error in bind");
    exit(1);
  }
  printf("[+]Binding successfull.\n");

  if(listen(sockfd, 10) == 0){
		printf("[+]Listening....\n");
	}else{
		perror("[-]Error in listening");
    exit(1);
	}

  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
  write_file(new_sock);
  printf("[+]Data written in the file successfully.\n");

  return 0;
}
