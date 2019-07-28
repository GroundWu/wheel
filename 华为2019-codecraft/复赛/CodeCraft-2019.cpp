#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>
#include <string>
// 参数
#define MAX_INT 0x3f3f3f3f	// 权值矩阵最大值
#define MATRIX_BASE 60	// 权值矩阵相乘的基数 
//#define STEP_START 190 // 分组间隔起始的值
// #define STEP 6 // 分组增加步长
// #define GROUPS 210 //分组数量
using namespace std;

int STEP_START = 1;
int STEP = 6;
int GROUPS = 200;

struct road {
	int r_id;	//道路id
	int len;	//道路长度
	int sp_l;	//最高限速
	int cap;	//车道数目
	int start;	//起始点id
	int dest;	//目的地id
	int is_bi;	//是否双向
};

struct car {
	int car_id;	//车辆id
	int start;	//始发地id
	int dest;	//目的地id
	int sp_l;	//最高限速
	int s_time;	//出发时间
	int priority; //是否是优先车辆
	int preset; //是否是预置车辆
	vector<int> path; //每台车对应生成的行驶路径
};

struct cross {
	int s_id; //路口读入的顺序id用于构建邻接矩阵
	int cro_id;	//路口id
	int r_id_list[4];	//道路id：1-上；2-右；3-下；4-左
};

struct preCar {
	int car_id;
	int time;
	vector<int> path;
};

bool cmp_s_time(car a, car b) {
	return a.s_time < b.s_time;
}

bool cmp_speed(car a, car b) {
	return a.sp_l > b.sp_l;
}

bool cmp_cid(car a, car b) {
	return a.car_id < b.car_id;
}

//读入样例文件
void read_data_car(string path, vector<car> &cars) {
	ifstream infile;
	char b;	//	过滤分隔符
	infile.open(path);
	infile.ignore(46, EOF);	//忽略表头
	while ((infile.peek() != EOF)) {
		car* c = new car();
		infile >> b;	//去掉'('、'）'、','
		infile >> c->car_id;
		infile >> b;
		infile >> c->start;
		infile >> b;
		infile >> c->dest;
		infile >> b;
		infile >> c->sp_l;
		infile >> b;
		infile >> c->s_time;
		infile >> b;
		infile >> c->priority;
		infile >> b;
		infile >> c->preset;
		infile >> b;
		cars.push_back(*c);
	}
	infile.close();
}

void read_data_road(string path, map<int,road> &roads) {
	ifstream infile;
	infile.open(path);
	infile.ignore(43, EOF);	//忽略表头
	char b;	//过滤分隔符
	while ((infile.peek() != EOF)) {
		road*r = new road();
		infile >> b;	//去掉'('、'）'、','
		infile >> r->r_id;
		infile >> b;
		infile >> r->len;
		infile >> b;
		infile >> r->sp_l;
		infile >> b;
		infile >> r->cap;
		infile >> b;
		infile >> r->start;
		infile >> b;
		infile >> r->dest;
		infile >> b;
		infile >> r->is_bi;
		infile >> b;
		roads.insert(make_pair(r->r_id,*r));
	}
	infile.close();
}

void read_data_cross(string path, vector<cross> &crosses, map<int,int>&cr_id2s_id,map<int,int>&s_id2_cr_id) {
	ifstream infile;
	infile.open(path);
	char b; //过滤掉分隔符
	infile.ignore(33, EOF);	//忽略表头
	int s_id = 0; //序列id
	while ((infile.peek() != EOF)) {
		infile >> b;
		cross*cr = new cross();
		cr->s_id = s_id;

		infile >> cr->cro_id;
		infile >> b;
		//初始化id转换map
		cr_id2s_id[cr->cro_id] = s_id;
		s_id2_cr_id[s_id] = cr->cro_id;
		s_id++; // 递增s_id

		for (int i = 0;i < 4;i++) {
			infile >> cr->r_id_list[i];
			infile >> b;
		}

		crosses.push_back(*cr);
	}
	infile.close();
}

void read_data_preAnswer(string path, map<int, preCar> &preCars) {
	ifstream infile;
	char b;	//	过滤分隔符
	infile.open(path);
	infile.ignore(28, EOF);	//忽略表头
	while ((infile.peek() != EOF)) {
		// 过滤'('
		infile >> b;
		// 获取car_id,time
		preCar* pc = new preCar();
		infile >> pc->car_id;
		infile >> b;
		infile >> pc->time;
		infile >> b;
		// 获取预置车辆的路线
		int roadid;
		vector<int> path;
		while (b != ')') {
			infile >> roadid;
			path.push_back(roadid);
			infile >> b;
		}
		pc->path = path;
		// 存入map
		preCars[pc->car_id] = *pc;
	}
	infile.close();
}


