/*
BEGIN ANNOTATION
PROBLEM URL: open.kattis.com/problems/abstractart
TAGS: java, geometry
EXPLANATION:
This problem is just finding the area of shapes with potential holes. We can lean on java's geometry library to solve this easily.
END ANNOTATION
*/
import java.awt.geom.Area;
import java.awt.geom.Path2D;
import java.awt.geom.PathIterator;
import java.util.Scanner;

public class abstractart{
    
    public static void main(String[] args)
    {
        Scanner file = new Scanner(System.in);
        int N = file.nextInt();
        Area[] areas = new Area[N];
        for(int i = 0;i<N;i++)
        {
            int M = file.nextInt();
            double[] x = new double[M];
            double[] y = new double[M];
            for(int j = 0;j<M;j++)
            {
                x[j] = file.nextDouble();
                y[j] = file.nextDouble();
                areas[i] = makeArea(x,y);
            }
        }
        Area together = new Area();
        for(Area x:areas)
            together.add(x);
        double sum = 0;
        for(Area x:areas)
            sum+=getArea(x.getPathIterator(null));
        System.out.println(sum+" "+getArea(together.getPathIterator(null)));
    }
    
    public static boolean cw(double x1, double y1, double x2, double y2, double x3, double y3)
    {
        return (y3-y1)*(x2-x1)<(y2-y1)*(x3-x1);
    }
    
    public static Area makeArea(double[] xp, double[] yp)
    {
        Path2D path = new Path2D.Float();
        path.moveTo(xp[0], yp[0]);
        for(int i = 1;i<xp.length;i++)
            path.lineTo(xp[i], yp[i]);
        path.closePath();
        return new Area(path);
    }
    
    public static double getArea(PathIterator path)
    {   
        double area = 0;
        double firstX = -1, firstY = -1;
        double prevX = 0;
        double prevY = 0;
        boolean newPolygon = true;
        boolean gone = false;
        while(!path.isDone())
        {
            double coords[] = new double[2];
            path.currentSegment(coords);
            if(coords[0] == 0 && coords[1] == 0 && gone)
            {
                newPolygon = true;
                area += prevY * firstX - prevX * firstY;
                path.next();
                continue;
            }
            if(newPolygon)
            {
                firstX = coords[0];
                firstY = coords[1];
                prevX = 0;
                prevY = 0;
                newPolygon = false;
            }
            gone = true;
            area += prevY * coords[0] - prevX * coords[1];
            prevX = coords[0];
            prevY = coords[1];
            path.next();
        }
        area /= 2;
        return area;
    }

    
}
