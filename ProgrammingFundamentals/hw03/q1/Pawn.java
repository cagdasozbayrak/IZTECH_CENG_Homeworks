public class Pawn extends ChessPiece {

	public Pawn(boolean isWhite) {
		super(isWhite);
	}

	@Override
	public void print() {
		if(getIsWhite())
			System.out.print("P ");
		else
			System.out.print("p ");
	}

}