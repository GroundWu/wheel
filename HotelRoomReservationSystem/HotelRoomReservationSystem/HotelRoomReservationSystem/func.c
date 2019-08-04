#include "func.h"

// global variable
USER ul[USER_MAX_NUM];
ROOM rl[ROOM_MAX_NUM];
RESERV rs[RESERVATION_MAX_LEN];
int user_num = 0;
int room_num = 0;
int reserv_num = 0;

void run()
{
	while (1)
	{
		int i = 0;
		printf("Enter a value to select an operation as follow:\n");
		printf("1. login\n");
		printf("2. register\n");
		printf("3. exit\n");
		printf("your input:");
		scanf("%d", &i);

		switch (i)
		{
		case 1:
			printf("\nlogin...\n");
			user_login();
			system("cls");
			break;
		case 2:
			printf("\nregister...\n");
			user_register();
			system("cls");
			break;
		case 3:
			printf("\nexit the system\n");
			system("cls");
			exit(0);
		default:
			printf("\nYour input is not valid! Please input the correct number.\n\n");
			break;
		}
	}
}

void create_sys_file()
{
	FILE *user_f = NULL;
	FILE *room_f = NULL;
	FILE *reserv_f = NULL;

	if ((user_f = fopen("user_file.txt", "a")) == NULL)
	{
		printf("user_file.txt open failed!\n");
		exit(1);
	}

	if ((room_f = fopen("room_file.txt", "a")) == NULL)
	{
		printf("room_file.txt open failed!\n");
		exit(1);
	}

	if ((reserv_f = fopen("reserv_file.txt", "a")) == NULL)
	{
		printf("reserv_file.txt open failed!\n");
		exit(1);
	}

	fclose(user_f);
	fclose(room_f);
	fclose(reserv_f);

	return;
}

void init()
{
	//check the system_file ,if not exist,create the files
	create_sys_file();
	// read user_file.txt to load the users
	read_user_file(ul);
	read_room_file(rl);
	read_reserv_file(rs);

}

void write_user_file(USER *u)
{
	FILE *fp = NULL;
	if ((fp = fopen("user_file.txt", "a+")) == NULL)
	{
		printf("user_file.txt write failed!\n");
		exit(1);
	}

	fprintf(fp, "%s %s %d\n", u->user_id, u->passwd, u->role);
	fclose(fp);
	return;
}

void write_room_file(ROOM *r)
{
	FILE *fp = NULL;
	if ((fp = fopen("room_file.txt", "a+")) == NULL)
	{
		printf("room_file.txt write failed!\n");
		exit(1);
	}

	fprintf(fp, "%s %d %d\n", r->room_id, r->adults_kids, r->room_type);
	fclose(fp);
	return;
}

void read_user_file(USER *u)
{
	FILE *fp = NULL;
	USER tmp;
	if ((fp = fopen("user_file.txt", "r")) == NULL)
	{
		printf("user_file.txt read failed!\n");
		exit(1);
	}

	while (fscanf(fp, "%s %s %d\n", tmp.user_id, tmp.passwd, &tmp.role) != EOF)
	{
		strcpy(u[user_num].user_id, tmp.user_id);
		strcpy(u[user_num].passwd, tmp.passwd);
		u[user_num].role = tmp.role;
		// print_user(&u[user_num]);
		user_num++;
	}
	fclose(fp);
	return;
}

void read_room_file(ROOM *r)
{
	FILE *fp = NULL;
	ROOM tmp;
	if ((fp = fopen("room_file.txt", "r")) == NULL)
	{
		printf("room_file.txt read failed!\n");
		exit(1);
	}

	while (fscanf(fp, "%s %d %d\n", tmp.room_id, &tmp.adults_kids, &tmp.room_type) != EOF)
	{
		strcpy(r[room_num].room_id, tmp.room_id);
		r[room_num].adults_kids = tmp.adults_kids;
		r[room_num].room_type = tmp.room_type;
		//print_room(&rl[room_num]);
		room_num++;
	}
	fclose(fp);
}

void write_reserv_file(RESERV * r)
{
	FILE *fp = NULL;
	if ((fp = fopen("reserv_file.txt", "a+")) == NULL)
	{
		printf("reserv_file.txt write failed!\n");
		exit(1);
	}

	fprintf(fp, "%d %s %s %s %d %d %s %s %s %s %s %s %d %s\n", r->r_id, r->room_id, r->c.user_id,
		r->c.name, r->c.gender, r->c.age, r->check_in.year, r->check_in.month, r->check_in.day,
		r->check_out.year, r->check_out.month, r->check_out.day, r->is_cancel, r->cancel_reason);
	fclose(fp);
	return;
}

