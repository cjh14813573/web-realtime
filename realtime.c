#define SAVED_ENVIRONMENT "/tmp/cgicsave.env"

#include <stdio.h>
#include "cgic.h"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/shm.h>
#include "inifile.h"

#define MYPORT  10086
#define SEND_BUFFER_SIZE 1024
#define RECV_BUFFER_SIZE 10240
//设备号
#define POWER_1_DEVICE          1
#define UPS_1_DEVICE            2
#define ACDU_DEVICE             3
#define ENVIRONMENT_DEVICE      4
#define AIRCONDITIONER_DEVICE   5
#define SPD_DEVICE              6
#define BATTERY_DEVICE          7
#define SMART_LOCK_DEVICE       8
#define DCDU_DEVICE             9
#define GENERATOR_DEVICE        10
#define POWER_2_DEVICE          11
#define POWER_3_DEVICE          12
#define UPS_2_DEVICE            13
#define UPS_3_DEVICE            14


//防雷器
#define SPD_LAST_LIGHTNING_TIME_YEAR        1
#define SPD_LAST_LIGHTNING_TIME_MONTH       2
#define SPD_LAST_LIGHTNING_TIME_DAY         3
#define SPD_LAST_LIGHTNING_TIME_HOUR        4
#define SPD_LAST_LIGHTNING_TIME_MINUTE      5
#define SPD_LAST_LIGHTNING_TIME_SECOND      6
#define SPD_LAST_LIGHTNING_PEAK             7
#define SPD_CUMULATIVE_NUMBER               8
#define SPD_CONNECTION                      9
#define SPD_INVALID_1_ALARM                 10
#define SPD_INVALID_2_ALARM                 11
#define SPD_SWITCH_TRIP_1_ALARM             12
#define SPD_SWITCH_TRIP_2_ALARM             13
#define SPD_POWER_OFF_1_ALARM               14
#define SPD_POWER_OFF_2_ALARM               15
#define SPD_ERROR_1                         16
#define SPD_ERROR_2                         17

//电源各项
#define POWER_A_VOLTAGE_1               1
#define POWER_B_VOLTAGE_1               2
#define POWER_C_VOLTAGE_1               3
#define POWER_A_VOLTAGE_2               4
#define POWER_B_VOLTAGE_2               5
#define POWER_C_VOLTAGE_2               6
#define POWER_DC_CURRENT                7
#define POWER_DC_VOLTAGE                8
#define POWER_BATTERY_VOLTAGE_1         9
#define POWER_BATTERY_VOLTAGE_2         10
#define POWER_BATTERY_CURRENT_1         11
#define POWER_BATTERY_CURRENT_2         12
#define POWER_BATTERY_TEM_1             13
#define POWER_BATTERY_TEM_2             14
#define POWER_BATTERY_CAP_1             15
#define POWER_BATTERY_CAP_2             16
#define POWER_CONNECTION                17
#define POWER_RECTIFIER_CURRENT_1       18
//18-33为整流器1-16电流
#define POWER_RECTIFIER_SWITCH_1        34
//34-49为整流器1-16开关机状态
#define POWER_RECTIFIER_STATUS_1        50
//50-65为整流器1-16运行状态
#define POWER_RECTIFIER_CHARGE_1        66
//66-81为整流器1-16均浮充状态
#define POWER_DC_STATUS_1               82
//82-91为直流分路1-10状态
#define POWER_AC_OFF_ALARM              92
#define POWER_LOAD_BREAK_ALARM          93
#define POWER_CITY_OFF_1                94
#define POWER_CITY_OFF_2                95
#define POWER_CITY_STATUS               96
#define POWER_SPD_STATUS                97
#define POWER_AC_IN_STATUS              98
#define POWER_AC_OUT_STATUS             99
#define POWER_BATTERY_STATUS_1          100
#define POWER_BATTERY_STATUS_2          101
#define POWER_BATTERY_CHARGE_1          102
#define POWER_BATTERY_CHARGE_2          103
#define POWER_RECTIFIER_CONNECTION_1    104
//104-119为整流器1-16通信状态




//环境量
#define TEMPERATURE_1      1
#define HUMIDITY_1         2
#define TEMPERATURE_2      3
#define HUMIDITY_2         4
#define TEMPERATURE_3      5
#define HUMIDITY_3         6
#define TEMPERATURE_4      7
#define HUMIDITY_4         8
#define TEMPERATURE_5      9
#define HUMIDITY_5         10
#define ACCESS_1           11
#define WATER_1            12
#define SMOKE_1            13
#define GLASS_1            14
#define INFRARED_1         15
#define LIGHT_1            16
#define BUZZER_1           17
#define SPD_1              18
#define ACCESS_2           19
#define WATER_2            20
#define SMOKE_2            21
#define GLASS_2            22
#define INFRARED_2         23
#define LIGHT_2            24
#define BUZZER_2           25
#define SPD_2              26
#define ACCESS_3           27
#define WATER_3            28
#define SMOKE_3            29
#define GLASS_3            30
#define INFRARED_3         31
#define LIGHT_3            32
#define BUZZER_3           33
#define SPD_3              34
#define ACCESS_4           35
#define WATER_4            36
#define SMOKE_4            37
#define GLASS_4            38
#define INFRARED_4         39
#define LIGHT_4            40
#define BUZZER_4           41
#define SPD_4              42
#define ACCESS_5           43
#define WATER_5            44
#define SMOKE_5            45
#define GLASS_5            46
#define INFRARED_5         47
#define LIGHT_5            48
#define BUZZER_5           49
#define SPD_5              50
#define SMOKE_RESET        67
#define LIGHT_CONTROL_1    68
#define LIGHT_CONTROL_2    69
#define LIGHT_CONTROL_3    70
#define LIGHT_CONTROL_4    71
#define LIGHT_DELAY        72

//ups
#define UPS_BATTERY_VOLTAGE             1
#define UPS_BATTERY_CAPACITY            2
#define UPS_BATTERY_TIME_LEFT           3
#define UPS_INPUT_FREQUENCY             4
#define UPS_OUTPUT_FREQUENCY            5
#define UPS_BYPASS_FREQUENCY            6
#define UPS_INPUT_VOLTAGE_A             7
#define UPS_INPUT_VOLTAGE_B             8
#define UPS_INPUT_VOLTAGE_C             9
#define UPS_OUTPUT_VOLTAGE_A            10
#define UPS_OUTPUT_VOLTAGE_B            11
#define UPS_OUTPUT_VOLTAGE_C            12
#define UPS_BYPASS_VOLTAGE_A            13
#define UPS_BYPASS_VOLTAGE_B            14
#define UPS_BYPASS_VOLTAGE_C            15
#define UPS_OUTPUT_CURRENT_A            16
#define UPS_OUTPUT_CURRENT_B            17
#define UPS_OUTPUT_CURRENT_C            18
#define UPS_LOAD_A                      19
#define UPS_LOAD_B                      20
#define UPS_LOAD_C                      21
#define UPS_TEMPERATURE                 22
#define UPS_CONNECTION                  23
#define UPS_STATUS                      24
#define UPS_CHARGE_STATUS               25
#define UPS_OUTPUT_STATUS               26


//空调
#define AIR_CONNECTION_1             1
#define AIR_POWER_SWITCH_I_1         2
#define AIR_POWER_SWITCH_O_1         3
#define AIR_MODE_I_1                 4
#define AIR_MODE_O_1                 5
#define AIR_TEM_SET_I_1              6
#define AIR_TEM_SET_O_1              7
#define AIR_VOLTAGE_A_1              8
#define AIR_CURRENT_A_1              9
#define AIR_VOLTAGE_B_1              10
#define AIR_CURRENT_B_1              11
#define AIR_VOLTAGE_C_1              12
#define AIR_CURRENT_C_1              13
#define AIR_CONNECTION_2             14
#define AIR_POWER_SWITCH_I_2         15
#define AIR_POWER_SWITCH_O_2         16
#define AIR_MODE_I_2                 17
#define AIR_MODE_O_2                 18
#define AIR_TEM_SET_I_2              19
#define AIR_TEM_SET_O_2              20
#define AIR_VOLTAGE_A_2              21
#define AIR_CURRENT_A_2              22
#define AIR_VOLTAGE_B_2              23
#define AIR_CURRENT_B_2              24
#define AIR_VOLTAGE_C_2              25
#define AIR_CURRENT_C_2              26
#define AIR_CONNECTION_3             27
#define AIR_POWER_SWITCH_I_3         28
#define AIR_POWER_SWITCH_O_3         29
#define AIR_MODE_I_3                 30
#define AIR_MODE_O_3                 31
#define AIR_TEM_SET_I_3              32
#define AIR_TEM_SET_O_3              33
#define AIR_VOLTAGE_A_3              34
#define AIR_CURRENT_A_3              35
#define AIR_VOLTAGE_B_3              36
#define AIR_CURRENT_B_3              37
#define AIR_VOLTAGE_C_3              38
#define AIR_CURRENT_C_3              39


//交流配电
#define ACDU_VOLTAGE_A_1          1
#define ACDU_VOLTAGE_B_1          2
#define ACDU_VOLTAGE_C_1          3
#define ACDU_CONNECTION_1         4
#define ACDU_VOLTAGE_A_2          5
#define ACDU_VOLTAGE_B_2          6
#define ACDU_VOLTAGE_C_2          7
#define ACDU_CONNECTION_2         8
#define ACDU_CURRENT_A_1          9
#define ACDU_CURRENT_B_1          10
#define ACDU_CURRENT_C_1          11
#define ACDU_CURRENT_A_2          12
#define ACDU_CURRENT_B_2          13
#define ACDU_CURRENT_C_2          14
#define ACDU_QUANTITY_1           15
#define ACDU_QUANTITY_2           16

