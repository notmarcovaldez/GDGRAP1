#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
const int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
bool isValid(int x, int y, int n) {
 return x >= 0 && y >= 0 && x < n && y < n;
}
int bfs(int startX, int startY, int n, vector<string>& grid, vector<bool>& visited) {
 vector<pair<int, int>> queue = {{startX, startY}};
 visited[startX * n + startY] = true;
 vector<pair<int, int>> uniqueWater;
 for (size_t i = 0; i < queue.size(); ++i) {
 int x = queue[i].first;
 int y = queue[i].second;
 for (const auto& dir : directions) {
 int nx = x + dir[0];
 int ny = y + dir[1];
 if (isValid(nx, ny, n)) {
 if (grid[nx][ny] == '~') {
 if (find(uniqueWater.begin(), uniqueWater.end(), make_pair(nx,
ny)) == uniqueWater.end()) {
 uniqueWater.emplace_back(nx, ny);
 }
 } else if (grid[nx][ny] == '#' && !visited[nx * n + ny]) {
 visited[nx * n + ny] = true;
 queue.emplace_back(nx, ny);
 }
 }
 }
 }
 return uniqueWater.size();
}
int main() {
 int n;
 cin >> n;
 cin.ignore();
 vector<string> grid(n);
 vector<bool> visited(n * n, false);
 for (int i = 0; i < n; i++) {
 getline(cin, grid[i]);
 }
 int maxCoast = 0, bestIslandIndex = -1, currentIslandIndex = 1;
 for (int i = 0; i < n; i++) {
 for (int j = 0; j < n; j++) {
 if (grid[i][j] == '#' && !visited[i * n + j]) {
 int coastLength = bfs(i, j, n, grid, visited);
 if (coastLength > maxCoast) {
 maxCoast = coastLength;
 bestIslandIndex = currentIslandIndex;
 }
 if (bestIslandIndex == -1) {
 bestIslandIndex = currentIslandIndex;
 }
 currentIslandIndex++;
 }
 }
 }
 cout << bestIslandIndex << " " << maxCoast << endl;
 retu