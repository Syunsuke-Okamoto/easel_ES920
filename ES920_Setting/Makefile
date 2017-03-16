#CC = gcc #selfbuild
CC		=	arm-linux-gnueabi-gcc #crossbuild
LD		=	arm-linux-gnueabi-ld
#LIBDIR		= 	-L${CPS_SDK_INSTALL_FULLDIR}/${CPS_SDK_ROOTFS}/usr/local/lib
LIBS		=	-leasel_ES920 -lSerialFunc -lm

all:easel_ES920_Setting_test  

easel_ES920_Setting_test: easel_ES920_Setting_test.c 
	${CC} ${CFLAGS} -o ES920SettingTest easel_ES920_Setting_test.c ${LIBDIR} ${LIBS} -lpthread

clean:
	rm -f *.o CMM920*Test_*
