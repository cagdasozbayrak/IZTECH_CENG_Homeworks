import java.util.ArrayList;

public class BookTest {
	public static void main(String args[]){
		ArrayList<Book> bookList = new ArrayList<Book>();
		
		bookList.add(new Book("The Lord Of The Rings: The Fellowship Of The Ring", "9789753421638"));
		bookList.get(0).addAuthor("J.R.R. Tolkien");
		
		bookList.add(new Book("Artificial Intelligence: A Modern Approach", "9780137903955"));
		bookList.get(1).addAuthor("Stuart J. Russell");
		bookList.get(1).addAuthor("Peter Norvig");
		
		bookList.add(new Book("The Lord Of The Rings: The Two Towers", "9789753421812"));
		bookList.get(2).addAuthor("J.R.R. Tolkien");
		
		printBookList(bookList);
		
		bookList.get(1).borrow(30, 12, 2015);
		
		printBookList(bookList);
	}
	
	public static void printBookList(ArrayList<Book> books){
		for(Book book: books)
			book.printInformation();
	}
}
