import java.util.Scanner;

public class q2 {
	public static void main(String[] args){
		String current = new String();
		String last = new String();
		Scanner scan = new Scanner(System.in);

		while(scan.hasNext()){
			current = scan.next();
			if(lastWordOfSentence(last))
				current = current.substring(0,1).toUpperCase() + current.substring(1);

			System.out.printf("%s ", current);
			last = current;
		}
		
		scan.close();
	}
	
	public static boolean lastWordOfSentence(String last){
	    return last.endsWith(".") || last.endsWith("?") || last.endsWith("!") || last.isEmpty();
	}
}