void read_reserv_file(RESERV * r)
{
	FILE *fp = NULL;
	RESERV tmp;
	if ((fp = fopen("reserv_file.txt", "r")) == NULL)
	{
		printf("reserv_file.txt read failed!\n");
		exit(1);
	}

	while (fscanf(fp, "%d %s %s %s %d %d %s %s %s %s %s %s %d %s\n",
		&tmp.r_id, tmp.room_id, tmp.c.user_id, tmp.c.name, &tmp.c.gender, &tmp.c.age, tmp.check_in.year,
		tmp.check_in.month, tmp.check_in.day, tmp.check_out.year, tmp.check_out.month, tmp.check_out.day,
		&tmp.is_cancel, tmp.cancel_reason) != EOF)
	{
		copy_resv_obj(&rs[reserv_num], &tmp);
		reserv_num++;
	}

	fclose(fp);
	return;
}

void print_user(USER *u)
{
	printf("\nuser info\nuser_id:%s\npassword:%s\nrole:%d\n", u->user_id, u->passwd, u->role);
}

void print_room(ROOM *r)
{
	printf("\nroom detail\nroom_id:%s\nadults_kids:%d\nroom_type:%d\n", r->room_id, r->adults_kids, r->room_type);
}

void print_reserv(RESERV * r)
{
	printf("\nreservations info\nreservation id:%d\nroom_id:%s\nuser_id:%s\ncustomer name:%s\ngender:%d\nage:%d\ncheck in date:%s-%s-%s\ncheck out date:%s-%s-%s\nis_cancel:%s\ncancel reason:%s\n",
		r->r_id, r->room_id, r->c.user_id,
		r->c.name, r->c.gender, r->c.age, r->check_in.year, r->check_in.month, r->check_in.day,
		r->check_out.year, r->check_out.month, r->check_out.day, (r->is_cancel == 1 ? "YES" : "NO"), r->cancel_reason);
}

void user_login()
{
	USER u;
	int i = 0;
	int is_login = 0;

	while (i<3) {
		printf("No.%d\'s input\n", i);
		// get the user_id and password from stdin

		get_login_info(&u);
		// check the user_id and password 
		is_login = check_login_info(&u);
		// the use_id and password is correct
		if (is_login == 1) {
			printf("\nlogin sucessfully!\n\n");
			break;
		}
		else {
			printf("\nyour user_id or password is wrong.please retry.\n\n");
		}
		i++;
	}

	if (i == 3) {
		printf("Your user_id or password is not correct.Please retry or register a new account!\n\n");
		return;
	}

	while (1)
	{
		int op = 0;
		// display the menu after login successfully
		printf("Enter a value to select a operation as follow:\n");
		printf("1. Booking\n");
		printf("2. Cancellation\n");
		printf("3. Modify Booking\n");
		printf("4. View the Reservation\n");
		if (u.role == 1)
		{
			printf("5. Upload Room detail (for Admin)\n");
			printf("6. Modify the room detail (for Admin)\n");
			printf("7. View all the Reservations (for Admin)\n");
			printf("8. Search the Reservation (for Admin)\n");
			printf("9. View all the Cancellations (for Admin)\n");
			printf("10. Search the Cancellation (for Admin)\n");
		}
		printf("\n0. exit\n");

		printf("your input:");
		scanf("%d", &op);

		switch (op)
		{
		case 1:
			printf("\nBooking...\n");
			booking(&u);
			break;
		case 2:
			printf("\nCacellation...\n");
			cancellation(&u);
			break;
		case 3:
			printf("\nModify Booking...\n");
			modify_booking(&u);
			break;
		case 4:
			printf("\nView the Reservation...\n");
			view_reservation(&u);
			break;
		case 5:
			printf("\nUpload Room detail...(for Admin)\n");
			upload_room_detail();
			break;
		case 6:
			printf("\nModify the room detail...(for Admin)\n");
			modify_room_detail();
			break;
		case 7:
			printf("\nView all the Reservations...(for Admin)\n");
			view_all_reservations();
			break;
		case 8:
			printf("\nSearch the Reservation...(for Admin)\n");
			search_reservation();
			break;
		case 9:
			printf("\nView all the Cancellations (for Admin)...\n");
			view_cancellation();
			break;
		case 10:
			printf("\nSearch the Cancellation (for Admin)...\n");
			search_reservation();
			break;
		case 0:
			printf("\nexit...\n");
			return;
		default:
			printf("\nYour input is not valid! Please input the correct number.\n\n");
			break;

		}
	}
}

