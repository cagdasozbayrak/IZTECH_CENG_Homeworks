import java.util.Scanner;
import java.util.ArrayList;

public class q1{
	public static void main(String[] args){
		java.util.Scanner scan = new Scanner(System.in);
		ArrayList<Float> list = new ArrayList<Float>();
		
		for(int i=0; i<1000 && (scan.hasNextFloat() == true); i++ )
		{
			float grade1, grade2, grade3;
			grade1 = scan.nextFloat();
			grade2 = scan.nextFloat();
			grade3 = scan.nextFloat();
			
			list.add(grade1*0.2f+grade2*0.4f+grade3*0.4f);
		}
		
		for(int i=0; i<list.size(); i++)
			System.out.printf("%.2f \n", list.get(i));
		
		scan.close();
	}
}