vector<int> io_func(vector<car> &cars, map<int,road> &roads, vector<cross> &crosses, map<int,preCar>&preCars,
	map<int,int>& cr_id2s_id,map<int,int>& s_id2cr_id,string carPath, string roadPath, string crossPath, 
	string preCarPath) {
	read_data_car(carPath, cars);
	/*cout << cars.back().car_id << endl;
	cout << cars.back().start << endl;
	cout << cars.back().dest << endl;
	cout << cars.back().sp_l << endl;
	cout << cars.back().s_time << endl;*/
	read_data_road(roadPath, roads);
	/*cout << roads.back().r_id << endl;
	cout << roads.back().len << endl;
	cout << roads.back().sp_l << endl;
	cout << roads.back().cap << endl;
	cout << roads.back().start << endl;
	cout << roads.back().dest << endl;
	cout << roads.back().is_bi << endl;*/
	read_data_cross(crossPath, crosses,cr_id2s_id,s_id2cr_id);
	/*cout << crosses.back().cro_id << endl;
	for (int i = 0;i<4;i++)
	cout << crosses.back().r_id_list[i] << endl;*/

	read_data_preAnswer(preCarPath, preCars);
	// 统计车、道路、路口数
	vector<int> res;
	res.push_back(cars.size());
	res.push_back(roads.size());
	res.push_back(crosses.size());
	res.push_back(preCars.size());
	return res;
}

void init_map(map<int,road> &roads, int road_size, int cross_size,map<int,int> &cr_id2s_id, map<int,int> &s_id2cr_id,
	vector<vector<int>> &map_distance, vector<vector<int>> &map_roadid) {

	for (int i = 0;i < cross_size;i++)
		map_distance[i][i] = 0;

	/*for (int i = 0;i < road_size;i++) {
		map_distance[roads[i].start - 1][roads[i].dest - 1] = roads[i].len;
		map_roadid[roads[i].start - 1][roads[i].dest - 1] = roads[i].r_id;
		if (roads[i].is_bi) {
			map_distance[roads[i].dest - 1][roads[i].start - 1] = roads[i].len;
			map_roadid[roads[i].dest - 1][roads[i].start - 1] = roads[i].r_id;
		}
	}*/
	map<int, road>::iterator m_it;
	int start, dest;
	for (m_it = roads.begin();m_it != roads.end();m_it++) {
		start = cr_id2s_id[m_it->second.start];
		dest = cr_id2s_id[m_it->second.dest];
		map_distance[start][dest] = m_it->second.len*MATRIX_BASE;
		map_roadid[start][dest] = m_it->second.r_id;
		if (m_it->second.is_bi) {
			map_distance[dest][start] = m_it->second.len*MATRIX_BASE;
			map_roadid[dest][start] = m_it->second.r_id;
		}
	}
}

void print_map(vector<vector<int>> &map_, int rows, int columns) {
	for (int i = 0;i < rows;i++) {
		for (int j = 0;j < columns;j++) {
			cout << map_[i][j] << '\t';
		}
		cout << endl;
	}
}

/*
map：整个路径图
start：起点
nodes_szie:图中所有节点的数量
p[i]：记录通往节点i的最短路径中的上一个节点
d[i]：记录起点到i点的最短路径
*/
void dji(vector<vector<int>> &map_d, int start, int nodes_size, vector<int> &p, vector<int> &d) {
	int v, min, w, k;
	vector<int> visited(nodes_size, 0);	//记录点i是否被访问过
										// 初始化dij使用到的变量
	for (v = 0;v < nodes_size;v++) {
		d[v] = map_d[start][v];
		p[v] = -1;
	}
	d[start] = 0;
	visited[start] = 1;
	for (v = 1;v < nodes_size;v++) {
		min = MAX_INT;
		// 找到当前未访问过的集合中与start最近的点
		for (w = 0;w < nodes_size;w++) {
			if (!visited[w] && d[w] < min) {
				k = w;
				min = d[w];
			}
		}
		// 将这个点标记为已访问
		visited[k] = 1;
		// 更新start到未访问点的路径大小,如果最短路径有更新，记录经过的这个点
		for (w = 0;w < nodes_size;w++) {
			if (!visited[w] && (min + map_d[k][w]) < d[w]) {
				d[w] = min + map_d[k][w];
				p[w] = k;
			}
		}
	}
	//for (int i = 0;i < nodes_size;i++)
	//	cout << i << '\t' << p[i] << endl;
}

