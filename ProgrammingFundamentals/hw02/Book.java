import java.util.ArrayList;

public class Book {
	private String title;
	private ArrayList<String> authorList;
	private String catalogIdentifier;
	private boolean borrowed;
	private int[] returnDate = new int[3];
	
	public Book(String title, String identifier){
		this.title = title;
		catalogIdentifier = identifier;
		authorList = new ArrayList<String>();
		borrowed = false;
	}
	
	public void printInformation(){
		System.out.println("Title: " + title);
		
		System.out.println("Author(s): ");
		for(String author : authorList)
			System.out.println(author);
		
		System.out.println("Catalog Identifier: " + catalogIdentifier);
		
		if(borrowed)
			System.out.println("Return Date:" + returnDate[0] + "/" + returnDate[1] + "/" + returnDate[2]);
		
		System.out.println();
	}
	
	public void addAuthor(String authorName){
		authorList.add(authorName);
	}
	
	public void borrow(int day, int month, int year){
		returnDate[0] = day;
		returnDate[1] = month;
		returnDate[2] = year;
		
		borrowed = true;
	}
	
	public void returnBack(){
		borrowed = false;
		returnDate = new int[3]; //to empty the returnDate array since the book is returned back.
	}
}