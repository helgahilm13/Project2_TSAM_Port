
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

bool is_port_open(char* IP, int )
{

}

void scanner(char* IP, int low, int high)
{
	struct sockaddr_in addr;
	struct sockaddr_in target_addr;
	memset(&target_addr, '0', sizeof(target_addr));
	int sock = 0;


	target_addr.sin_family = AF_INET;

	if(inet_pton(AF_INET, IP, &target_addr.sin_addr)<=0)
	{
		std::cout << "Error converting target ip address to binary form" << std::endl;
	}


	for(int i = low; i <= high; i++)
	{
		target_addr.sin_port = htons(i);
		
		if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
		{
			std::cout << "Error creating socket: ";
			std::cout << std::strerror(errno) << std::endl;
		}

		if (connect(sock, (struct sockaddr*)&target_addr, sizeof(target_addr)) < 0)
		{
			std::cout << "port " << i << " closed: ";
			std::cout << std::strerror(errno) << std::endl;
		} 
		else 
		{
			std::cout << "Port " << i << " open!! " << std::endl;
		}
	
	close(sock);
	}

}

int main(int argc, char *argv[])
{

	char* IPaddress = argv[1];
	int lowPort = atoi(argv[2]);
	int highPort = atoi(argv[3]);


	scanner(IPaddress, lowPort, highPort);

	return 0;
}