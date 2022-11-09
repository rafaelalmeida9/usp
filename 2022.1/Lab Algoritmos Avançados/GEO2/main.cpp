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

double dist(Point a, Point b){
    return sqrt(pow(b.x - a.x,2) + pow(b.y - a.y,2));
}

bool comp(Point a, Point b){
    if(a.x > b.x) return false;
    else if(a.x < b.x) return true;
    else{
        if(a.y > b.y) return false;
        else return true;
    }
}

int main(){

    vector<Point> p;

    int n; cin >> n;
    for(int i = 0; i < n; i++){
        int x,y; cin >> x >> y;
        Point tmp(x,y);
        p.push_back(tmp);
    }

    sort(p.begin(),p.end(),comp); //ordenação dos pontos

    //cálculo do lower hull
    vector<Point> lw{p[0],p[1]};
    for(int i = 2; i < n; i++){
        while(lw.size() >= 2u){
            Point a = lw[lw.size() - 2];
            Point b = lw[lw.size() - 1];
            Point c = p[i];

            Point tmp1 = b-a;
            Point tmp2 = c-a;
            long long tmp3 = tmp1^tmp2;

            if(tmp3 < 0) lw.pop_back();
            else break;
        }

        lw.push_back(p[i]);
    }

    //cálculo do upper hull
    vector<Point> up{p[n-1],p[n-2]};
    for(int i = n - 3; i >= 0; i--){
        while(up.size() >= 2u){
            Point a = up[up.size() - 2];
            Point b = up[up.size() - 1];
            Point c = p[i];

            Point tmp1 = b-a;
            Point tmp2 = c-a;
            long long tmp3 = tmp1^tmp2;

            if(tmp3 < 0) up.pop_back();
            else break;
        }

        up.push_back(p[i]);
    }

    //junção do upper hull com o lower hull
    vector<Point> chull = lw;
    chull.insert(chull.end(),up.begin() + 1,up.begin() + up.size() - 1);

    double res = 0;

    //cálculo do perímetro do poligono
    for(int i = 0; i < (int)chull.size(); i++){
        res += dist(chull[i],chull[(i+1)%(chull.size())]);
    }

    cout << fixed << setprecision(6) << res << "\n";

    return 0;
}