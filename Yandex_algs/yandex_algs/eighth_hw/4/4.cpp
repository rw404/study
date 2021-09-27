#include <iostream>
#include <vector>
#include <unordered_map>

void
visit(int j, std::vector<bool> &visited, 
        std::vector<std::vector<int>> &heights, 
        std::unordered_map<int, std::vector<int>> &lines)
{
    visited[j] = false;
    for (int i=0; i<lines[j].size(); ++i) {
        if (visited[lines[j][i]]) {
            visit(lines[j][i], visited, heights, lines);
            if (heights[lines[j][i]][0] >= heights[j][0]) {
                int tmp = heights[j][0];
                heights[j][0] = heights[lines[j][i]][0]+1;
                heights[j][1] = tmp;
            } else if (heights[lines[j][i]][0] >= heights[j][1]) {
                heights[j][1] = heights[lines[j][i]][0]+1;
            }
        }
    }
}

int
main()
{
    int N = 0;
    std::cin >> N;
    std::vector<std::vector<int>> heights = std::vector<std::vector<int>>(N);
    std::unordered_map<int, std::vector<int>> lines;
    std::vector<bool> visited = std::vector<bool>(N);

    for (int i=0; i<N-1; ++i) {
        int l, r;
        std::cin >> l >> r;
        if (!lines.count(l-1)) {
            lines[l-1] = std::vector<int>();
        }
        lines[l-1].push_back(r-1);
        if (!lines.count(r-1)) {
            lines[r-1] = std::vector<int>();
        }
        lines[r-1].push_back(l-1);
        heights[i] = std::vector<int>(2, 0);
        visited[i] = true;
    }

    visited[N-1] = true;
    heights[N-1] = std::vector<int>(2, 0);

    for (int i=0; i<N; ++i) {
        visit(i, visited, heights, lines);
    }

/*    for (auto i: heights) {
        for (auto j: i) {
            std::cout << j << std::endl;    
        }
    }*/
    int ans = 0;
    for (int i=0; i<N; ++i) {
        ans = std::max(ans, heights[i][0]+heights[i][1]);
    }

    ++ans;
    std::cout << ans << std::endl;
    return 0;
}
