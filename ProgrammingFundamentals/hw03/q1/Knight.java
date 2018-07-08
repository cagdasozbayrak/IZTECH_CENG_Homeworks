public class Knight extends ChessPiece {

	public Knight(boolean isWhite) {
		super(isWhite);
	}

	@Override
	public void print() {
		if(getIsWhite())
			System.out.print("N ");
		else
			System.out.print("n ");
	}

}