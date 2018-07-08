public class NoPiece extends ChessPiece {

	public NoPiece(boolean isWhite) {
		super(isWhite);
	}

	@Override
	public void print() {
		System.out.println("<rect x=\"0\" y=\"0\" width=\"45\" height=\"45\" style=\"fill:#d18b47; stroke:#000000;\" />");
	}

}