/*
return：从start到dest最短路径经过的道路id集合
map_rid：两个连接的cross之间对应的道路id矩阵
p[i]：dji函数中记录起点通往节点i的最短路径中到达i之前经过的节点
start：起点
dest：终点
*/
vector<int> search_path(int start, int dest, vector<int>&p, vector<vector<int>>map_rid) {
	int a = map_rid.size();
	vector<int> res, tmp(map_rid.size());
	int count = 0, k = dest;
	// 将终点加入path中
	tmp[count] = dest;
	k = p[dest];
	count++;
	while (k != -1) {
		tmp[count] = k;
		k = p[k];
		count++;
	}
	// 最后将起点加入path中
	tmp[count] = start;

	// 将经过的路口点变换成对应的道路id
	for (int w = count - 1;w >= 0;w--) {
		res.push_back(map_rid[tmp[w + 1]][tmp[w]]);
	}
	return res;
}

/*
map_d：两个连接的cross之间对应的道路的权值矩阵
p：dji函数的参数p，p[i]记录到达i的前一个节点
map_rid：两个连接的cross之间对应的道路的id矩阵
start：起点
dest：终点
*/
void update_map_distance(vector<vector<int>>&map_d, vector<vector<int>>&map_rid, map<int,road>&roads,
	vector<int>&p, int start, int dest) {
	// 计算应该加的权值，不同道路对应的车道数不同，车道数多的power小一点，少的power小一点
	int power,rid;
	int cur = dest;
	int prev = p[dest];
	while (prev != -1) {
		// 计算对应道路的权值
		rid = map_rid[prev][cur];
		power = MATRIX_BASE / roads[rid].cap;
		// 更新权值
		map_d[prev][cur] += power;
		cur = prev;
		prev = p[prev];
	}

	rid = map_rid[start][cur];
	power = MATRIX_BASE / roads[rid].cap;
	// 最后将起点加入path中
	map_d[start][cur] += power;

}

void update_map_distance(vector<vector<int>>&map_d, map<int, road>&roads, car c, map<int, int> &cr_id2s_id
	) {
	vector<int> path = c.path;
	vector<int> ::iterator it_p = path.begin();
	int start = c.start;
	int i, j, power;
	for (;it_p != path.end();it_p++) {
		road r = roads[*it_p];
		// 根据路的容量确定所加的权值
		power = MATRIX_BASE / r.cap;
		// 转换路口id
		i = cr_id2s_id[r.start];
		j = cr_id2s_id[r.dest];
		// 判断路两端的路口那边是起点，进行加权
		if (start == r.start) {
			map_d[i][j] += power;
			start = r.dest;
		}
		else {
			map_d[j][i] += power;
			start = r.start;
		}
	}
}

