import java.util.Scanner;

public class MenuTest {
	public static void main(String args[]){
		
		Scanner scanner = new Scanner(System.in);
		Menu menu = new Menu();
		
		menu.addItem(new MenuItem("Add numbers", new Command(){
			@Override
			public void run(){
				double d0, d1;
				System.out.print("Enter two numbers to sum: ");
				d0 = scanner.nextDouble();
				d1 = scanner.nextDouble();
				System.out.println("The result is " + (d0+d1));
				}
		}));
		
		menu.addItem(new MenuItem("Multiply numbers", new Command(){
			@Override
			public void run() {
				double d0, d1;
				System.out.print("Enter two numbers to multiply: ");
				d0 = scanner.nextDouble();
				d1 = scanner.nextDouble();
				System.out.println("The result is " + (d0*d1));
			}
	
		}));
		
		menu.addItem(new MenuItem("Quit", new Command(){
			@Override
			public void run() {
				System.exit(0);
			}
		}));
	
		while(true)
			menu.display();
	}
}
