#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include "object.h"

// entrance function
void init();
void run();

// sys file operation
void create_sys_file();
void write_user_file(USER *u);
void read_user_file(USER *u);
void write_room_file(ROOM *r);
void read_room_file(ROOM *r);
void write_reserv_file(RESERV *r);
void read_reserv_file(RESERV *r);
void print_user(USER *u);
void print_room(ROOM *r);
void print_reserv(RESERV *r);

// login
void user_login();
void get_login_info(USER *u);
int check_login_info(USER *u);

// register
void user_register();
// date operation
int compare_date(DATE *d1, DATE *d2);
int is_date_conflict(DATE *d1_in, DATE *d2_in, DATE *d1_out, DATE *d2_out);

// room operation
// return -1->not found,return >=0->rl the index of array
int find_room_by_id(ROOM *rl, char *room_id);
// success return 0,fail return 1
int add_room(ROOM *r);
// success return 0,fail return 1
int modify_room(ROOM *r);

// reservation operation
int find_resv_by_id(int r_id);
int add_resv(RESERV *r);
int update_resv(RESERV *r);
void copy_resv_obj(RESERV *dest, RESERV *sour);

//menu
void booking(USER *u);
int search_available_room(int room_type, int adults_kids, DATE check_in, DATE check_out);
void cancellation(USER *u);
void modify_booking(USER *u);
void view_reservation(USER *u);
void upload_room_detail();
void modify_room_detail();
void view_all_reservations();
void search_reservation();
void view_cancellation();
void search_cancellation(int r_id);