//单体电池
#define BATTERY_VOLTAGE_DIFFERENTIAL_1     1
#define BATTERY_VOLTAGE_DIFFERENTIAL_2     2
#define BATTERY_VOLTAGE_DIFFERENTIAL_3     3
#define BATTERY_VOLTAGE_DIFFERENTIAL_4     4
#define BATTERY_VOLTAGE_DIFFERENTIAL_5     5
#define BATTERY_VOLTAGE_DIFFERENTIAL_6     6
#define BATTERY_READ_RESISTANCE            7
// 从11开始，每个电池使用四个点，电压、温度、内阻、通信

int real_time_value[15][1000][2];
int pointer=34;

struct completeID{
	short int ss;//AA,5位,最多32个
	short int rtuID;//BBB,10位,最多1022个
	short int device;//CC,6位,最多62个
	short int point;//DDD,11位,最多2046个
};
long IDstruct_to_long(struct completeID device_struct){
	int a=device_struct.ss*134217728;
	int b=device_struct.rtuID*131072;
	int c=device_struct.device*2048;
	int d=device_struct.point;
	int whole_id=a+b+c+d;
	return whole_id;
}
struct completeID long_to_IDstruct(long whole_id){
	struct completeID device_struct;
	device_struct.ss=(short int)(whole_id>>27);
	device_struct.rtuID=(short int)((whole_id<<5)>>22);
	device_struct.device=(short int)(whole_id&0x01f800)/2048;
	device_struct.point=(short int)(whole_id&0x07ff);
	return device_struct;
}

void char_to_int(int *lgint,char *charResult)
{
	int lg,lgH,lgL;
	lgH=*charResult&0xff;
	lgL=*(charResult+2)&0xff;
	lgH=((lgH<<8)|(*(charResult+1)&0xff));
	lgL=((lgL<<8)|(*(charResult+3)&0xff));
	lg=((lgH<<16)|lgL);
	*lgint=lg;
}

void char_to_float(char *charbuf,float *floatbuf,int head,int end)
{
	int iii=0,fi;
	union fl_value
	{
		unsigned char cch[4];
		float fv;
	}fl_hw;
	for(fi=head;fi<end;fi+=4)
	{
		fl_hw.cch[3]=*(charbuf+fi);
		fl_hw.cch[2]=*(charbuf+fi+1);
		fl_hw.cch[1]=*(charbuf+fi+2);
		fl_hw.cch[0]=*(charbuf+fi+3);
		*(floatbuf+iii)=(float)(fl_hw.fv);
		iii++;
	}
}
void ini_to_array(char *str, unsigned char *charResult,int n)
{
	int i=0,ii=0,iii;
	char *q;
	char qq[30]={0};
	q=qq;
	char *p=str;
	for(iii=0;iii<n;iii++)
	{
		ii=0;
		memset(qq,0,30);
		while( p[i]!=',' && p[i]!='\0'&&p[i]!=':')
		{
			q[ii++]=p[i];
			i++;
		}
		i+=1;
		*(charResult++)=atoi(qq);
	}
}
void read_next_value(char *recvbuf){
  int id;
  struct completeID id_struct;
	int status;
  if(recvbuf[pointer+3]==2||recvbuf[pointer+3]==4){
    //DI量
    char_to_int(&id,&recvbuf[pointer+4]);//id号
    id_struct=long_to_IDstruct(id);
    real_time_value[id_struct.device][id_struct.point][0]=recvbuf[pointer+8];
		char_to_int(&status,&recvbuf[pointer+9]);//STATUS
    real_time_value[id_struct.device][id_struct.point][1]=status;
    pointer=pointer+13;
  }
  else if(recvbuf[pointer+3]==3||recvbuf[pointer+3]==5){
    //AI量
    char_to_int(&id,&recvbuf[pointer+4]);//id号
    id_struct=long_to_IDstruct(id);
    float float_value;
    char_to_float(recvbuf,&float_value,pointer+8,pointer+11);
    if(id_struct.device==7){
      real_time_value[id_struct.device][id_struct.point][0]=(int)(float_value*1000);
    }
    else real_time_value[id_struct.device][id_struct.point][0]=(int)(float_value*10);
		char_to_int(&status,&recvbuf[pointer+12]);//STATUS
    real_time_value[id_struct.device][id_struct.point][1]=status;
    pointer=pointer+16;
  }
/*
  printf("\n[%d][%d][0]=%d",id_struct.device,id_struct.point,real_time_value[id_struct.device][id_struct.point][0]);
  printf("\n[%d][%d][1]=%d",id_struct.device,id_struct.point,real_time_value[id_struct.device][id_struct.point][1]);*/
}

