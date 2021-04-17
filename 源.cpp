#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;
struct Point {
	int x, y;
}p[100];

double dmin = 10000;
int n;
int cmpx(Point a, Point b) {//按x排序
	return a.x < b.x;
}

double dist(Point a, Point b) {//计算两点距离
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

double threeMin(Point a, Point b, Point c) {//计算三点距离最小值
	double d = min(min(dist(a,b),dist(a,c)), dist(b, c));
	return d;
}

double twoMin(Point a, Point b) {//计算两点最小值
	double d = dist(a, b);
	return d;
}

double strength(int low, int high) {//计算2d间的最小值
	int i, j;
	int d1 = 10000, d2;
	for (i = low; i < high; i++) {
		for (j = i + 1; j < high; j++) {
			d2 = dist(p[i], p[j]);
			if (d2 < d1) {
				d1 = d2;
			}
		}
	}
	return d1;
}

double closeset(int low, int high) {//分治最近对的基本函数
	double d;
	if (high - low == 2) {
		d = threeMin(p[low], p[low + 1], p[low + 2]);
		if (d < dmin)
			dmin = d;
		return dmin;
	}
	else if (high - low == 1) {
		d = twoMin(p[low], p[high]);
		if (d < dmin)
			dmin = d;
		return dmin;
	}
	else if (high - low == 0) {
		dmin = dist(p[low], p[low]);
		return dmin;
	}
	else {
		int mid;
		mid = (low + high) >> 1;
		double d1 = closeset(low, mid);
		double d2 = closeset(mid, high);
		d = min(d1, d2);
		int i, a = 0, b = n;
		for (i = 0; i < n; i++) {//找到2d间的两个横坐标
			if (p[i].x > p[mid].x - d) {
				a = i;
				break;
			}
		}
		for (i = 0; i < n; i++) {
			if (p[i].x > p[mid].x + d) {
				b = i - 1;
				break;
			}
		}
		return min(strength(p[a].x, p[b].x), d);
	}
}
int main() {
	int i;
	cin >> n;
	for (i = 0; i < n; i++) {
		cin >> p[i].x >> p[i].y;
	}
	sort(p, p + n, cmpx);
	closeset(0, n - 1);
	cout << dmin << endl;
	return 0;
}
/*
15
5 10
9 1
10 12
10 19
13 15
15 19
16 20
19 9
24 0
24 12
31 32
32 24
38 29
40 56
45 23
*/