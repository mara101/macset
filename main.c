#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <net/if_arp.h>
#include <time.h>
#include <ctype.h>

//Create a function thah takes as an input a pointer to a 6 byte array as an argoument and generate random mac adress

void generate_random_mac(unsigned char *mac){
	//option is set to  "eth0" or  "wlo1"
	int i;
	time_t t;
	srand((unsigned) time(&t));
        unsigned char dig = 0;	
	for(i = 0; i < 6; i++){
		mac[i] = rand() % 256;
		//The first octet of a valid MAC address must be an even value
		if(i == 0){
			while((int)mac[i] % 2 != 0){
				mac[i] = rand() % 256;
			}
		}
	}
	return;
}
int valid_mac(unsigned char *mac){
	if(mac[0] % 2 != 0 || (int)mac[0] > 256 || (int)mac[0] < 0){
		return -1;
	}
	for(int i = 1; i < 6; i++){
		if((int)mac[i] > 256 || (int)mac[i] < 0){
			return -1;
		}
	}
	return 1;
}
int change_mac(unsigned char *mac,char *option ){
	int sockfd;
	struct ifreq ifr;
	//Now we create a socket;
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 1){
		perror("Error in creating a socket\n");
		return -1;
	}
	strncpy(ifr.ifr_name, option, IFNAMSIZ);
	ifr.ifr_hwaddr.sa_data[0] = mac[0];
	ifr.ifr_hwaddr.sa_data[1] = mac[1];
	ifr.ifr_hwaddr.sa_data[2] = mac[2];
	ifr.ifr_hwaddr.sa_data[3] = mac[3];
	ifr.ifr_hwaddr.sa_data[4] = mac[4];
	ifr.ifr_hwaddr.sa_data[5] = mac[5];
	
	//Set MAc adress of the interf	
	 ifr.ifr_hwaddr.sa_family = ARPHRD_ETHER;
	 if (ioctl(sockfd, SIOCSIFHWADDR, &ifr) == -1) {
    		perror("ioctl eRROR\n");
    		return -1;
  	}
	return 1;
}
void print_mac(unsigned char *mac){
	printf("This is the new MAC address: ");
	for(int i = 0; i < 5; i++){
		printf("%02X:", (int)mac[i]);
	}
	printf("%02X:", (int)mac[5]);
	puts("\n");
	return;
}
void display_usage(){
	printf("Usage: macset [Name of the network interface] [Flag]\n-r Set random MAC address\n-s Set a specific MAC address, format: xx:xx:xx:xx:xx:xx\n");
	return;
}
void display_problems(){
	                               fprintf(stderr, "The MAC address has not been set. Those are the possible problems that may arise:\n1 - Your Network interface those not support MAC address changes\n2 - The nettwork interface is currently in use\n3 - The name of the network interface is not correct. (Try the ifconfig command to list all the network interfaces)\n4 - You don't have root privilege to execute the command\n5- If you set your personal MAC address note that the first octet must be a even value in order to be a valid address\n");
                                          exit(1);
					  return;

}
int set_mac(unsigned char *mac, char *arg){
	   sscanf(arg, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx",&mac[0],&mac[1],&mac[2],&mac[3],&mac[4],&mac[5]);
	if(valid_mac(mac) == -1){
		return -1;
	}
	return 1;
	
}
int main(int argc, char **argv){
	unsigned char mac[6];
	char interface[20];
	int c;
	if(argc < 2){
		display_usage();
		exit(1);
	}
	strcpy(interface, argv[1]);
	while((c = getopt(argc, argv , "rs:")) != -1){
		switch(c){
			case('r'):
				generate_random_mac(mac);
				if(change_mac(mac, interface) == -1){
					display_problems();
					exit(1);
				}
				print_mac(mac);
				break;
			case('s'):
				if(set_mac(mac, optarg) == -1){
				       fprintf(stderr, "The MAC address you inserted is not valid. (xx:xx:xx:xx:xx:xx)\n");
				       display_problems();
			       		exit(1);
			 	}
				if(change_mac(mac, interface) == -1){
					display_problems();
					exit(1);
				}		
				print_mac(mac);
				break;
			case('?'):
				if(optopt == 's' ){
					fprintf(stderr, "flag -%c needs argoument\n", optopt);
					exit(1);
				}else{
					fprintf(stderr, "unknown option -%c\n", optopt);
				}
				break;
		}

	}
	return 0;
}
