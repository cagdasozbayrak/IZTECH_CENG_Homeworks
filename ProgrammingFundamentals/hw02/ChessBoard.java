public class ChessBoard{
	private char[][] chessBoard;
		
	public ChessBoard(){
		chessBoard = new char[8][8];
		for(int i=0; i<8; i++){
			for(int j=0; j<8; j++){
				if(j == 0 || j == 7){
					if(i == 0)
						chessBoard[i][j] = 'R';
					else if(i == 7)
						chessBoard[i][j] = 'r';
				}
				
				else if(j == 1 || j == 6){
					if(i == 0)
						chessBoard[i][j] = 'N';
					else if(i == 7)
						chessBoard[i][j] = 'n';
				}
				
				else if(j == 2 || j == 5){
					if(i == 0)
						chessBoard[i][j] = 'B';
					else if(i == 7)
						chessBoard[i][j] = 'b';
				}
				
				else if(j == 3){
					if(i == 0)
						chessBoard[i][j] = 'Q';
					else if(i == 7)
						chessBoard[i][j] = 'q';
				}
				
				else if(j == 4){
					if(i == 0)
						chessBoard[i][j] = 'K';
					else if(i == 7)
						chessBoard[i][j] = 'k';
				}
				
				if(i == 1)
					chessBoard[i][j] = 'P';
				
				else if(i == 6)
					chessBoard[i][j] = 'p';
				else if(i>1 && i<6)
					chessBoard[i][j] = ' ';
				
			}
		}
	}
	
	public void printChess(){
		for(int i = 7; i>=0; i--){
			for(int j = 0; j<8; j++){
				System.out.printf("%c ", this.chessBoard[i][j]);
			}
				System.out.printf("\n");
		}
	}
}