/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/zoning
TAGS: bfs
EXPLANATION:
This is a standard shortest path problem on a grid
END ANNOTATION
*/

import java.util.*;
public class Zoning {
	static class Point {
		int x, y;

		Point(int x, int y) {
			this.x = x;
			this.y = y;
		}

		@Override
		public String toString() {
			return "Point [x=" + x + ", y=" + y + "]";
		}
	}

	static final int[] dx = { 0, 1, 0, -1 }, dy = { -1, 0, 1, 0 };
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		int N = in.nextInt();
		in.nextLine();
		char[][] grid = new char[N][];
		for (int i = 0; i < N; ++i)
			grid[i] = in.nextLine().toCharArray();
		in.close();

		int[][] dist = new int[N][N];
		for (int i = 0; i < N; ++i)
			Arrays.fill(dist[i], Integer.MAX_VALUE >> 3);

		// start (end) points
		ArrayDeque<Point> totallynotastack = new ArrayDeque<>();
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				if (grid[i][j] == '3') {
					totallynotastack.add(new Point(i, j));
					dist[i][j] = 0;
				}
		// bfs
		while (!totallynotastack.isEmpty()) {
			Point p = totallynotastack.pop();
			for (int d = 0; d < 4; ++d)
				if (p.x + dx[d] >= 0 && p.x + dx[d] < N)
					if (p.y + dy[d] >= 0 && p.y + dy[d] < N)
						if (dist[p.x + dx[d]][p.y + dy[d]] > dist[p.x][p.y] + 1) {
							dist[p.x + dx[d]][p.y + dy[d]] = dist[p.x][p.y] + 1;
							totallynotastack.add(new Point(p.x + dx[d], p.y + dy[d]));
						}
		}
		int max = 0;
		for (int i = 0; i < N; ++i)
			for (int j = 0; j < N; ++j)
				if (grid[i][j] == '1')
					max = Math.max(max, dist[i][j]);
		System.out.println(max);
	}
}
