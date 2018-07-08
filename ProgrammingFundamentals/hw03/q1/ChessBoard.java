import java.util.ArrayList;
public class ChessBoard {

	private ArrayList<ArrayList<ChessPiece>> chessPieces;
	
	public ChessBoard(){
		chessPieces = new ArrayList<ArrayList<ChessPiece>>();
		
		for(int i=0; i<8; i++){
			boolean isWhite = (i==0 || i == 1); 
			ArrayList<ChessPiece> temp = new ArrayList<ChessPiece>();
			for(int j=0; j<8; j++){
				if(i>1 &&i<6)
					temp.add(new NoPiece(true));
				else if(i == 1 || i == 6)
					temp.add(new Pawn(isWhite));
				
				else if(j == 0 || j == 7)
						temp.add(j, new Rook(isWhite));
				
				else if(j == 1 || j == 6)
						temp.add(j, new Knight(isWhite));
				
				else if(j == 2 || j == 5)
						temp.add(j, new Bishop(isWhite));
				
				else if(j == 3)
						temp.add(j, new Queen(isWhite));
				
				else if(j == 4)
					temp.add(new King(isWhite));
			}
			chessPieces.add(i, temp);
		}
	}
	
	public void printChess(){
		for(int i=7; i>=0; i--){
			for(int j=0; j<8; j++)
				chessPieces.get(i).get(j).print();
			System.out.println();
		}
	}
}