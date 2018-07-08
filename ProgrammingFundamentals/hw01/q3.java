import java.util.Scanner;

public class q3 {
	public static void main(String[] args){
		float min = Float.MAX_VALUE;
		float max = Float.MIN_VALUE;
		float average = 0.0f;
		float grade = 0.0f;
		Scanner scan = new Scanner(System.in);
		
		int i=0;
		while(scan.hasNextFloat()){
			 grade = scan.nextFloat();
			 i++;
			 if(grade <= min)
				 min = grade;
			 else if(grade >= max)
				 max = grade;
			 average = (average + grade) / i; 
		}
		
		System.out.printf("Number of grades: %d\n", i);
		System.out.printf("Average grade: %.2f\n", average);
		System.out.printf("Minimum grade: %.2f\n", min);
		System.out.printf("Maximum grade: %.2f\n", max);
		
		scan.close();
	}
}