int cgiMain() {
  int i=0;
  int j=0;
	//从RTUcfg.ini中读取电源整流器个数和单体电池数量等
	char *cfgFile="/app/RTUcfg.ini";
	char *section;
	char *key;
	char temp[96]={0};
	unsigned char DB[7];//DB
	section="RTUDBSet";
	key="DB";
	read_profile_string(section,key,temp,96,"",cfgFile);
	ini_to_array(temp,DB,7);
	unsigned char rec_number_1;//电源整流器个数
	section="Power";
	key="rec_number_1";
	read_profile_string(section,key,temp,96,"0",cfgFile);
	ini_to_array(temp,&rec_number_1,1);
	unsigned char rec_number_2;//电源整流器个数
	section="Power";
	key="rec_number_2";
	read_profile_string(section,key,temp,96,"0",cfgFile);
	ini_to_array(temp,&rec_number_2,1);
	unsigned char rec_number_3;//电源整流器个数
	section="Power";
	key="rec_number_3";
	read_profile_string(section,key,temp,96,"0",cfgFile);
	ini_to_array(temp,&rec_number_3,1);
	//本机ip
	section="RTUNetset";
	key="IP";
	char ip_address[32]={0};
	read_profile_string(section,key,ip_address,32,"0",cfgFile);
  ///定义sockfd
  int sock_cli = socket(AF_INET,SOCK_STREAM, 0);

  ///定义sockaddr_in
  struct sockaddr_in servaddr;
  memset(&servaddr, 0, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(MYPORT);  ///服务器端口
  servaddr.sin_addr.s_addr = inet_addr(ip_address);  ///服务器ip

  ///连接服务器，成功返回0，错误返回-1
  if (connect(sock_cli, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
  {
    perror("connect");
    exit(1);
  }


  char sendbuf[SEND_BUFFER_SIZE];
  char recvbuf[RECV_BUFFER_SIZE];

  sendbuf[0]=0x23;//报头
  sendbuf[1]=0x64;//报头
  sendbuf[2]=0x01;//实时数据为0x01

  send(sock_cli, sendbuf, strlen(sendbuf),0); //发送
  bzero(recvbuf,sizeof(recvbuf));
  recv(sock_cli, recvbuf, sizeof(recvbuf),0); //接收
  close(sock_cli);
  for(i=0;i<15;i++){
    for(j=0;j<1000;j++){
      real_time_value[i][j][0]=0;
      real_time_value[i][j][1]=0xff;
    }
  }
  int point_number;
  char_to_int(&point_number,&recvbuf[30]);//点的个数
  for(i=0;i<point_number;i++){
    read_next_value(recvbuf);
  }



	//以下为网页部分
	cgiHeaderContentType("text/html");
	printf("<!DOCTYPE html>");
	printf("<html>");
	printf("<head>");
	printf("<meta charset='utf-8'>");
	printf("<title>实时数据</title>");
	printf("<link href='/realtime.css' rel='stylesheet'>");
	printf("</head>");
	printf("<body>");
	printf("<header>");
	printf("<div class='wrapper'>");
	printf("    <div id='logo' class='brand'>");
	printf("	   <p><a href='#' class='logo'>实时数据</a></p>");
	printf("    </div>");
	printf("    <div class='rm-container'>");
	printf("        <a class='rm-toggle rm-button rm-nojs'></a>");
	printf("        <nav class='rm-nav rm-nojs rm-lighten'>");
	printf("            <ul>");
	printf("                <li id='powerPointer' >");
	printf("                    <a href='#'>电源</a>");
	printf("                    <ul>");
	printf("                        <li>");
	printf("                            <a href='#'>电源 1</a>");
	printf("                        </li>");
	printf("                        <li>");
	printf("                            <a href='#'>电源 2</a>");
	printf("                        </li>");
	printf("                        <li>");
	printf("                            <a href='#'>电源 3</a>");
	printf("                        </li>");
	printf("                    </ul>");
	printf("                </li>");
	printf("                <li id='upsPointer'><a href='#'>UPS</a>");
	printf("                    <ul>");
	printf("                        <li>");
	printf("                            <a href='#'>UPS 1</a>");
	printf("                        </li>");
	printf("                        <li>");
	printf("                            <a href='#'>UPS 2</a>");
	printf("                        </li>");
	printf("                        <li>");
	printf("                            <a href='#'>UPS 3</a>");
	printf("                        </li>");
	printf("                    </ul>");
	printf("                </li>");
	printf("                <li id='acduPointer'>");
	printf("                    <a href='#'>交流配电</a>");
	printf("                </li>");
	printf("                <li id='airPointer'>");
	printf("                    <a href='#'>空调</a>");
	printf("                    <ul>");
	printf("                        <li>");
	printf("                            <a href='#'>空调 1</a>");
	printf("                        </li>");
	printf("                        <li>");
	printf("                            <a href='#'>空调 2</a>");
	printf("                        </li>");
	printf("                        <li>");
	printf("                            <a href='#'>空调 3</a>");
	printf("                        </li>");
	printf("                        <li>");
	printf("                            <a href='#'>空调 4</a>");
	printf("                        </li>");
	printf("                        <li>");
	printf("                            <a href='#'>空调 5</a>");
	printf("                        </li>");
	printf("                        <li>");
	printf("                            <a href='#'>空调 6</a>");
	printf("                        </li>");
	printf("                        <li>");
	printf("                            <a href='#'>空调 7</a>");
	printf("                        </li>");
	printf("                    </ul>");
	printf("                </li>");
	printf("                <li id='dbPointer'><a href='#'>单体电池</a>");
	printf("                    <ul>");
	printf("                        <li>");
	printf("                            <a href='#'>第 1 组</a>");
	printf("                        </li>");
	printf("                        <li>");
	printf("                            <a href='#'>第 2 组</a>");
	printf("                        </li>");
	printf("                        <li>");
	printf("                            <a href='#'>第 3 组</a>");
	printf("                        </li>");
	printf("                        <li>");
	printf("                            <a href='#'>第 4 组</a>");
	printf("                        </li>");
	printf("                        <li>");
	printf("                            <a href='#'>第 5 组</a>");
	printf("                        </li>");
	printf("                        <li>");
	printf("                            <a href='#'>第 6 组</a>");
	printf("                        </li>");
	printf("                    </ul>");
	printf("                </li>");
	printf("                <li id='spdPointer'><a href='#'>防雷</a>");
	printf("                </li>");
	printf("                <li id='enPointer'><a href='#'>环境</a>");
	printf("                </li>");
	printf("            </ul>");
	printf("        </nav>");
	printf("    </div>");
	printf("</div>");
	printf("</header>");
	printf("<script>$(function() { $('pre').addClass('prettyprint');})</script>");
	printf("<div id='valueDiv'>");
	printf("    <div id='powerDetail'>");
	printf("        <div id='power1' style='display:none'>");
	printf("            <p class='eachTitle'>");
	printf("                电源 1");
	printf("            </p>");
	printf("            <table>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        通信状态：");
	printf("                    </td>");
	if(real_time_value[POWER_1_DEVICE][POWER_CONNECTION][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_CONNECTION][1]);
		printf("                        正常");
		printf("                    </td>");
	}else if(real_time_value[POWER_1_DEVICE][POWER_CONNECTION][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_CONNECTION][1]);
		printf("                        断开");
		printf("                    </td>");
	}
	printf("                    <td class='td-head'>");
	printf("                        直流电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_DC_CURRENT][1]);
	printf("                        %.1fA",((float)real_time_value[POWER_1_DEVICE][POWER_DC_CURRENT][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        直流电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_DC_VOLTAGE][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_1_DEVICE][POWER_DC_VOLTAGE][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='tdhead'>");
	printf("                        1路A相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_A_VOLTAGE_1][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_1_DEVICE][POWER_A_VOLTAGE_1][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        1路B相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_B_VOLTAGE_1][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_1_DEVICE][POWER_B_VOLTAGE_1][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        1路C相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_C_VOLTAGE_1][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_1_DEVICE][POWER_C_VOLTAGE_1][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        2路A相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_A_VOLTAGE_2][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_1_DEVICE][POWER_A_VOLTAGE_2][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        2路B相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_B_VOLTAGE_2][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_1_DEVICE][POWER_B_VOLTAGE_2][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        2路C相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_C_VOLTAGE_2][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_1_DEVICE][POWER_C_VOLTAGE_2][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        1组电池电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_BATTERY_VOLTAGE_1][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_1_DEVICE][POWER_BATTERY_VOLTAGE_1][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        1组电池电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_BATTERY_CURRENT_1][1]);
	printf("                        %.1fA",((float)real_time_value[POWER_1_DEVICE][POWER_BATTERY_CURRENT_1][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        1组剩余容量：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_BATTERY_CAP_1][1]);
	printf("                        %.1f%%",((float)real_time_value[POWER_1_DEVICE][POWER_BATTERY_CAP_1][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        2组电池电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_BATTERY_VOLTAGE_2][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_1_DEVICE][POWER_BATTERY_VOLTAGE_2][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        2组电池电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_BATTERY_CURRENT_2][1]);
	printf("                        %.1fA",((float)real_time_value[POWER_1_DEVICE][POWER_BATTERY_CURRENT_2][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        2组剩余容量：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_BATTERY_CAP_2][1]);
	printf("                        %.1f%%",((float)real_time_value[POWER_1_DEVICE][POWER_BATTERY_CAP_2][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        市电1输入：");
	printf("                    </td>");
	if(real_time_value[POWER_1_DEVICE][POWER_CITY_OFF_1][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_CITY_OFF_1][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_1_DEVICE][POWER_CITY_OFF_1][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_CITY_OFF_1][1]);
		printf("                        停电");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        市电2输入：");
	printf("                    </td>");
	if(real_time_value[POWER_1_DEVICE][POWER_CITY_OFF_2][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_CITY_OFF_2][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_1_DEVICE][POWER_CITY_OFF_2][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_CITY_OFF_2][1]);
		printf("                        停电");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        交流输入供电：");
	printf("                    </td>");
	if(real_time_value[POWER_1_DEVICE][POWER_AC_OFF_ALARM][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_AC_OFF_ALARM][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_1_DEVICE][POWER_AC_OFF_ALARM][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_AC_OFF_ALARM][1]);
		printf("                        停电");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        交流输入空开：");
	printf("                    </td>");
	if(real_time_value[POWER_1_DEVICE][POWER_AC_IN_STATUS][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_AC_IN_STATUS][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_1_DEVICE][POWER_AC_IN_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_AC_IN_STATUS][1]);
		printf("                        断开");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        交流输出空开：");
	printf("                    </td>");
	if(real_time_value[POWER_1_DEVICE][POWER_AC_OUT_STATUS][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_AC_OUT_STATUS][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_1_DEVICE][POWER_AC_OUT_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_AC_OUT_STATUS][1]);
		printf("                        断开");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        防雷器状态：");
	printf("                    </td>");
	if(real_time_value[POWER_1_DEVICE][POWER_SPD_STATUS][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_SPD_STATUS][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_1_DEVICE][POWER_SPD_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_SPD_STATUS][1]);
		printf("                        故障");
	}
	printf("                    </td>");
	printf("                </tr>");
	for(i=1;i<=rec_number_1;i++){
		printf("                <tr>");
		printf("                    <td class='td-head'>");
		printf("                        整流器%d通信：",i);
		printf("                    </td>");
		if(real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_CONNECTION_1+i-1][0]==1){
			printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_CONNECTION_1+i-1][1]);
			printf("                        正常");
		}else if(real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_CONNECTION_1+i-1][0]==0){
			printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_CONNECTION_1+i-1][1]);
			printf("                        断开");
		}
		printf("                    </td>");
		printf("                    <td class='td-head'>");
		printf("                        整流器%d运行状态：",i);
		printf("                    </td>");
		if(real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_STATUS_1+i-1][0]==1){
			printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_STATUS_1+i-1][1]);
			printf("                        正常");
		}else if(real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_STATUS_1+i-1][0]==0){
			printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_STATUS_1+i-1][1]);
			printf("                        故障");
		}
		printf("                    </td>");
		printf("                    <td class='td-head'>");
		printf("                        整流器%d开关状态：",i);
		printf("                    </td>");
		if(real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_SWITCH_1+i-1][0]==1){
			printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_SWITCH_1+i-1][1]);
			printf("                        开机");
		}else if(real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_SWITCH_1+i-1][0]==0){
			printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_SWITCH_1+i-1][1]);
			printf("                        关机");
		}
		printf("                    </td>");
		printf("                </tr>");
		printf("                <tr>");
		printf("                    <td class='td-head'>");
		printf("                        整流器%d均浮充：",i);
		printf("                    </td>");
		if(real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_CHARGE_1+i-1][0]==1){
			printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_CHARGE_1+i-1][1]);
			printf("                        均充");
		}else if(real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_CHARGE_1+i-1][0]==0){
			printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_CHARGE_1+i-1][1]);
			printf("                        浮充");
		}
		printf("                    </td>");
		printf("                    <td class='td-head'>");
		printf("                        整流器%d电流：",i);
		printf("                    </td>");
		printf("                    <td class='value status%d'>",real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_CURRENT_1+i-1][1]);
		printf("                        %.1fA",((float)real_time_value[POWER_1_DEVICE][POWER_RECTIFIER_CURRENT_1+i-1][0])/10);
		printf("                    </td>");
		printf("                </tr>");
	}
	printf("            </table>");
	printf("        </div>");
	printf("        <div id='power2' style='display:none'>");
	printf("            <p class='eachTitle'>");
	printf("                电源 2");
	printf("            </p>");
	printf("            <table>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        通信状态：");
	printf("                    </td>");
	if(real_time_value[POWER_2_DEVICE][POWER_CONNECTION][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_CONNECTION][1]);
		printf("                        正常");
		printf("                    </td>");
	}else if(real_time_value[POWER_2_DEVICE][POWER_CONNECTION][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_CONNECTION][1]);
		printf("                        断开");
		printf("                    </td>");
	}
	printf("                    <td class='td-head'>");
	printf("                        直流电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_DC_CURRENT][1]);
	printf("                        %.1fA",((float)real_time_value[POWER_2_DEVICE][POWER_DC_CURRENT][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        直流电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_DC_VOLTAGE][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_2_DEVICE][POWER_DC_VOLTAGE][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='tdhead'>");
	printf("                        1路A相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_A_VOLTAGE_1][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_2_DEVICE][POWER_A_VOLTAGE_1][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        1路B相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_B_VOLTAGE_1][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_2_DEVICE][POWER_B_VOLTAGE_1][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        1路C相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_C_VOLTAGE_1][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_2_DEVICE][POWER_C_VOLTAGE_1][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        2路A相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_A_VOLTAGE_2][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_2_DEVICE][POWER_A_VOLTAGE_2][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        2路B相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_B_VOLTAGE_2][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_2_DEVICE][POWER_B_VOLTAGE_2][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        2路C相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_C_VOLTAGE_2][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_2_DEVICE][POWER_C_VOLTAGE_2][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        1组电池电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_BATTERY_VOLTAGE_1][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_2_DEVICE][POWER_BATTERY_VOLTAGE_1][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        1组电池电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_BATTERY_CURRENT_1][1]);
	printf("                        %.1fA",((float)real_time_value[POWER_2_DEVICE][POWER_BATTERY_CURRENT_1][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        1组剩余容量：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_BATTERY_CAP_1][1]);
	printf("                        %.1f%%",((float)real_time_value[POWER_2_DEVICE][POWER_BATTERY_CAP_1][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        2组电池电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_BATTERY_VOLTAGE_2][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_2_DEVICE][POWER_BATTERY_VOLTAGE_2][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        2组电池电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_BATTERY_CURRENT_2][1]);
	printf("                        %.1fA",((float)real_time_value[POWER_2_DEVICE][POWER_BATTERY_CURRENT_2][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        2组剩余容量：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_BATTERY_CAP_2][1]);
	printf("                        %.1f%%",((float)real_time_value[POWER_2_DEVICE][POWER_BATTERY_CAP_2][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        市电1输入：");
	printf("                    </td>");
	if(real_time_value[POWER_2_DEVICE][POWER_CITY_OFF_1][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_CITY_OFF_1][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_2_DEVICE][POWER_CITY_OFF_1][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_CITY_OFF_1][1]);
		printf("                        停电");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        市电2输入：");
	printf("                    </td>");
	if(real_time_value[POWER_2_DEVICE][POWER_CITY_OFF_2][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_CITY_OFF_2][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_2_DEVICE][POWER_CITY_OFF_2][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_CITY_OFF_2][1]);
		printf("                        停电");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        交流输入供电：");
	printf("                    </td>");
	if(real_time_value[POWER_2_DEVICE][POWER_AC_OFF_ALARM][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_AC_OFF_ALARM][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_2_DEVICE][POWER_AC_OFF_ALARM][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_AC_OFF_ALARM][1]);
		printf("                        停电");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        交流输入空开：");
	printf("                    </td>");
	if(real_time_value[POWER_2_DEVICE][POWER_AC_IN_STATUS][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_AC_IN_STATUS][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_2_DEVICE][POWER_AC_IN_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_AC_IN_STATUS][1]);
		printf("                        断开");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        交流输出空开：");
	printf("                    </td>");
	if(real_time_value[POWER_2_DEVICE][POWER_AC_OUT_STATUS][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_AC_OUT_STATUS][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_2_DEVICE][POWER_AC_OUT_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_AC_OUT_STATUS][1]);
		printf("                        断开");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        防雷器状态：");
	printf("                    </td>");
	if(real_time_value[POWER_2_DEVICE][POWER_SPD_STATUS][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_SPD_STATUS][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_2_DEVICE][POWER_SPD_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_SPD_STATUS][1]);
		printf("                        故障");
	}
	printf("                    </td>");
	printf("                </tr>");
	for(i=1;i<=rec_number_2;i++){
		printf("                <tr>");
		printf("                    <td class='td-head'>");
		printf("                        整流器%d通信：",i);
		printf("                    </td>");
		if(real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_CONNECTION_1+i-1][0]==1){
			printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_CONNECTION_1+i-1][1]);
			printf("                        正常");
		}else if(real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_CONNECTION_1+i-1][0]==0){
			printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_CONNECTION_1+i-1][1]);
			printf("                        断开");
		}
		printf("                    </td>");
		printf("                    <td class='td-head'>");
		printf("                        整流器%d运行状态：",i);
		printf("                    </td>");
		if(real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_STATUS_1+i-1][0]==1){
			printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_STATUS_1+i-1][1]);
			printf("                        正常");
		}else if(real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_STATUS_1+i-1][0]==0){
			printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_STATUS_1+i-1][1]);
			printf("                        故障");
		}
		printf("                    </td>");
		printf("                    <td class='td-head'>");
		printf("                        整流器%d开关状态：",i);
		printf("                    </td>");
		if(real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_SWITCH_1+i-1][0]==1){
			printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_SWITCH_1+i-1][1]);
			printf("                        开机");
		}else if(real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_SWITCH_1+i-1][0]==0){
			printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_SWITCH_1+i-1][1]);
			printf("                        关机");
		}
		printf("                    </td>");
		printf("                </tr>");
		printf("                <tr>");
		printf("                    <td class='td-head'>");
		printf("                        整流器%d均浮充：",i);
		printf("                    </td>");
		if(real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_CHARGE_1+i-1][0]==1){
			printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_CHARGE_1+i-1][1]);
			printf("                        均充");
		}else if(real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_CHARGE_1+i-1][0]==0){
			printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_CHARGE_1+i-1][1]);
			printf("                        浮充");
		}
		printf("                    </td>");
		printf("                    <td class='td-head'>");
		printf("                        整流器%d电流：",i);
		printf("                    </td>");
		printf("                    <td class='value status%d'>",real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_CURRENT_1+i-1][1]);
		printf("                        %.1fA",((float)real_time_value[POWER_2_DEVICE][POWER_RECTIFIER_CURRENT_1+i-1][0])/10);
		printf("                    </td>");
		printf("                </tr>");
	}
	printf("            </table>");
	printf("        </div>");
	printf("        <div id='power3' style='display:none'>");
	printf("            <p class='eachTitle'>");
	printf("                电源 3");
	printf("            </p>");
	printf("            <table>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        通信状态：");
	printf("                    </td>");
	if(real_time_value[POWER_3_DEVICE][POWER_CONNECTION][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_CONNECTION][1]);
		printf("                        正常");
		printf("                    </td>");
	}else if(real_time_value[POWER_3_DEVICE][POWER_CONNECTION][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_CONNECTION][1]);
		printf("                        断开");
		printf("                    </td>");
	}
	printf("                    <td class='td-head'>");
	printf("                        直流电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_DC_CURRENT][1]);
	printf("                        %.1fA",((float)real_time_value[POWER_3_DEVICE][POWER_DC_CURRENT][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        直流电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_DC_VOLTAGE][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_3_DEVICE][POWER_DC_VOLTAGE][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='tdhead'>");
	printf("                        1路A相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_A_VOLTAGE_1][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_3_DEVICE][POWER_A_VOLTAGE_1][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        1路B相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_B_VOLTAGE_1][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_3_DEVICE][POWER_B_VOLTAGE_1][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        1路C相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_C_VOLTAGE_1][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_3_DEVICE][POWER_C_VOLTAGE_1][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        2路A相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_A_VOLTAGE_2][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_3_DEVICE][POWER_A_VOLTAGE_2][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        2路B相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_B_VOLTAGE_2][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_3_DEVICE][POWER_B_VOLTAGE_2][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        2路C相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_C_VOLTAGE_2][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_3_DEVICE][POWER_C_VOLTAGE_2][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        1组电池电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_BATTERY_VOLTAGE_1][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_3_DEVICE][POWER_BATTERY_VOLTAGE_1][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        1组电池电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_BATTERY_CURRENT_1][1]);
	printf("                        %.1fA",((float)real_time_value[POWER_3_DEVICE][POWER_BATTERY_CURRENT_1][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        1组剩余容量：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_BATTERY_CAP_1][1]);
	printf("                        %.1f%%",((float)real_time_value[POWER_3_DEVICE][POWER_BATTERY_CAP_1][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        2组电池电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_BATTERY_VOLTAGE_2][1]);
	printf("                        %.1fV",((float)real_time_value[POWER_3_DEVICE][POWER_BATTERY_VOLTAGE_2][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        2组电池电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_BATTERY_CURRENT_2][1]);
	printf("                        %.1fA",((float)real_time_value[POWER_3_DEVICE][POWER_BATTERY_CURRENT_2][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        2组剩余容量：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_BATTERY_CAP_2][1]);
	printf("                        %.1f%%",((float)real_time_value[POWER_3_DEVICE][POWER_BATTERY_CAP_2][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        市电1输入：");
	printf("                    </td>");
	if(real_time_value[POWER_3_DEVICE][POWER_CITY_OFF_1][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_CITY_OFF_1][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_3_DEVICE][POWER_CITY_OFF_1][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_CITY_OFF_1][1]);
		printf("                        停电");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        市电2输入：");
	printf("                    </td>");
	if(real_time_value[POWER_3_DEVICE][POWER_CITY_OFF_2][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_CITY_OFF_2][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_3_DEVICE][POWER_CITY_OFF_2][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_CITY_OFF_2][1]);
		printf("                        停电");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        交流输入供电：");
	printf("                    </td>");
	if(real_time_value[POWER_3_DEVICE][POWER_AC_OFF_ALARM][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_AC_OFF_ALARM][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_3_DEVICE][POWER_AC_OFF_ALARM][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_AC_OFF_ALARM][1]);
		printf("                        停电");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        交流输入空开：");
	printf("                    </td>");
	if(real_time_value[POWER_3_DEVICE][POWER_AC_IN_STATUS][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_AC_IN_STATUS][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_3_DEVICE][POWER_AC_IN_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_AC_IN_STATUS][1]);
		printf("                        断开");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        交流输出空开：");
	printf("                    </td>");
	if(real_time_value[POWER_3_DEVICE][POWER_AC_OUT_STATUS][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_AC_OUT_STATUS][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_3_DEVICE][POWER_AC_OUT_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_AC_OUT_STATUS][1]);
		printf("                        断开");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        防雷器状态：");
	printf("                    </td>");
	if(real_time_value[POWER_3_DEVICE][POWER_SPD_STATUS][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_SPD_STATUS][1]);
		printf("                        正常");
	}else if(real_time_value[POWER_3_DEVICE][POWER_SPD_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_SPD_STATUS][1]);
		printf("                        故障");
	}
	printf("                    </td>");
	printf("                </tr>");
	for(i=1;i<=rec_number_3;i++){
		printf("                <tr>");
		printf("                    <td class='td-head'>");
		printf("                        整流器%d通信：",i);
		printf("                    </td>");
		if(real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_CONNECTION_1+i-1][0]==1){
			printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_CONNECTION_1+i-1][1]);
			printf("                        正常");
		}else if(real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_CONNECTION_1+i-1][0]==0){
			printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_CONNECTION_1+i-1][1]);
			printf("                        断开");
		}
		printf("                    </td>");
		printf("                    <td class='td-head'>");
		printf("                        整流器%d运行状态：",i);
		printf("                    </td>");
		if(real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_STATUS_1+i-1][0]==1){
			printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_STATUS_1+i-1][1]);
			printf("                        正常");
		}else if(real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_STATUS_1+i-1][0]==0){
			printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_STATUS_1+i-1][1]);
			printf("                        故障");
		}
		printf("                    </td>");
		printf("                    <td class='td-head'>");
		printf("                        整流器%d开关状态：",i);
		printf("                    </td>");
		if(real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_SWITCH_1+i-1][0]==1){
			printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_SWITCH_1+i-1][1]);
			printf("                        开机");
		}else if(real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_SWITCH_1+i-1][0]==0){
			printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_SWITCH_1+i-1][1]);
			printf("                        关机");
		}
		printf("                    </td>");
		printf("                </tr>");
		printf("                <tr>");
		printf("                    <td class='td-head'>");
		printf("                        整流器%d均浮充：",i);
		printf("                    </td>");
		if(real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_CHARGE_1+i-1][0]==1){
			printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_CHARGE_1+i-1][1]);
			printf("                        均充");
		}else if(real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_CHARGE_1+i-1][0]==0){
			printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_CHARGE_1+i-1][1]);
			printf("                        浮充");
		}
		printf("                    </td>");
		printf("                    <td class='td-head'>");
		printf("                        整流器%d电流：",i);
		printf("                    </td>");
		printf("                    <td class='value status%d'>",real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_CURRENT_1+i-1][1]);
		printf("                        %.1fA",((float)real_time_value[POWER_3_DEVICE][POWER_RECTIFIER_CURRENT_1+i-1][0])/10);
		printf("                    </td>");
		printf("                </tr>");
	}
	printf("            </table>");
	printf("        </div>");
	printf("    </div>");
	printf("    <div id='upsDetail'>");
	printf("        <div id='ups1' style='display:none'>");
	printf("            <p class='eachTitle'>");
	printf("                UPS 1");
	printf("            </p>");
	printf("            <table>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        ups通信状态：");
	printf("                    </td>");
	if(real_time_value[UPS_1_DEVICE][UPS_CONNECTION][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_CONNECTION][1]);
		printf("                        正常");
	}else if(real_time_value[UPS_1_DEVICE][UPS_CONNECTION][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_CONNECTION][1]);
		printf("                        断开");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        ups工作状态：");
	printf("                    </td>");
	if(real_time_value[UPS_1_DEVICE][UPS_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_STATUS][1]);
		printf("                        无输出");
	}else if(real_time_value[UPS_1_DEVICE][UPS_STATUS][0]==10){
		printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_STATUS][1]);
		printf("                        UPS供电");
	}else if(real_time_value[UPS_1_DEVICE][UPS_STATUS][0]==20){
		printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_STATUS][1]);
		printf("                        旁路供电");
	}else if(real_time_value[UPS_1_DEVICE][UPS_STATUS][0]==30){
		printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_STATUS][1]);
		printf("                        电池供电");
	}else if(real_time_value[UPS_1_DEVICE][UPS_STATUS][0]==40){
		printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_STATUS][1]);
		printf("                        手动旁路");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        均浮充状态：");
	printf("                    </td>");
	if(real_time_value[UPS_1_DEVICE][UPS_CHARGE_STATUS][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_CHARGE_STATUS][1]);
		printf("                        浮充");
	}else if(real_time_value[UPS_1_DEVICE][UPS_CHARGE_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_CHARGE_STATUS][1]);
		printf("                        均充");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        负载状态：");
	printf("                    </td>");
	if(real_time_value[UPS_1_DEVICE][UPS_OUTPUT_STATUS][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_OUTPUT_STATUS][1]);
		printf("                        正常");
	}else if(real_time_value[UPS_1_DEVICE][UPS_OUTPUT_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_OUTPUT_STATUS][1]);
		printf("                        过载");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        输入A相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_INPUT_VOLTAGE_A][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_1_DEVICE][UPS_INPUT_VOLTAGE_A][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输入B相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_INPUT_VOLTAGE_B][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_1_DEVICE][UPS_INPUT_VOLTAGE_B][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输入C相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_INPUT_VOLTAGE_C][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_1_DEVICE][UPS_INPUT_VOLTAGE_C][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        输出A相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_OUTPUT_VOLTAGE_A][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_1_DEVICE][UPS_OUTPUT_VOLTAGE_A][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输出B相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_OUTPUT_VOLTAGE_B][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_1_DEVICE][UPS_OUTPUT_VOLTAGE_B][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输出C相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_OUTPUT_VOLTAGE_C][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_1_DEVICE][UPS_OUTPUT_VOLTAGE_C][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        旁路A相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_BYPASS_VOLTAGE_A][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_1_DEVICE][UPS_BYPASS_VOLTAGE_A][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        旁路B相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_BYPASS_VOLTAGE_B][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_1_DEVICE][UPS_BYPASS_VOLTAGE_B][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        旁路C相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_BYPASS_VOLTAGE_C][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_1_DEVICE][UPS_BYPASS_VOLTAGE_C][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        输出A相电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_OUTPUT_CURRENT_A][1]);
	printf("                        %.1fA",((float)real_time_value[UPS_1_DEVICE][UPS_OUTPUT_CURRENT_A][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输出B相电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_OUTPUT_CURRENT_B][1]);
	printf("                        %.1fA",((float)real_time_value[UPS_1_DEVICE][UPS_OUTPUT_CURRENT_B][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输出C相电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_OUTPUT_CURRENT_C][1]);
	printf("                        %.1fA",((float)real_time_value[UPS_1_DEVICE][UPS_OUTPUT_CURRENT_C][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        A相负载：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_LOAD_A][1]);
	printf("                        %.1f%%",((float)real_time_value[UPS_1_DEVICE][UPS_LOAD_A][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        B相负载：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_LOAD_B][1]);
	printf("                        %.1f%%",((float)real_time_value[UPS_1_DEVICE][UPS_LOAD_B][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        C相负载：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_LOAD_C][1]);
	printf("                        %.1f%%",((float)real_time_value[UPS_1_DEVICE][UPS_LOAD_C][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        输入频率：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_INPUT_FREQUENCY][1]);
	printf("                        %.1fHz",((float)real_time_value[UPS_1_DEVICE][UPS_INPUT_FREQUENCY][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        旁路频率：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_BYPASS_FREQUENCY][1]);
	printf("                        %.1fHz",((float)real_time_value[UPS_1_DEVICE][UPS_BYPASS_FREQUENCY][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输出频率：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_OUTPUT_FREQUENCY][1]);
	printf("                        %.1fHz",((float)real_time_value[UPS_1_DEVICE][UPS_OUTPUT_FREQUENCY][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        电池电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_BATTERY_VOLTAGE][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_1_DEVICE][UPS_BATTERY_VOLTAGE][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        电池剩余容量：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_BATTERY_CAPACITY][1]);
	printf("                        %.1f%%",((float)real_time_value[UPS_1_DEVICE][UPS_BATTERY_CAPACITY][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        机内温度：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_1_DEVICE][UPS_TEMPERATURE][1]);
	printf("                        %.1f℃",((float)real_time_value[UPS_1_DEVICE][UPS_TEMPERATURE][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("            </table>");
	printf("        </div>");
	printf("        <div id='ups2' style='display:none'>");
	printf("            <p class='eachTitle'>");
	printf("                UPS 2");
	printf("            </p>");
	printf("            <table>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        ups通信状态：");
	printf("                    </td>");
	if(real_time_value[UPS_2_DEVICE][UPS_CONNECTION][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_CONNECTION][1]);
		printf("                        正常");
	}else if(real_time_value[UPS_2_DEVICE][UPS_CONNECTION][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_CONNECTION][1]);
		printf("                        断开");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        ups工作状态：");
	printf("                    </td>");
	if(real_time_value[UPS_2_DEVICE][UPS_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_STATUS][1]);
		printf("                        无输出");
	}else if(real_time_value[UPS_2_DEVICE][UPS_STATUS][0]==10){
		printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_STATUS][1]);
		printf("                        UPS供电");
	}else if(real_time_value[UPS_2_DEVICE][UPS_STATUS][0]==20){
		printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_STATUS][1]);
		printf("                        旁路供电");
	}else if(real_time_value[UPS_2_DEVICE][UPS_STATUS][0]==30){
		printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_STATUS][1]);
		printf("                        电池供电");
	}else if(real_time_value[UPS_2_DEVICE][UPS_STATUS][0]==40){
		printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_STATUS][1]);
		printf("                        手动旁路");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        均浮充状态：");
	printf("                    </td>");
	if(real_time_value[UPS_2_DEVICE][UPS_CHARGE_STATUS][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_CHARGE_STATUS][1]);
		printf("                        浮充");
	}else if(real_time_value[UPS_2_DEVICE][UPS_CHARGE_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_CHARGE_STATUS][1]);
		printf("                        均充");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        负载状态：");
	printf("                    </td>");
	if(real_time_value[UPS_2_DEVICE][UPS_OUTPUT_STATUS][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_OUTPUT_STATUS][1]);
		printf("                        正常");
	}else if(real_time_value[UPS_2_DEVICE][UPS_OUTPUT_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_OUTPUT_STATUS][1]);
		printf("                        过载");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        输入A相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_INPUT_VOLTAGE_A][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_2_DEVICE][UPS_INPUT_VOLTAGE_A][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输入B相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_INPUT_VOLTAGE_B][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_2_DEVICE][UPS_INPUT_VOLTAGE_B][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输入C相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_INPUT_VOLTAGE_C][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_2_DEVICE][UPS_INPUT_VOLTAGE_C][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        输出A相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_OUTPUT_VOLTAGE_A][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_2_DEVICE][UPS_OUTPUT_VOLTAGE_A][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输出B相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_OUTPUT_VOLTAGE_B][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_2_DEVICE][UPS_OUTPUT_VOLTAGE_B][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输出C相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_OUTPUT_VOLTAGE_C][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_2_DEVICE][UPS_OUTPUT_VOLTAGE_C][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        旁路A相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_BYPASS_VOLTAGE_A][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_2_DEVICE][UPS_BYPASS_VOLTAGE_A][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        旁路B相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_BYPASS_VOLTAGE_B][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_2_DEVICE][UPS_BYPASS_VOLTAGE_B][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        旁路C相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_BYPASS_VOLTAGE_C][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_2_DEVICE][UPS_BYPASS_VOLTAGE_C][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        输出A相电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_OUTPUT_CURRENT_A][1]);
	printf("                        %.1fA",((float)real_time_value[UPS_2_DEVICE][UPS_OUTPUT_CURRENT_A][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输出B相电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_OUTPUT_CURRENT_B][1]);
	printf("                        %.1fA",((float)real_time_value[UPS_2_DEVICE][UPS_OUTPUT_CURRENT_B][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输出C相电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_OUTPUT_CURRENT_C][1]);
	printf("                        %.1fA",((float)real_time_value[UPS_2_DEVICE][UPS_OUTPUT_CURRENT_C][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        A相负载：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_LOAD_A][1]);
	printf("                        %.1f%%",((float)real_time_value[UPS_2_DEVICE][UPS_LOAD_A][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        B相负载：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_LOAD_B][1]);
	printf("                        %.1f%%",((float)real_time_value[UPS_2_DEVICE][UPS_LOAD_B][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        C相负载：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_LOAD_C][1]);
	printf("                        %.1f%%",((float)real_time_value[UPS_2_DEVICE][UPS_LOAD_C][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        输入频率：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_INPUT_FREQUENCY][1]);
	printf("                        %.1fHz",((float)real_time_value[UPS_2_DEVICE][UPS_INPUT_FREQUENCY][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        旁路频率：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_BYPASS_FREQUENCY][1]);
	printf("                        %.1fHz",((float)real_time_value[UPS_2_DEVICE][UPS_BYPASS_FREQUENCY][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输出频率：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_OUTPUT_FREQUENCY][1]);
	printf("                        %.1fHz",((float)real_time_value[UPS_2_DEVICE][UPS_OUTPUT_FREQUENCY][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        电池电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_BATTERY_VOLTAGE][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_2_DEVICE][UPS_BATTERY_VOLTAGE][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        电池剩余容量：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_BATTERY_CAPACITY][1]);
	printf("                        %.1f%%",((float)real_time_value[UPS_2_DEVICE][UPS_BATTERY_CAPACITY][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        机内温度：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_2_DEVICE][UPS_TEMPERATURE][1]);
	printf("                        %.1f℃",((float)real_time_value[UPS_2_DEVICE][UPS_TEMPERATURE][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("            </table>");
	printf("        </div>");
	printf("        <div id='ups3' style='display:none'>");
	printf("            <p class='eachTitle'>");
	printf("                UPS 3");
	printf("            </p>");
	printf("            <table>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        ups通信状态：");
	printf("                    </td>");
	if(real_time_value[UPS_3_DEVICE][UPS_CONNECTION][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_CONNECTION][1]);
		printf("                        正常");
	}else if(real_time_value[UPS_3_DEVICE][UPS_CONNECTION][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_CONNECTION][1]);
		printf("                        断开");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        ups工作状态：");
	printf("                    </td>");
	if(real_time_value[UPS_3_DEVICE][UPS_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_STATUS][1]);
		printf("                        无输出");
	}else if(real_time_value[UPS_3_DEVICE][UPS_STATUS][0]==10){
		printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_STATUS][1]);
		printf("                        UPS供电");
	}else if(real_time_value[UPS_3_DEVICE][UPS_STATUS][0]==20){
		printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_STATUS][1]);
		printf("                        旁路供电");
	}else if(real_time_value[UPS_3_DEVICE][UPS_STATUS][0]==30){
		printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_STATUS][1]);
		printf("                        电池供电");
	}else if(real_time_value[UPS_3_DEVICE][UPS_STATUS][0]==40){
		printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_STATUS][1]);
		printf("                        手动旁路");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        均浮充状态：");
	printf("                    </td>");
	if(real_time_value[UPS_3_DEVICE][UPS_CHARGE_STATUS][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_CHARGE_STATUS][1]);
		printf("                        浮充");
	}else if(real_time_value[UPS_3_DEVICE][UPS_CHARGE_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_CHARGE_STATUS][1]);
		printf("                        均充");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        负载状态：");
	printf("                    </td>");
	if(real_time_value[UPS_3_DEVICE][UPS_OUTPUT_STATUS][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_OUTPUT_STATUS][1]);
		printf("                        正常");
	}else if(real_time_value[UPS_3_DEVICE][UPS_OUTPUT_STATUS][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_OUTPUT_STATUS][1]);
		printf("                        过载");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        输入A相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_INPUT_VOLTAGE_A][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_3_DEVICE][UPS_INPUT_VOLTAGE_A][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输入B相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_INPUT_VOLTAGE_B][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_3_DEVICE][UPS_INPUT_VOLTAGE_B][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输入C相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_INPUT_VOLTAGE_C][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_3_DEVICE][UPS_INPUT_VOLTAGE_C][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        输出A相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_OUTPUT_VOLTAGE_A][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_3_DEVICE][UPS_OUTPUT_VOLTAGE_A][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输出B相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_OUTPUT_VOLTAGE_B][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_3_DEVICE][UPS_OUTPUT_VOLTAGE_B][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输出C相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_OUTPUT_VOLTAGE_C][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_3_DEVICE][UPS_OUTPUT_VOLTAGE_C][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        旁路A相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_BYPASS_VOLTAGE_A][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_3_DEVICE][UPS_BYPASS_VOLTAGE_A][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        旁路B相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_BYPASS_VOLTAGE_B][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_3_DEVICE][UPS_BYPASS_VOLTAGE_B][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        旁路C相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_BYPASS_VOLTAGE_C][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_3_DEVICE][UPS_BYPASS_VOLTAGE_C][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        输出A相电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_OUTPUT_CURRENT_A][1]);
	printf("                        %.1fA",((float)real_time_value[UPS_3_DEVICE][UPS_OUTPUT_CURRENT_A][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输出B相电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_OUTPUT_CURRENT_B][1]);
	printf("                        %.1fA",((float)real_time_value[UPS_3_DEVICE][UPS_OUTPUT_CURRENT_B][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输出C相电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_OUTPUT_CURRENT_C][1]);
	printf("                        %.1fA",((float)real_time_value[UPS_3_DEVICE][UPS_OUTPUT_CURRENT_C][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        A相负载：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_LOAD_A][1]);
	printf("                        %.1f%%",((float)real_time_value[UPS_3_DEVICE][UPS_LOAD_A][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        B相负载：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_LOAD_B][1]);
	printf("                        %.1f%%",((float)real_time_value[UPS_3_DEVICE][UPS_LOAD_B][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        C相负载：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_LOAD_C][1]);
	printf("                        %.1f%%",((float)real_time_value[UPS_3_DEVICE][UPS_LOAD_C][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        输入频率：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_INPUT_FREQUENCY][1]);
	printf("                        %.1fHz",((float)real_time_value[UPS_3_DEVICE][UPS_INPUT_FREQUENCY][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        旁路频率：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_BYPASS_FREQUENCY][1]);
	printf("                        %.1fHz",((float)real_time_value[UPS_3_DEVICE][UPS_BYPASS_FREQUENCY][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        输出频率：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_OUTPUT_FREQUENCY][1]);
	printf("                        %.1fHz",((float)real_time_value[UPS_3_DEVICE][UPS_OUTPUT_FREQUENCY][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        电池电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_BATTERY_VOLTAGE][1]);
	printf("                        %.1fV",((float)real_time_value[UPS_3_DEVICE][UPS_BATTERY_VOLTAGE][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        电池剩余容量：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_BATTERY_CAPACITY][1]);
	printf("                        %.1f%%",((float)real_time_value[UPS_3_DEVICE][UPS_BATTERY_CAPACITY][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        机内温度：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[UPS_3_DEVICE][UPS_TEMPERATURE][1]);
	printf("                        %.1f℃",((float)real_time_value[UPS_3_DEVICE][UPS_TEMPERATURE][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("            </table>");
	printf("        </div>");
	printf("    </div>");
	printf("    <div id='acduDetail'>");
	printf("        <div id='acdu' style='display:none'>");
	printf("            <p class='eachTitle'>");
	printf("                交流配电");
	printf("            </p>");
	printf("            <table>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        1路通信状态：");
	printf("                    </td>");
	if(real_time_value[ACDU_DEVICE][ACDU_CONNECTION_1][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_CONNECTION_1][1]);
		printf("                        正常");
	}else if(real_time_value[ACDU_DEVICE][ACDU_CONNECTION_1][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_CONNECTION_1][1]);
		printf("                        断开");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        总电量：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_QUANTITY_1][1]);
	printf("                        %.1fKWh",((float)real_time_value[ACDU_DEVICE][ACDU_QUANTITY_1][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        A相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_VOLTAGE_A_1][1]);
	printf("                        %.1fV",((float)real_time_value[ACDU_DEVICE][ACDU_VOLTAGE_A_1][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        B相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_VOLTAGE_B_1][1]);
	printf("                        %.1fV",((float)real_time_value[ACDU_DEVICE][ACDU_VOLTAGE_B_1][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        C相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_VOLTAGE_C_1][1]);
	printf("                        %.1fV",((float)real_time_value[ACDU_DEVICE][ACDU_VOLTAGE_C_1][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        A相电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_CURRENT_A_1][1]);
	printf("                        %.1fA",((float)real_time_value[ACDU_DEVICE][ACDU_CURRENT_A_1][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        B相电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_CURRENT_B_1][1]);
	printf("                        %.1fA",((float)real_time_value[ACDU_DEVICE][ACDU_CURRENT_B_1][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        C相电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_CURRENT_C_1][1]);
	printf("                        %.1fA",((float)real_time_value[ACDU_DEVICE][ACDU_CURRENT_C_1][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        2路通信状态：");
	printf("                    </td>");
	if(real_time_value[ACDU_DEVICE][ACDU_CONNECTION_2][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_CONNECTION_2][1]);
		printf("                        正常");
	}else if(real_time_value[ACDU_DEVICE][ACDU_CONNECTION_2][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_CONNECTION_2][1]);
		printf("                        断开");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        总电量：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_QUANTITY_2][1]);
	printf("                        %.1fKWh",((float)real_time_value[ACDU_DEVICE][ACDU_QUANTITY_2][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        A相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_VOLTAGE_A_2][1]);
	printf("                        %.1fV",((float)real_time_value[ACDU_DEVICE][ACDU_VOLTAGE_A_2][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        B相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_VOLTAGE_B_2][1]);
	printf("                        %.1fV",((float)real_time_value[ACDU_DEVICE][ACDU_VOLTAGE_B_2][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        C相电压：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_VOLTAGE_C_2][1]);
	printf("                        %.1fV",((float)real_time_value[ACDU_DEVICE][ACDU_VOLTAGE_C_2][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        A相电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_CURRENT_A_2][1]);
	printf("                        %.1fA",((float)real_time_value[ACDU_DEVICE][ACDU_CURRENT_A_2][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        B相电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_CURRENT_B_2][1]);
	printf("                        %.1fA",((float)real_time_value[ACDU_DEVICE][ACDU_CURRENT_B_2][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        C相电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ACDU_DEVICE][ACDU_CURRENT_C_2][1]);
	printf("                        %.1fA",((float)real_time_value[ACDU_DEVICE][ACDU_CURRENT_C_2][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("            </table>");
	printf("        </div>");
	printf("    </div>");
	printf("    <div id='airDetail'>");
	for(i=1;i<=7;i++){
		printf("        <div id='air%d' style='display:none'>",i);
		printf("            <p class='eachTitle'>");
		printf("                空调%d",i);
		printf("            </p>");
		printf("            <table>");
		printf("                <tr>");
		printf("                    <td class='td-head'>");
		printf("                        通信状态：");
		printf("                    </td>");
		if(real_time_value[AIRCONDITIONER_DEVICE][AIR_CONNECTION_1+(i-1)*13][0]==1){
			printf("                    <td class='value status%d'>",real_time_value[AIRCONDITIONER_DEVICE][AIR_CONNECTION_1+(i-1)*13][1]);
			printf("                        正常");
		}else if(real_time_value[AIRCONDITIONER_DEVICE][AIR_CONNECTION_1+(i-1)*13][0]==0){
			printf("                    <td class='value status%d'>",real_time_value[AIRCONDITIONER_DEVICE][AIR_CONNECTION_1+(i-1)*13][1]);
			printf("                        断开");
		}
		printf("                    </td>");
		printf("                </tr>");
		printf("                <tr>");
		printf("                    <td class='td-head'>");
		printf("                        开关机状态：");
		printf("                    </td>");
		if(real_time_value[AIRCONDITIONER_DEVICE][AIR_POWER_SWITCH_I_1+(i-1)*13][0]==1){
			printf("                    <td class='value status%d'>",real_time_value[AIRCONDITIONER_DEVICE][AIR_POWER_SWITCH_I_1+(i-1)*13][1]);
			printf("                        开机");
		}else if(real_time_value[AIRCONDITIONER_DEVICE][AIR_POWER_SWITCH_I_1+(i-1)*13][0]==0){
			printf("                    <td class='value status%d'>",real_time_value[AIRCONDITIONER_DEVICE][AIR_POWER_SWITCH_I_1+(i-1)*13][1]);
			printf("                        关机");
		}
		printf("                    </td>");
		printf("                    <td class='td-head'>");
		printf("                        工作状态：");
		printf("                    </td>");
		if(real_time_value[AIRCONDITIONER_DEVICE][AIR_MODE_I_1+(i-1)*13][0]==0){
			printf("                    <td class='value status%d'>",real_time_value[AIRCONDITIONER_DEVICE][AIR_MODE_I_1+(i-1)*13][1]);
			printf("                        无");
		}else if(real_time_value[AIRCONDITIONER_DEVICE][AIR_MODE_I_1+(i-1)*13][0]==10){
			printf("                    <td class='value status%d'>",real_time_value[AIRCONDITIONER_DEVICE][AIR_MODE_I_1+(i-1)*13][1]);
			printf("                        制冷");
		}else if(real_time_value[AIRCONDITIONER_DEVICE][AIR_MODE_I_1+(i-1)*13][0]==20){
			printf("                    <td class='value status%d'>",real_time_value[AIRCONDITIONER_DEVICE][AIR_MODE_I_1+(i-1)*13][1]);
			printf("                        制热");
		}else if(real_time_value[AIRCONDITIONER_DEVICE][AIR_MODE_I_1+(i-1)*13][0]==30){
			printf("                    <td class='value status%d'>",real_time_value[AIRCONDITIONER_DEVICE][AIR_MODE_I_1+(i-1)*13][1]);
			printf("                        自动");
		}else if(real_time_value[AIRCONDITIONER_DEVICE][AIR_MODE_I_1+(i-1)*13][0]==40){
			printf("                    <td class='value status%d'>",real_time_value[AIRCONDITIONER_DEVICE][AIR_MODE_I_1+(i-1)*13][1]);
			printf("                        除湿");
		}
		printf("                    </td>");
		printf("                    <td class='td-head'>");
		printf("                        设定温度：");
		printf("                    </td>");
		printf("                    <td class='value status%d'>",real_time_value[AIRCONDITIONER_DEVICE][AIR_TEM_SET_I_1+(i-1)*13][1]);
		printf("                        %.1f℃",((float)real_time_value[AIRCONDITIONER_DEVICE][AIR_TEM_SET_I_1+(i-1)*13][0])/10);
		printf("                    </td>");
		printf("                </tr>");
		printf("                <tr>");
		printf("                    <td class='td-head'>");
		printf("                        A相电压：");
		printf("                    </td>");
		printf("                    <td class='value status%d'>",real_time_value[AIRCONDITIONER_DEVICE][AIR_VOLTAGE_A_1+(i-1)*13][1]);
		printf("                        %.1fV",((float)real_time_value[AIRCONDITIONER_DEVICE][AIR_VOLTAGE_A_1+(i-1)*13][0])/10);
		printf("                    </td>");
		printf("                    <td class='td-head'>");
		printf("                        B相电压：");
		printf("                    </td>");
		printf("                    <td class='value status%d'>",real_time_value[AIRCONDITIONER_DEVICE][AIR_VOLTAGE_B_1+(i-1)*13][1]);
		printf("                        %.1fV",((float)real_time_value[AIRCONDITIONER_DEVICE][AIR_VOLTAGE_B_1+(i-1)*13][0])/10);
		printf("                    </td>");
		printf("                    <td class='td-head'>");
		printf("                        C相电压：");
		printf("                    </td>");
		printf("                    <td class='value status%d'>",real_time_value[AIRCONDITIONER_DEVICE][AIR_VOLTAGE_C_1+(i-1)*13][1]);
		printf("                        %.1fV",((float)real_time_value[AIRCONDITIONER_DEVICE][AIR_VOLTAGE_C_1+(i-1)*13][0])/10);
		printf("                    </td>");
		printf("                </tr>");
		printf("                <tr>");
		printf("                    <td class='td-head'>");
		printf("                        A相电流：");
		printf("                    </td>");
		printf("                    <td class='value status%d'>",real_time_value[AIRCONDITIONER_DEVICE][AIR_CURRENT_A_1+(i-1)*13][1]);
		printf("                        %.1fA",((float)real_time_value[AIRCONDITIONER_DEVICE][AIR_CURRENT_A_1+(i-1)*13][0])/10);
		printf("                    </td>");
		printf("                    <td class='td-head'>");
		printf("                        B相电流：");
		printf("                    </td>");
		printf("                    <td class='value status%d'>",real_time_value[AIRCONDITIONER_DEVICE][AIR_CURRENT_B_1+(i-1)*13][1]);
		printf("                        %.1fA",((float)real_time_value[AIRCONDITIONER_DEVICE][AIR_CURRENT_B_1+(i-1)*13][0])/10);
		printf("                    </td>");
		printf("                    <td class='td-head'>");
		printf("                        C相电流：");
		printf("                    </td>");
		printf("                    <td class='value status%d'>",real_time_value[AIRCONDITIONER_DEVICE][AIR_CURRENT_C_1+(i-1)*13][1]);
		printf("                        %.1fA",((float)real_time_value[AIRCONDITIONER_DEVICE][AIR_CURRENT_C_1+(i-1)*13][0])/10);
		printf("                    </td>");
		printf("                </tr>");
		printf("            </table>");
		printf("        </div>");
	}
	printf("    </div>");
	printf("    <div id='dbDetail'>");
	int previous_battery_number=0;
	for(j=1;j<=6;j++){
		printf("        <div id='db%d' style='display:none'>",j);
		printf("            <p class='eachTitle'>");
		printf("                单体电池%d组",j);
		printf("            </p>");
		printf("            <table>");
		printf("                <tr>");
		printf("                    <td class='td-head'>");
		printf("                        %d组压差：",j);
		printf("                    </td>");
		printf("                    <td class='value status%d'>",real_time_value[BATTERY_DEVICE][BATTERY_VOLTAGE_DIFFERENTIAL_1+j-1][1]);
		printf("                        %.1fV",((float)real_time_value[BATTERY_DEVICE][BATTERY_VOLTAGE_DIFFERENTIAL_1+j-1][0])/1000);
		printf("                    </td>");
		printf("                </tr>");
		for(i=1;i<=DB[j];i++){
			printf("                <tr>");
			printf("                    <td class='td-head'>");
			printf("                        %d节通信：",i);
			printf("                    </td>");
			if(real_time_value[BATTERY_DEVICE][14+(previous_battery_number+i-1)*4][0]==1){
				printf("                    <td class='value status%d'>",real_time_value[BATTERY_DEVICE][14+(previous_battery_number+i-1)*4][1]);
				printf("                        断开");
			}else if(real_time_value[BATTERY_DEVICE][14+(previous_battery_number+i-1)*4][0]==0){
				printf("                    <td class='value status%d'>",real_time_value[BATTERY_DEVICE][14+(previous_battery_number+i-1)*4][1]);
				printf("                        正常");
			}
			printf("                    </td>");
			printf("                </tr>");
			printf("                <tr>");
			printf("                    <td class='td-head'>");
			printf("                        %d节电压：",i);
			printf("                    </td>");
			printf("                    <td class='value status%d'>",real_time_value[BATTERY_DEVICE][11+(previous_battery_number+i-1)*4][1]);
			printf("                        %.1fV",((float)real_time_value[BATTERY_DEVICE][11+(previous_battery_number+i-1)*4][0])/1000);
			printf("                    </td>");
			printf("                    <td class='td-head'>");
			printf("                        %d节温度：",i);
			printf("                    </td>");
			printf("                    <td class='value status%d'>",real_time_value[BATTERY_DEVICE][12+(previous_battery_number+i-1)*4][1]);
			printf("                        %.1f℃",((float)real_time_value[BATTERY_DEVICE][12+(previous_battery_number+i-1)*4][0])/1000);
			printf("                    </td>");
			printf("                    <td class='td-head'>");
			printf("                        %d节内阻：",i);
			printf("                    </td>");
			printf("                    <td class='value status%d'>",real_time_value[BATTERY_DEVICE][13+(previous_battery_number+i-1)*4][1]);
			printf("                        %.1fmΩ",((float)real_time_value[BATTERY_DEVICE][13+(previous_battery_number+i-1)*4][0])/1000);
			printf("                    </td>");
			printf("                </tr>");
		}
		printf("            </table>");
		printf("        </div>");
		previous_battery_number=previous_battery_number+DB[j];
	}
	printf("    </div>");
	printf("    <div id='spdDetail'>");
	printf("        <div id='spd' style='display:none'>");
	printf("            <p class='eachTitle'>");
	printf("                防雷");
	printf("            </p>");
	printf("            <table>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        防雷器通信：");
	printf("                    </td>");
	if(real_time_value[SPD_DEVICE][SPD_CONNECTION][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[SPD_DEVICE][SPD_CONNECTION][1]);
		printf("                        正常");
	}else if(real_time_value[SPD_DEVICE][SPD_CONNECTION][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[SPD_DEVICE][SPD_CONNECTION][1]);
		printf("                        断开");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        1路防雷状态：");
	printf("                    </td>");
	if(real_time_value[SPD_DEVICE][SPD_ERROR_1][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[SPD_DEVICE][SPD_ERROR_1][1]);
		printf("                        正常");
	}else if(real_time_value[SPD_DEVICE][SPD_ERROR_1][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[SPD_DEVICE][SPD_ERROR_1][1]);
		printf("                        故障");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        1路空开状态：");
	printf("                    </td>");
	if(real_time_value[SPD_DEVICE][SPD_SWITCH_TRIP_1_ALARM][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[SPD_DEVICE][SPD_SWITCH_TRIP_1_ALARM][1]);
		printf("                        正常");
	}else if(real_time_value[SPD_DEVICE][SPD_SWITCH_TRIP_1_ALARM][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[SPD_DEVICE][SPD_SWITCH_TRIP_1_ALARM][1]);
		printf("                        故障");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        累计雷击次数：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[SPD_DEVICE][SPD_CUMULATIVE_NUMBER][1]);
	printf("                        %d℃",((int)real_time_value[SPD_DEVICE][TEMPERATURE_1][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        2路防雷状态：");
	printf("                    </td>");
	if(real_time_value[SPD_DEVICE][SPD_ERROR_2][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[SPD_DEVICE][SPD_ERROR_2][1]);
		printf("                        正常");
	}else if(real_time_value[SPD_DEVICE][SPD_ERROR_2][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[SPD_DEVICE][SPD_ERROR_2][1]);
		printf("                        故障");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        2路空开状态：");
	printf("                    </td>");
	if(real_time_value[SPD_DEVICE][SPD_SWITCH_TRIP_2_ALARM][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[SPD_DEVICE][SPD_SWITCH_TRIP_2_ALARM][1]);
		printf("                        正常");
	}else if(real_time_value[SPD_DEVICE][SPD_SWITCH_TRIP_2_ALARM][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[SPD_DEVICE][SPD_SWITCH_TRIP_2_ALARM][1]);
		printf("                        故障");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        最近雷击电流：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[SPD_DEVICE][SPD_LAST_LIGHTNING_PEAK][1]);
	printf("                        %.1fA",((float)real_time_value[SPD_DEVICE][SPD_LAST_LIGHTNING_PEAK][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("            </table>");
	printf("        </div>");
	printf("    </div>");
	printf("    <div id='enDetail'>");
	printf("        <div id='en' style='display:block'>");
	printf("            <p class='eachTitle'>");
	printf("                环境");
	printf("            </p>");
	printf("            <table>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        温度1：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][TEMPERATURE_1][1]);
	printf("                        %.1f℃",((float)real_time_value[ENVIRONMENT_DEVICE][TEMPERATURE_1][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        湿度1：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][HUMIDITY_1][1]);
	printf("                        %.1f%%",((float)real_time_value[ENVIRONMENT_DEVICE][HUMIDITY_1][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        门禁1：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][ACCESS_1][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][ACCESS_1][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][ACCESS_1][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][ACCESS_1][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        水浸1：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][WATER_1][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][WATER_1][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][WATER_1][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][WATER_1][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        烟感1：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][SMOKE_1][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][SMOKE_1][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][SMOKE_1][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][SMOKE_1][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        玻璃破碎1：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][GLASS_1][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][GLASS_1][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][GLASS_1][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][GLASS_1][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        红外1：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][INFRARED_1][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][INFRARED_1][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][INFRARED_1][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][INFRARED_1][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        温度2：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][TEMPERATURE_2][1]);
	printf("                        %.1f℃",((float)real_time_value[ENVIRONMENT_DEVICE][TEMPERATURE_2][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        湿度2：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][HUMIDITY_2][1]);
	printf("                        %.1f%%",((float)real_time_value[ENVIRONMENT_DEVICE][HUMIDITY_2][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        门禁2：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][ACCESS_2][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][ACCESS_2][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][ACCESS_2][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][ACCESS_2][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        水浸2：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][WATER_2][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][WATER_2][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][WATER_2][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][WATER_2][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        烟感2：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][SMOKE_2][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][SMOKE_2][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][SMOKE_2][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][SMOKE_2][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        玻璃破碎2：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][GLASS_2][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][GLASS_2][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][GLASS_2][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][GLASS_2][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        红外2：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][INFRARED_2][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][INFRARED_2][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][INFRARED_2][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][INFRARED_2][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        温度3：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][TEMPERATURE_3][1]);
	printf("                        %.1f℃",((float)real_time_value[ENVIRONMENT_DEVICE][TEMPERATURE_3][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        湿度3：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][HUMIDITY_3][1]);
	printf("                        %.1f%%",((float)real_time_value[ENVIRONMENT_DEVICE][HUMIDITY_3][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        门禁3：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][ACCESS_3][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][ACCESS_3][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][ACCESS_3][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][ACCESS_3][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        水浸3：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][WATER_3][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][WATER_3][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][WATER_3][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][WATER_3][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        烟感3：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][SMOKE_3][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][SMOKE_3][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][SMOKE_3][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][SMOKE_3][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        玻璃破碎3：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][GLASS_3][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][GLASS_3][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][GLASS_3][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][GLASS_3][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        红外3：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][INFRARED_3][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][INFRARED_3][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][INFRARED_3][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][INFRARED_3][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        温度4：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][TEMPERATURE_4][1]);
	printf("                        %.1f℃",((float)real_time_value[ENVIRONMENT_DEVICE][TEMPERATURE_4][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        湿度4：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][HUMIDITY_4][1]);
	printf("                        %.1f%%",((float)real_time_value[ENVIRONMENT_DEVICE][HUMIDITY_4][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        门禁4：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][ACCESS_4][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][ACCESS_4][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][ACCESS_4][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][ACCESS_4][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        水浸4：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][WATER_4][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][WATER_4][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][WATER_4][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][WATER_4][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        烟感4：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][SMOKE_4][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][SMOKE_4][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][SMOKE_4][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][SMOKE_4][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        玻璃破碎4：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][GLASS_4][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][GLASS_4][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][GLASS_4][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][GLASS_4][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        红外4：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][INFRARED_4][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][INFRARED_4][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][INFRARED_4][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][INFRARED_4][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        温度5：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][TEMPERATURE_5][1]);
	printf("                        %.1f℃",((float)real_time_value[ENVIRONMENT_DEVICE][TEMPERATURE_5][0])/10);
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        湿度5：");
	printf("                    </td>");
	printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][HUMIDITY_5][1]);
	printf("                        %.1f%%",((float)real_time_value[ENVIRONMENT_DEVICE][HUMIDITY_5][0])/10);
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        门禁5：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][ACCESS_5][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][ACCESS_5][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][ACCESS_5][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][ACCESS_5][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        水浸5：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][WATER_5][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][WATER_5][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][WATER_5][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][WATER_5][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        烟感5：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][SMOKE_5][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][SMOKE_5][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][SMOKE_5][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][SMOKE_5][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("                <tr>");
	printf("                    <td class='td-head'>");
	printf("                        玻璃破碎5：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][GLASS_5][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][GLASS_5][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][GLASS_5][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][GLASS_5][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                    <td class='td-head'>");
	printf("                        红外5：");
	printf("                    </td>");
	if(real_time_value[ENVIRONMENT_DEVICE][INFRARED_5][0]==0){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][INFRARED_5][1]);
		printf("                        正常");
	}else if(real_time_value[ENVIRONMENT_DEVICE][INFRARED_5][0]==1){
		printf("                    <td class='value status%d'>",real_time_value[ENVIRONMENT_DEVICE][INFRARED_5][1]);
		printf("                        告警");
	}
	printf("                    </td>");
	printf("                </tr>");
	printf("            </table>");
	printf("        </div>");
	printf("    </div>");
	printf("</div>");
	printf("</body>");
	printf("<script src='/realtime.js'></script>");
	printf("<script src='/realtime2.js'></script>");
	printf("<script>");
	printf("	jQuery(function ($) {");
	printf("		var menu = $('.rm-nav').rMenu({");
	printf("			minWidth: '960px',");
	printf("		});");
	printf("	});");
	printf("</script>");
	printf("</html>");

  return 1;
}
