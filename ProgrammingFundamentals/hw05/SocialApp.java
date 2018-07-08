import java.util.ArrayList;
import java.util.Scanner;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.EOFException;

public class SocialApp {
	private ArrayList<User> users = new ArrayList<User>();
	private boolean firstRun = true;
	
	public void run() {
		Menu menu = new Menu();
		
		menu.addItem(new MenuItem("Add user", new MenuCommand(){
			Scanner scan = new Scanner(System.in);
			String name;
			
			@Override
			public void run() {
				System.out.print("Please enter your name: ");
				name = scan.nextLine();
				User u = new User(name);
				users.add(u);
			}
		}));
		
		menu.addItem(new MenuItem("List users", new MenuCommand(){
			@Override
			public void run() {
				printUsers();
			}
		}));
		
		menu.addItem(new MenuItem("Post message", new MenuCommand(){
			String message;
			String name;
			Scanner scan = new Scanner(System.in);
			@Override
			public void run() {
				while(true){
					System.out.print("Enter your user name: ");
					name = scan.nextLine();
					User u = new User(name);
					if(users.contains(u)){
						int i = users.indexOf(u);
						System.out.print("Enter the message you want to post: ");
						message = scan.nextLine();
						users.get(i).postMessage(message);
						break;
					}
				}
			}
		}));
		
		menu.addItem(new MenuItem("Message list", new MenuCommand(){
			String name;
			Scanner scan = new Scanner(System.in);
			@Override
			public void run() {
				while(true){
					System.out.print("Enter the name of the user you want to see his/her posts: ");
					name = scan.nextLine();
					User u = new User(name);
					if(users.contains(u)){
						int i = users.indexOf(u);
						System.out.println("Posts of " + name + ":");
						for(String message: users.get(i).getMessages())
							System.out.println(message);
						break;
					}
				}
			}
		}));
		
		menu.addItem(new MenuItem("Follow", new MenuCommand(){
			@Override
			public void run() {
				String name1;
				String name2;
				Scanner scan = new Scanner(System.in);
				while(true){
					System.out.print("Enter your user name: ");
					name1 = scan.nextLine();
					System.out.print("Enter the name of the user you want to follow: ");
					name2 = scan.nextLine();
					
					User u1 = new User(name1);
					User u2 = new User(name2);
					
					if(users.contains(u1) && users.contains(u2)){
						int i1 = users.indexOf(u1);
						int i2 = users.indexOf(u2);
						users.get(i1).follow(users.get(i2));
						users.get(i2).addFollower(users.get(i1));
						break;
					}
				}
			}
		}));
		
		menu.addItem(new MenuItem("Following list", new MenuCommand(){
			@Override
			public void run() {
				String name;
				Scanner scan = new Scanner(System.in);
				while(true){
					System.out.print("Enter the name of the user you want to see his/her following list: ");
					name = scan.nextLine();
					
					User u = new User(name);
					if(users.contains(u)){
						int i = users.indexOf(u);
						System.out.println(name + " is following: ");
						for(User user: users.get(i).getFollowing())
							System.out.println(user.getName());
						break;
					}
				}
			}
		}));
		
		menu.addItem(new MenuItem("Follower list", new MenuCommand(){
			@Override
			public void run() {
				String name;
				Scanner scan = new Scanner(System.in);
				while(true){
					System.out.print("Enter the name of the user you want to see his/her following list: ");
					name = scan.nextLine();
					
					User u = new User(name);
					
					if(users.contains(u)){
						int i = users.indexOf(u);
						System.out.println("Followers of " + name + " are: ");
						for(User user: users.get(i).getFollower())
							System.out.println(user.getName());
						break;
					}
				}
			}
		}));
		
		menu.addItem(new MenuItem("Load", new MenuCommand(){
			@Override
			public void run() {
				try{
					FileInputStream input = new FileInputStream("social_app.bin");
					ObjectInputStream fin = new ObjectInputStream(input);
					users = new ArrayList<User>();
					User loadUser;
					while((loadUser = (User) fin.readObject()) != null){
						users.add(loadUser);
						}
				input.close();
				} catch(EOFException e){
					return;
				} catch(ClassNotFoundException ex){
					ex.printStackTrace();
				} catch(IOException ex){
					ex.printStackTrace();
				}
			}
		}));
		
		menu.addItem(new MenuItem("Save", new MenuCommand(){
			@Override
			public void run() {
				try{
					ObjectOutputStream fout = new ObjectOutputStream(new FileOutputStream("social_app.bin"));
					for(User user: users)
						fout.writeObject(user);
					fout.flush();
					fout.close();
				} catch(IOException e){
					e.printStackTrace();
					return;
				}
			}
		}));
		
		menu.addItem(new MenuItem("Quit", new MenuCommand(){
			@Override
			public void run() {
				System.exit(0);
			}
		}));
		
		while(true){
			if(!firstRun)
				System.out.println();
			menu.display();
			firstRun = false;
		}
	}
	
	public void printUsers() {
		for (User u:users)
			System.out.println(u.toString());
	}

}