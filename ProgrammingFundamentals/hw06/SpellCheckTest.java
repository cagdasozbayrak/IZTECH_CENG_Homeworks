import java.io.IOException;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

public class SpellCheckTest {
	public static final String WORDS_FILE = "data/big.txt";
	
	public static void main(String[] args) throws IOException {
		WordSet wordSet = new WordSet(WORDS_FILE);
		Map<String, Integer> words = wordSet.getWords();
		SpellChecker checker = new SpellChecker(words);
		
		List<SplitWord> ws = SplitWord.allSplits("abcd");
		for (SplitWord w:ws)
			System.out.println(w);
		
		System.out.println(SpellChecker.edits1("ab"));
		
		String toCheck = "ling";
		System.out.println("Checking \"" + toCheck + "\": " + checker.check(toCheck));
		
		
		int n = Math.min(words.size(), 10);
		Iterator<String> it = words.keySet().iterator();
		for (int i = 0; i < n; ++i)
			System.out.println(it.next());	}
}