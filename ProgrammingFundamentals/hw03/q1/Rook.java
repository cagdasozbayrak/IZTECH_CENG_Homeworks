public class Rook extends ChessPiece {

	public Rook(boolean isWhite) {
		super(isWhite);
	}

	@Override
	public void print() {
		if(getIsWhite())
			System.out.print("R ");
		else
			System.out.print("r ");
	}

}