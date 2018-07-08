import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class WordSet {
	private final Map<String, Integer> mWords = new HashMap<String, Integer>();
	
	public WordSet(String filename) throws IOException {
		super();
		loadWordFile(filename);
	}
	
	public Map<String, Integer> getWords() { return mWords; }
	
	public void loadWordFile(String filename) throws IOException {
		BufferedReader reader = new BufferedReader(new FileReader(filename));
		mWords.clear();
		String line = reader.readLine();
		while (line != null) {
			Integer count;
			String[] ws = line.split("\\W+");
			for (String w: ws){
				count = mWords.get(w.toLowerCase());
				if(count == null)
					count = 0;
				mWords.put(w.toLowerCase(), ++count);
			}
			line = reader.readLine();
		}
		reader.close();
	}
}