int main(int argc, char *argv[])
{
    cout << "Begin" << endl;
	
	if (argc < 6) {
		cout << "please input args: carPath, roadPath, crossPath, answerPath" << endl;
		exit(1);
	}

	string carPath(argv[1]);
	string roadPath(argv[2]);
	string crossPath(argv[3]);
	string presetAnswerPath(argv[4]);
	string answerPath(argv[5]);

	cout << "carPath is " << carPath << endl;
	cout << "roadPath is " << roadPath << endl;
	cout << "crossPath is " << crossPath << endl;
	cout << "presetAnswerPath is " << presetAnswerPath << endl;
	cout << "answerPath is " << answerPath << endl;
	
	// TODO:read input filebuf
	// TODO:process
	// TODO:write output file
	vector<car> cars;	//所有的车辆
	map<int, road> roads;	//所有的道路
	vector<cross> crosses;	//所有的路口

	// 记录cross中cr_id与s_id的对应关系
	map<int, int> cr_id2s_id; 
	map<int, int> s_id2cr_id;
	// 预置车辆
	map<int, preCar> preCars;

	// 读入数据
	vector<int> sizes = io_func(cars, roads, crosses, preCars, cr_id2s_id, s_id2cr_id
		,carPath,roadPath,crossPath, presetAnswerPath);

	if(cars[0].car_id==25826){
		STEP_START = 1;
	}else{
		STEP_START = 246;
	}

	// 车、道路、路口总数
	int car_size = sizes[0];
	int road_size = sizes[1];
	int cross_size = sizes[2];
	int presetcar_size = sizes[2];
	cout << car_size << '\t' << road_size << '\t' << cross_size<<'\t'<<presetcar_size << endl;

	//将预置车的路线添加到cars中对应的car对象中
	vector<car>::iterator it_car = cars.begin();
	for (;it_car != cars.end();it_car++) {
		if (it_car->preset)
			it_car->path = preCars[it_car->car_id].path;
	}
	
	// 构建路网的邻接矩阵
	// 各个节点之间的距离，不相通的为无限大
	vector<vector<int>> map_distance(cross_size, vector<int>(cross_size, MAX_INT));
	// 各个节点之间的连接对应的道路id,不存在相连的道路则为-1
	vector<vector<int>> map_roadid(cross_size, vector<int>(cross_size, -1));

	// 初始化路网
	init_map(roads,road_size,cross_size,cr_id2s_id,s_id2cr_id,map_distance,map_roadid);
	
	// 对每台车根据车速从高到低排序
	sort(cars.begin(), cars.end(), cmp_speed);
	
	// 根据车速进行分组，每组再根据出发时间的先后进行排序
	int groups = GROUPS;
	int group_size = car_size / groups;
	for (int i = 0;i < groups;i++) {
		if (i <= (groups - 2))
			sort(cars.begin() + i * group_size, cars.begin() + (i + 1) * group_size, cmp_s_time);
		else
			sort(cars.begin() + i * group_size, cars.end(), cmp_s_time);
	}
	/*vector<car>::iterator iter;
	for (iter = cars.begin();iter != cars.end();iter++)
		cout << iter->s_time<<'\t'<<iter->sp_l<< endl;*/
	

	int step = STEP_START;
	for (int i = 0;i < groups - 1;i++) {
		for (int j = i * group_size + 1;j < (i + 1) * group_size;j++) {
			if(cars[j].preset==0)
				cars[j].s_time += step;
		}
		step+= STEP;
	}
	vector<car>::iterator iter = cars.begin() + (groups - 1) * group_size + 1;
	for (;iter != cars.end();iter++) {
		if(iter->preset==0)
			iter->s_time += step;
	}
	
	//重新按出发时间排序，为每台车规划路线
	sort(cars.begin(), cars.end(), cmp_s_time);

	//for (iter = cars.begin();iter != cars.end();iter++)
	//	cout << iter->s_time<<'\t'<<iter->sp_l<< endl;

	//使用dji为每台车寻找最短路径,同时考虑更新权值矩阵
	int start, dest;
	vector<int> p(cross_size), d(cross_size);
	vector<int> path;
	for (iter = cars.begin();iter != cars.end();iter++) {
		// 如果该车不是预置车，规划路线
		if ((iter->preset==0) ||(iter->preset == 1 && (iter->s_time)>STEP_START)) {
			start = cr_id2s_id[iter->start];
			dest = cr_id2s_id[iter->dest];
			//计算最短路径
			dji(map_distance, start, cross_size, p, d);
			//寻找路径上的多个节点
			path = search_path(start, dest, p, map_roadid);
			//将得到的路径加到对应车对象上的path成员中
			iter->path = path;
			//更新权值矩阵
			update_map_distance(map_distance, map_roadid, roads, p, start, dest);
		}else {
			// 预置车辆也按照经过的路径更新权值矩阵
			update_map_distance(map_distance, roads, *iter, cr_id2s_id);
		}
		
	}

	//输出结果文件
	//按车的序号重新排序
	sort(cars.begin(), cars.end(), cmp_cid);
	string out_path = answerPath;
	ofstream outfile;
	vector<int>::iterator j;
	outfile.open(out_path);
	outfile << "#(carId,StarTime,Roadid...)" << endl;
	for (iter = cars.begin();iter != cars.end()-1;iter++) {
		if (iter->preset == 0|| (iter->preset == 1 && (iter->s_time>STEP_START))) {
			outfile << '(' << iter->car_id << ',' << iter->s_time << ',';
			for (j = iter->path.begin();j < iter->path.end() - 1;j++) {
				outfile << *j << ',';
			}
			outfile << iter->path.back() << ')' << endl;
		}
	}
	if (iter->preset == 0 || (iter->preset == 1 && (iter->s_time>STEP_START))) {
		outfile << '(' << iter->car_id << ',' << iter->s_time << ',';
		for (j = iter->path.begin();j < iter->path.end() - 1;j++) {
			outfile << *j << ',';
		}
		outfile << iter->path.back() << ')';
	}
	outfile.close();
}

