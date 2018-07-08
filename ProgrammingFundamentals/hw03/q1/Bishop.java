public class Bishop extends ChessPiece {

	public Bishop(boolean isWhite) {
		super(isWhite);
	}

	@Override
	public void print() {
		if(getIsWhite())
			System.out.print("B ");
		else
			System.out.print("b ");
	}

}