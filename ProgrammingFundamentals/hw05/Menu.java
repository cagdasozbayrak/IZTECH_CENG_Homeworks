import java.util.ArrayList;
import java.util.Scanner;

public class Menu {
	private ArrayList<MenuItem> menuItems = new ArrayList<MenuItem>();
	
	public void addItem(MenuItem item){
		menuItems.add(item);
	}
	
	public void display(){
		int choice = 0;
		Scanner scan = new Scanner(System.in);
		for(int i=0; i<menuItems.size(); i++){
			System.out.printf("%d ", i+1);
			System.out.println(menuItems.get(i).getTitle());
		}
		
		while(choice<=0 || choice>menuItems.size()){
			System.out.print("\nPlease pick a command to run: ");
			choice = scan.nextInt();
		}
		menuItems.get(choice-1).execute();
	}
}
