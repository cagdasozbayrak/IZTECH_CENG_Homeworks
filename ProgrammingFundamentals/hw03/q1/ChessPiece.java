public abstract class ChessPiece {
	private boolean isWhite;

	ChessPiece(boolean isWhite){
		this.isWhite = isWhite;
	}
	
	public abstract void print();
	
	public boolean getIsWhite(){
		return isWhite;
	}
	
	public void setIsWhite(boolean isWhite){
		this.isWhite = isWhite;
	}
}