void get_login_info(USER* u)
{
	char c = '\0';
	printf("input your user_id and password\n");
	printf("use_id (max length is 12):");
	scanf("%s", u->user_id);
	printf("password (max length is 12):");
	int i = 0;
	do
	{
		c = getch();

		if (c != '\r' && c != '\b')
		{
			u->passwd[i++] = c;
			putchar('*');
		}
		else if (c == '\b')
		{
			u->passwd[--i] = '\0';
			putchar('\b');
			putchar(' ');
			putchar('\b');
		}
		else
		{
			break;
		}

	} while (i < (PASSWORD_MAX_LEN - 1) && c != '\r');

	u->passwd[i] = '\0';
	return;
}

// return->1,correct;return->0,wrong
int check_login_info(USER *u)
{
	for (int i = 0;i < user_num;i++)
	{

		if (strcmp(u->user_id, ul[i].user_id) == 0)
		{
			if (strcmp(u->passwd, ul[i].passwd) == 0)
			{
				u->role = ul[i].role;
				return 1;
			}
		}
	}
	return 0;

}

void user_register()
{
	// create a new user
	USER new_user;
	printf("\ninput your user_id and password\n");
	printf("use_id (max length is 12):");
	scanf("%s", new_user.user_id);
	printf("password (max length is 12):");
	scanf("%s", new_user.passwd);
	new_user.role = 0;
	// update the user list
	strcpy(ul[user_num].user_id, new_user.user_id);
	strcpy(ul[user_num].passwd, new_user.passwd);
	ul[user_num].role = new_user.role;
	user_num++;

	// write the new user info to the user_file.txt 
	write_user_file(&new_user);

	// display the user info
	printf("\nRegister sccuessfully!\n");
	print_user(&new_user);
}
//d1>d2 return 1;else return 0
int compare_date(DATE * d1, DATE * d2)
{
	if (strcmp(d1->year, d2->year) > 0) {
		return 1;
	}
	else if (strcmp(d1->year, d2->year) == 0) {

		if (strcmp(d1->month, d2->month) > 0) {
			return 1;
		}
		else if (strcmp(d1->month, d2->month) == 0)
		{
			if (strcmp(d1->day, d2->day) > 0)
				return 1;
		}
	}
			
	return 0;
}
// conflict return 1 else return 0
int is_date_conflict(DATE *d1_in, DATE *d2_in, DATE *d1_out, DATE *d2_out)
{
	if (compare_date(d2_in, d1_out) == 1 || compare_date(d1_in, d2_out) == 1)
		return 0;
	return 1;
}

int find_room_by_id(ROOM *rl, char * room_id)
{
	for (int i = 0;i < room_num;i++)
	{
		if (strcmp(rl[i].room_id, room_id) == 0)
		{
			return i;
		}
	}
	return -1;
}

int add_room(ROOM * r)
{

	if (room_num + 1 > ROOM_MAX_NUM)
		return 1;

	// check the room_id if exist
	if (find_room_by_id(rl, r->room_id) == -1) {

		// add to list
		strcpy(rl[room_num].room_id, r->room_id);
		rl[room_num].adults_kids = r->adults_kids;
		rl[room_num].room_type = r->room_type;
		room_num++;
		// append to room_file.txt
		write_room_file(r);
		return 0;
	}
	return 1;
}

int modify_room(ROOM * r)
{
	int idx = find_room_by_id(rl, r->room_id);
	if (idx != -1)
	{
		strcpy(rl[idx].room_id, r->room_id);
		rl[idx].adults_kids = r->adults_kids;
		rl[idx].room_type = r->room_type;

		//rewrite the room_file.txt
		FILE *fp = NULL;
		if ((fp = fopen("room_file.txt", "w")) == NULL)
		{
			printf("room_file.txt write failed!\n");
			exit(1);
		}
		for (int i = 0;i<room_num;i++)
			fprintf(fp, "%s %d %d\n", rl[i].room_id, rl[i].adults_kids, rl[i].room_type);
		fclose(fp);
		return 0;
	}
	return 1;
}

int find_resv_by_id(int r_id)
{
	for (int i = 0;i < reserv_num;i++)
	{
		if (rs[i].r_id == r_id)
			return i;
	}
	return -1;
}

int add_resv(RESERV * r)
{
	if (find_resv_by_id(r->r_id) == -1)
	{
		copy_resv_obj(&rs[reserv_num], r);
		reserv_num++;
		write_reserv_file(r);
		return 0;
	}
	return 1;
}

