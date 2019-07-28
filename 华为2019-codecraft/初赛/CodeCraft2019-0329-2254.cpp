#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<algorithm>
#include <string>
// 参数
#define MAX_INT 0x3f3f3f3f	// 权值矩阵最大值
#define MATRIX_BASE 60	// 权值矩阵相乘的基数 
#define STEP_START 1 // 分组间隔起始的值
#define STEP 5 // 分组增加步长
#define GROUPS 250 //分组数量

using namespace std;

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
	vector<int> path; //每台车对应生成的行驶路径
};

struct cross {
	int cro_id;	//路口id
	int r_id_list[4];	//道路id：1-上；2-右；3-下；4-左
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
	infile.ignore(28, EOF);	//忽略表头
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

void read_data_cross(string path, vector<cross> &crosses) {
	ifstream infile;
	infile.open(path);
	char b; //过滤掉分隔符
	infile.ignore(33, EOF);	//忽略表头
	while ((infile.peek() != EOF)) {
		infile >> b;
		cross*cr = new cross();
		infile >> cr->cro_id;
		infile >> b;
		for (int i = 0;i < 4;i++) {
			infile >> cr->r_id_list[i];
			infile >> b;
		}

		crosses.push_back(*cr);
	}
	infile.close();
}

vector<int> io_func(vector<car> &cars, map<int,road> &roads, vector<cross> &crosses,
	string carPath, string roadPath, string crossPath) {
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
	read_data_cross(crossPath, crosses);
	/*cout << crosses.back().cro_id << endl;
	for (int i = 0;i<4;i++)
	cout << crosses.back().r_id_list[i] << endl;*/
	// 统计车、道路、路口数
	vector<int> res;
	res.push_back(cars.size());
	res.push_back(roads.size());
	res.push_back(crosses.size());
	return res;
}

void init_map(map<int,road> &roads, int road_size, int cross_size,
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
	for (m_it = roads.begin();m_it != roads.end();m_it++) {
		map_distance[m_it->second.start - 1][m_it->second.dest - 1] = m_it->second.len*MATRIX_BASE;
		map_roadid[m_it->second.start - 1][m_it->second.dest - 1] = m_it->second.r_id;
		if (m_it->second.is_bi) {
			map_distance[m_it->second.dest - 1][m_it->second.start - 1] = m_it->second.len*MATRIX_BASE;
			map_roadid[m_it->second.dest - 1][m_it->second.start - 1] = m_it->second.r_id;
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
int main(int argc, char *argv[])
{
    cout << "Begin" << endl;
	
	if(argc < 5){
		cout << "please input args: carPath, roadPath, crossPath, answerPath" << endl;
		exit(1);
	}
	
	string carPath(argv[1]);
	string roadPath(argv[2]);
	string crossPath(argv[3]);
	string answerPath(argv[4]);
	
	cout << "carPath is " << carPath << endl;
	cout << "roadPath is " << roadPath << endl;
	cout << "crossPath is " << crossPath << endl;
	cout << "answerPath is " << answerPath << endl;
	
	// TODO:read input filebuf
	// TODO:process
	// TODO:write output file
	vector<car> cars;	//所有的车辆
	map<int, road> roads;	//所有的道路
	vector<cross> crosses;	//所有的路口
	// 读入数据
	vector<int> sizes = io_func(cars, roads, crosses,carPath,roadPath,crossPath);

	// 车、道路、路口总数
	int car_size = sizes[0];
	int road_size = sizes[1];
	int cross_size = sizes[2];
	cout << car_size << '\t' << road_size << '\t' << cross_size << endl;
	
	// 构建路网的邻接矩阵
	// 各个节点之间的距离，不相通的为无限大
	vector<vector<int>> map_distance(cross_size, vector<int>(cross_size, MAX_INT));
	// 各个节点之间的连接对应的道路id,不存在相连的道路则为-1
	vector<vector<int>> map_roadid(cross_size, vector<int>(cross_size, -1));
	// 初始化路网
	init_map(roads,road_size,cross_size,map_distance,map_roadid);
	
	// 对每台车根据车速从高到低排序
	sort(cars.begin(), cars.end(), cmp_speed);
	/*vector<car>::iterator iter;
	for (iter = cars.begin();iter != cars.end();iter++)
		cout << iter->sp_l<< endl;*/
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
	
	//对分组后的每台车设置出发时间，高速组的车先出发，发车间隔采用等差的方式
	int step = STEP_START;
	for (int i = 0;i < groups - 1;i++) {
		for (int j = i * group_size + 1;j < (i + 1) * group_size;j++) {
			cars[j].s_time += step;
		}
		step+= STEP;
	}
	vector<car>::iterator iter = cars.begin() + (groups - 1) * group_size + 1;
	for (;iter != cars.end();iter++) {
		iter->s_time += step;
	}
	
	//重新按出发时间排序，为每台车规划路线
	sort(cars.begin(), cars.end(), cmp_s_time);

	//for (iter = cars.begin();iter != cars.end();iter++)
	//	cout << iter->s_time<<'\t'<<iter->sp_l<< endl;

	//使用dji为每台车寻找最短路径,同时考虑更新权值矩阵
	int start, dest;int count = 0;
	vector<int> p(cross_size), d(cross_size);
	vector<int> path;
	for (iter = cars.begin();iter != cars.end();iter++) {
		
		start = (iter->start) - 1;
		dest = (iter->dest) - 1;
		//计算最短路径
		dji(map_distance, start, cross_size, p, d);
		//寻找路径上的多个节点
		path = search_path(start, dest, p, map_roadid);
		//将得到的路径加到对应车对象上的path成员中
		iter->path=path;
		//更新权值矩阵
		update_map_distance(map_distance,map_roadid, roads, p, start, dest);
		count++;
		cout << count << endl;
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
		outfile << '(' << iter->car_id << ',' << iter->s_time << ',';
		for (j = iter->path.begin();j < iter->path.end() - 1;j++) {
			outfile << *j << ',';
		}
		outfile <<iter->path.back() <<')'<< endl;
	}
	outfile << '(' << iter->car_id << ',' << iter->s_time << ',';
	for (j = iter->path.begin();j < iter->path.end() - 1;j++) {
		outfile << *j << ',';
	}
	outfile << iter->path.back() << ')' ;
	outfile.close();
}

