/*
BEGIN ANNOTATION
PROBLEM URL: https://open.kattis.com/problems/transitwoes
TAGS: example tag 1, example tag 2, etc...
EXPLANATION:
example explanation,
can span multiple lines
END ANNOTATION
*/
import java.util.Scanner;

public class transitwoes {
    public static void main(String[] args) {
        Scanner scnr = new Scanner(System.in);
        int leaveTime, classTime, numberOfBuses;
        //System.out.println("Enter first line: ");
        leaveTime = scnr.nextInt();
        classTime = scnr.nextInt();
        numberOfBuses = scnr.nextInt();

        int[] walkTimes = new int[numberOfBuses + 1];
        int[] driveTimes = new int[numberOfBuses + 1];
        driveTimes[0] = 0;
        int[] busArrivalIntervals = new int[numberOfBuses];

        int walkTimesSum = 0;
        int driveTimesSum = 0;
        int busWaitTimeSum = 0;
        int tempSum = 0;
        int totalTime;

        int timeLimit = classTime - leaveTime;

        boolean onTime = false;

        //System.out.println("Enter second line: ");
        for (int i = 0; i < walkTimes.length; i++) {
            walkTimes[i] = scnr.nextInt();
        }

        //System.out.println("Enter third line: ");
        for (int i = 1; i < driveTimes.length; i++) {
            driveTimes[i] = scnr.nextInt();
        }

        //System.out.println("Enter fourth line: ");
        for (int i = 0; i < busArrivalIntervals.length; i++) {
            busArrivalIntervals[i] = scnr.nextInt();
        }

        scnr.close();

        for (int i = 0; i < walkTimes.length; i++) {
            walkTimesSum += walkTimes[i];
        }
        for (int i = 1; i < driveTimes.length; i++) {
            driveTimesSum += driveTimes[i];
        }
        for (int i = 0; i < busArrivalIntervals.length; i++) {
            tempSum += walkTimes[i] + driveTimes[i];
            if (!(tempSum % busArrivalIntervals[i] == 0)) {
                busWaitTimeSum += busArrivalIntervals[i] - (tempSum % busArrivalIntervals[i]);
            }
            tempSum += busWaitTimeSum;
        }

        totalTime = walkTimesSum + driveTimesSum + busWaitTimeSum;
        
        if (totalTime <= timeLimit) {
            onTime = true;
        }

        if (onTime) {
            System.out.println("yes");
        } else {
            System.out.println("no");
        }
    }
}