int update_resv(RESERV *r)
{
	int idx = find_resv_by_id(r->r_id);
	if (idx != -1)
	{
		copy_resv_obj(&rs[idx], r);
		FILE *fp = NULL;
		if ((fp = fopen("reserv_file.txt", "w")) == NULL)
		{
			printf("reserv_file.txt write failed!\n");
			exit(1);
		}

		for (int i = 0;i<reserv_num;i++)
			fprintf(fp, "%d %s %s %s %d %d %s %s %s %s %s %s %d %s\n", rs[i].r_id, rs[i].room_id, rs[i].c.user_id,
				rs[i].c.name, rs[i].c.gender, rs[i].c.age, rs[i].check_in.year, rs[i].check_in.month,
				rs[i].check_in.day, rs[i].check_out.year, rs[i].check_out.month, rs[i].check_out.day,
				rs[i].is_cancel, rs[i].cancel_reason);

		fclose(fp);
		return 0;

	}
	return 1;
}

void copy_resv_obj(RESERV * dest, RESERV * sour)
{
	dest->r_id = sour->r_id;
	strcpy(dest->room_id, sour->room_id);
	strcpy(dest->c.user_id, sour->c.user_id);
	strcpy(dest->c.name, sour->c.name);
	dest->c.gender = sour->c.gender;
	dest->c.age = sour->c.age;
	strcpy(dest->check_in.year, sour->check_in.year);
	strcpy(dest->check_in.month, sour->check_in.month);
	strcpy(dest->check_in.day, sour->check_in.day);
	strcpy(dest->check_out.year, sour->check_out.year);
	strcpy(dest->check_out.month, sour->check_out.month);
	strcpy(dest->check_out.day, sour->check_out.day);
	dest->is_cancel = sour->is_cancel;
	strcpy(dest->cancel_reason, sour->cancel_reason);
	return;
}

void booking(USER * u)
{

	RESERV rs;
	// fill in the room
	int room_type; // 1 or 2
	int adults_kids; // 1 or 2
	DATE check_in;
	DATE check_out;
	// get values from stdin
	printf("Please input the room type(1-single,2-double):");
	scanf("%d", &room_type);
	printf("Please select the adult (1) or kid (2):");
	scanf("%d", &adults_kids);
	printf("Please input the check in date (format as yyyy mm dd):");
	scanf("%s %s %s", check_in.year, check_in.month, check_in.day);
	printf("Please input the check out date (format as yyyy mm dd):");
	scanf("%s %s %s", check_out.year, check_out.month, check_out.day);
	// search for available room and display the result
	int res = search_available_room(room_type, adults_kids, check_in, check_out);
	printf("there are %d available rooms.\n",res);
	if (res == 0)
		return;

	//select the specific available room
	printf("Please select the specific room showed above:(input the room_id:xxx):");
	scanf("%s", rs.room_id);
	rs.r_id = ++reserv_num;
	memcpy(&(rs.check_in), &check_in, sizeof(DATE));
	memcpy(&(rs.check_out), &check_out, sizeof(DATE));
	printf("input your personal info:\n");
	strcpy(rs.c.user_id, u->user_id);
	printf("name:");
	scanf("%s", rs.c.name);
	printf("age:");
	scanf("%d", &rs.c.age);
	printf("gender:(male:1,female:2):");
	scanf("%d", &rs.c.gender);
	rs.is_cancel = 0;
	strcpy(rs.cancel_reason, "none");
	//add the reservation
	if (add_resv(&rs) == 0)
	{
		printf("\nbooking successfully,your reservation info:");
		print_reserv(&rs);
		putchar('\n');
	}
	else {
		printf("\nyour booking operation is failed.Please retry.\n");
		--reserv_num;
	}


}

int search_available_room(int room_type, int adults_kids, DATE check_in, DATE check_out)
{
	int res = 0;
	int count = 0;
	for (int i = 0;i < room_num;i++)
	{
		if (rl[i].room_type == room_type && rl[i].adults_kids == adults_kids)
		{
			count = 0;
			for (int j = 0;j < reserv_num;j++)
			{
				if (strcmp(rs[j].room_id, rl[i].room_id) == 0)
				{
					count++;
					if (is_date_conflict(&(rs[j].check_in), &(check_in), &(rs[j].check_out), &(check_out)) == 0)
					{
						//print the available room info
						print_room(&rl[i]);
						res++;
					}
				}
			}
			// the room is not reservation
			if (count == 0)
			{
				print_room(&rl[i]);
				res++;
			}
		}
	}

	return res;
}

