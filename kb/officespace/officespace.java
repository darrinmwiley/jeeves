/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/officespace
TAGS: brute-force
EXPLANATION: The problem only allows for 10 test cases, each limited 
	to 20 employees in a 100x100 grid. There is no need for any fancy 
	algorithms or optimizations. Simply	labeling a matrix with the
	employee names and then	counting up the names will suffice. 
END ANNOTATION
*/

import java.util.*;

public class officespace {
	public static void main(String[] args) {
		Scanner in = new Scanner(System.in);
		while(in.hasNext()) {
			int w = in.nextInt(), h = in.nextInt();
			String[][] grid = new String[h + 1][w + 1];
			LinkedHashMap<String, Integer> area = new LinkedHashMap<>();
			area.put("Total", h * w);
			area.put("Unallocated", 0);
			area.put("Contested", 0);
			
			int P = in.nextInt();
			in.nextLine();
			for(int p = 0; p < P; ++p) {
				String n = in.next();
				area.put(n, 0);
				int x1 = in.nextInt(), y1 = in.nextInt(), x2 = in.nextInt(), y2 = in.nextInt();
				for (int x = x1; x < x2; ++x)
					for (int y = y1; y < y2; ++y)
						if (grid[y][x] == null)
							grid[y][x] = n;
						else
							grid[y][x] = "Contested";
			}
			
			for(int i = 0; i < h; ++i)
				for(int j = 0; j < w; ++j)
					if(grid[i][j] == null)
						area.put("Unallocated", area.get("Unallocated") + 1);
					else
						area.put(grid[i][j], area.get(grid[i][j]) + 1);

			for (String name : area.keySet())
				System.out.println(name + " " + area.get(name));
			System.out.println();
		}
		in.close();
	}
}