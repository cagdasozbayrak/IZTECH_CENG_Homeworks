import java.io.Serializable;
import java.util.ArrayList;

public class User implements Serializable{
	private static final long serialVersionUID = -7253205119913363329L;
	private String name;
	private ArrayList<String> posts = new ArrayList<String>();
	private ArrayList<User> following = new ArrayList<User>();
	private ArrayList<User> followers = new ArrayList<User>();
	
	public User(String name) {
		this.name = name;
	}
	
	public String getName() {
		return name;
	}
	
	public void postMessage(String message) {
		posts.add(message);
	}
	
	public void follow(User u) {
		following.add(u);
	}
	
	public void addFollower(User u){
		followers.add(u);
	}
	
	public ArrayList<String> getMessages(){
		return posts;
	}
	
	public ArrayList<User> getFollowing(){
		return following;
	}
	
	public ArrayList<User> getFollower(){
		return followers;
	}
	
	@Override
	public String toString() {
		String s = name + " has (" + posts.size() + ") posts.";
		return s;
	}
	
	@Override
	public boolean equals(Object o){
		return this.name.equals(((User) o).name);
	}
}