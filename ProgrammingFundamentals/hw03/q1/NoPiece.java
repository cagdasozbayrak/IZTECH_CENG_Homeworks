public class NoPiece extends ChessPiece {

	public NoPiece(boolean isWhite) {
		super(isWhite);
	}

	@Override
	public void print() {
		System.out.print("  ");
	}

}