void cancellation(USER * u)
{
	int count = 0;
	//search and display the user reservation
	printf("All your reservation:");
	for (int i = 0;i < reserv_num;i++)
	{
		if (strcmp(u->user_id, rs[i].c.user_id) == 0 && rs[i].is_cancel == 0)
		{
			print_reserv(&rs[i]);
			count++;
		}
	}
	if (count != 0)
	{
		int r_id = -1;
		printf("Please select and input the reservation r_id to cancel:");
		scanf("%d", &r_id);
		int idx = find_resv_by_id(r_id);
		rs[idx].is_cancel = 1;
		printf("Please input your cancellation reason:");
		scanf("%s", rs[idx].cancel_reason);
		int rc = update_resv(&rs[idx]);
		if (rc == 0)
			printf("Successfully cancel the reservation.\n");
		else
			printf("Failed!Please retry.\n");
	}
	else
	{
		printf("no reservation to cancel.\n");
	}
}

void modify_booking(USER * u)
{
	//search and display the user reservation
	int count = 0;
	printf("All your reservation:\n");
	for (int i = 0;i < reserv_num;i++)
	{
		if (strcmp(u->user_id, rs[i].c.user_id) == 0 && rs[i].is_cancel == 0)
		{
			print_reserv(&rs[i]);
			count++;
		}
	}
	if (count == 0)
	{
		printf("You have no reservation to modify.\n");
		return;
	}

	int r_id = -1;
	printf("Please select and input the reservation r_id to cancel:");
	scanf("%d", &r_id);
	int idx = find_resv_by_id(r_id);
	rs[idx].is_cancel = 1;
	strcpy(rs[idx].cancel_reason, "modify the reservation");
	int rc = update_resv(&rs[idx]);
	if (rc == 0)
	{
		printf("Return to generate a new reservation.\n");
		booking(u);
	}
	else
	{
		printf("modify the reservation failed.Please retry.\n");
	}

}

void view_reservation(USER * u)
{
	int res = 0;
	printf("All your reservation(including the cancellation):");
	for (int i = 0;i < reserv_num;i++)
	{
		if (strcmp(u->user_id, rs[i].c.user_id) == 0)
		{
			res++;
			print_reserv(&rs[i]);
		}
	}
	printf("there are %d reservation in your account.\n\n",res);
}


void upload_room_detail()
{
	ROOM r;
	printf("input the room detail as follow:\n");
	printf("room_id(xxx):");
	scanf("%s", r.room_id);
	printf("room_type(1 or 2):");
	scanf("%d", &r.room_type);
	printf("adult or kid (1-adult,2-kid):");
	scanf("%d", &r.adults_kids);
	if (add_room(&r) == 0)
	{
		printf("Upload room detail sccuessfully.\n");
	}
	else {
		printf("Upload failed\n");
	}
}

void modify_room_detail()
{
	ROOM r;
	printf("input the room id:");
	scanf("%s", r.room_id);
	int idx = find_room_by_id(rl, r.room_id);
	if (idx != -1)
	{
		printf("display the original room detail.\n");
		print_room(&rl[idx]);
		putchar('\n');
		printf("input the new room detail as follow:\n");
		printf("room_id:%s", rl[idx].room_id);
		printf("room_type(1 or 2):");
		scanf("%d", &rl[idx].room_type);
		printf("adult or kid (1-adult,2-kid):");
		scanf("%d", &rl[idx].adults_kids);

		if (modify_room(&rl[idx]) == 0)
		{
			printf("modify the room detail sccuessfully.\n\n");
		}
		else {
			printf("modify the room detail failed.\n\n");
		}
	}
	else {
		printf("can no find the room.\n");
	}
	return;
}


void view_all_reservations()
{
	for (int i = 0;i < reserv_num;i++)
		print_reserv(&rs[i]);
	putchar('\n');
}

void search_reservation()
{
	int r_id = -1;
	printf("Please input the serservation id:");
	scanf("%d", &r_id);
	if (find_resv_by_id(r_id) != -1)
	{
		//printf("%d", r_id);
		print_reserv(&rs[r_id]);
		return;
	}
	else {
		printf("can not find the reservation.\n");
	}
}

void view_cancellation()
{
	for (int i = 0;i < reserv_num;i++)
	{
		if (rs[i].is_cancel == 1)
		{
			print_reserv(&rs[i]);
		}
	}
}

void search_cancellation(int r_id)
{
	if (find_resv_by_id(r_id) != -1 && rs[r_id].is_cancel == 1)
	{
		print_reserv(&rs[r_id]);
		return;
	}
	else {
		printf("can not find the cancellation.\n");
	}
}
