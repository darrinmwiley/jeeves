/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/cheatingluck
TAGS: dp, game
EXPLANATION:
for any given (n,k), there is a threshold at which it becomes 
profitable for gladstone to win instead of lose. 

additionally, any given (m,n,k) will have an optimal betting amount which is
at least as much as the optimal bet for (m-1,n,k).

you can use these two properties to reduce the branching factor of DP
END ANNOTATION
*/
import java.util.Scanner;

public class CheatingLuck {
	
	public static void main(String[] args) throws Exception
	{
		new CheatingLuck().run();
	}
	
	int[][][] minBet, result;
	int totalMoney, dMoney, gMoney, n, k;
	
	public void run() throws Exception{
		Scanner file = new Scanner(System.in);
		dMoney = file.nextInt();
		gMoney = file.nextInt();
		totalMoney = dMoney+gMoney;
		n = file.nextInt();
		k = file.nextInt();
		minBet = new int[gMoney+dMoney+1][n+1][n-k+1];
		result = new int[gMoney+dMoney+1][n+1][n-k+1];
		System.out.println(opt(dMoney, n, n-k));
	}
	
	public int minBet(int money, int turns, int losses)
	{
		opt(money, turns, losses);
		return minBet[money][turns][losses];
	}
	
	public int opt(int money, int turns, int losses)
	{
		//if you reach here, the game is over
		if(money == 0 || turns == 0)
			return money;
		//if you can't lose, always bet maximum
		if(losses == 0)
			return (int) Math.min(totalMoney, money*(1l<<turns));
		int ans = result[money][turns][losses];
		if (ans == 0) {
			ans = money;
			/*smallest feasible bet
			important observation - optimal bet is weakly increasing with respect to money.
			
			how can we be sure? following the same strategy as (money-1,turns,losses), 
			essentially ignoring one unit of money in your possession, will lead you to the same profit. 
			betting less will lead you to a strictly weaker state on the next turn (less money, same number of turns and wins remaining)
			
			This implies that the optimal bet will be the same or more than the optimal bet for money-1.
			*/
			int min = minBet(money-1, turns, losses);
			//largest feasible bet
			int max = Math.min(money, totalMoney-money);
			for (int bet = Math.min(min, max); bet <= max; bet++) {
				int lose = opt(money-bet, turns-1, losses-1);
				int cheat = opt(money+bet, turns-1, losses);
				int candidate = Math.min(lose, cheat);
				/*if betting b is not profitable, betting anything larger won't be either
				
				  how can we be sure? first, we will show that a bet not being profitable implies that this round is a loss. 
				  
				  assume betting b is not profitable in the long run, but the immediate round is won. You can simply pocket 
				  your winnings from this round and bet zero until the end of the game, coming out with a net profit (contradiction)
				  
				  Hence, raising our bet and losing more money would just put the opponent in a strictly better state 
				  (more money, same number of turns, same number of wins remaining)
				*/
				if (candidate < ans) break;
				minBet[money][turns][losses] = bet;
				ans = candidate;
			}
		}
		return result[money][turns][losses] = ans;
	}
}
