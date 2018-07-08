public class Queen extends ChessPiece {

	public Queen(boolean isWhite) {
		super(isWhite);
	}

	@Override
	public void print() {
		if(getIsWhite())
			System.out.print("Q ");
		else
			System.out.print("q ");
	}

}