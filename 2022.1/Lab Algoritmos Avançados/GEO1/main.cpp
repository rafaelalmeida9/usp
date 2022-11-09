#include <bits/stdc++.h>
using namespace std;

struct Point{
    long long x,y;

    Point(long long x, long long y){
        this->x = x;
        this->y = y;
    }

    Point operator+(Point &b){
        return Point(x + b.x,y + b.y);
    }

    Point operator-(Point &b){
        return Point(x - b.x,y - b.y);
    }

    long long operator*(Point &b){
        return x*b.x + y*b.y;
    }

    long long operator^(Point &b){
        return x*b.y - y*b.x;
    }
};

long long area(vector<Point> p){
    long long area = 0;
    int n = p.size();

    for(int i = 0, j = n-1; i < n; j = i, i++) area += p[i]^p[j];

    return abs(area);
}

int main(){

    vector<Point> p;

    int t; cin >> t;
    while(t--){
        int x,y; cin >> x >> y;
        Point tmp(x,y);
        p.push_back(tmp);
    }

    cout << area(p) << "\n";

    return 0;
}