public class King extends ChessPiece {

	public King(boolean isWhite) {
		super(isWhite);
	}

	@Override
	public void print() {
		if(getIsWhite())
			System.out.print("K ");
		else
			System.out.print("k ");
	}

}