#include <iostream>
#include <set>
#include <unordered_map>

using namespace std;

int main() {
    int n, m;
    // 读取 n 和 m
    if (!(cin >> n >> m)) return 0;
    
    set<int> occupied;
    unordered_map<int, int> guard2seat;

    while (m--) {
        int t, d;
        if (!(cin >> t >> d)) break;
        
        if (t == 1) { // 守卫到达
            if (occupied.empty()) {
                int seat = 0;
                cout << seat << endl;
                occupied.insert(seat);
                guard2seat[d] = seat;
                continue;
            }
            
            int best_seat = -1;
            int max_dist = -1;
            
            // 1. 检查最左边位置 0
            int first_seat = *occupied.begin();
            if (first_seat > 0) {
                max_dist = first_seat;
                best_seat = 0;
            }
            
            // 2. 检查中间的所有区间
            for (auto it = occupied.begin(); next(it) != occupied.end(); ++it) {
                int left = *it;
                int right = *next(it);
                int dist = (right - left) / 2;
                int mid_pos = left + dist;
                
                // 距离严格大于才更新，保证相同距离选左边
                if (dist > max_dist) {
                    max_dist = dist;
                    best_seat = mid_pos;
                }
            }
            
            // 3. 检查最右边位置 n-1
            int last_seat = *occupied.rbegin();
            int dist_right = (n - 1) - last_seat;
            if (dist_right > max_dist) {
                max_dist = dist_right;
                best_seat = n - 1;
            }

            if (best_seat == -1) best_seat = 0;

            cout << best_seat << endl;
            occupied.insert(best_seat);
            guard2seat[d] = best_seat;
        } 
        else { // t == 2 守卫离开

                int seat = guard2seat[d];
                cout << seat << endl;
                occupied.erase(seat);
                guard2seat.erase(d);
            
        }
    }
    
    return 0;
}