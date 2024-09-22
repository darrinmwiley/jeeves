/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/safety
TAGS: math, binary search
EXPLANATION:
for each contestant C, we can binary search the minimum passing audience value.

For some candidate audience value V, we can calculate the minimum audience value
that each other contestant would need to achieve to surpass C.

If the sum of all of these minimum audience values exceeds 1, then there is no way for 
C to come in last place, so a lower threshold is needed.

If the sum of all minimum audience values is <= 1, then it is possible for C to come in last, 
so a higher theshold is needed

maybe there's an explicit way to calculate this, but small brain binary search is easier.
END ANNOTATION
*/

import java.util.Arrays;
import java.util.Scanner;

public class Safety {
	
	public static void main(String[] args) throws Exception
	{
		new Safety().run();
	}
	
	public void run() throws Exception{
		Scanner file = new Scanner(System.in);
		int T = file.nextInt();
		for(int z = 0;z<T;z++)
		{
			int N = file.nextInt();
			int[] J = new int[N];
			int X = 0;
			for(int i = 0;i<N;i++)
			{
				X += J[i] = file.nextInt();
			}
			String output = "Case #"+(z+1)+": ";
			for(int i = 0;i<N;i++)
			{
				double L = 0;
				double R = 1;
				double M = .5;
				while(R-L > .00000001)
				{
					M = (R+L)/2;
					double score = J[i] + X*M;
					double sum = M;
					for(int j = 0;j<N;j++)
					{
						if(i == j)
							continue;
						sum += Math.max(0, (score - J[j])/X);
					}
					if(sum > 1) {
						R = M;
					}else {
						L = M;
					}
				}
				output += String.format("%.6f ", M*100);
			}
			System.out.println(output.trim());
		}
	}
}
