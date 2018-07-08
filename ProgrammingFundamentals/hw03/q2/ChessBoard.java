import java.util.ArrayList;
public class ChessBoard {

	private static final String SVG_XML_HEADER = "<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">";
	private static final String SVG_TAG_START = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"360\" height=\"360\">\"";
	private static final String SVG_TAG_END = "</svg>";
	private static final String SVG_MOVE = "<svg x=\"%d\" y=\"%d\">";
	
	private ArrayList<ArrayList<ChessPiece>> chessPieces;
	
	public ChessBoard(){
		chessPieces = new ArrayList<ArrayList<ChessPiece>>();
		
		for(int i=0; i<8; i++){
			boolean isWhite = (i==0 || i == 1); //if the piece is in first or second row then it is white.
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
		System.out.println(SVG_XML_HEADER);
		System.out.println(SVG_TAG_START);
		for(int i=0; i<8; i++){
			for(int j=0; j<8; j++){
				System.out.printf(SVG_MOVE, 45*(7-j),45*(7-i));
				chessPieces.get(i).get(j).print();
				System.out.println(SVG_TAG_END);
			}
			System.out.println();
		}
		System.out.println(SVG_TAG_END);
	}
}
