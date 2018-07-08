import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.TreeMap;
import java.util.Comparator;
import java.util.HashMap;
import java.util.HashSet;
import java.util.ArrayList;
import java.util.Collections;

public class SpellChecker {
	private Map<String, Integer> mWords;
	private static final String ALPHABET = "abcdefghijklmnopqrstuvwxyz";
	public SpellChecker(Map<String, Integer> words) {
		if (words == null)
			mWords = new HashMap<String, Integer>();
		else
			mWords = words;
	}
	
	public static Set<String> edits1(String word) {
		Set<String> edits = new HashSet<String>();
		List<SplitWord> splits = SplitWord.allSplits(word);
		for (SplitWord split: splits) {
			String a = split.prefix;
			String b = split.suffix;
			int lb = b.length();
			if (lb > 0) {
				edits.add(a + b.substring(1)); // delete
				for (int i = 0; i < ALPHABET.length(); ++i)
					edits.add(a + ALPHABET.charAt(i) + b.substring(1)); // replace
			}
			if (lb > 1)
				edits.add(a + b.charAt(1) + b.charAt(0) + b.substring(2)); // transpose
			for (int i = 0; i < ALPHABET.length(); ++i)
				edits.add(a + ALPHABET.charAt(i) + b); // insert
		}
		return edits;
	}
	
	public Set<String> edits2(String word){
		Set<String> edits = new HashSet<String>();
		for(String s1: edits1(word))
			for(String s2: edits1(s1))
				if(mWords.containsKey(s2))
					edits.add(s2);
		return edits;
	}

	List<String> check(String word) {
		Map<String, Integer> alternatives = new TreeMap<String, Integer>();
		List<String> sortedKeys = new ArrayList<String>();
		word.toLowerCase();
		
		Comparator<Map.Entry<String, Integer>> byMapValues = new Comparator<Map.Entry<String, Integer>>(){
			@Override
			public int compare(Map.Entry<String, Integer> left, Map.Entry<String, Integer> right){
				return right.getValue().compareTo(left.getValue());
			}
		};
		
		if(mWords.containsKey(word)){
			alternatives.put(word, mWords.get(word));
			sortedKeys.add(word);
			return sortedKeys;
		}
			
		Set<String> edits = edits1(word);
		for (String w: edits)
			if(mWords.containsKey(w)){
				Integer counter = mWords.get(w);
				alternatives.put(w, counter);
			}
		
		if(alternatives.isEmpty()){
			Set<String> edits2 = edits2(word);
			for(String w: edits2)
				if(mWords.containsKey(w)){
					Integer counter = mWords.get(w);
					alternatives.put(w, counter);
				}
		}
		
	    List<Map.Entry<String, Integer>> sorted = new ArrayList<Map.Entry<String, Integer>>();
	    sorted.addAll(alternatives.entrySet());
	    Collections.sort(sorted, byMapValues);
		
		for(Map.Entry<String, Integer> entry: sorted)
			sortedKeys.add(entry.getKey());
		
		return sortedKeys;
	}

}