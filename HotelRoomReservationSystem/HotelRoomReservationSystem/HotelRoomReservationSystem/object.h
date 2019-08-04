#pragma once
#define USER_ID_MAX_LEN 13
#define PASSWORD_MAX_LEN 13
#define USER_MAX_NUM 100
#define ROOM_ID_LEN 4
#define ROOM_MAX_NUM 100
#define RESERVATION_MAX_LEN 1000
typedef struct user
{
	char user_id[USER_ID_MAX_LEN];
	char passwd[PASSWORD_MAX_LEN];
	int role; //0-->customer ;1-->admin
}USER;

typedef struct date
{
	char year[5]; //e.g. "2019\0" 
	char month[3]; //e.g. "07\0"
	char day[3]; //e.g. "01\0"
}DATE;

typedef struct room
{
	char room_id[ROOM_ID_LEN];
	int room_type; //1-single,2-double
	int adults_kids; //1-adults,2-kids
}ROOM;

typedef struct customer
{
	char user_id[13];
	char name[10];
	int gender;
	int age;
}CUSTOMER;

typedef struct reservation
{
	int r_id;
	char room_id[ROOM_ID_LEN];
	CUSTOMER c;
	DATE check_in;
	DATE check_out;
	int is_cancel;
	char cancel_reason[100];
}RESERV;
