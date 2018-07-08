import java.util.List;
import java.util.ArrayList;

public class SplitWord {
	public final String prefix;
	public final String suffix;
	
	public SplitWord(String word, int splitPos) {
		prefix = word.substring(0, splitPos);
		suffix = word.substring(splitPos, word.length());
	}
	
	@Override
	public String toString() {
		return prefix + "-" + suffix;
	}
	
	public static List<SplitWord> allSplits(String word) {
		List<SplitWord> splits = new ArrayList<SplitWord>();
		for (int i = 0; i <= word.length(); ++i)
			splits.add(new SplitWord(word, i));
		return splits;
	}
}