#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

int
main(void)
{
	int s;
	int nbytes;
	char  buff[20];
	const char *ifname = "can0";

	//1 SOCKET CREATE  
	if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Error while opening socket");
		return -1;
	}
	
	struct sockaddr_can addr;
	struct can_frame frame;
	struct ifreq ifr;

	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);
	

	//2 ACTIVATE STRUCTURE
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

	//3 BINDING socket
	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Error in socket bind");
		return -2;
	}

	frame.can_id  = 0x0ff;
	frame.can_dlc = 2;
	frame.data[0] = 0xff;
	frame.data[1] = 0xff;

while(1)
{
	int i=0;

	nbytes = write(s, &frame, sizeof(struct can_frame));
	printf("Wrote %d bytes\n", nbytes);
	sleep(1);
	recv(s, buff, 20,0);
	for(i=0;i<20;i++)
		printf("%d",buff[i]);

	printf("\n");
	sleep(1);
}
	
	return 0;
}

