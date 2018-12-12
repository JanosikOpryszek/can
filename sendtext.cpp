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
	char buff[]="12345678910";
	struct sockaddr_can addr;
	struct can_frame frame;
	struct ifreq ifr;

	const char *ifname = "can0";

	if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Error while opening socket");
		return -1;
	}

	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);
	
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

//	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
//		perror("Error in socket bind");
//		return -2;
//	}

	frame.can_id  = 0x325;
	frame.can_dlc = 8;
	frame.data[0] = 0xff;
	frame.data[1] = 0xff;
	frame.data[2] = 0xff;
	frame.data[3] = 0xff;
	frame.data[4] = 0xff;
	frame.data[5] = 0xff;
	frame.data[6] = 0xff;
	frame.data[7] = 0xa0;

	nbytes = sendto(s,&frame ,sizeof(struct can_frame) ,0,(struct sockaddr *)&addr, sizeof(addr) );

	printf("Wrote %d bytes\n", nbytes);
	
	return 0;
}

